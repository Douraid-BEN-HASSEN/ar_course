#include "playerGraphics3D.h"


PlayerGraphics3D::PlayerGraphics3D(Player *player, Qt3DCore::QEntity *mScene, QNode *parent): Qt3DCore::QEntity(parent)
{
    this->uuid = player->getUuid();
    //this->pseudo = player->getPseudo();
    this->x = player->getX();
    this->y = player->getY();
    //this->angle = playe        //Qt3DCore::QTransform *obstacleTransform = new Qt3DCore::QTransform();
    //obstacleTransform->setTranslation(QVector3D(iterPlayer->getX()/10, 0.0f, iterPlayer->getY()));
    //playerGraphics3D->addComponent(obstacleTransform);r->getAngle();
    this->_player = player;

    Qt3DExtras::QDiffuseSpecularMaterial *material = new Qt3DExtras::QDiffuseSpecularMaterial(mScene);
    material->setDiffuse(QColor(Qt::yellow));
    this->setParent(mScene);
    //Qt3DExtras::QSphereMesh *sphereMesh = new Qt3DExtras::QSphereMesh;
    //sphereMesh->setRadius(3);
    Qt3DExtras::QCuboidMesh *cuboid = new Qt3DExtras::QCuboidMesh();

    Qt3DCore::QTransform *cuboidTransform = new Qt3DCore::QTransform();
    cuboidTransform->setTranslation(QVector3D(this->x/10, 0.0f ,this->y/10));
    cuboidTransform->setScale(4.0f);
    this->addComponent(material);
    this->addComponent(cuboid);
    this->addComponent(cuboidTransform);
}



void PlayerGraphics3D::updatePlayer3D(Player *player){
    this->x = player->getX();
    this->y = player->getY();

    Qt3DCore::QTransform *obstacleTransform = new Qt3DCore::QTransform();
    obstacleTransform->setTranslation(QVector3D(this->getX()/10, 0.0f, this->getY()/10));

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
