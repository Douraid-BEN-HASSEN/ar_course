#include "Engine.h"

// diviser les angles par 10 (à voir)
// gestion graphique
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

    this->envoiGameInfo();
    this->control_th();

    this->g_engine.show();

    this->envoiGameProperties();
    this->envoiGameInfo();
}

Engine::~Engine()
{
}

void Engine::envoiGameProperties()
{
    QTimer::singleShot(1000, this, &Engine::envoiGameProperties);
    _properties->publish();
}

void Engine::envoiGameInfo()
{
    QTimer::singleShot(100, this, &Engine::envoiGameInfo);
    this->_gameMode->publish();

    // ajout dans le moteur graphique
    for(Checkpoint *checkpoint: *this->_map->getCheckpoints()) {
        this->g_engine.updateCheckpoint(checkpoint);
    }

    for(Obstacle *obstacle: *this->_map->getObstacles()) {
        this->g_engine.updateObstacle(obstacle);
    }

    for(Player *player: *this->_gameMode->_players) {
        this->g_engine.updatePlayer(player);
    }
}

void Engine::control_th()
{
    QTimer::singleShot(1000, this, &Engine::control_th);

    // traitement
    for(Control *control: this->_controls->values()) {
        Player *player = this->_gameMode->_players->value(control->getUuid());


        QList<QGraphicsItem*> g_items = this->g_engine.collision(player);
        if(g_items.count() > 0) {
            for(int iItem=0; iItem<g_items.count(); iItem++) {
                GPlayer* g_player = (GPlayer*)g_items[iItem];
                GCheckpoint* g_checkpoint = (GCheckpoint*)g_items[iItem];
                GObstacle* g_obstacle = (GObstacle*)g_items[iItem];

                // collision avec player
                if(g_player->getPlayer()) {

                }

                // collision avec checkpoint
                if(g_checkpoint->getCheckpoint()) {
                    int nextCheckpoint = this->getNextCheckpointId(player->getLastCheckpoint());
                    if(g_checkpoint->getId() == nextCheckpoint) {
                        player->setLastCheckpoint(nextCheckpoint);
                        nextCheckpoint = this->getNextCheckpointId(player->getLastCheckpoint());
                        if(nextCheckpoint == -1) {
                            qDebug() << "new checkpoint";
                            player->setCurrentLap(player->getCurrentLap()+1);
                        }
                    }
                }

                // collision avec obstacle
                if(g_obstacle->getObstacle()) {
                    player->setSpeed(0);
                }


            }
        }

        player->update(control);

        //Vehicle *vehicule = new Vehicle(player->getVehicule());

        /*float P = 1000;

        float F = control->getPower() * P;
        float C = 1.9;
        float Ff = 0.5 * C * 1.09 * (player->getSpeed()*player->getSpeed());
        float acceleration = (F-Ff) / (vehicule->getWeight()*1000); // acceleration
        float speed = player->getSpeed() + acceleration;
        // a faire
        int x = player->getX() + (control->getPower()) * cos(player->getAngle());
        int y = player->getY() + (control->getPower()) * -sin(player->getAngle());
        float angle = player->getAngle() + (player->getAngle()-control->getAngle());*/

        /*int x = player->getX() + (control->getPower()) * cos(control->getAngle());
        int y = player->getY() + (control->getPower()) * -sin(control->getAngle());
        float angle = player->getAngle();
        int speed = player->getSpeed();*/


        /*
        player->setX(x);
        player->setY(y);
        player->setAngle(angle);
        player->setSpeed(speed);*/

        // gerer les checkpoints
        // gerer les obstacles

        /*this->_gameMode->_players->remove(player->getUuid());
        this->_gameMode->_players->insert(player->getUuid(), player);*/

    }

}

int Engine::getNextCheckpointId(int pCurrentCheckpoint)
{
    QList<int> ids;
    foreach(Checkpoint *checkpoint, this->_map->getCheckpoints()->values()) {
        ids.append(checkpoint->getId());
    }

    std::sort(ids.begin(), ids.end());

    if(pCurrentCheckpoint == 0) return ids[0];

    for(int iCheckpoint=0; iCheckpoint<ids.count(); iCheckpoint++) {
        if(ids[iCheckpoint] == pCurrentCheckpoint) {
            if(iCheckpoint+1 >= ids.count()) {
                return -1;
            } else return ids[iCheckpoint+1];
            break;
        }
    }

    return -1;
}

void Engine::traitementPlayerRegister(QJsonObject pMessage)
{
    Player *player = new Player();
    player->deserialize(pMessage);
    this->_gameMode->_players->remove(player->getUuid());
    this->_gameMode->_players->insert(player->getUuid(), player);

    qDebug() << player->serialize();
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
        player = new Player();
        player->deserialize(pMessage);
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
}

