#include "IA.h"

IA::IA(QObject *parent): QObject{parent}
{
    qDebug() << "Ia::Ia()";
    this->currentCheckpointId = 0 ;
    //this->path =b new QList<Checkpoint*> ;
}

IA::IA(Register *r, QObject *parent): QObject{parent}
{
    qDebug() << "IA::IA()" ;
    //QTimer::singleShot(1000, this, &IA::initIA);

    this->_register = r;
    this->_control = new Control(r->getUuid());
    QTimer::singleShot(1000, this, &IA::initIA);

}


void IA::setRegister(Register *reg) {
    qDebug() << "IA::setRegister()" ;
    this->_register = reg;
}

Player* IA::getActivePlayer() {
    qDebug() << "IA::getActivePlayer()" ;
    return GameMode::getInstance()->_players->value(this->_register->getUuid());

}

float normalizeAngleR(float angle) {
    qDebug() << "IA::normalizeAngleR()" ;

    while (angle > 0) {
        angle -= 2 * M_PI;
    }

    while (angle < -M_PI) {
        angle += 2 * M_PI;
    }
}

float IA::normalizeAngleD(float angle) {
    qDebug() << "IA::normalizeAngleD()" ;
    if (angle > 180) {
        angle = angle-360;
    }

    return angle;
}


void IA::brain2() {
    qDebug() << "brain 2" ;
    QTimer::singleShot(1000 , this , &IA::brain2);

    QMap<int , Checkpoint*> *steps  ;

    if (this->_register == nullptr) {
        qDebug() << "not register" ;
        return ;
    }

    Player *player = getActivePlayer() ;

    if (player == nullptr) {
        qDebug() << "player == nullptr" ;
        return ;
    }

    //Get all checkpoints
    QMap<int, Checkpoint*> *checkpoints = Map::getInstance()->getCheckpoints();

    //Get all obstacles
    QMap<int, Obstacle*> *obstacles = Map::getInstance()->getObstacles() ;

    Checkpoint * tmpCheckpoint = new Checkpoint ;
    tmpCheckpoint = this->getNextCheckpoint(player->getLastCheckpoint());

    //Determiner si je ne detecte pas un obstacle
    //qDebug() << WorldDirection ;
    //qDebug() << WorldDirection.dx() ;

    bool isObstacle = false ;
    int limXMinus ;
    int limXPlus ;
    int limYMinus ;
    int limYPlus ;

    int obstacleRectangleWidth = Properties::getInstance()->getRectangleWidth() ;
    int obstacleRectangleHeight = Properties::getInstance()->getRectangleHeight();
    int obstacleCircleRadius  = Properties::getInstance()->getCircleRadius();
    for (Obstacle *obstacle: obstacles->values()) {
        //qDebug() << "id" << obstacle->getId() <<  "x : " <<  obstacle->getX() << " y : " << obstacle->getY() << " size : "   ;
        //obstacle->getId() % 2 == 0 ? qDebug() << " radius " << obstacleCircleRadius   : qDebug() << " width / height" << obstacleRectangleWidth << obstacleRectangleHeight ;
        limXMinus = player->getX()-200 ;
        limXPlus = player->getX() + 200 ;
        limYMinus =  player->getY() -200 ;
        limYPlus =  player->getY() +200;
        if ((limXMinus < obstacle->getX() && limYMinus > obstacle->getX() ) || (limYMinus < obstacle->getY() && limYPlus > obstacle->getY() ) ) {
            qDebug("OBSTACLE DETECTED !!!!");
            isObstacle = true ;
            tmpCheckpoint->setX(obstacle->getX() + obstacleCircleRadius < 1000 ? obstacle->getX() + obstacleCircleRadius + 100 : obstacle->getX() - obstacleCircleRadius - 100   ) ;
            tmpCheckpoint->setY(obstacle->getY());
        }
    }

    QLineF WorldDirection = QLineF(player->getPosition(), tmpCheckpoint->getPosition());
    float playerAngle = qRadiansToDegrees(player->getAngle());
    float relativeDirection = WorldDirection.angle() - playerAngle;

    qDebug() << "***" << tmpCheckpoint->getX() << tmpCheckpoint->getY() ;

    _control->setAngle(qDegreesToRadians(normalizeAngleD(relativeDirection)));
    _control->setPower(15);
    _control->publish();
}

void IA::initIA()
{

    this->determinerChemin();
    /*
    if (this->_register == nullptr)
        return;

    this->player = getActivePlayer();

    if (this->player == nullptr)
        return;

    QTimer::singleShot(1000, this, &IA::brain3);

   for (Checkpoint *checkpoint: Map::getInstance()->getCheckpoints()->values()) {
       qDebug() << checkpoint->getId() ;
       qDebug() << checkpoint->getX() << checkpoint->getY() ;
   }
   */
}

void IA::mooveToCheckpoint()
{
    qDebug() << "Ia::mooveToCheckpoint()" ;
    QTimer::singleShot(1000 , this , &IA::mooveToCheckpoint);

    if (this->path.size() != 0) {
        qDebug() <<  this->currentCheckpointId << this->path.size() ;
    }


    qDebug() << this->currentCheckpointId << this->path.size() ;
    while (this->currentCheckpointId < this->path.size()){
        //qDebug() << "turn while" ;

        Checkpoint *target = path.at(this->currentCheckpointId);
        //qDebug() << "target " << target ;


        if (target == nullptr) {
            qDebug() << "no checkpoint";
            return;
        }

        this->player = this->getActivePlayer() ;
        qDebug () << this->player->getPosition() << target->getPosition() ;
        QLineF WorldDirection = QLineF(this->player->getPosition(), target->getPosition());

        Map::getInstance()->addLine(&WorldDirection );
        float playerAngle = qRadiansToDegrees(player->getAngle());
        float relativeDirection = WorldDirection.angle() - playerAngle;


        //qDebug() << "SEND ORDER " ;
        _control->setAngle(qDegreesToRadians(normalizeAngleD(relativeDirection)));
        _control->setPower(10);
        _control->publish();

        QEventLoop loop;
        QTimer::singleShot(10, &loop, &QEventLoop::quit);
        loop.exec();

        qDebug() << "TEST" ;
        qDebug() << Properties::getInstance()->getCheckpointRadius();
        //if (player->getX() == target->getX() && player->getY() == target->getY()) {
        qDebug() << (player->getX() > ( target->getX() -  Properties::getInstance()->getCheckpointRadius() ))
                 << (player->getX() < (target->getX() +  Properties::getInstance()->getCheckpointRadius()) )
                 << (player->getY() > (target->getY() -  Properties::getInstance()->getCheckpointRadius()))
                 <<( player->getY() < (target->getY() +  Properties::getInstance()->getCheckpointRadius())) ;
        if (  player->getX() > ( target->getX() -  Properties::getInstance()->getCheckpointRadius())
              && player->getX() < ( target->getX() +  Properties::getInstance()->getCheckpointRadius())
              && player->getY() > ( target->getY() -  Properties::getInstance()->getCheckpointRadius())
              && player->getY() < (target->getY() +  Properties::getInstance()->getCheckpointRadius())
              ) {
            qDebug() << "CHECKPOINT ! " ;
            this->currentCheckpointId ++ ;
        }
    }
}

void IA::determinerChemin()
{
    QMap<int, Checkpoint*> *checkpoints = Map::getInstance()->getCheckpoints();
    QList<Checkpoint *> path ;

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

        //Vérifier si il y a un obstacle entre l'ancien et le nouveau checkpoitn


        path.append(currentChoice);
    }

    /*
    QList<Checkpoint*>::iterator i;
    for (i = path.begin(); i != path.end(); ++i)
        qDebug() <<  (*i)->getId() << (*i)->getX() << (*i)->getY() ;

    */

    //Faire bouger le truc
    int a = 0 ;
    Player *player = getActivePlayer();

    if (player == nullptr)
        return;


    qDebug() << path.size() ;
    this->path = path ;
    qDebug() << this->path.size() ;
    qDebug() << "end init" ;

    QTimer::singleShot(1000 , this , &IA::mooveToCheckpoint);

}


void IA::brain3()
{
    qDebug() << "Start brain " ;
    QTimer::singleShot(1000, this, &IA::brain);


    Checkpoint *target = getNextCheckpoint(player->getLastCheckpoint());

    if (target == nullptr) {
        qDebug() << "no checkpoint";
        return;
    }

    QLineF WorldDirection = QLineF(player->getPosition(), target->getPosition());
    Map::getInstance()->addLine(&WorldDirection );
    float playerAngle = qRadiansToDegrees(player->getAngle());

    //qDebug() << QString("Target : %1, Player Angle : %2").arg(QString::number(target->getId()), QString::number(playerAngle));
    //qDebug() << QString("WorldDirection : %1").arg(QString::number(WorldDirection.angle()));

    float relativeDirection = WorldDirection.angle() - playerAngle;
    //qDebug() << QString("relative Direction : %1").arg(QString::number(relativeDirection));
    //qDebug() << QString("Normalized relative Direction : %1").arg(QString::number(normalizeAngleD(relativeDirection)));

    //Essayer de detecter si il y a un obstacle sur la route

    _control->setAngle(qDegreesToRadians(normalizeAngleD(relativeDirection)));
    _control->setPower(25);
    _control->publish();
}



void IA::brain()
{
    qDebug() << "IA::brain()";
    QTimer::singleShot(1000, this, &IA::brain);

    //If not register
    if (this->_register == nullptr)
        return;

    Player *player = getActivePlayer();

    if (player == nullptr)
        return;

    Checkpoint *target = getNextCheckpoint(player->getLastCheckpoint());

    if (target == nullptr) {
        qDebug() << "no checkpoint";
        return;
    }

    QLineF WorldDirection = QLineF(player->getPosition(), target->getPosition());
    Map::getInstance()->addLine(&WorldDirection );
    float playerAngle = qRadiansToDegrees(player->getAngle());

    qDebug() << QString("Target : %1, Player Angle : %2").arg(QString::number(target->getId()), QString::number(playerAngle));
    qDebug() << QString("WorldDirection : %1").arg(QString::number(WorldDirection.angle()));

    float relativeDirection = WorldDirection.angle() - playerAngle;
    qDebug() << QString("relative Direction : %1").arg(QString::number(relativeDirection));
    qDebug() << QString("Normalized relative Direction : %1").arg(QString::number(normalizeAngleD(relativeDirection)));

    QMap<int, Obstacle*> *obstacles = Map::getInstance()->getObstacles();
    for (Obstacle *obstacle: obstacles->values()) {
        qDebug() << "x : " <<  obstacle->getX() << " y : " << obstacle->getY() ;
    }

    //Essayer de detecter si il y a un obstacle sur la route

    _control->setAngle(qDegreesToRadians(normalizeAngleD(relativeDirection)));
    _control->setPower(25);
    _control->publish();

}


Checkpoint* IA::getNextCheckpoint(int lastCheckpointId)
{
    qDebug() << "IA::getNextCheckpoint()" ;

    QMap<int, Checkpoint*> *checkpoints = Map::getInstance()->getCheckpoints();

    int bestCheckpointId = -1;

    for (Checkpoint *checkpoint: checkpoints->values()) {
        if (checkpoint->getId() > lastCheckpointId && (checkpoint->getId() < bestCheckpointId || bestCheckpointId == -1)) {
            bestCheckpointId = checkpoint->getId();
        }
    }

    qDebug() << "end game" ;
    //End game
    if (bestCheckpointId == -1)
        return nullptr;
    _control->setPower(0);
    _control->setAngle(0);
    _control->publish();


    return checkpoints->value(bestCheckpointId);
}

