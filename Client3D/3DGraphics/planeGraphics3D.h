#ifndef PLANEGRAPHICS3D_H
#define PLANEGRAPHICS3D_H
#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>
#include <Qt3DExtras/QPlaneMesh>
#include <Qt3DExtras/QPhongMaterial>

#include <Qt3DExtras/QPlaneMesh>
#include <Qt3DCore/QTransform>
#include <Qt3DCore/QEntity>
#include <QDiffuseSpecularMaterial>

#include <Qt3DRender/QPointLight>


class PlaneGraphics3D: public Qt3DCore::QEntity
{
    Q_OBJECT
public:
    PlaneGraphics3D(Qt3DCore::QEntity *rootEntity, Qt3DCore::QNode *parent = nullptr);
          //~PlaneGraphics3D();
       //Qt3DExtras::QPlaneMesh *mesh() const;

       //Qt3DExtras::QPlaneMesh *m_mesh;
       //Qt3DCore::QTransform *m_transform;
       //Qt3DExtras::QPhongMaterial *m_material;


};

#endif // PLANEGRAPHICS3D_H
