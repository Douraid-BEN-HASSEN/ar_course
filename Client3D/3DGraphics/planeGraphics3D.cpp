#include "planeGraphics3D.h"


PlaneGraphics3D::PlaneGraphics3D(Qt3DCore::QEntity *rootEntity, Qt3DCore::QNode *parent): Qt3DCore::QEntity(parent)
{

    Qt3DExtras::QDiffuseSpecularMaterial *material = new Qt3DExtras::QDiffuseSpecularMaterial(rootEntity);
    material->setDiffuse(QColor(Qt::gray));
    material->setAmbient(QColor(Qt::gray));
    material->shininess();

    Qt3DRender::QPointLight *light = new Qt3DRender::QPointLight(rootEntity);
    light->setColor("white");
    light->setIntensity(30);

    this->setParent(rootEntity);

    Qt3DExtras::QPlaneMesh *planeMesh = new Qt3DExtras::QPlaneMesh();
    planeMesh->setHeight(2000);
    planeMesh->setWidth(2000);

    Qt3DCore::QTransform *planeTransform = new Qt3DCore::QTransform();
    planeTransform->setTranslation(QVector3D(0.0f, 0.0f ,0.0f));

    this->addComponent(material);
    this->addComponent(planeMesh);
    this->addComponent(planeTransform);
    this->addComponent(light);

}
