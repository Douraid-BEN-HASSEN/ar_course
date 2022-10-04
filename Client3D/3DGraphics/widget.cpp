#include "widget.h"
#include "ui_widget.h"

#include <QHBoxLayout>
#include "obstacleGraphics3D.h"
#include "checkpointGraphics3D.h"

#include <Kart/Map/Map.h>
#include <Kart/Game/Properties.h>
#include <Kart/Player/GameMode.h>

#include <Mqtt/MqttService.h>

Widget::Widget(QWidget *parent): QWidget(parent)
{
    this->mView3D = new Qt3DExtras::Qt3DWindow();
    Qt3DCore::QEntity *rootEntity = new Qt3DCore::QEntity;
    Qt3DExtras::QDiffuseSpecularMaterial *material = new Qt3DExtras::QDiffuseSpecularMaterial(rootEntity);

    Qt3DCore::QEntity *m_cuboidEntity = new Qt3DCore::QEntity(rootEntity);
    Qt3DExtras::QCuboidMesh *cuboid = new Qt3DExtras::QCuboidMesh();
    // CuboidMesh Transform
    Qt3DCore::QTransform *cuboidTransform = new Qt3DCore::QTransform();
    cuboidTransform->setScale(4.0f);
    cuboidTransform->setTranslation(QVector3D(5.0f, -4.0f, 0.0f));
    material->setDiffuse(QColor(QRgb(0x665423)));

    //Cuboid
    m_cuboidEntity->addComponent(cuboid);
    m_cuboidEntity->addComponent(material);
    m_cuboidEntity->addComponent(cuboidTransform);

    // Camera
    Qt3DRender::QCamera *camera = mView3D->camera();
    camera->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    camera->setPosition(QVector3D(0, 0, 40.0f));
    camera->setViewCenter(QVector3D(0, 0, 0));

    // For camera controls
    Qt3DExtras::QOrbitCameraController *camController = new Qt3DExtras::QOrbitCameraController(rootEntity);
    camController->setLinearSpeed( 50.0f );
    camController->setLookSpeed( 180.0f );
    camController->setCamera(camera);


    mView3D->setRootEntity(rootEntity);

    QHBoxLayout* layout = new QHBoxLayout(this);
    QWidget *container = QWidget::createWindowContainer(mView3D);

    layout->addWidget(container);
    setLayout(layout);





    // L'objet que l on observe Field::instance()
    // regarder a chaque fois que cette méthode est appellé
    // Pour finir sur this = Widget apperler updateMap

    connect(Map::getInstance(), SIGNAL(updated()), this, SLOT(updateMap()));
    connect(Properties::getInstance(), SIGNAL(updated()), this, SLOT(updateProperties()));
    connect(GameMode::getInstance(), SIGNAL(updated()), this, SLOT(updateGameMode()));

}

Widget::~Widget() {}

void Widget::updateProperties() {
    ObstacleGraphics::heigth = Properties::getInstance()->getRectangleHeight();
    ObstacleGraphics::width = Properties::getInstance()->getRectangleWidth();
    ObstacleGraphics::radius = Properties::getInstance()->getCircleRadius();

    CheckpointGraphics::radiusCheckpoint = Properties::getInstance()->getCheckpointRadius();
}

void Widget::updateMap() {

    qDebug() << "map";
    //new QMap<int, Obstacle*>();
    // Faire une boucle sur tous les obstacles
    // Sur chaque obstacle on va devoir le créer + le placer

    for (Obstacle *iterObstacle : Map::getInstance()->getObstacles()->values()) {
        // Verifier si l object ObstacleRect* obstaclerect  exist

        ObstacleGraphics *obstacleGraphics = localObstacles.value(iterObstacle->getId());

        if (!obstacleGraphics) {
            obstacleGraphics = new ObstacleGraphics(iterObstacle);
            mScene->addItem(obstacleGraphics);
            localObstacles.insert(obstacleGraphics->getId(), obstacleGraphics);
        }

        obstacleGraphics->setPos(iterObstacle->getX(),iterObstacle->getY());
    }


    for (Checkpoint *iterCheckpoint : Map::getInstance()->getCheckpoints()->values()) {

        CheckpointGraphics *checkpointGraphics = localCheckpoint.value(iterCheckpoint->getId());

        if (!checkpointGraphics) {
            checkpointGraphics = new CheckpointGraphics(iterCheckpoint);

            mScene->addItem(checkpointGraphics);
            localCheckpoint.insert(checkpointGraphics->getId(), checkpointGraphics);
        }

        checkpointGraphics->setPos(iterCheckpoint->getX(), iterCheckpoint->getY());
    }

}

void Widget::updateGameMode() {

    for (Player *iterPlayer : GameMode::getInstance()->_players->values()) {

        PlayerGraphics *playerGraphics = localPlayers.value(iterPlayer->getUuid());

        if (!playerGraphics) {
            playerGraphics = new PlayerGraphics(iterPlayer);
            mScene->addItem(playerGraphics);
            localPlayers.insert(playerGraphics->getUuid(), playerGraphics);
        }

        playerGraphics->setPos(iterPlayer->getX(), iterPlayer->getY());
    }

}

void Widget::resizeEvent(QResizeEvent *event)
{
    mView->fitInView(mScene->sceneRect(),Qt::KeepAspectRatio);
}
