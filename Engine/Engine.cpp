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
    this->_properties = Properties::FromFile();

    GObstacle::radius = this->_properties->getCircleRadius();
    GObstacle::heigth = this->_properties->getRectangleHeight();
    GObstacle::width = this->_properties->getRectangleWidth();

    GBanana::radius = this->_properties->getBananaRadius(); 
    GBomb::radius = this->_properties->getBombRadius();

    GRocket::radius = this->_properties->getRocketRadius();
    GRocket::speed = this->_properties->getRocketSpeed();

    GCheckpoint::radiusCheckpoint = this->_properties->getCheckpointRadius();

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

void Engine::gameUpdate()
{
    emit updated();
}

void Engine::startGame()
{
    this->gameStartAt = QDateTime::currentDateTime();
}

QDateTime Engine::getGameStartAt() const
{
    return this->gameStartAt;
}

void Engine::envoiGameProperties()
{
    QTimer::singleShot(1000, this, &Engine::envoiGameProperties);
    _properties->publish();
}

void Engine::envoiGameInfo()
{
    QTimer::singleShot(ENGINE_FREQUENCY, this, &Engine::envoiGameInfo);
    this->_gameMode->publish();
}

QList<QGraphicsItem *> Engine::collision(GPlayer* g_player)
{
    QList<QGraphicsItem*> g_items;


    for(GCheckpoint *g_checkpoint: this->checkpointsGraphics.values()) {
        if(g_checkpoint->collidesWithItem(g_player)) g_items.append(g_checkpoint);

//        if(g_checkpoint->shape().intersects(g_player->shape())) {

//            g_items.append(g_checkpoint);
//        }
    }

    for(GObstacle *g_obstacle: this->obstaclesGraphics.values()) {
//        if(g_obstacle->collidesWithItem(g_player)) g_items.append(g_obstacle);

        QPainterPath pp = g_obstacle->shape();
        pp.translate(g_player->pos());
        qDebug() << pp;

        if(pp.intersects(g_player->shape().translated(g_player->pos()))) {
            g_items.append(g_obstacle);
        }
    }

    for(GPlayer *g_player: this->playersGraphics.values()) {
        if(g_player->getUuid() != g_player->getUuid() && g_player->collidesWithItem(g_player)) g_items.append(g_player);
    }

    for(GItem *g_item: this->itemsGraphics) {
        if(g_item->collidesWithItem(g_player))
            g_items.append(g_item);
    }

    return g_items;
}

qreal Engine::intersectionVal(QGraphicsItem *pItem1, QGraphicsItem *pItem2)
{
    return pItem1->shape().intersected(pItem2->shape()).boundingRect().height() * pItem1->shape().intersected(pItem2->shape()).boundingRect().width();
}

void Engine::control_th()
{
    QTimer::singleShot(ENGINE_FREQUENCY, this, &Engine::control_th);

    // traitement
    for (Player *player: this->_gameMode->_players->values()) {
        GPlayer* g_player = this->playersGraphics.value(player->getUuid());
        if(g_player->getBananaCooldown() > 0) g_player->setBananaCooldown(g_player->getBananaCooldown() - 1);
        if(g_player->getBombCooldown() > 0) g_player->setBombCooldown(g_player->getBombCooldown() - 1);
        if(g_player->getRocketCooldown() > 0) g_player->setRocketCooldown(g_player->getRocketCooldown() - 1);

        Control *control = this->_controls->value(player->getUuid());

        g_player->update(control);

        QList<QGraphicsItem*> g_items = g_player->collidingItems();

        for (QGraphicsItem *gItem : g_items ) {
            QGraphicsObject *gObject = static_cast<QGraphicsObject *>(gItem);

            if (gObject->property("type") == GCheckpoint::type) {
                GCheckpoint* g_checkpoint = (GCheckpoint*)gObject;

                int nextCheckpoint = this->getNextCheckpointId(player->getLastCheckpoint());

                if (g_checkpoint->getId() == nextCheckpoint) {


                    player->setLastCheckpoint(nextCheckpoint);
                    nextCheckpoint = this->getNextCheckpointId(player->getLastCheckpoint());

                     Checkpoint *ch = Map::getInstance()->getCheckpoints()->first();

                     if (ch) {

                         qDebug() << "first is : " << ch->getId();

                         if (g_checkpoint->getCheckpoint()->getId() == ch->getId()) {
                             player->setCurrentLap(player->getCurrentLap()+1);
                         }

//                         if (nextCheckpoint == ch->getId()) {
//                             qDebug() << "new checkpoint";
//                             player->setCurrentLap(player->getCurrentLap()+1);
//                             player->setLastCheckpoint(nextCheckpoint);
//                         }
                     }
                }

                if (player->getCurrentLap() == this->_properties->getLaps()) {
                    qDebug() << player->getPseudo() << " finish!";

                    this->_gameMode->_players->remove(player->getUuid());
                }

//                qDebug() << player->getPseudo() << " Last checkpoint : " << player->getLastCheckpoint() << " nextCheckpoint : " << nextCheckpoint << " laps " << player->getCurrentLap();

            } else if (gObject->property("type") == GBanana::type) {
                GBanana* g_banana = (GBanana*)gObject;
                qDebug() << "hit banana";

                g_player->hit();
                this->destoryItem(g_banana);

            } else if (gObject->property("type") == GBomb::type) {
                GBomb* g_bomb = (GBomb*)gObject;
                qDebug() << "hit bomb";

                g_player->hit();
                this->destoryItem(g_bomb);
            } else if (gObject->property("type") == GRocket::type) {
                qDebug() << "hit rocket";
                GRocket* g_rocket = (GRocket*)gObject;

                g_player->hit();
                this->destoryItem(g_rocket);

            } else if (gObject->property("type") == GPlayer::type) {
                GPlayer* g_player = (GPlayer*)gObject;

            } else if (gObject->property("type") == GObstacle::type) {
                qDebug() << "obstacle";
                GObstacle* g_obstacle = (GObstacle*)gObject;


                // faire le déplacement
//                g_player->setPos(player->getPosition());
//                g_player->setRotation(player->getAngle());

                auto direction =player->getPosition() - QPoint(g_obstacle->getX()-g_obstacle->getRadius(),g_obstacle->getY()-g_obstacle->getRadius());
                qDebug() << player->getPosition() << g_obstacle->getX() << g_obstacle->getY() << player->getAngle()/3.14*180 << direction;

                auto angle = atan2(direction.y(),direction.x());
                QPointF FRepousse(cos(-angle),-sin(-angle));
                g_player->setPos(g_player->getPos()+FRepousse*10);
            }
        }

        player->setPos(g_player->getPos());
        player->setAngle(g_player->getAngle());


        /* --- spawn item ---*/
        if (control) {
            //  SI cooldown =< 0 ET nItem > 0
            //  ALORS:  => placer item
            //          => cooldown = 5
            //  FIN SI
            if (control->getButton("banana")) {
                if(g_player->getBananaCooldown() <= 0 && g_player->getnBanana() > 0) {
                    qDebug() << "drop banana";
                    control->setButton("banana", false);

                    QPoint spanwPoint = (QPoint)(player->getPosition() + (-player->getVector() * (GBanana::radius + 15)).toPoint());
                    GBanana *gBanana = new GBanana(spanwPoint);
                    gBanana->setTtl(_properties->getBananaTtl() * ENGINE_CYCLE);

                    this->spawnItem(gBanana);
                    // engine cycle enfoiré alexis
                    g_player->setBananaCooldown(5*20);
                    g_player->setnBanana(g_player->getnBanana()-1);
                }
            } else if (control->getButton("bomb") && g_player->getnBomb() > 0) {
                if(g_player->getBombCooldown() <= 0) {
                    qDebug() << "drop bomb";
                    control->setButton("bomb", false);

                    QPoint spanwPoint = (QPoint)(player->getPosition() + (player->getVector() * (GBomb::radius + 15)).toPoint());
                    GBomb *gBomb = new GBomb(spanwPoint, player->getAngle());
                    gBomb->setTtl(_properties->getBombTtl() * ENGINE_CYCLE);

                    this->spawnItem(gBomb);
                    // engine cycle enfoiré alexis
                    g_player->setBombCooldown(5*20);
                    g_player->setnBomb(g_player->getnBomb()-1);
                }
            } else if (control->getButton("rocket")) {
                if(g_player->getRocketCooldown() <= 0 && g_player->getnRocket() > 0) {
                    qDebug() << "drop rocket";
                    control->setButton("rocket", false);

                    QPoint spanwPoint = (QPoint)(player->getPosition() + (player->getVector() * (GRocket::radius + 15)).toPoint());
                    GRocket *gRocket = new GRocket(spanwPoint, player->getAngle());

                    this->spawnItem(gRocket);
                    // engine cycle enfoiré alexis
                    g_player->setRocketCooldown(5*20);
                    g_player->setnRocket(g_player->getnRocket()-1);
                }
            }
        }

        /*limite map*/
        if(g_player->getPos().x() < 0){

            g_player->setX(0);


        }

        if(g_player->getPos().y() < 0){

            g_player->setY(0);

        }

        if (g_player->getPos().x() > _map->getMapHeight()){
            g_player->setX(_map->getMapWidth());

        }

        if (g_player->getPos().x() > _map->getMapWidth()){

            g_player->setX(_map->getMapHeight());


        }
    }


    for (GItem *gItem: itemsGraphics) {
        lifeCycleItem(gItem);
    }
}

void Engine::lifeCycleItem(GItem *gItem) {

    int ttl = gItem->getTtl();

    if (ttl > 0) {
        gItem->setTtl(ttl - 1);
    }

    if (ttl == 0) {
        destoryItem(gItem);
        return;
    }

    gItem->update();

    if (gItem->property("type") == GBanana::type) {
        GBanana* g_banana = (GBanana*)gItem;

    } else if (gItem->property("type") == GBomb::type) {
        GBomb* g_bomb = (GBomb*)gItem;

    } else if (gItem->property("type") == GRocket::type) {
        GRocket* g_rocket = (GRocket*)gItem;

    }
}

void Engine::spawnItem(GItem *gItem)
{
    this->itemsGraphics.append(gItem);
    this->g_engine->addItemGraphics(gItem);
    this->_gameMode->_items->append(gItem->getItem());
}

void Engine::destoryItem(GItem *gItem)
{
    this->itemsGraphics.removeAll(gItem);
    this->g_engine->removeItem(gItem);
    this->_gameMode->_items->removeAll(gItem->getItem());

    delete gItem;
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
                return ids[0];
            } else return ids[iCheckpoint+1];
            break;
        }
    }

    return -1;
}

void Engine::traitementPlayerControl(QJsonObject pMessage)
{

    QString uuid = pMessage["uuid"].toString();

    Player *player = this->_gameMode->_players->value(uuid);

    if(!player) {
        return;
    }

    Control *control = new Control();
    control->deserialize(pMessage);

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

        QPoint spawnPoint = QPoint(0, 0);

        Checkpoint *c = Map::getInstance()->getCheckpoints()->first();
        if (c != nullptr) {
            spawnPoint = c->getPosition();
            p->setLastCheckpoint(c->getId());
        }

        qDebug() << "spwn point" << spawnPoint;

        p->setPos(spawnPoint);

        playerGraphics->setPos(spawnPoint);


        playerGraphics->setnBanana(this->_properties->getBanana());
        playerGraphics->setnBomb(this->_properties->getBomb());
        playerGraphics->setnRocket(this->_properties->getRocket());

        this->g_engine->addPlayerGraphics(playerGraphics);
        this->playersGraphics.insert(p->getUuid(), playerGraphics);
    }

    qDebug() << p->getVehicule();

    Vehicle *veh = this->_properties->vehicleOptions->value(p->getVehicule());

    qDebug() << veh->toString();

    if (veh != nullptr) {
        qDebug() << veh->getHeight();
        qDebug() << veh->getWidth();

        playerGraphics->setHeigth(veh->getHeight());
        playerGraphics->setWidth(veh->getWidth());
    }

    playerGraphics->setPos(p->getPosition());

    delete r;

    gameUpdate();
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

void Engine::traitementPlayerRegister(QJsonObject pMessage)
{
    Player *player = new Player();
    player->deserialize(pMessage);
    this->_gameMode->_players->remove(player->getUuid());
    this->_gameMode->_players->insert(player->getUuid(), player);
}

GameMode *Engine::getGameMode()
{
    return _gameMode;
}

Properties *Engine::getProperties()
{
    return _properties;
}

void Engine::reset()
{
    qDebug() << "reset";

    for (QGraphicsItem *item : this->checkpointsGraphics.values()) {
        this->g_engine->removeItem(item);
    }
    this->checkpointsGraphics.clear();

    for (QGraphicsItem *item : this->obstaclesGraphics.values()) {
        this->g_engine->removeItem(item);
    }
    this->obstaclesGraphics.clear();

    for (QGraphicsItem *item : this->playersGraphics.values()) {
        this->g_engine->removeItem(item);
    }
    this->playersGraphics.clear();

    for (QGraphicsItem *item : this->itemsGraphics) {
        this->g_engine->removeItem(item);
    }
    this->itemsGraphics.clear();

    this->_gameMode->reset();
    this->_map->reste();

    this->gameUpdate();
}
