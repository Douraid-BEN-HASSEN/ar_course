#include "IA.h"

IA::IA(QObject *parent): QObject{parent}
{
    qDebug() << "Ia::Ia()";
    this->currentCheckpointId = 0 ;
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

    while (this->currentCheckpointId < this->path.size()){

        Checkpoint *target = path.at(this->currentCheckpointId);
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
        _control->setPower(15);
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
    int obstacleWidth = Properties::getInstance()->getRectangleWidth() ;
    int obstacleHeight = Properties::getInstance()->getRectangleHeight() ;
    int obstacleRadius = Properties::getInstance()->getCircleRadius();

    int lastChoice = -1;
    Checkpoint *currentChoice = new Checkpoint  ;

    for (int i = 0 ; i < checkpoints->size() ; i++) {
        //qDebug() << "CHECKPOINT " << i ;
        int bestChoice = -1;
        for (Checkpoint *checkpoint : checkpoints->values()){
            if (checkpoint->getId() > lastChoice && (bestChoice == -1 || checkpoint->getId() < bestChoice )) {
                bestChoice = checkpoint->getId();
                currentChoice = checkpoint ;
            }

        }
        lastChoice = bestChoice ;

        //Vérifier si il y a un obstacle entre l'ancien et le nouveau checkpoint

        QLineF trajectory = QLineF(path.length() == 0 ? QPoint(0,0) :  path.at(path.length()-1)->getPosition(), currentChoice->getPosition());
        qDebug() << "trajectory : " << trajectory ;
        QPointF *test = new QPointF(-1,-1);
        QLineF obstacleLine ;
        //qDebug() << "test : " << *test ;
        for (Obstacle *obstacle : obstacles->values()){
            test->setX(-1) ;
            test->setY(-1);
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
            trajectory.intersects(obstacleLine , test) ;
            qDebug() << "************" << test << obstacleLine ;
            if (test->x() > -1 && test->y() > -1 && (test->y() > -1 && test->y() > obstacleLine.y1() &&  test->y() < obstacleLine.y2()) ) {
                qDebug() << "OBSTACLE !!!!" ;
                Checkpoint *newCheck  = new Checkpoint ;
                newCheck->setX(test->x() +200) ;
                newCheck->setY(test->y());

                qDebug() << "add obstacle checkpoint" ;
                path.append(newCheck);
            }
        }

        qDebug() << "add checkpoint" ;
        path.append(currentChoice);

    }

    Player *player = getActivePlayer();
    if (player == nullptr)
        return;

    this->path = path ;

    qDebug() << "Nombre de checkpoints " << this->path.size() ;

    for (int i = 0 ; i < this->path.size() ; i++ ) {
        qDebug() << this->path.at(i)->getX() << this->path.at(i)->getY() ;
    }

    QTimer::singleShot(1000 , this , &IA::mooveToCheckpoint);
}


