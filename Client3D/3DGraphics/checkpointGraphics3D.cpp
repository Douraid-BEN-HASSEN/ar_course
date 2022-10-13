#include "checkpointGraphics3D.h"
// Valeur par défaut
qreal CheckpointGraphics3D::radiusCheckpoint = 50;


CheckpointGraphics3D::CheckpointGraphics3D(Checkpoint *checkpoint,
                                           Qt3DCore::QEntity *mScene,
                                           int mapIndex,
                                           QNode *parent): Qt3DCore::QEntity(parent)
{
    qDebug() << "CheckpointGraphics3D " << mScene;
    this->id = checkpoint->getId();
    this->x = checkpoint->getX();
    this->y = checkpoint->getY();

    this->setParent(mScene);

    Qt3DExtras::QDiffuseSpecularMaterial *material = new Qt3DExtras::QDiffuseSpecularMaterial(mScene);
    material->setDiffuse(QColor(Qt::green));
    material->setAmbient(QColorConstants::Green);

    Qt3DExtras::QCylinderMesh *cylindreMesh = new Qt3DExtras::QCylinderMesh;
    cylindreMesh->setRadius(radiusCheckpoint);
    cylindreMesh->setLength(1);

    Qt3DCore::QTransform *cylindreTransform = new Qt3DCore::QTransform();
    cylindreTransform->setTranslation(QVector3D(this->x, 0.0f ,this->y));

    this->addComponent(material);
    this->addComponent(cylindreMesh);
    this->addComponent(cylindreTransform);

    qDebug() << "ID=> " << checkpoint->getId();
    qDebug() << "index=> " << mapIndex;

    // text
    this->text2D = new Qt3DExtras::QText2DEntity();
    this->text2D->setParent(mScene);
    this->text2D->setFont(QFont("Times", 3, QFont::Bold));
    this->text2D->setHeight(5);
    this->text2D->setWidth(QString::number(mapIndex).length() * 3);
    this->text2D->setText(QString::number(mapIndex));
    this->text2D->setColor(Qt::green);
    this->textTransform = new Qt3DCore::QTransform();
    this->textTransform->setScale(10);

    this->textTransform->setTranslation(QVector3D(this->x, 0,this->y-10));
    //this->textTransform->setRotationY(50);
    this->text2D->addComponent(this->textTransform);

}

void CheckpointGraphics3D::updateCheckpoint3D(Checkpoint *checkpoint, Player *playerCamFocus){
   this->x =  checkpoint->getX();
   this->y = checkpoint->getY();

   Qt3DCore::QTransform *checkpointTransform = new Qt3DCore::QTransform();
   checkpointTransform->setTranslation(QVector3D(this->x, 0.0f ,this->y));

   this->textTransform->setRotationY((playerCamFocus->getAngle() * 180/3.14)-90.0);
   this->text2D->removeComponent(this->text2D->components().at(0));
   this->text2D->addComponent(this->textTransform);

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

qreal CheckpointGraphics3D::getY()
{
    return y;
}

qreal CheckpointGraphics3D::getRadius()
{
    return radiusCheckpoint;
}

