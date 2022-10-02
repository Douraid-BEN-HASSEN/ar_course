#include "IA.h"

IA::IA(QObject *parent): QObject{parent}
{}

IA::IA(Register *r, QObject *parent): QObject{parent}
{
    QTimer::singleShot(1000, this, &IA::brain);

    this->_register = r;
    this->_control = new Control(r->getUuid());
}


void IA::setRegister(Register *reg) {
    this->_register = reg;
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

float normalizeAngleD(float angle) {
    if (angle > 180) {
        angle = angle-360;
    }

    return angle;
}

void IA::brain()
{

    QTimer::singleShot(1000, this, &IA::brain);
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
    float playerAngle = qRadiansToDegrees(player->getAngle());

    qDebug() << QString("Target : %1, Player Angle : %2").arg(QString::number(target->getId()), QString::number(playerAngle));
    qDebug() << QString("WorldDirection : %1").arg(QString::number(WorldDirection.angle()));


    float relativeDirection = WorldDirection.angle() - playerAngle;
    qDebug() << QString("relative Direction : %1").arg(QString::number(relativeDirection));
    qDebug() << QString("Normalized relative Direction : %1").arg(QString::number(normalizeAngleD(relativeDirection)));

    _control->setAngle(qDegreesToRadians(normalizeAngleD(relativeDirection)));
    _control->setPower(15);

    _control->publish();


}

Checkpoint* IA::getNextCheckpoint(int lastCheckpointId)
{
    QMap<int, Checkpoint*> *checkpoints = Map::getInstance()->getCheckpoints();

    int bestCheckpointId = -1;

    for (Checkpoint *checkpoint: checkpoints->values()) {

        if (checkpoint->getId() > lastCheckpointId && (checkpoint->getId() < bestCheckpointId || bestCheckpointId == -1)) {
            bestCheckpointId = checkpoint->getId();
        }
    }

    if (bestCheckpointId == -1)
        return nullptr;

    return checkpoints->value(bestCheckpointId);
}
