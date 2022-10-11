#include "rocketGraphics3D.h"
// Valeur par défaut
qreal RocketGraphics3D::rocketRadius = 10;

RocketGraphics3D::RocketGraphics3D(Item *rocket, Qt3DCore::QEntity *mScene, QNode *parent): Qt3DCore::QEntity(parent)
{
    this->x = rocket->getX();
    this->y = rocket->getY();

    this->setParent(mScene);

    Qt3DExtras::QDiffuseSpecularMaterial *material = new Qt3DExtras::QDiffuseSpecularMaterial(mScene);
    material->setDiffuse(QColor(Qt::black));

    Qt3DExtras::QSphereMesh *sphereMesh = new Qt3DExtras::QSphereMesh;
    sphereMesh->setRadius(rocketRadius);

    Qt3DCore::QTransform *cylindreTransform = new Qt3DCore::QTransform();
    cylindreTransform->setTranslation(QVector3D(this->x, 0.0f ,this->y));

    this->addComponent(material);
    this->addComponent(sphereMesh);
    this->addComponent(cylindreTransform);
}
