#include "IA.h"

IA::IA(QObject *parent): QObject{parent}
{
    qDebug() << "Ia::Ia()";
    this->currentCheckpointId = 0 ;
    this->obstacleWidth = Properties::getInstance()->getRectangleWidth() ;
    this->obstacleHeight = Properties::getInstance()->getRectangleHeight() ;
    this->obstacleRadius = Properties::getInstance()->getCircleRadius();
}

IA::IA(Register *r, QObject *parent): QObject{parent}
{
    qDebug() << "IA::IA()" ;

    this->_register = r;
    this->_control = new Control(r->getUuid());

    QTimer::singleShot(1000, this, &IA::initIA);
}


void IA::setRegister(Register *reg) {
    qDebug() << "IA::setRegister()" ;
    this->_register = reg;
}

Player* IA::getActivePlayer() {
    //qDebug() << "IA::getActivePlayer()" ;
    return GameMode::getInstance()->_players->value(this->_register->getUuid());

}

float normalizeAngleR(float angle) {
    //qDebug() << "IA::normalizeAngleR()" ;

    while (angle > 0) {
        angle -= 2 * M_PI;
    }

    while (angle < -M_PI) {
        angle += 2 * M_PI;
    }
}

float IA::normalizeAngleD(float angle) {
    //qDebug() << "IA::normalizeAngleD()" ;
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

    //qDebug() << "Ia::mooveToCheckpoint()" ;
    QTimer::singleShot(1000 , this , &IA::mooveToCheckpoint);



    //while (this->currentCheckpointId < this->path.size() ){

    while (this->currentCheckpointId < this->path2.size() ){
        //Checkpoint *target = path.at(this->currentCheckpointId);
        Checkpoint *target = path2.at(this->currentCheckpointId).second;
        if (target == nullptr) {
            qDebug() << "no checkpoint";
            return;
        }
        qDebug() << target->getPosition() ;
        this->player = this->getActivePlayer() ;
        QLineF WorldDirection = QLineF(this->player->getPosition(), target->getPosition());
        Map::getInstance()->addLine(&WorldDirection );
        float playerAngle = qRadiansToDegrees(player->getAngle());
        float relativeDirection = WorldDirection.angle() - playerAngle;
        _control->setAngle(qDegreesToRadians(normalizeAngleD(relativeDirection)));
        _control->setPower(10);
        _control->publish();

        QEventLoop loop;
        QTimer::singleShot(10, &loop, &QEventLoop::quit);
        loop.exec();

        if (  player->getX() > ( target->getX() -  Properties::getInstance()->getCheckpointRadius())
              && player->getX() < ( target->getX() +  Properties::getInstance()->getCheckpointRadius())
              && player->getY() > ( target->getY() -  Properties::getInstance()->getCheckpointRadius())
              && player->getY() < (target->getY() +  Properties::getInstance()->getCheckpointRadius())
              ) {
            qDebug() << "CHECKPOINT ATTEIGNED ";
            this->currentCheckpointId ++ ;
        }
    }

    //End game
    _control->setPower(0);
    _control->publish() ;
}

void IA::determinePath()
{
    QMap<int, Checkpoint*> *checkpoints = Map::getInstance()->getCheckpoints();
    QMap<int, Obstacle*> *obstacles = Map::getInstance()->getObstacles() ;
    QList<Checkpoint *> path ;
    QList<QPair<QString , Checkpoint*>> path2;

    int lastChoice = -1;

    Checkpoint *currentChoice = new Checkpoint  ;

    for (int i = 0 ; i < checkpoints->size() ; i++) {
        int bestChoice = -1;
        for (Checkpoint *checkpoint : checkpoints->values()){
            if (checkpoint->getId() > lastChoice && (bestChoice == -1 || checkpoint->getId() < bestChoice )) {
                bestChoice = checkpoint->getId();
                currentChoice = checkpoint ;
            }
        }

        lastChoice = bestChoice ;

        //Vérifier si il y a un obstacle entre l'ancien et le nouveau checkpoint
        bool isObstacle = false ;
        QLineF trajectory = QLineF(path.length() == 0 ? QPoint(0,0) :  path.at(path.length()-1)->getPosition(), currentChoice->getPosition());
        //qDebug() << "trajectory : " << trajectory ;
        QPointF *collisionPoint = new QPointF(-1,-1);
        QLineF obstacleLine ;
        for (Obstacle *obstacle : obstacles->values()){
            collisionPoint->setX(-1) ;
            collisionPoint->setY(-1);
            //qDebug() << " test : " << *test ;

            if (obstacle->getId() % 2 == 0) {
                qDebug() << "ROND" ;
                //Obstacle rond
                obstacleLine.setP1(QPointF(obstacle->getX() - obstacleRadius - 20 , obstacle->getY() - obstacleRadius +20));
                obstacleLine.setP2(QPointF(obstacle->getX() + obstacleRadius - 20, obstacle->getY() + obstacleRadius + 20));

            } else {
                qDebug() << "CARRÉ" ;
                //Obstacle carré
                obstacleLine.setP1(QPointF(obstacle->getX() - (obstacleWidth/2) - 20 , obstacle->getY() - (obstacleWidth/2) + 20 ));
                obstacleLine.setP2(QPointF(obstacle->getX() - (obstacleWidth/2) - 20, obstacle->getY() + (obstacleWidth/2) + 20));
            }

            qDebug() << "trajectory , obstacleLine" << trajectory << obstacleLine ;
            trajectory.intersects(obstacleLine , collisionPoint) ;
            qDebug() << "************" << collisionPoint << obstacleLine ;
            if (collisionPoint->x() > -1 && collisionPoint->y() > -1 && (collisionPoint->y() > -1 && collisionPoint->y() > obstacleLine.y1() &&  collisionPoint->y() < obstacleLine.y2()) ) {
                qDebug() << "OBSTACLE !!!!" ;
                isObstacle = true ;
                Checkpoint *newCheck  = new Checkpoint ;
                newCheck->setX(collisionPoint->x() + 100 < 1000 ? collisionPoint->x()+100 : collisionPoint->x() -100 ) ;
                newCheck->setY(collisionPoint->y() + 100 < 1000 ? collisionPoint->y()+100 : collisionPoint->y() -100 );

                qDebug() << "add obstacle checkpoint" ;
                path.append(newCheck);
                QPair<QString, Checkpoint*> p("obstacle" , newCheck);
                path2.append(p);

            }
        }

        qDebug() << "add checkpoint" ;
        if (isObstacle == false) {
            QPair<QString, Checkpoint*> p("obstacle" , currentChoice);
            path2.append(p);
            path.append(currentChoice);
        }

    }

    Player *player = getActivePlayer();
    if (player == nullptr)
        return;

    this->path = path ;
    this->path2 = path2 ;

    qDebug() << "Nombre de checkpoints " << this->path.size() ;

    for (int i = 0 ; i < this->path.size() ; i++ ) {
        qDebug() << this->path.at(i)->getX() << this->path.at(i)->getY() ;
    }

    emit this->determinePathDone(this->path2);
    QTimer::singleShot(1000 , this , &IA::mooveToCheckpoint);
}



