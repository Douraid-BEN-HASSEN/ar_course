#include "Engine.h"

Engine::Engine(QObject *parent): QObject{parent}
{
    this->_mqtt = MqttService::instance();
    this->_mqtt->subscribe("player/register");
    this->_mqtt->subscribe("player/control");

    connect(this->_mqtt,
                SIGNAL(message(QJsonObject,QString)),
                this,
                SLOT(receivedMessage(QJsonObject,QString)));

    this->_map = Map::getInstance();
    this->_gameMode = new GameMode();
    this->_properties = new Properties(5);

    this->_players = new QMap<QString, Player*>;
    this->_controls = new QMap<QString, Control*>;

    tempCp = new Checkpoint;
    tempCp->setId(100);
    tempCp->setX(200);
    tempCp->setY(20);
    this->g_engine.addCheckpoint(tempCp);


    this->control_th();

    this->g_engine.show();


    _gameMode->publish();
    _properties->publish();
}

void Engine::envoiGameInfo()
{
    QTimer::singleShot(100, this, &Engine::envoiGameInfo);
    this->_gameMode->publish();   
}


void Engine::control_th()
{
    QTimer::singleShot(1000, this, &Engine::control_th);

    qDebug() << "control_th";

    this->tempCp->setX(this->tempCp->getX()+1);
    this->g_engine.updateCheckpoint(tempCp);

    // traitement
    foreach(Control *control, this->_controls->values()) {
        Player *player = this->_players->value("sdsd");
        Vehicle *vehicule = new Vehicle(player->getVehicule());

        float P = 1000;

        float F = control->getPower() * P;
        float C = 1.9;
        float Ff = 0.5 * C * 1.09 * (player->getSpeed()*player->getSpeed());
        float acceleration = (F-Ff) / (vehicule->getWeight()*1000); // acceleration
        float speed = player->getSpeed() + acceleration;
        // a faire
        int x = speed * 25;
        int y = speed * 25;
        float angle = player->getAngle() + (player->getAngle()-control->getAngle());

        player->setX(x);
        player->setY(y);
        player->setAngle(angle);
        player->setSpeed(speed);

        // gerer les checkpoints
        // gerer les obstacles

        this->_players->remove(player->getUuid());
        this->_players->insert(player->getUuid(), player);

    }

}


void Engine::traitementPlayerRegister(QJsonObject pMessage)
{
    Player *player = new Player();
    player->deserialize(pMessage);
    this->_players->remove(player->getUuid());
    this->_players->insert(player->getUuid(), player);
}


void Engine::traitementPlayerControl(QJsonObject pMessage)
{
/*
    "uuid": str,
    "angle": float, // en rad
    "power": int, // [-100%;100%]
    "buttons": { // état des boutons
        "banana": bool,
        "bomb": bool,
        "rocket": bool
     }
*/
    qDebug() << "data";
    QString uuid = pMessage["uuid"].toString();
    float angle = pMessage["angle"].toDouble();
    int power = pMessage["power"].toInt();

    QMap<QString, bool> buttons;
    buttons["banana"] = pMessage["banana"].toBool();
    buttons["bomb"] = pMessage["bomb"].toBool();
    buttons["rocket"] = pMessage["rocket"].toBool();

    Player *player = this->_players->value(uuid);

    if(!player) {
        qDebug() << "[ERROR] traitementPlayerControl player not found";
        return;
    }

    Control *control = new Control();
    control->setUuid(uuid);
    control->setAngle(angle);
    control->setPower(power);
    control->setButtons(buttons);

    this->_controls->remove(player->getUuid());
    this->_controls->insert(player->getUuid(), control);
}

//  +------+
//  | SLOT |
//  +------+
void Engine::receivedMessage(QJsonObject pMessage, QString pTopic)
{
    if (pTopic == "player/register") this->traitementPlayerRegister(pMessage);
    if (pTopic == "player/control") this->traitementPlayerControl(pMessage);

    qDebug() << "message";
}

