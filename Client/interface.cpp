#include "interface.h"
#include "ui_interface.h"
#include<QFile>
#include<QJsonObject>
#include <QJsonArray>
#include<QJsonDocument>
#include <QDebug>
#include <QMainWindow>
#include <QObject>
#include <QTcpSocket>
#include <QArrayData>
#include <QFileDialog>
#include<QTextEdit>



interface::interface(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::interface)
{
    ui->setupUi(this);
}

interface::~interface()
{
    delete ui;
}
