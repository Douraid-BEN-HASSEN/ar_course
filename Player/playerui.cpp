#include "playerui.h"
#include <QVBoxLayout>

void PlayerUi::keyPressEvent(QKeyEvent *key){
    switch(key->key()) {
    case Qt::Key_Z:
        this->catchKeyUp();
    break;
    case Qt::Key_Q:
        this->catchKeyLeft();
    break ;
    case Qt::Key_S:
        this->catchKeyDown();
    break ;
    case Qt::Key_D:
        this->catchKeyRight();
    break ;
    case Qt::Key_1:
        this->catchActionKey(1);
    break ;
    case Qt::Key_2:
        this->catchActionKey(2);
    break ;
    case Qt::Key_3:
        this->catchActionKey(3);
    break ;
    case Qt::Key_4:
        this->catchActionKey(4);
    break ;
    }
    this->updateLabel();

}

void PlayerUi::catchKeyUp() {
    qDebug() << "Catch key up" ;
    this->power++ ;
    this->makeMqttMessage(0 , this->power , 0 );

}

void PlayerUi::catchKeyDown() {
    qDebug() << "Catch key down" ;
    this->power--;
    this->makeMqttMessage(0 , this->power , 0 );
}

void PlayerUi::catchActionKey(int idKey)
{
    qDebug() << "Catch action key id : " << idKey ;
    this->makeMqttMessage(0 , this->power , idKey );
}

void PlayerUi::makeMqttMessage(int angle, int power, int keyAction)
{
    qDebug() << "makeMqttMessage angle : " << angle << " power : " << power << " keyAction : " << keyAction ;

    QString topic = "/player/control" ;

    //Make json object
    QJsonObject messageJsonObject ;
    messageJsonObject.insert("uuid" , this->uuid);
    messageJsonObject.insert("angle" , angle);
    messageJsonObject.insert("power" , power);
    QJsonObject messageJsonButtonsObject ;
    messageJsonButtonsObject.insert("banana" , keyAction == 1 ? true : false);
    messageJsonButtonsObject.insert("bomb" , keyAction == 2 ? true : false);
    messageJsonButtonsObject.insert("rocket" , keyAction == 3 ? true : false);
    messageJsonObject.insert("buttons" , messageJsonButtonsObject);
    QJsonDocument doc(messageJsonObject);
    QString strJson(doc.toJson(QJsonDocument::Compact));
    QByteArray paquet ;
    paquet.push_back(strJson.toUtf8());

    qDebug() << strJson ;
}

void PlayerUi::updateLabel()
{
    this->labelAngle->setText("<h1> Angle : " + QString::number(this->angle) + " </h1> ");
    this->labelPower->setText("<h1> Power : " + QString::number(this->power) + " </h1> ");
}

void PlayerUi::catchKeyLeft() {
    qDebug() << "Catch key left" ;
    if (this->angle == 0)
        this->angle = 270;
    else
        this->angle -= 90 ;
    this->makeMqttMessage(-90 , this->power , 0 );
}

void PlayerUi::catchKeyRight() {
    qDebug() << "Catch key right" ;
    if (this->angle == 270)
        this->angle = 0 ;
    else
        this->angle += 90 ;
    this->makeMqttMessage(+90 , this->power , 0 );
}


PlayerUi::PlayerUi(QWidget *parent)
    : QWidget(parent)
{
    qDebug() << "constructor" ;
    this->angle = 180 ;
    this->power = 0 ;
    this->uuid = QUuid::createUuid().toString();
    this->labelPower = new QLabel("<h1> Power : " + QString::number(this->power) + " </h1>") ;
    this->labelAngle = new QLabel("<h1> Angle : " + QString::number(this->angle) + " </h1> ") ;
    this->mainLayout = new QVBoxLayout ;
    this->mainLayout->addWidget(this->labelPower);
    this->mainLayout->addWidget(this->labelAngle);

    this->setLayout(mainLayout);

    //Modale pseudo

}

PlayerUi::~PlayerUi()
{
    qDebug() << "Destructeur" ;
}


