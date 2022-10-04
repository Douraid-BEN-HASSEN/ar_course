#include "Engine.h"

// diviser les angles par 10 (à voir)
// gestion graphique
Engine::Engine(QObject *parent): QObject{parent}
{
    this->_mqtt = MqttService::instance();
    connect(this->_mqtt, SIGNAL(message(QJsonObject,QString)), this, SLOT(receivedMessage(QJsonObject,QString)));
    this->_mqtt->subscribe("player/control");


    this->_map = Map::getInstance();
    this->_gameMode = new GameMode();
    this->_properties = new Properties(5);

    connect(RegisterManager::getInstance(), SIGNAL(application(Register*)), this, SLOT(registered(Register*)));
    connect(Map::getInstance(), SIGNAL(updated()), this, SLOT(updateMap()));


    this->_controls = new QMap<QString, Control*>;


    this->g_engine = new GEngine();
    this->control_th();

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
}

QList<QGraphicsItem *> Engine::collision(Player* pPlayer)
{
    QList<QGraphicsItem*> g_items;
    QGraphicsItem* g_player = this->playersGraphics.value(pPlayer->getUuid());

    for(GCheckpoint *g_checkpoint: this->checkpointsGraphics.values()) {
        if(g_checkpoint->collidesWithItem(g_player)) g_items.append(g_checkpoint);
    }

    for(GObstacle *g_obstacle: this->obstaclesGraphics.values()) {
        if(g_obstacle->collidesWithItem(g_player)) g_items.append(g_obstacle);
    }

    for(GPlayer *g_player: this->playersGraphics.values()) {
        if(g_player->getUuid() != pPlayer->getUuid() && g_player->collidesWithItem(g_player)) g_items.append(g_player);
    }

    return g_items;
}


void Engine::control_th()
{
    QTimer::singleShot(100, this, &Engine::control_th);
    // traitement
    for (Player *player: this->_gameMode->_players->values()) {
        Control *control = this->_controls->value(player->getUuid());

        player->update(control);






/*        float P = vehicule->getMaxSpeed() * vehicule->getMaxSpeed() * (1/2) * vehicule->getWeight();  //1000 avant
        float F = control->getPower() * P;
        float C = 1.9;//coef de penetration dans l'air a 20°
        float Ff = 0.5 * C * 1.09 * (player->getSpeed()*player->getSpeed());
        float acceleration = (F-Ff) / (vehicule->getWeight()*1000); // acceleration
        float speed = player->getSpeed() + acceleration;
        // a faire
        float angle = (player->getAngle() +(control->getAngle()));
        qDebug()<<"angle"<<angle;
        qDebug()<<"acceleration"<<acceleration;
        qDebug()<<"speed"<<speed;
        qDebug()<<"===================";
        qDebug()<<"xDepart"<<player->getX();
        qDebug()<<"yDepart"<<player->getY();

        int Newx = player->getX() + (control->getPower() * cos(player->getAngle()));
        int Newy = player->getY() + (control->getPower() * -sin(player->getAngle()));

        qDebug()<<"===================";
        qDebug()<<"xArriv"<<Newx;
        qDebug()<<"yArriv"<<Newy;

        qDebug()<<"vehicule"<<player->getVehicule()<<"poid"<<vehicule->getWeight();

        //playersGraphics.value(player->getUuid())->moveBy(Newx,Newy); //int vers real ?? des soucis a prevoir
        player->setX(Newx);
        player->setY(Newy);
        player->setAngle(angle);
        player->setSpeed(speed);
*/


        QList<QGraphicsItem*> g_items = this->collision(player);

        for (QGraphicsItem *gItem : g_items ) {
            QGraphicsObject *gObject = static_cast<QGraphicsObject *>(gItem);


            if (gObject->property("type") == GCheckpoint::type) {
                GCheckpoint* g_checkpoint = (GCheckpoint*)gObject;

                int nextCheckpoint = this->getNextCheckpointId(player->getLastCheckpoint());

                if (g_checkpoint->getId() == nextCheckpoint) {
                    player->setLastCheckpoint(nextCheckpoint);
                    nextCheckpoint = this->getNextCheckpointId(player->getLastCheckpoint());
                    if (nextCheckpoint == -1) {
                        qDebug() << "new checkpoint";
                        player->setCurrentLap(player->getCurrentLap()+1);
                    }
                }

            } else if (gObject->property("type") == GPlayer::type) {
                GPlayer* g_player = (GPlayer*)gObject;

            } else if (gObject->property("type") == GObstacle::type) {
                GObstacle* g_obstacle = (GObstacle*)gObject;

               //obstacleCollision = true;
            }

        }


    }




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

void Engine::traitementPlayerControl(QJsonObject pMessage)
{
    //qDebug() << pMessage;
    QString uuid = pMessage["uuid"].toString();
    float angle = pMessage["angle"].toDouble();
    int power = pMessage["power"].toInt();

    QMap<QString, bool> buttons;
    buttons["banana"] = pMessage["banana"].toBool();
    buttons["bomb"] = pMessage["bomb"].toBool();
    buttons["rocket"] = pMessage["rocket"].toBool();

    Player *player = this->_gameMode->_players->value(uuid);

    if(!player) {
        return;
    }

    Control *control = new Control();
    control->setUuid(uuid);
    control->setAngle(angle);
    control->setPower(power);
    control->setButtons(buttons);

    this->_controls->insert(player->getUuid(), control);
}

//  +------+
//  | SLOT |
//  +------+
void Engine::receivedMessage(QJsonObject pMessage, QString pTopic)
{
    if (pTopic == "player/control") this->traitementPlayerControl(pMessage);
}

void Engine::registered(Register *r) {
    qDebug() << "register";

    if (GameMode::getInstance()->_players->value(r->getUuid()) != nullptr) {
        return;
    }

    Player *p = new Player(r);
    _gameMode->_players->insert(p->getUuid(), p);

    GPlayer *playerGraphics = playersGraphics.value(p->getUuid());

    if (!playerGraphics) {
        playerGraphics = new GPlayer(p);
        this->g_engine->addPlayerGraphics(playerGraphics);
    }

    playerGraphics->setPos(p->getX(), p->getY());

    delete r;
}

void Engine::updateMap() {

    for (Obstacle *iterObstacle : Map::getInstance()->getObstacles()->values()) {
        // Verifier si l object ObstacleRect* obstaclerect  exist

        GObstacle *obstacleGraphics = obstaclesGraphics.value(iterObstacle->getId());

        if (!obstacleGraphics) {
            obstacleGraphics = new GObstacle(iterObstacle);
            this->g_engine->addObstacleGraphics(obstacleGraphics);
            obstaclesGraphics.insert(obstacleGraphics->getId(), obstacleGraphics);
        }

        obstacleGraphics->setPos(iterObstacle->getX(),iterObstacle->getY());
    }


    for (Checkpoint *iterCheckpoint : Map::getInstance()->getCheckpoints()->values()) {

        GCheckpoint *checkpointGraphics = checkpointsGraphics.value(iterCheckpoint->getId());

        if (!checkpointGraphics) {
            checkpointGraphics = new GCheckpoint(iterCheckpoint);
            this->g_engine->addCheckpointGraphics(checkpointGraphics);
            checkpointsGraphics.insert(checkpointGraphics->getId(), checkpointGraphics);
        }

        checkpointGraphics->setPos(iterCheckpoint->getX(), iterCheckpoint->getY());
    }
}

GEngine * Engine::getGEngine()
{
    return g_engine;
}
