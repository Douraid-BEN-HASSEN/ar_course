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

qreal Engine::intersectionVal(QGraphicsItem *pItem1, QGraphicsItem *pItem2)
{
    return pItem1->shape().intersected(pItem2->shape()).boundingRect().height() * pItem1->shape().intersected(pItem2->shape()).boundingRect().width();
}

void Engine::control_th()
{
    QTimer::singleShot(100, this, &Engine::control_th);
    // traitement
    for (Player *player: this->_gameMode->_players->values()) {
        QGraphicsItem* g_player = this->playersGraphics.value(player->getUuid());
        Control *control = this->_controls->value(player->getUuid());

        player->update(control);
        g_player->setX(player->getX());
        g_player->setY(player->getY());

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
                        player->setLastCheckpoint(0);
                    }
                }

            } else if (gObject->property("type") == GPlayer::type) {
                GPlayer* g_player = (GPlayer*)gObject;


            } else if (gObject->property("type") == GObstacle::type) {
                GObstacle* g_obstacle = (GObstacle*)gObject;

                // copie du player
                Player oldPlayer;
                qreal oldIntersectionVal = this->intersectionVal(g_player, g_obstacle);
                oldPlayer.copyPlayer(player);

                // faire le déplacement
                player->update(control);

                // comparer les valeur
                qreal newIntersectionVal = this->intersectionVal(g_player, g_obstacle);
                qDebug() << "newIntersectionVal => " << newIntersectionVal;
                qDebug() << "oldIntersectionVal => " << oldIntersectionVal;
                if(newIntersectionVal > oldIntersectionVal) {
                    // restauration du player
                    player->setUuid(oldPlayer.getUuid());
                    player->setPseudo(oldPlayer.getPseudo());
                    player->setColor(oldPlayer.getColor());
                    player->setTeam(oldPlayer.getTeam());
                    player->setX(oldPlayer.getX());
                    player->setY(oldPlayer.getY());
                    player->setAngle(oldPlayer.getAngle());
                    player->setSpeed(oldPlayer.getSpeed());
                    player->setVehicule(oldPlayer.getVehicule());
                    player->setLastCheckpoint(oldPlayer.getLastCheckpoint());
                    player->setCurrentLap(oldPlayer.getCurrentLap());
                    player->setStatus(oldPlayer.getStatus());
                    player->setController(oldPlayer.getController());
                }
            }

        }

        //g_player->setPos(player->getX(), player->getY());
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
        this->playersGraphics.insert(p->getUuid(), playerGraphics);
    }

    playerGraphics->setPos(p->getX(), p->getY());

    //delete r;
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

    for (GPlayer *g_player : this->playersGraphics) {
        Player *player = _gameMode->_players->value(g_player->getUuid());
        g_player->setPos(player->getX(), player->getY());
    }

}

GEngine * Engine::getGEngine()
{
    return g_engine;
}

void Engine::traitementPlayerRegister(QJsonObject pMessage)
{
    Player *player = new Player();
    player->deserialize(pMessage);
    this->_gameMode->_players->remove(player->getUuid());
    this->_gameMode->_players->insert(player->getUuid(), player);
}
