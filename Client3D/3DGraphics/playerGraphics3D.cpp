#include "playerGraphics3D.h"
//const QUrl url = QUrl("/home/pierre/Documents/ar_course/Client3D/vehiculeObj/DeLorean.obj");
//QUrl car_path = QStringLiteral("qrc:/vehicule.qrc/DeLorean.obj");

PlayerGraphics3D::PlayerGraphics3D(Player *player, Qt3DCore::QEntity *mScene, QNode *parent): Qt3DCore::QEntity(parent)
{
    this->uuid = player->getUuid();
    this->x = player->getX();
    this->y = player->getY();
    this->_player = player;

    Vehicle *veh = Properties::getInstance()->vehicleOptions->value(player->getVehicule());
    if (veh != nullptr){
        this->heigth = veh->getHeight();
        this->width = veh->getWidth();
    }

    this->setParent(mScene);

    Qt3DExtras::QDiffuseSpecularMaterial *material = new Qt3DExtras::QDiffuseSpecularMaterial(mScene);
    material->setDiffuse(QColor(Qt::yellow));
    material->setAmbient(QColorConstants::Yellow);
    material->setSpecular(QColorConstants::Yellow);
    material->setShininess(10.0f);

    Qt3DRender::QMesh *cuboid = new Qt3DRender::QMesh();
    cuboid->setSource(QStringLiteral("qrc:/Car.obj"));
    //cuboid->setGeometry()

    Qt3DCore::QTransform *cuboidTransform = new Qt3DCore::QTransform();
    cuboidTransform->setTranslation(QVector3D(this->x, 0.0f ,this->y));
    cuboidTransform->setScale3D(QVector3D(this->width, this->width, this->heigth));
    cuboidTransform->setRotationY(qRadiansToDegrees(player->getAngle()) + 90);
    this->addComponent(material);
    this->addComponent(cuboid);
    this->addComponent(cuboidTransform);
}


void PlayerGraphics3D::updatePlayer3D(Player *player){
    this->x = player->getX();
    this->y = player->getY();

    Qt3DCore::QTransform *palyerTransform = new Qt3DCore::QTransform();
    palyerTransform->setTranslation(QVector3D(this->getX(), 0.0f, this->getY()));

    palyerTransform->setScale3D(QVector3D(width, width, heigth));

    palyerTransform->setRotationY(qRadiansToDegrees(player->getAngle()) + 90);

    if(!this->components().empty()){
        this->removeComponent(this->components().at(2));
        this->addComponent(palyerTransform);
    }
}

void PlayerGraphics3D::followCameraPlayer(Player *playerCamFocus, Qt3DRender::QCamera *camerA){

    int dist = 150 + heigth;
    float camX = playerCamFocus->getX() - cos(-playerCamFocus->getAngle()) * dist;
    float camY = playerCamFocus->getY() - sin(-playerCamFocus->getAngle()) * dist;
    camerA->setPosition(QVector3D(camX, 40, camY));
    camerA->setViewCenter( QVector3D(playerCamFocus->getX(), 40, playerCamFocus->getY()));
}

Player* PlayerGraphics3D::getPlayer()
{
    return _player;
}

QString PlayerGraphics3D::getUuid()
{
    return uuid;
}

qreal PlayerGraphics3D::getX()
{
    return x;
}

qreal PlayerGraphics3D::getY()
{
    return y;
}
