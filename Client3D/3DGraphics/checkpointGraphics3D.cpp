#include "checkpointGraphics3D.h"

qreal CheckpointGraphics3D::radiusCheckpoint = 50;


CheckpointGraphics3D::CheckpointGraphics3D(Checkpoint *checkpoint, Qt3DCore::QEntity *mScene, QNode *parent): Qt3DCore::QEntity(parent)
{
    qDebug() << "CheckpointGraphics3D " << mScene;
    this->id = checkpoint->getId();
    this->x = checkpoint->getX();
    this->y = checkpoint->getY();

    Qt3DExtras::QDiffuseSpecularMaterial *material = new Qt3DExtras::QDiffuseSpecularMaterial(mScene);
    material->setDiffuse(QColor(Qt::green));

    this->setParent(mScene);

    //Qt3DExtras::QSphereMesh *sphereMesh = new Qt3DExtras::QSphereMesh;
    //sphereMesh->setRadius(radiusCheckpoint);
    Qt3DExtras::QCylinderMesh *cylindreMesh = new Qt3DExtras::QCylinderMesh;
    cylindreMesh->setRadius(radiusCheckpoint);
    cylindreMesh->setLength(1);

    Qt3DCore::QTransform *cylindreTransform = new Qt3DCore::QTransform();
    cylindreTransform->setTranslation(QVector3D(this->x, 0.0f ,this->y));

    this->addComponent(material);
    this->addComponent(cylindreMesh);
    this->addComponent(cylindreTransform);

    // text
    auto *text2D = new Qt3DExtras::QText2DEntity();
   text2D->setParent(mScene);
   text2D->setFont(QFont("Times", 3, QFont::Bold));
   text2D->setHeight(5);
   text2D->setWidth(QString::number(checkpoint->getId()).length() * 3);
   text2D->setText(QString::number(checkpoint->getId()));

   text2D->setColor(Qt::green);
   auto *textTransform = new Qt3DCore::QTransform(text2D);
   textTransform->setScale(20);
   textTransform->setTranslation(QVector3D(this->x-((20*text2D->width())/3), 5.0 ,this->y));
   //textTransform->setRotationY(50.0); //angle
   text2D->addComponent(textTransform);
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

