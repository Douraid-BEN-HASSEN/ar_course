#include "obstacleGraphics3D.h"

#include <QBrush>

qreal ObstacleGraphics3D::heigth = 100;
qreal ObstacleGraphics3D::width = 100;
qreal ObstacleGraphics3D::radius = 50;

ObstacleGraphics3D::ObstacleGraphics3D(Obstacle *obstacle, Qt3DCore::QEntity *mScene, QNode *parent): Qt3DCore::QEntity(parent)
{
    this->id = obstacle->getId();
    this->x = obstacle->getX();
    this->y = obstacle->getY();

    Qt3DExtras::QDiffuseSpecularMaterial *material = new Qt3DExtras::QDiffuseSpecularMaterial(mScene);
    material->setDiffuse(QColor(Qt::blue));
    Qt3DCore::QEntity *obstacleEntity = new Qt3DCore::QEntity(mScene);

    if((int)this->getId() % 2 == 1){
        Qt3DExtras::QSphereMesh *sphereMesh = new Qt3DExtras::QSphereMesh;
        sphereMesh->setRadius(3);
        Qt3DCore::QTransform *shpereTransform = new Qt3DCore::QTransform();
        shpereTransform->setTranslation(QVector3D(this->x/10, 0.0f ,this->y/10));

        obstacleEntity->addComponent(sphereMesh);
        obstacleEntity->addComponent(shpereTransform);

    }else{

        Qt3DExtras::QCuboidMesh *cuboidMesh = new Qt3DExtras::QCuboidMesh();
        Qt3DCore::QTransform *cuboidTransform = new Qt3DCore::QTransform();
        cuboidTransform->setScale(4.0f);
        // X Y Z
        //cuboidTransform->setTranslation(QVector3D(5.0, -4.0f, 0.0f));
        cuboidTransform->setTranslation(QVector3D(this->x/10, 0.0f ,this->y/10));

        obstacleEntity->addComponent(cuboidMesh);
        obstacleEntity->addComponent(cuboidTransform);
    }
    obstacleEntity->addComponent(material);

}



qreal ObstacleGraphics3D::getId()
{
    return id;
}

qreal ObstacleGraphics3D::getX()
{
    return x;
}

qreal ObstacleGraphics3D::getY()
{
    return y;
}

qreal ObstacleGraphics3D::getHeigth()
{
    return heigth;
}
qreal ObstacleGraphics3D::getWidth()
{
    return width;
}

qreal ObstacleGraphics3D::getRadius()
{
    return radius;
}

