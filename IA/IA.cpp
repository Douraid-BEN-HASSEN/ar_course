#include "IA.h"

IA::IA(QObject *parent): QObject{parent}
{
    qDebug() << "Ia::Ia()";
    this->currentCheckpointId = 0 ;

    //Get constant from the properties
    this->obstacleWidth = Properties::getInstance()->getRectangleWidth() ;
    this->obstacleHeight = Properties::getInstance()->getRectangleHeight() ;
    this->obstacleRadius = Properties::getInstance()->getCircleRadius();
}

IA::IA(Register *r, int speed, int offset ,   QObject *parent): QObject{parent}
{
    qDebug() << "IA::IA()" ;
    this->_register = r;
    this->_control = new Control(r->getUuid());
    this->speedSelected = speed ;
    this->offsetSelected = offset;
    QTimer::singleShot(1000, this, &IA::initIA);
}

void IA::setRegister(Register *reg) {
    qDebug() << "IA::setRegister()" ;
    this->_register = reg;
}

void IA::updateLabel()
{

}

Player* IA::getActivePlayer() {
    return GameMode::getInstance()->_players->value(this->_register->getUuid());

}

float normalizeAngleR(float angle) {
    while (angle > 0) {
        angle -= 2 * M_PI;
    }

    while (angle < -M_PI) {
        angle += 2 * M_PI;
    }
}

float IA::normalizeAngleD(float angle) {
    if (angle > 180) {
        angle = angle-360;
    }

    return angle;
}

void IA::initIA()
{
    qDebug() << "Ia::initIA()";
    this->determinePath();
}

void IA::mooveToCheckpoint()
{
    //Launch this every second
    QTimer::singleShot(1000 , this , &IA::mooveToCheckpoint);


    //While the run is not terminate
    while (this->currentCheckpointId < this->path.size() ){

        //Get the current checkpoint
        Checkpoint *target = path.at(this->currentCheckpointId).second;
        emit this->changeTarget(target->getPosition());

        //If no checkpoint, return
        if (target == nullptr)
            return;

        //Get the player
        this->player = this->getActivePlayer() ;

        //Draw the line to go the checkpiint
        QLineF WorldDirection = QLineF(this->player->getPosition(), target->getPosition());
        float playerAngle = qRadiansToDegrees(player->getAngle());
        float relativeDirection = WorldDirection.angle() - playerAngle;

        //Send order to the MQTT service
        _control->setAngle(qDegreesToRadians(normalizeAngleD(relativeDirection)));
        _control->setPower(this->speedSelected);
        _control->publish();


        QEventLoop loop;
        QTimer::singleShot(10, &loop, &QEventLoop::quit);
        loop.exec();

        //If checkpoint atteigned
        if (player->getX() > ( target->getX() -  Properties::getInstance()->getCheckpointRadius())
                && player->getX() < ( target->getX() +  Properties::getInstance()->getCheckpointRadius())
                && player->getY() > ( target->getY() -  Properties::getInstance()->getCheckpointRadius())
                && player->getY() < (target->getY() +  Properties::getInstance()->getCheckpointRadius())
                ) {
            qDebug() << "CHECKPOINT ATTEIGNED ";
            this->currentCheckpointId ++ ;
        }
    }

    //Ending game , make another loop
    this->currentCheckpointId = 0 ;
}

void IA::determinePath()
{
    //Update the constants
    this->obstacleWidth = Properties::getInstance()->getRectangleWidth() ;
    this->obstacleHeight = Properties::getInstance()->getRectangleHeight() ;
    this->obstacleRadius = Properties::getInstance()->getCircleRadius();

    //Get the checkpoint and the obstacles
    QMap<int, Checkpoint*> *checkpoints = Map::getInstance()->getCheckpoints();
    QMap<int, Obstacle*> *obstacles = Map::getInstance()->getObstacles() ;

    int lastChoice = -1;
    Checkpoint *currentChoice = new Checkpoint  ;

    //Add a the end the first checkpoint to make a lloop
    checkpoints->insert(100 , checkpoints->first());

    //Initialise an empty path
    QList<QPair<QString , Checkpoint*>> path;

    //If an obstacle is encounter, add one to the counter because there is another checkpoint
    int obstacleCheckpointLenght = 0 ;

    //Iterate the checkpoints
    //for(int i = 0 ; i < checkpoints->size() + 100 ; i ++){
    for (int i = 0 ; i < checkpoints->size() + obstacleCheckpointLenght + 1   ; i++) {

        /* Get the next checkpoint or get the current checkpoint if the previous checkpoint
        was a checkpoint created to avoid an obstacle */
        int bestChoice = -1;
        if (i == checkpoints->size() + obstacleCheckpointLenght)
            //Reloop on the first checkpoint if the turn is finished
            currentChoice = path.at(0).second;
        else {
            if (takeNextCheckpoint == true) {
                //Take the next checkpoint
                for (Checkpoint *checkpoint : checkpoints->values()){
                    if (checkpoint->getId() > lastChoice && (bestChoice == -1 || checkpoint->getId() < bestChoice )) {
                        bestChoice = checkpoint->getId();
                        currentChoice = checkpoint ;
                    }
                }
            } else
                //Rest in the last checkpoint
                bestChoice = lastChoice ;
            lastChoice = bestChoice ;
        }

        //Get the current checkpoint
        QPoint currentCheckpoint = path.length() == 0 ? QPoint(0,0) : path.at(path.length()-1).second->getPosition();
        //Get the trajectory
        QLineF trajectory = QLineF(currentCheckpoint, currentChoice->getPosition());
        //Init a collision point to calculate if there is a collision with an obstacle
        QPointF *collisionPoint = new QPointF(-1,-1);
        //Line of a obstacle
        QLineF obstacleLineWidth ;

        //Is there a obstacle ?
        bool isObstacle = false ;

        //Iterate the obstacle list to see if there is an obstacle
        for (Obstacle *obstacle : obstacles->values()){

            //Init value of the point on collisiton
            collisionPoint->setX(-1) ;
            collisionPoint->setY(-1);

            //Determine is the obstacle is a circle of a rectangle
            if (obstacle->getId() % 2 == 0) {

                obstacleLineWidth.setP1(QPointF(obstacle->getX() - obstacleRadius - ( obstacle->getX() - obstacleRadius - 50 < 0 ? 0 : 50 ) , obstacle->getY()));
                obstacleLineWidth.setP2(QPointF(obstacle->getX() + obstacleRadius + ( obstacle->getX() + obstacleRadius + 50 > 1000 ? 0 : 50 ), obstacle->getY() ));
            } else {
                obstacleLineWidth.setP1(QPointF(obstacle->getX() - (obstacleWidth/2) - ( obstacle->getX() - ( obstacleWidth / 2 ) -  50 < 0 ? 0 : 50) , obstacle->getY()  ));
                obstacleLineWidth.setP2(QPointF(obstacle->getX() - (obstacleWidth/2) + ( obstacle->getX() + ( obstacleWidth / 2 ) +  50 > 1000 ? 0 : 50), obstacle->getY()));
            }

            //Determine if is a collision between the trajectory and a obstacle
            trajectory.intersects(obstacleLineWidth , collisionPoint) ;

            //If collision
            if (collisionPoint->x() > -1 &&
                    collisionPoint->y() > -1 &&
                    collisionPoint->x() > obstacleLineWidth.x1() &&
                    collisionPoint->x() < obstacleLineWidth.x2() &&
                    (
                        (currentCheckpoint.y() >= collisionPoint->y() && collisionPoint->y() >= currentChoice->getY())
                        ||
                        (currentCheckpoint.y() <= collisionPoint->y() && collisionPoint->y() <= currentChoice->getY())
                        )
                    &&
                    (
                        (currentCheckpoint.x() >= collisionPoint->x() && collisionPoint->x() >= currentChoice->getX())
                        ||
                        (currentCheckpoint.x() <= collisionPoint->x() && collisionPoint->x() <= currentChoice->getX())
                        )
                    )
            {

                isObstacle = true ;

                //New checkpoint to avoid the obstacle
                Checkpoint *newCheck  = new Checkpoint ;

                //Calculate coordinates of the new checkpoint according the position of obstacle
                int offsetX = 0 ;
                int offsetY = 0 ;

                //Calculate the offset
                //Top
                if (currentCheckpoint.y() < obstacle->getY()) {
                    //Top Left
                    if (currentCheckpoint.x() > obstacle->getX()) {
                        offsetX = 0 ;
                        offsetY = this->offsetSelected ;
                    } else { //Top Right
                        offsetX = 0 ;
                        offsetY = -this->offsetSelected ;
                    }
                }

                //Bottom
                else if (currentCheckpoint.y() > obstacle->getY()) {
                    //Bottom left
                    if (currentCheckpoint.x() > obstacle->getX()) {
                        offsetX = -this->offsetSelected ;
                        offsetY = 0;
                    } else { //Top Right
                        offsetX = this->offsetSelected ;
                        offsetY = 0;
                    }
                }

                //Left
                if (currentCheckpoint.x() < obstacle->getX()) {
                    //Left top
                    if (currentCheckpoint.y() < obstacle->getY()) {
                        offsetX =0 ;
                        offsetY = -this->offsetSelected ;
                    } else { //Left bottom
                        offsetX = 0 ;
                        offsetY = +this->offsetSelected ;
                    }
                }

                //Right
                if (currentCheckpoint.x() > obstacle->getX()) {
                    //Right top
                    if (currentCheckpoint.x() < obstacle->getX()) {
                        offsetX = 0 ;
                        offsetY = this->offsetSelected ;
                    } else { //Right bottom
                        offsetX = 0 ;
                        offsetY = this->offsetSelected ;
                    }
                }

                newCheck->setX(obstacle->getId() % 2 == 0 ? collisionPoint->x() +  obstacleRadius + offsetX : collisionPoint->x() + obstacleWidth/2  + offsetX );
                newCheck->setY(obstacle->getId() % 2 == 0 ? collisionPoint->y() +  obstacleRadius + offsetY : collisionPoint->y() +  obstacleWidth/2  + offsetY );

                //Add the new checkpoint
                QPair<QString, Checkpoint*> p("obstacle" , newCheck);
                path.append(p);
                obstacleCheckpointLenght += 1  ;
                takeNextCheckpoint = false ;
            }
        }



        if (isObstacle == false  ) {
            //If not obstacle , add to the path the current checkpoint and go to the new checkpoint
            QPair<QString, Checkpoint*> *p = new QPair<QString, Checkpoint*>("obstacle" , currentChoice);
            path.append(*p);
            takeNextCheckpoint = true ;
        }
    }

    //Save the path
    this->path = path ;

    //Print the path
    for (int i = 0 ; i < this->path.size() ; i++ )
        qDebug() << this->path.at(i).second->getX() << this->path.at(i).second->getY() ;

    //Launch the function to do the path and emit signal to draw the path
    emit this->determinePathDone(this->path);
}


