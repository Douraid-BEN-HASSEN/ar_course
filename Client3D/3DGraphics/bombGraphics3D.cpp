

#include "bombGraphics3D.h"
// Valeur par défaut
qreal BombGraphics3D::bombRadius = 10;

BombGraphics3D::BombGraphics3D(Item *bomb, Qt3DCore::QEntity *mScene, QNode *parent): Qt3DCore::QEntity(parent)
{
    this->x = bomb->getX();
    this->y = bomb->getY();
    qDebug() << "bomb x= " << x ;
    qDebug() << "bomb y = " << y ;

    this->setParent(mScene);

    Qt3DExtras::QDiffuseSpecularMaterial *material = new Qt3DExtras::QDiffuseSpecularMaterial(mScene);
    material->setDiffuse(QColor(Qt::red));

    Qt3DExtras::QCylinderMesh *cylindreMesh = new Qt3DExtras::QCylinderMesh;
    cylindreMesh->setRadius(bombRadius);
    cylindreMesh->setLength(1);

    Qt3DCore::QTransform *cylindreTransform = new Qt3DCore::QTransform();
    cylindreTransform->setTranslation(QVector3D(this->x, 0.0f ,this->y));

    this->addComponent(material);
    this->addComponent(cylindreMesh);
    this->addComponent(cylindreTransform);
}

void BombGraphics3D::updateBomb3D(Item *bomb){
    this->x = bomb->getX();
    this->y = bomb->getY();

    Qt3DCore::QTransform *bombTransform = new Qt3DCore::QTransform();
    bombTransform->setTranslation(QVector3D(this->x, 0.0f ,this->y));

     if(!this->components().empty()){
         this->removeComponent(this->components().at(2));
         this->addComponent(bombTransform);
     }
}
