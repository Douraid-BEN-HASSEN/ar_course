#include "interface.h"
#include "ui_interface.h"

interface::interface(QWidget *parent): QMainWindow(parent), ui(new Ui::interface)
{
    ui->setupUi(this);
    Widget *widget = new Widget;
    ui->verticalLayout->addWidget(widget);

    /*
    Qt3DExtras::Qt3DWindow mView;
    Qt3DCore::QEntity *rootEntity = new Qt3DCore::QEntity;
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

    // Camera
    Qt3DRender::QCamera *camera = mView.camera();
    camera->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    camera->setPosition(QVector3D(0, 0, 40.0f));
    camera->setViewCenter(QVector3D(0, 0, 0));

    // For camera controls
    Qt3DExtras::QOrbitCameraController *camController = new Qt3DExtras::QOrbitCameraController(rootEntity);
    camController->setLinearSpeed( 50.0f );
    camController->setLookSpeed( 180.0f );
    camController->setCamera(camera);

    mView.setRootEntity(rootEntity);
    */

}

interface::~interface()
{
    delete ui;
}

