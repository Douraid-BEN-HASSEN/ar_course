#include "Engine.h"

Engine::Engine(QObject *parent): QObject{parent}
{
    this->_mqtt = MqttService::instance();
    this->_mqtt->subscribe("player/register");
    this->_mqtt->subscribe("player/control");

    connect(this->_mqtt, SIGNAL(message(QJsonObject,QString)), this, SLOT(receivedMessage(QJsonObject,QString)));

    this->_map = Map::getInstance();
    this->_gameMode = new GameMode();
    this->_properties = new Properties(5);

    this->_controls = new QMap<QString, Control*>;

    // ==== temp ====
    testCheckpoint = new Checkpoint;
    testCheckpoint->setId(150);
    testCheckpoint->setX(500);
    testCheckpoint->setY(20);
    this->g_engine.addCheckpoint(testCheckpoint);

    testObstacle = new Obstacle;
    testObstacle->setId(210);
    testObstacle->setX(800);
    testObstacle->setY(20);
    this->g_engine.addObstacle(testObstacle);

    testPlayer = new Player;
    testPlayer->setUuid("testPlayer");
    testPlayer->setX(20);
    testPlayer->setY(20);
    this->g_engine.addPlayer(testPlayer);
    // =======

    this->envoiGameInfo();
    this->control_th();

    this->g_engine.show();

    _gameMode->publish();
    _properties->publish();
    envoiGameInfo();
}

Engine::~Engine()
{
    delete this->testCheckpoint;
    delete this->testObstacle;
    delete this->testPlayer;
}

void Engine::envoiGameInfo()
{
    QTimer::singleShot(100, this, &Engine::envoiGameInfo);
    this->_gameMode->publish();
}

void Engine::control_th()
{
    QTimer::singleShot(1000, this, &Engine::control_th);

    testPlayer->setX(testPlayer->getX()+10);
    this->g_engine.updatePlayer(testPlayer);

    // traitement
    foreach(Control *control, this->_controls->values()) {
        Player *player = this->_gameMode->_players->value(control->getUuid());
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

        this->_gameMode->_players->remove(player->getUuid());
        this->_gameMode->_players->insert(player->getUuid(), player);

    }

}

int Engine::getNextCheckpointId(int pCurrentCheckpoint)
{
    /*QList<int> ids;
    foreach(Checkpoint *checkpoint, this->_map->getCheckpoints()) {
        ids.append(checkpoint->getId());
    }

    std::sort(ids.begin(), ids.end());

    for(int iCheckpoint=0; iCheckpoint<ids.count(); iCheckpoint++) {
        if(ids[iCheckpoint] == pCurrentCheckpoint) {
            if(iCheckpoint+1 >= ids.count()) {
                return -1;
            } else return ids[iCheckpoint+1];
            break;
        }
    }*/

    return -1;
}


void Engine::traitementPlayerRegister(QJsonObject pMessage)
{
    Player *player = new Player();
    player->deserialize(pMessage);
    this->_gameMode->_players->remove(player->getUuid());
    this->_gameMode->_players->insert(player->getUuid(), player);

    qDebug() << player->serialize();

    // ajout dans le moteur graphique
    this->g_engine.addPlayer(player);
}


void Engine::traitementPlayerControl(QJsonObject pMessage)
{
    qDebug() << pMessage;
    QString uuid = pMessage["uuid"].toString();
    float angle = pMessage["angle"].toDouble();
    int power = pMessage["power"].toInt();

    QMap<QString, bool> buttons;
    buttons["banana"] = pMessage["banana"].toBool();
    buttons["bomb"] = pMessage["bomb"].toBool();
    buttons["rocket"] = pMessage["rocket"].toBool();

    Player *player = this->_gameMode->_players->value(uuid);

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

