#include "roadgraphics3d.h"

RoadGraphics3D::RoadGraphics3D( Checkpoint *checkpoint1, Checkpoint *checkpoint2, Qt3DCore::QEntity *mScene, QNode *parent): Qt3DCore::QEntity(parent)
{
        this->id = checkpoint1->getId();
        this->x = checkpoint1->getX();
        this->y = checkpoint1->getY();

        Qt3DExtras::QDiffuseSpecularMaterial *material = new Qt3DExtras::QDiffuseSpecularMaterial(mScene);
        material->setDiffuse(QColor(Qt::blue));

        this->setParent(mScene);

        int width = checkpoint1->getX() > checkpoint2->getX() ? checkpoint1->getX() - checkpoint2->getX() : checkpoint2->getX() - checkpoint1->getX();
        int height = checkpoint1->getY() > checkpoint2->getY() ? checkpoint1->getY() - checkpoint2->getY() : checkpoint2->getY() - checkpoint1->getY();

        Qt3DExtras::QCuboidMesh *cuboidMesh = new Qt3DExtras::QCuboidMesh;
        cuboidMesh->setXExtent(width);
        cuboidMesh->setYExtent(height);



        Qt3DCore::QTransform *cuboidTransform = new Qt3DCore::QTransform();
        cuboidTransform->setTranslation(QVector3D(this->x, this->y, 0.0f));

        this->addComponent(material);
        this->addComponent(cuboidMesh);
        this->addComponent(cuboidTransform);
}

