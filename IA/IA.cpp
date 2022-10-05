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



void IA::initIA()
{
    qDebug() << "Ia::initIA()";
    this->determinePath();
}

void IA::mooveToCheckpoint()
{
    qDebug() << "Ia::mooveToCheckpoint()" ;
    QTimer::singleShot(1000 , this , &IA::mooveToCheckpoint);

    while (this->currentCheckpointId < this->path.size()){
        Checkpoint *target = path.at(this->currentCheckpointId);
        if (target == nullptr) {
            qDebug() << "no checkpoint";
            return;
        }
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
            this->currentCheckpointId ++ ;
        }
    }
}

void IA::determinePath()
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

    Player *player = getActivePlayer();
    if (player == nullptr)
        return;

    this->path = path ;
    QTimer::singleShot(1000 , this , &IA::mooveToCheckpoint);

}


