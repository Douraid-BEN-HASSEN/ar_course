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

IA::IA(Register *r, int speed,  QObject *parent): QObject{parent}
{
    qDebug() << "IA::IA()" ;
    this->_register = r;
    this->_control = new Control(r->getUuid());
    this->speedSelected = speed ;
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
    //qDebug() << "IA::getActivePlayer()" ;
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
        //qDebug() << "TARGET : " << target->getId() << target->getPosition() ;
        qDebug() << this->currentCheckpointId ;
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
        if (  player->getX() > ( target->getX() -  Properties::getInstance()->getCheckpointRadius())
              && player->getX() < ( target->getX() +  Properties::getInstance()->getCheckpointRadius())
              && player->getY() > ( target->getY() -  Properties::getInstance()->getCheckpointRadius())
              && player->getY() < (target->getY() +  Properties::getInstance()->getCheckpointRadius())
              ) {
            qDebug() << "CHECKPOINT ATTEIGNED ";
            this->currentCheckpointId ++ ;
        }
    }

    //Ending game
    this->currentCheckpointId = 0 ;
    //_control->setPower(0);
    //_control->publish() ;
}

void IA::determinePath()
{
    //Update the constants
    this->obstacleWidth = Properties::getInstance()->getRectangleWidth() ;
    this->obstacleHeight = Properties::getInstance()->getRectangleHeight() ;
    this->obstacleRadius = Properties::getInstance()->getCircleRadius();

    //Get the checkpoint et the obstacles
    QMap<int, Checkpoint*> *checkpoints = Map::getInstance()->getCheckpoints();
    qDebug() << checkpoints->size() ;

    //qDebug() << checkpoints->size() ;
    QMap<int, Obstacle*> *obstacles = Map::getInstance()->getObstacles() ;

    //Initialise an empty path
    QList<QPair<QString , Checkpoint*>> path;

    int lastChoice = -1;
    int obstacleCheckpointLenght = 0 ;
    Checkpoint *currentChoice = new Checkpoint  ;

    //Iterate the checkpoints
    for (int i = 0 ; i < checkpoints->size() + obstacleCheckpointLenght   ; i++) {

        /* Get the next checkpoint or get the current checkpoint if the previous checkpoint
        was a checkpoint created to avoid an obstacle */
        int bestChoice = -1;
        if (takeNextCheckpoint == true) {
            for (Checkpoint *checkpoint : checkpoints->values()){
                if (checkpoint->getId() > lastChoice && (bestChoice == -1 || checkpoint->getId() < bestChoice )) {
                    bestChoice = checkpoint->getId();
                    currentChoice = checkpoint ;
                }
            }
        } else
            bestChoice = lastChoice ;
        lastChoice = bestChoice ;

        //Get the current checkpoint
        QPoint currentCheckpoint = path.length() == 0 ? QPoint(0,0) : path.at(path.length()-1).second->getPosition();
        bool isObstacle = false ;
        QLineF trajectory = QLineF(currentCheckpoint, currentChoice->getPosition());
        QPointF *collisionPoint = new QPointF(-1,-1);
        QLineF obstacleLine ;

        //Iterate the obstacle list to see if there is an obstacle
        for (Obstacle *obstacle : obstacles->values()){
            collisionPoint->setX(-1) ;
            collisionPoint->setY(-1);

            //Determine is the obstacle is a circle of a rectangle
            if (obstacle->getId() % 2 == 0) {
                obstacleLine.setP1(QPointF(obstacle->getX() - obstacleRadius - 50 , obstacle->getY()));
                obstacleLine.setP2(QPointF(obstacle->getX() + obstacleRadius + 50, obstacle->getY() ));
            } else {
                obstacleLine.setP1(QPointF(obstacle->getX() - (obstacleWidth/2) - 50 , obstacle->getY()  ));
                obstacleLine.setP2(QPointF(obstacle->getX() - (obstacleWidth/2) + 50, obstacle->getY()));
            }

            //Determine if is a collision between the trajectory and a obstacle
            trajectory.intersects(obstacleLine , collisionPoint) ;

            //If collision
            if (collisionPoint->x() > -1 &&
                    collisionPoint->y() > -1 &&
                    collisionPoint->x() > obstacleLine.x1() &&
                    collisionPoint->x() < obstacleLine.x2() &&
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
                int offset = 200 ;
                Checkpoint *newCheck  = new Checkpoint ;
                newCheck->setX(collisionPoint->x() + obstacle->getId() % 2 == 0 ? obstacleRadius + offset : obstacleWidth / 2 + offset  < 1000 ? collisionPoint->x()+obstacle->getId() % 2 == 0 ? collisionPoint->x() + obstacleRadius + offset : collisionPoint->x() + obstacleWidth / 2 + offset  : obstacle->getId() % 2 == 0 ? collisionPoint->x() - obstacleRadius + offset : collisionPoint->x() - obstacleWidth / 2 + offset  ) ;
                newCheck->setY(collisionPoint->y() + obstacle->getId() % 2 == 0 ? obstacleRadius + offset : obstacleWidth / 2 + offset  < 1000 ? collisionPoint->y()+obstacle->getId() % 2 == 0 ? collisionPoint->y() + obstacleRadius + offset : collisionPoint->y() + obstacleWidth / 2 + offset  : obstacle->getId() % 2 == 0 ? collisionPoint->y() - obstacleRadius + offset : collisionPoint->y() - obstacleWidth / 2 + offset  );

                //Create a new checkpoint
                QPair<QString, Checkpoint*> p("obstacle" , newCheck);
                path.append(p);
                obstacleCheckpointLenght += 1  ;
                takeNextCheckpoint = false ;
            }
        }

        if (isObstacle == false  ) {
            //If not obstacle , add to the path the checkpoint
            QPair<QString, Checkpoint*> p("obstacle" , currentChoice);
            path.append(p);
            takeNextCheckpoint = true ;
        }
    }

    Player *player = getActivePlayer();
    if (player == nullptr)
        return;

    //Save the path
    this->path = path ;

    //Print the path
    for (int i = 0 ; i < this->path.size() ; i++ )
        qDebug() << this->path.at(i).second->getX() << this->path.at(i).second->getY() ;

    //Launch the function to do the path
    QTimer::singleShot(1000 , this , &IA::mooveToCheckpoint);
}
