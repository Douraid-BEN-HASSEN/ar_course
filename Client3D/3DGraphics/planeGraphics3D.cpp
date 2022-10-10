#include "planeGraphics3D.h"

#include <Qt3DExtras/QPlaneMesh>
#include <Qt3DCore/QTransform>
#include <Qt3DCore/QEntity>

PlaneGraphics3D::PlaneGraphics3D(Qt3DCore::QNode *parent): Qt3DCore::QEntity(parent)
    , m_mesh(new Qt3DExtras::QPlaneMesh())
    , m_transform(new Qt3DCore::QTransform())
    , m_material(new Qt3DExtras::QPhongMaterial())
{
    addComponent(m_mesh);
    addComponent(m_transform);
    addComponent(m_material);

}
PlaneGraphics3D::~PlaneGraphics3D()
{
}

Qt3DExtras::QPlaneMesh* PlaneGraphics3D::mesh() const
{
    return m_mesh;
}
