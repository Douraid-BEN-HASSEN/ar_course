#include "playerui.h"
#include <QVBoxLayout>

//Catch event of key pressed
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

//Callback when "Vroum vroum" button is pressed
void PlayerUi::buttonPlayPressed()
{
    if (this->lineEditPseudo->text() != "")
    {
        MqttService::instance()->sendMessageRegister(this->uuid , this->lineEditPseudo->text() , this->comboBoxController->currentText(), this->comboBoxVehicle->currentText() , this->comboBoxTeam->currentText());
        delete this->initialLayout ;
        qDeleteAll(this->children());
        this->setLayout(mainLayout);
    }
}

void PlayerUi::catchKeyUp() {
    if (this->power != 100)
        this->power++ ;
    this->makeMqttMessage(0 , this->power , 0 );

}

void PlayerUi::catchKeyDown() {
    if (this->power != -100)
        this->power--;
    this->makeMqttMessage(0 , this->power , 0 );
}

void PlayerUi::catchActionKey(int idKey)
{
    qDebug() << idKey ;
    if ((idKey == 1 && this->nbBanana > 0) || (idKey == 2 && this->nbBomb > 0) || (idKey == 3 && this->nbRocket > 0)) {
        this->makeMqttMessage(0 , this->power , idKey );
        idKey == 1 ? this->nbBanana-- : idKey == 2 ? this->nbBomb -- : this->nbRocket -- ;
    }

}

void PlayerUi::makeMqttMessage(int angle, int power, int keyAction)
{
    MqttService::instance()->sendMessageControl(this->uuid , angle , this->power , keyAction);
}

void PlayerUi::updateLabel()
{
    this->labelAngle->setText("<h1> Angle : " + QString::number(this->angle) + " </h1> ");
    this->labelPower->setText("<h1> Power : " + QString::number(this->power) + " </h1> ");
    switch ((int)this->angle) {
    case 0 :
        this->labelImage->setText("^");
        break;
    case 90 :
        this->labelImage->setText(">");
        break ;
    case 180 :
        this->labelImage->setText("V");
        break ;
    case 270 :
        this->labelImage->setText("<");
        break ;
    }
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
    this->angle = 180 ;
    this->power = 0 ;
    this->nbBanana = 3 ;
    this->nbBomb = 0 ;
    this->nbRocket = 2 ;
    this->uuid = QUuid::createUuid().toString();

    //Graphic content for debugging
    this->labelPower = new QLabel("<h1> Power : " + QString::number(this->power) + " </h1>") ;
    this->labelAngle = new QLabel("<h1> Angle : " + QString::number(this->angle) + " </h1> ") ;
    this->labelImage = new QLabel("V") ;

    this->mainLayout = new QVBoxLayout ;
    this->mainLayout->addWidget(this->labelPower);
    this->mainLayout->addWidget(this->labelAngle);
    this->mainLayout->addWidget(this->labelImage);

    //Make initial modale
    this->resize(500 , 300);

    this->initialLayout = new QVBoxLayout ;
    this->horizontalLayout_1 = new QHBoxLayout ;
    this->horizontalLayout_2 = new QHBoxLayout ;
    this->horizontalLayout_3 = new QHBoxLayout ;
    this->horizontalLayout_4 = new QHBoxLayout ;

    this->labelTitle = new QLabel("<h1 text-align=\"center\" `> <font color=\"blue\"> > FIST </font> <font color=\"green\"> AND </font>  <font color=\"red\"> FURIOUS < </font> </h1> ");
    this->labelTitle->setAlignment(Qt::AlignCenter);

    this->labelPseudo = new QLabel("<h3> Pseudo : </h3>");
    this->lineEditPseudo = new QLineEdit ;
    this->horizontalLayout_1->addWidget(this->labelPseudo);
    this->horizontalLayout_1->addWidget(this->lineEditPseudo);

    this->labelController = new QLabel("<h3> Controller : </h3>");
    this->comboBoxController = new QComboBox ;
    this->comboBoxController->addItem("ia");
    this->comboBoxController->addItem("keyboard");
    this->comboBoxController->addItem("controller");
    this->comboBoxController->addItem("vr");
    this->comboBoxController->addItem("phone");
    this->horizontalLayout_2->addWidget(this->labelController);
    this->horizontalLayout_2->addWidget(this->comboBoxController);

    this->labelVehicle = new QLabel("<h3> Vehicle : </h3>");
    this->comboBoxVehicle = new QComboBox ;
    this->comboBoxVehicle->addItem("bike");
    this->comboBoxVehicle->addItem("car");
    this->comboBoxVehicle->addItem("truck");
    this->horizontalLayout_3->addWidget(labelVehicle);
    this->horizontalLayout_3->addWidget(comboBoxVehicle);

    this->labelTeam = new QLabel("<h3> Team </h3>");
    this->comboBoxTeam = new QComboBox;
    this->comboBoxTeam->addItem("No team");
    for (int i = 1 ; i < 101 ; i++)
        this->comboBoxTeam->addItem(QString::number(i));
    this->horizontalLayout_4->addWidget(labelTeam);
    this->horizontalLayout_4->addWidget(comboBoxTeam);

    this->initialButton = new QPushButton("Warm up the engine !")  ;

    this->initialLayout->addWidget(labelTitle);
    this->initialLayout->addLayout(this->horizontalLayout_1);
    this->initialLayout->addLayout(this->horizontalLayout_2);
    this->initialLayout->addLayout(this->horizontalLayout_3);
    this->initialLayout->addLayout(this->horizontalLayout_4);
    this->initialLayout->addWidget(initialButton);

    this->setLayout(this->initialLayout);

    //Connect
    this->connect(this->initialButton , SIGNAL(clicked()) , this , SLOT(buttonPlayPressed()));
}

PlayerUi::~PlayerUi()
{
    qDebug() << "Destructeur" ;
}


