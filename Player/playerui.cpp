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
    this->pseudo = this->lineEditPseudo->text();
    this->labelSelectionPseudo->setText("<h1> " + this->pseudo + " </h1> ");
    this->labelSelectionTeam->setText(" <h2> " + this->comboBoxTeam->currentText() + "</h2>");
    this->labelSelectionController->setText( " <h3> " + this->comboBoxController->currentText() + " </h3> ");
    this->labelSelectionVehicle->setText(" <h3> " + this->comboBoxVehicle->currentText() + " </h3> ");

    if (this->lineEditPseudo->text() != "")
    {

        MqttService::instance()->sendMessageRegister(this->uuid , this->lineEditPseudo->text() , this->comboBoxController->currentText(), this->comboBoxVehicle->currentText() , this->comboBoxTeam->currentText());

        this->team = this->comboBoxTeam->currentText();
        this->vehicle = this->comboBoxVehicle->currentText();
        delete this->registerLayout ;
        qDeleteAll(this->children());
        this->setLayout(gameLayout);
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
    this->labelAngle->setText("<h4> Angle : " + QString::number(this->angle) + " </h4> ");
    this->labelPower->setText("<h4> Power : " + QString::number(this->power) + " </h4> ");
    this->labelBanana->setText(" <h4> " + QString::number(this->nbBanana) + " banana(s) </h4> ");
    this->labelBomb->setText(" <h4> " + QString::number(this->nbBomb) + " bomb(s) </h4> ");
    this->labelRocket->setText(" <h4> " + QString::number(this->nbRocket) + " rocket(s) </h4>");
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

    //Graphic content for game
    this->gameLayout = new QVBoxLayout ;

    this->horizontalLayout_5 = new QHBoxLayout ;
    this->labelSelectionPseudo = new QLabel("a");
    this->labelSelectionTeam= new QLabel("team");
    this->horizontalLayout_5->addWidget(this->labelSelectionPseudo);
    this->horizontalLayout_5->addWidget(this->labelSelectionTeam);

    this->horizontalLayout_6 = new QHBoxLayout ;
    this->labelSelectionController = new QLabel("");
    this->labelSelectionVehicle = new QLabel("");
    this->horizontalLayout_6->addWidget(this->labelSelectionController);
    this->horizontalLayout_6->addWidget(this->labelSelectionVehicle);

    this->horizontalLayout_7 = new QHBoxLayout ;
    this->labelBanana = new QLabel(" <h4> " + QString::number(this->nbBanana) + " banana(s) </h4> ");
    this->labelBomb = new QLabel(" <h4> " + QString::number(this->nbBomb) + " bomb(s) </h4> ");
    this->labelRocket = new QLabel(" <h4> " + QString::number(this->nbRocket) + " rocket(s) </h4>");
    this->horizontalLayout_7->addWidget(this->labelBanana);
    this->horizontalLayout_7->addWidget(this->labelBomb);
    this->horizontalLayout_7->addWidget(this->labelRocket);

    this->horizontalLayout_8 = new QHBoxLayout ;
    this->labelPower = new QLabel("<h4> Power : " + QString::number(this->power) + " </h4>") ;
    this->labelAngle = new QLabel("<h4> Angle : " + QString::number(this->angle) + " </h4> ") ;
    this->horizontalLayout_8->addWidget(this->labelPower);
    this->horizontalLayout_8->addWidget(this->labelAngle);

    this->gameLayout->addLayout(this->horizontalLayout_5);
    this->gameLayout->addLayout(this->horizontalLayout_6);
    this->gameLayout->addLayout(this->horizontalLayout_7);
    this->gameLayout->addLayout(this->horizontalLayout_8);

    //Make initial modale
    this->resize(500 , 300);

    this->registerLayout = new QVBoxLayout ;
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

    this->registerButton = new QPushButton("Warm up the engine !")  ;

    this->registerLayout->addWidget(labelTitle);
    this->registerLayout->addLayout(this->horizontalLayout_1);
    this->registerLayout->addLayout(this->horizontalLayout_2);
    this->registerLayout->addLayout(this->horizontalLayout_3);
    this->registerLayout->addLayout(this->horizontalLayout_4);
    this->registerLayout->addWidget(registerButton);

    this->setLayout(this->registerLayout);

    //Connect
    this->connect(this->registerButton , SIGNAL(clicked()) , this , SLOT(buttonPlayPressed()));
}


PlayerUi::~PlayerUi()
{
    qDebug() << "Destructeur" ;
}
