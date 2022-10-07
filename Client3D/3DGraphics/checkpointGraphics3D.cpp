#include "checkpointGraphics3D.h"

qreal CheckpointGraphics3D::radiusCheckpoint = 50;


CheckpointGraphics3D::CheckpointGraphics3D(Checkpoint *checkpoint, Qt3DCore::QEntity *mScene, QNode *parent): Qt3DCore::QEntity(parent)
{
    this->id = checkpoint->getId();
    this->x = checkpoint->getX();
    this->y = checkpoint->getY();

    Qt3DExtras::QDiffuseSpecularMaterial *material = new Qt3DExtras::QDiffuseSpecularMaterial(mScene);
    material->setDiffuse(QColor(Qt::green));

    this->setParent(mScene);

    Qt3DExtras::QSphereMesh *sphereMesh = new Qt3DExtras::QSphereMesh;
    sphereMesh->setRadius(3);
    Qt3DCore::QTransform *shpereTransform = new Qt3DCore::QTransform();
    shpereTransform->setTranslation(QVector3D(this->x, 0.0f ,this->y));

    this->addComponent(material);
    this->addComponent(sphereMesh);
    this->addComponent(shpereTransform);

}

void CheckpointGraphics3D::updateCheckpoint3D(Checkpoint *checkpoint){
   this->x =  checkpoint->getX();
   this->y = checkpoint->getY();

   Qt3DCore::QTransform *checkpointTransform = new Qt3DCore::QTransform();
   checkpointTransform->setTranslation(QVector3D(this->x, 0.0f ,this->y));

    if(!this->components().empty()){
        this->removeComponent(this->components().at(2));
        this->addComponent(checkpointTransform);
    }
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

