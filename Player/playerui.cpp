#include "playerui.h"
#include <QVBoxLayout>

//to do :
// changer le layout
// ajouter le code d'alexis
// envoyer du mqtt
//améliorer le visuel ( plus tard ça  )

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

void PlayerUi::buttonPlayPressed()
{
    qDebug() << "button clicked" ;

    //Make json file for register
    QJsonObject messageJsonObject ;
    messageJsonObject.insert("uuid" , this->uuid);
    messageJsonObject.insert("pseudo" , this->lineEditPseudo->text());
    messageJsonObject.insert("controller" , this->comboBoxController->currentText());
    messageJsonObject.insert("vehicle" , this->comboBoxVehicle->currentText());
    messageJsonObject.insert("team" , this->comboBoxTeam->currentText() == "No team" ? "null" : this->comboBoxTeam->currentText());
    QJsonDocument doc(messageJsonObject);
    QString strJson(doc.toJson(QJsonDocument::Compact));
    QByteArray paquet ;
    paquet.push_back(strJson.toUtf8());
    qDebug() << strJson ;
}

void PlayerUi::catchKeyUp() {
    qDebug() << "Catch key up" ;
    if (this->power != 100)
        this->power++ ;
    this->makeMqttMessage(0 , this->power , 0 );

}

void PlayerUi::catchKeyDown() {
    qDebug() << "Catch key down" ;
    if (this->power != -100)
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
    messageJsonObject.insert("power" , this->power);
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

    //Make initial modale

    this->initialLayout = new QVBoxLayout ;
    this->labelPseudo = new QLabel("<h3> Pseudo : </h3>");
    this->lineEditPseudo = new QLineEdit ;
    this->labelController = new QLabel("<h3> Controller : </h3>");
    this->comboBoxController = new QComboBox ;
    this->comboBoxController->addItem("ia");
    this->comboBoxController->addItem("keyboard");
    this->comboBoxController->addItem("controller");
    this->comboBoxController->addItem("vr");
    this->comboBoxController->addItem("phone");
    this->labelVehicle = new QLabel("<h3> Vehicle </h3>");
    this->comboBoxVehicle = new QComboBox ;
    this->comboBoxVehicle->addItem("bike");
    this->comboBoxVehicle->addItem("car");
    this->comboBoxVehicle->addItem("truck");
    this->labelTeam = new QLabel("<h3> Team </h3>");
    this->comboBoxTeam = new QComboBox;
    this->comboBoxTeam->addItem("No team");
    for (int i = 0 ; i < 100 ; i++)
        this->comboBoxTeam->addItem(QString::number(i));
    this->initialButton = new QPushButton("VROOM VROOM !") ;

    this->initialLayout->addWidget(labelPseudo);
    this->initialLayout->addWidget(lineEditPseudo);
    this->initialLayout->addWidget(labelController);
    this->initialLayout->addWidget(comboBoxController);
    this->initialLayout->addWidget(labelVehicle);
    this->initialLayout->addWidget(comboBoxVehicle);
    this->initialLayout->addWidget(labelTeam);
    this->initialLayout->addWidget(comboBoxTeam);
    this->initialLayout->addWidget(initialButton);

    this->setLayout(this->initialLayout);
    //this->setLayout(initialLayout);


    //this->setLayout(mainLayout);

    //CONNECT
    this->connect(this->initialButton , SIGNAL(clicked()) , this , SLOT(buttonPlayPressed()));

}

PlayerUi::~PlayerUi()
{
    qDebug() << "Destructeur" ;
}


