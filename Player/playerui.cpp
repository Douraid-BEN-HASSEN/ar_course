#include "playerui.h"
#include <QDebug>
#include <QtAlgorithms>

//Catch event of key pressed
void PlayerUi::keyPressEvent(QKeyEvent *key){
    if (this->isGame == true ) {
        this->_controller->handleKeyEvent(this->uuid ,  key, &this->power , &this->angle , &this->nbBanana , &this->nbBomb , &this->nbRocket);
        this->updateLabel();
    }

}

void PlayerUi::keyReleaseEvent(QKeyEvent *key){
    qDebug(" key realese event ") ;

}
//Callback when start button is pressed
void PlayerUi::buttonPlayPressed()
{
    this->pseudo = this->lineEditPseudo->text();
    this->labelSelectionPseudo->setText("<h1> " + this->pseudo + " </h1> ");
    this->labelSelectionTeam->setText(" <h2> " + this->comboBoxTeam->currentText() + "</h2>");
    this->labelSelectionController->setText( " <h3> " + this->comboBoxController->currentText() + " </h3> ");
    this->labelSelectionVehicle->setText(" <h3> " + this->comboBoxVehicle->currentText() + " </h3> ");

    if (this->lineEditPseudo->text() != "")
    {
        this->_controller->sendMessageRegister(this->uuid , this->lineEditPseudo->text() , this->comboBoxController->currentText(), this->comboBoxVehicle->currentText().split(" ").at(0) , this->comboBoxTeam->currentText());
        this->team = this->comboBoxTeam->currentText();
        this->vehicle = this->comboBoxVehicle->currentText();
        this->stackedWidget->setCurrentIndex(2);
        this->isGame = true ;
    }
}

//When receive mqtt message on topic /game/properties
void PlayerUi::onRunFind(QByteArray datas)
{
    if ( this->isProperties == false ) {
        qDebug() << "on run find" ;
        this->props->deserialize(QJsonDocument::fromJson(datas).object());
        this->nbBanana = props->getBanana() ;
        this->nbBomb = props->getBomb() ;
        this->nbRocket = props->getRocket();
        this->nbTurn = props->getLaps() ;
        this->nbTeam = props->getTeam() ;
        for (Vehicle *vehicle : this->props->vehicleOptions->values()) {
            qDebug()  << vehicle ;
            this->comboBoxVehicle->addItem(vehicle->getType() + " " +  vehicle->toString());

        }
        this->stackedWidget->setCurrentIndex(1);
        this->labelNbLaps->setText("<h4> " + QString::number(this->nbTurn) + " laps </h4>");
        this->labelNbTeam->setText("<h4> " + QString::number(this->nbTeam) + " teams </h4>");
        for (int i = 1 ; i < this->nbTeam+1 ; i++)
            this->comboBoxTeam->addItem(QString::number(i));
        this->updateLabel();
        this->isProperties = true ;
    }
}

void PlayerUi::onExitRun()
{
    this->isGame = false ;
    this->isProperties = false ;
    this->stackedWidget->setCurrentIndex(0);
}

void PlayerUi::onCloseGame()
{
    this->isProperties = false ;
    this->close();
}

void PlayerUi::onGamepadUse()
{
    qDebug() << "on gamepad use" ;
    this->updateLabel();
}


//On action, make message for mqtt
void PlayerUi::makeMqttMessage(int angle, int power, int keyAction)
{
    this->_controller->sendMessageControl(this->uuid , this->angle , this->power , keyAction);
}


//Function to update label when catching keyboard actions
void PlayerUi::updateLabel()
{
    this->labelAngle->setText("<h4> Angle : " + QString::number(this->angle) + " </h4> ");
    this->labelPower->setText("<h4> Power : " + QString::number(this->power) + " </h4> ");
    this->labelBanana->setText(" <h4> " + QString::number(this->nbBanana) + " banana(s) </h4> ");
    this->labelBomb->setText(" <h4> " + QString::number(this->nbBomb) + " bomb(s) </h4> ");
    this->labelRocket->setText(" <h4> " + QString::number(this->nbRocket) + " rocket(s) </h4>");
}

void PlayerUi::connectToMqtt()
{
    MqttService::instance()->subscribe("/game/properties");
}

//Constructor
PlayerUi::PlayerUi(QWidget *parent)
    : QWidget(parent)
{
    //Init parameters
    this->isProperties = false ;
    this->isGame = false ;
    this->angle = 0 ;
    this->power = 0 ;
    this->nbBanana = 0 ;
    this->nbBomb = 0 ;
    this->nbRocket = 0 ;
    this->resize(500 , 300);
    this->uuid = QUuid::createUuid().toString();
    this->props = Properties::getInstance();

    qDebug() << "before" ;

    qDebug() << "after" ;

    //Graphic content for loading page
    this->loadingLayout = new QVBoxLayout ;

    this->labelLoading = new QLabel("<h1> Trying to find a ride... </h1> ");
    this->buttonClose = new QPushButton("Close game");
    this->loadingLayout->addWidget(labelLoading);
    this->loadingLayout->addWidget(buttonClose);
    //Graphic content for the game
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

    this->horizontalLayout_10 = new QHBoxLayout ;
    this->buttonExit = new QPushButton("EXIT THE GAME");
    this->horizontalLayout_10->addWidget(this->buttonExit);

    this->gameLayout->addLayout(this->horizontalLayout_5);
    this->gameLayout->addLayout(this->horizontalLayout_6);
    this->gameLayout->addLayout(this->horizontalLayout_7);
    this->gameLayout->addLayout(this->horizontalLayout_8);
    this->gameLayout->addLayout(this->horizontalLayout_10);



    //Graphic content for the register window
    this->registerLayout = new QVBoxLayout ;

    this->labelTitle = new QLabel("<h1 text-align=\"center\" `> <font color=\"blue\"> > FIST </font> <font color=\"green\"> AND </font>  <font color=\"red\"> FURIOUS < </font> </h1> ");
    this->labelTitle->setAlignment(Qt::AlignCenter);

    this->horizontalLayout_9 = new QHBoxLayout ;
    this->labelNbLaps = new QLabel("");
    this->labelNbTeam = new QLabel("");
    this->horizontalLayout_9->addWidget(this->labelNbLaps);
    this->horizontalLayout_9->addWidget(this->labelNbTeam);

    this->horizontalLayout_1 = new QHBoxLayout ;
    this->labelPseudo = new QLabel("<h3> Pseudo : </h3>");
    this->lineEditPseudo = new QLineEdit ;
    this->horizontalLayout_1->addWidget(this->labelPseudo);
    this->horizontalLayout_1->addWidget(this->lineEditPseudo);

    this->horizontalLayout_2 = new QHBoxLayout ;
    this->labelController = new QLabel("<h3> Controller : </h3>");
    this->comboBoxController = new QComboBox ;
    //this->comboBoxController->addItem("ia");
    this->comboBoxController->addItem("keyboard");
    //this->comboBoxController->addItem("controller");
    //this->comboBoxController->addItem("vr");
    //this->comboBoxController->addItem("phone");
    this->horizontalLayout_2->addWidget(this->labelController);
    this->horizontalLayout_2->addWidget(this->comboBoxController);

    this->horizontalLayout_3 = new QHBoxLayout ;
    this->labelVehicle = new QLabel("<h3> Vehicle : </h3>");
    this->comboBoxVehicle = new QComboBox ;
    this->horizontalLayout_3->addWidget(labelVehicle);
    this->horizontalLayout_3->addWidget(comboBoxVehicle);

    this->horizontalLayout_4 = new QHBoxLayout ;
    this->labelTeam = new QLabel("<h3> Team </h3>");
    this->comboBoxTeam = new QComboBox;
    this->comboBoxTeam->addItem("No team");
    this->horizontalLayout_4->addWidget(labelTeam);
    this->horizontalLayout_4->addWidget(comboBoxTeam);
    this->registerButton = new QPushButton("Warm up the engine !")  ;

    this->registerLayout->addWidget(labelTitle);
    this->registerLayout->addLayout(this->horizontalLayout_9);
    this->registerLayout->addLayout(this->horizontalLayout_1);
    this->registerLayout->addLayout(this->horizontalLayout_2);
    this->registerLayout->addLayout(this->horizontalLayout_3);
    this->registerLayout->addLayout(this->horizontalLayout_4);
    this->registerLayout->addWidget(registerButton);

    this->stackedWidget = new QStackedWidget ;

    QWidget * widget1 = new QWidget ;
    QWidget * widget2 = new QWidget ;
    QWidget * widget3 = new QWidget ;

    widget1->setLayout(this->loadingLayout);
    widget2->setLayout(this->registerLayout);
    widget3->setLayout(this->gameLayout);

    this->stackedWidget->addWidget(widget1);
    this->stackedWidget->addWidget(widget2);
    this->stackedWidget->addWidget(widget3);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(stackedWidget);
    this->setLayout(mainLayout);

    _controller = new Controller(&this->uuid , &this->power , &this->angle , &this->nbBanana , &this->nbBomb , &this->nbRocket) ;
    //Connect
    this->connect(this->buttonClose , SIGNAL(clicked()) , this , SLOT(onCloseGame()));
    this->connect(this->registerButton , SIGNAL(clicked()) , this , SLOT(buttonPlayPressed()));
    this->connect(this->buttonExit , SIGNAL(clicked()) , this , SLOT(onExitRun()));
    this->connect(MqttService::instance()->client , SIGNAL(messageReceived(QByteArray ,  QMqttTopicName)), this ,  SLOT(onRunFind(QByteArray)) );
    //Connect for the gamepad
    this->connect(this->_controller->gamepad , SIGNAL(buttonL1Changed(bool)) , this , SLOT(onGamepadUse()));
    this->connect(this->_controller->gamepad , SIGNAL(buttonR1Changed(bool)) , this , SLOT(onGamepadUse()));
    this->connect(this->_controller->gamepad , SIGNAL(buttonR2Changed(double)) , this , SLOT(onGamepadUse()));
    this->connect(this->_controller->gamepad , SIGNAL(buttonL2Changed(double)) , this , SLOT(onGamepadUse()));
    this->connect(this->_controller->gamepad , SIGNAL(buttonAChanged(bool)) , this , SLOT(onGamepadUse()));
    this->connect(this->_controller->gamepad , SIGNAL(buttonBChanged(bool)) , this , SLOT(onGamepadUse()));
    this->connect(this->_controller->gamepad , SIGNAL(buttonXChanged(bool)) , this , SLOT(onGamepadUse()));
    this->connect(this->_controller->gamepad , SIGNAL(buttonYChanged(bool)) , this , SLOT(onGamepadUse()));


    this->connectToMqtt();
}


PlayerUi::~PlayerUi()
{
    qDebug() << "Destructeur" ;
}
