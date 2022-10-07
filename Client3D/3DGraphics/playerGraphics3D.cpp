#include "playerGraphics3D.h"
//const QUrl url = QUrl("/home/pierre/Documents/ar_course/Client3D/vehiculeObj/DeLorean.obj");
PlayerGraphics3D::PlayerGraphics3D(Player *player, Qt3DCore::QEntity *mScene, QNode *parent): Qt3DCore::QEntity(parent)
{
    this->uuid = player->getUuid();
    //this->pseudo = player->getPseudo();
    this->x = player->getX();
    this->y = player->getY();
    //this->angle = player->getAngle();
    this->_player = player;

    Qt3DExtras::QDiffuseSpecularMaterial *material = new Qt3DExtras::QDiffuseSpecularMaterial(mScene);
    material->setDiffuse(QColor(Qt::yellow));
    this->setParent(mScene);
    Qt3DExtras::QCuboidMesh *cuboid = new Qt3DExtras::QCuboidMesh();

    //Qt3DRender::QMesh *dolorean = new Qt3DRender::QMesh();
    //dolorean->setSource(url);

    Qt3DCore::QTransform *cuboidTransform = new Qt3DCore::QTransform();
    cuboidTransform->setTranslation(QVector3D(this->x, 0.0f ,this->y));
    cuboidTransform->setScale(4.0f);

    this->addComponent(material);
    //this->addComponent(dolorean);
    this->addComponent(cuboid);
    this->addComponent(cuboidTransform);
}


void PlayerGraphics3D::updatePlayer3D(Player *player){
    this->x = player->getX();
    this->y = player->getY();

    Qt3DCore::QTransform *obstacleTransform = new Qt3DCore::QTransform();
    obstacleTransform->setTranslation(QVector3D(this->getX(), 0.0f, this->getY()));

    if(!this->components().empty()){
        this->removeComponent(this->components().at(2));
        this->addComponent(obstacleTransform);
    }
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

qreal PlayerGraphics3D::getY()        //painter->drawEllipse(0,0,this->heigth, this->width);
{
    return y;
}
