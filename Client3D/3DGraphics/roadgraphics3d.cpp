#include "roadgraphics3d.h"

RoadGraphics3D::RoadGraphics3D( Checkpoint *checkpoint1, Checkpoint *checkpoint2, Qt3DCore::QEntity *mScene, QNode *parent): Qt3DCore::QEntity(parent)
{
    this->drawLine({ (const float)checkpoint1->getX(), 0, (const float)checkpoint1->getY() },
                   { (const float)checkpoint2->getX(), 0, (const float)checkpoint2->getY() },
                   Qt::blue,
                   mScene);
    this->drawLine3D(checkpoint1, checkpoint2, mScene);



}

void RoadGraphics3D::drawLine(const QVector3D& start, const QVector3D& end, const QColor& color, Qt3DCore::QEntity *_rootEntity)
{
    auto *geometry = new Qt3DRender::QGeometry(_rootEntity);

    QByteArray bufferBytes;
    bufferBytes.resize(3 * 2 * sizeof(float));
    float *positions = reinterpret_cast<float*>(bufferBytes.data());
    *positions++ = start.x();
    *positions++ = start.y();
    *positions++ = start.z();
    *positions++ = end.x();
    *positions++ = end.y();
    *positions++ = end.z();

    auto *buf = new Qt3DRender::QBuffer(geometry);
    buf->setData(bufferBytes);

    auto *positionAttribute = new Qt3DRender::QAttribute(geometry);
    positionAttribute->setName(Qt3DRender::QAttribute::defaultPositionAttributeName());
    positionAttribute->setVertexBaseType(Qt3DRender::QAttribute::Float);
    positionAttribute->setVertexSize(3);
    positionAttribute->setAttributeType(Qt3DRender::QAttribute::VertexAttribute);
    positionAttribute->setBuffer(buf);
    positionAttribute->setByteStride(3 * sizeof(float));
    positionAttribute->setCount(2);
    geometry->addAttribute(positionAttribute);

    QByteArray indexBytes;
    indexBytes.resize(2 * sizeof(unsigned int));
    unsigned int *indices = reinterpret_cast<unsigned int*>(indexBytes.data());
    *indices++ = 0;
    *indices++ = 1;

    auto *indexBuffer = new Qt3DRender::QBuffer(geometry);
    indexBuffer->setData(indexBytes);

    auto *indexAttribute = new Qt3DRender::QAttribute(geometry);
    indexAttribute->setVertexBaseType(Qt3DRender::QAttribute::UnsignedInt);
    indexAttribute->setAttributeType(Qt3DRender::QAttribute::IndexAttribute);
    indexAttribute->setBuffer(indexBuffer);
    indexAttribute->setCount(2);
    geometry->addAttribute(indexAttribute);

    auto *line = new Qt3DRender::QGeometryRenderer(_rootEntity);
    line->setGeometry(geometry);
    line->setPrimitiveType(Qt3DRender::QGeometryRenderer::Lines);
    auto *material = new Qt3DExtras::QPhongMaterial(_rootEntity);
    material->setAmbient(color);

    auto *lineEntity = new Qt3DCore::QEntity(_rootEntity);
    lineEntity->addComponent(line);
    lineEntity->addComponent(material);
}

void RoadGraphics3D::drawLine3D(Checkpoint *checkpoint1, Checkpoint *checkpoint2, Qt3DCore::QEntity *mScene)
{
    float angle = 0;


    if(checkpoint1->getId() == 1) {
        angle = QLineF(QPointF(checkpoint1->getX(), checkpoint1->getY()),
                                             QPointF(checkpoint2->getX(), checkpoint2->getY())).angle();

        qDebug() << "ANGLE ===> " << angle;
    }


    int a = checkpoint1->getX() - checkpoint2->getX();
    int b = checkpoint1->getY() - checkpoint2->getY();

    float distance = std::sqrt(a*a+b*b);

    PlaneGraphics3D *planeEntity = new PlaneGraphics3D(mScene);

   planeEntity->mesh()->setHeight(distance);
   planeEntity->mesh()->setWidth(100.0f);

   planeEntity->m_transform->setTranslation(QVector3D(checkpoint1->getX(), 0, checkpoint1->getY()));
   planeEntity->m_transform->setRotationY(angle);

   planeEntity->m_material->setDiffuse(QColor(Qt::red));

}
