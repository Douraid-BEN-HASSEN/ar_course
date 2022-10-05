#include "obstacleGraphics3D.h"
#include "Kart/Game/Properties.h"

#include <QBrush>

qreal ObstacleGraphics3D::heigth = 100;
qreal ObstacleGraphics3D::width = 100;
qreal ObstacleGraphics3D::radius = 50;

ObstacleGraphics3D::ObstacleGraphics3D(QNode *parent): Qt3DCore::QEntity(parent)
{

}

ObstacleGraphics3D::ObstacleGraphics3D(Obstacle *obstacle, Qt3DCore::QEntity *mScene, QNode *parent): Qt3DCore::QEntity(parent)
{
    this->id = obstacle->getId();
    this->x = obstacle->getX();
    this->y = obstacle->getY();

    Qt3DExtras::QDiffuseSpecularMaterial *material = new Qt3DExtras::QDiffuseSpecularMaterial(mScene);

    Qt3DCore::QEntity *m_cuboidEntity = new Qt3DCore::QEntity(mScene);
    Qt3DExtras::QCuboidMesh *cuboid = new Qt3DExtras::QCuboidMesh();
    // CuboidMesh Transform
    Qt3DCore::QTransform *cuboidTransform = new Qt3DCore::QTransform();
    cuboidTransform->setScale(4.0f);
    // X Y Z
    //cuboidTransform->setTranslation(QVector3D(5.0, -4.0f, 0.0f));
    cuboidTransform->setTranslation(QVector3D(this->x/10, 0.0f ,this->y/10));

    material->setDiffuse(QColor(QRgb(0x665423)));

    m_cuboidEntity->addComponent(cuboid);
    m_cuboidEntity->addComponent(material);
    m_cuboidEntity->addComponent(cuboidTransform);

    //

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

/*
QRectF ObstacleGraphics3D::boundingRect() const
{
    if((int)this->id % 2 == 1){
        return QRectF(-this->heigth/2, -this->width/2,this->heigth,this->width);
    } else {
        return QRectF(-this->heigth/2, -this->width/2,this->radius*2,this->radius*2);
    }
}

void ObstacleGraphics3D::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::blue);

    if((int)this->getId() % 2 == 1){
        painter->drawRect(boundingRect());
    } else {
         painter->drawEllipse(boundingRect());
    }

    painter->setPen(Qt::black);
    painter->drawText(0,0,QString::number(this->getId()));

}
*/

