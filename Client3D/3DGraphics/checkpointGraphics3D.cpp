#include "checkpointGraphics3D.h"

qreal CheckpointGraphics3D::radiusCheckpoint = 50;


CheckpointGraphics3D::CheckpointGraphics3D(Checkpoint *checkpoint, Qt3DCore::QEntity *mScene, QNode *parent): Qt3DCore::QEntity(parent)
{
    this->id = checkpoint->getId();
    this->x = checkpoint->getX();
    this->y = checkpoint->getY();

    Qt3DExtras::QDiffuseSpecularMaterial *material = new Qt3DExtras::QDiffuseSpecularMaterial(mScene);
    material->setDiffuse(QColor(Qt::green));
    Qt3DCore::QEntity *obstacleEntity = new Qt3DCore::QEntity(mScene);
    Qt3DExtras::QSphereMesh *sphereMesh = new Qt3DExtras::QSphereMesh;
    sphereMesh->setRadius(3);
    Qt3DCore::QTransform *shpereTransform = new Qt3DCore::QTransform();
    shpereTransform->setTranslation(QVector3D(this->x/10, 0.0f ,this->y/10));

    obstacleEntity->addComponent(material);
    obstacleEntity->addComponent(sphereMesh);
    obstacleEntity->addComponent(shpereTransform);

}

qreal CheckpointGraphics3D::getId()
{
    return id;
}

qreal CheckpointGraphics3D::getX()
{
    return x;
}

qreal CheckpointGraphics3D::getY()        //painter->drawEllipse(0,0,this->heigth, this->width);
{
    return y;
}

qreal CheckpointGraphics3D::getRadius()
{
    return radiusCheckpoint;
}

