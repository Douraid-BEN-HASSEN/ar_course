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
    this->angle = obstacle->getAngle();

    Qt3DExtras::QDiffuseSpecularMaterial *material = new Qt3DExtras::QDiffuseSpecularMaterial(mScene);
    material->setDiffuse(QColor(Qt::blue));
    this->addComponent(material);
    this->setParent(mScene);

    if((int)this->getId() % 2 == 1){
        Qt3DExtras::QCuboidMesh *cuboidMesh = new Qt3DExtras::QCuboidMesh();
        cuboidMesh->setXExtent(heigth);
        cuboidMesh->setYExtent(width);
        cuboidMesh->setZExtent(width);
        Qt3DCore::QTransform *cuboidTransform = new Qt3DCore::QTransform();
        // X Y Z
        cuboidTransform->setTranslation(QVector3D(this->x, 0.0f ,this->y));
        cuboidTransform->setRotationY(qRadiansToDegrees(angle));
        this->addComponent(cuboidMesh);
        this->addComponent(cuboidTransform);
    }else{
        Qt3DExtras::QCylinderMesh *cylindreMesh = new Qt3DExtras::QCylinderMesh;
        cylindreMesh->setRadius(radius);
        cylindreMesh->setLength(width);
        Qt3DCore::QTransform *cylindreTransform = new Qt3DCore::QTransform();
        cylindreTransform->setTranslation(QVector3D(this->x, 0.0f ,this->y));
        cylindreTransform->setRotationY(qRadiansToDegrees(angle));
        this->addComponent(cylindreMesh);
        this->addComponent(cylindreTransform);
    }
}

void ObstacleGraphics3D::updateObstacle3D(Obstacle *obstacle){
   this->x =  obstacle->getX();
   this->y = obstacle->getY();

   Qt3DCore::QTransform *obstacleTransform = new Qt3DCore::QTransform();
   obstacleTransform->setTranslation(QVector3D(this->x, 0.0f ,this->y));
   obstacleTransform->setRotationY(qRadiansToDegrees(angle));

    if(!this->components().empty()){
        this->removeComponent(this->components().at(2));
        this->addComponent(obstacleTransform);
    }
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

qreal ObstacleGraphics3D::getAngle()
{
    return angle;
}

