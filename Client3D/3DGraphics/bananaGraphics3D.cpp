#include "bananaGraphics3D.h"
// Valeur par défaut
qreal BananaGraphics3D::bananaRadius = 10;

BananaGraphics3D::BananaGraphics3D(Item *banana, Qt3DCore::QEntity *mScene, QNode *parent): Qt3DCore::QEntity(parent)
{
    this->x = banana->getX();
    this->y = banana->getY();
    this->uuid = banana->getUuid();

    this->setParent(mScene);

    Qt3DExtras::QDiffuseSpecularMaterial *material = new Qt3DExtras::QDiffuseSpecularMaterial(mScene);
    material->setDiffuse(QColor(Qt::yellow));

    Qt3DExtras::QSphereMesh *sphereMesh = new Qt3DExtras::QSphereMesh;
    sphereMesh->setRadius(bananaRadius);

    Qt3DCore::QTransform *cylindreTransform = new Qt3DCore::QTransform();
    cylindreTransform->setTranslation(QVector3D(this->x, 0.0f ,this->y));

    this->addComponent(material);
    this->addComponent(sphereMesh);
    this->addComponent(cylindreTransform);
}


void BananaGraphics3D::updateBanana3D(Item *banana){
    this->x =  banana->getX();
    this->y = banana->getY();

    Qt3DCore::QTransform *bananeTransform = new Qt3DCore::QTransform();
    bananeTransform->setTranslation(QVector3D(this->x, 0.0f ,this->y));

     if(!this->components().empty()){
         this->removeComponent(this->components().at(2));
         this->addComponent(bananeTransform);
     }
}

QString BananaGraphics3D::getUuid()
{
    return uuid;
}

qreal BananaGraphics3D::getX()
{
    return x;
}

qreal BananaGraphics3D::getY()
{
    return y;
}
