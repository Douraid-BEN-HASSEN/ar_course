#include "Widget3D.h"

Qt3DCore::QEntity* Widget3D::createScene()
{
    // Configuration de la scène + spécification de l'entity racine
    //En soi, un Qt3DCore::QEntity est une coquille vide.
    //Le comportement d'un objet Qt3DCore::QEntity est défini par les objets Qt3DCore::QComponent auxquels il fait référence.
    Qt3DCore::QEntity *rootEntity = new Qt3DCore::QEntity;
    // Rendu Phong Material
    // La classe QDiffuseSpecularMaterial fournit une implémentation par défaut de l'effet d'éclairage phong
    // L'effet d'éclairage phong est basé sur la combinaison de 3 composants d'éclairage ambiant, diffus et spéculaire.
    // Les forces relatives de ces composants sont contrôlées au moyen de leurs coefficients de réflectivité qui sont modélisés comme des triplets RVB :
    Qt3DExtras::QDiffuseSpecularMaterial *material = new Qt3DExtras::QDiffuseSpecularMaterial(rootEntity);

    Qt3DCore::QEntity *m_cuboidEntity = new Qt3DCore::QEntity(rootEntity);

    Qt3DExtras::QCuboidMesh *cuboid = new Qt3DExtras::QCuboidMesh();
    // CuboidMesh Transform
    Qt3DCore::QTransform *cuboidTransform = new Qt3DCore::QTransform();
    cuboidTransform->setScale(4.0f);
    cuboidTransform->setTranslation(QVector3D(5.0f, -4.0f, 0.0f));

    material->setDiffuse(QColor(QRgb(0x665423)));

    //Cuboid
    m_cuboidEntity->addComponent(cuboid);
    m_cuboidEntity->addComponent(material);
    m_cuboidEntity->addComponent(cuboidTransform);

//####################################################################################################
    // Créer le plateau

    return rootEntity;
}

Widget3D::Widget3D(): Qt3DExtras::Qt3DWindow()
{
    Qt3DCore::QEntity *scene = Widget3D::createScene();

    // Camera
    Qt3DRender::QCamera *camera = this->camera();
    camera->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    camera->setPosition(QVector3D(0, 0, 40.0f));
    camera->setViewCenter(QVector3D(0, 0, 0));

    // For camera controls
    Qt3DExtras::QOrbitCameraController *camController = new Qt3DExtras::QOrbitCameraController(scene);
    camController->setLinearSpeed( 50.0f );
    camController->setLookSpeed( 180.0f );
    camController->setCamera(camera);



    connect(Map::getInstance(), SIGNAL(updated()), this, SLOT(updateMap3D()));
    //connect(Properties::getInstance(), SIGNAL(updated()), this, SLOT(updateProperties()));
    //connect(GameMode::getInstance(), SIGNAL(updated()), this, SLOT(updateGameMode()));
        this->setRootEntity(scene);
}

void Widget3D::updateMap3D() {
    qDebug() << "appel updateMap";
    qDebug() << "appel updateMap";
    qDebug() << "appel updateMap";


}
