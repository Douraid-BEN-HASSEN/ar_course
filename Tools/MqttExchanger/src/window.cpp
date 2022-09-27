#include "window.h"
#include "ui_window.h"
#include "Mqtt/MqttService.h"

Window::Window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Window)
{
    ui->setupUi(this);

    connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(connection()));
}

Window::~Window()
{
    delete ui;
}

void Window::connection() {
    MqttService::instance()->client->disconnectFromHost();
    MqttService::instance()->client->connectToHost();
}
