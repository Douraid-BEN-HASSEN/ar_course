#include "playerui.h"
#include <QDebug>
#include <QtAlgorithms>

//Catch event of key pressed
void PlayerUi::keyPressEvent(QKeyEvent *key){
    qDebug() << "PlayerUi::keyPressEvent()";
    if (this->isGame == true && this->controllerType == "keyboard" ) {
        this->_controller->handleKeyEvent(key);
        this->updateLabel();
    }
}

void PlayerUi::keyReleaseEvent(QKeyEvent *key){
    qDebug() << "PlayerUi::keyReleaseEvent()" ;
    if (this->isGame == true && this->controllerType == "keyboard" ) {
        this->_controller->handleReleaseKeyEvent(key);
        this->updateLabel();
    }
}


//Callback when start button is pressed
void PlayerUi::buttonPlayPressed()
{
    qDebug() << "PlayerUi::buttonPlayPressed()" ;
    this->pseudo = this->lineEditPseudo->text();
    this->labelSelectionPseudo->setText("<h1> " + this->pseudo + " </h1> ");
    this->labelSelectionTeam->setText(" <h2> " + this->comboBoxTeam->currentText() + "</h2>");
    this->labelSelectionController->setText( " <h3> " + this->comboBoxController->currentText() + " </h3> ");
    this->labelSelectionVehicle->setText(" <h3> " + this->comboBoxVehicle->currentText() + " </h3> ");
    this->controllerType = this->comboBoxController->currentText();
    this->_controller->setControllerType(this->controllerType);
    if (this->lineEditPseudo->text() != "")
    {
        this->_controller->sendMessageRegister( this->lineEditPseudo->text() , this->comboBoxController->currentText(), this->comboBoxVehicle->currentText().split(" ").at(0) , this->comboBoxTeam->currentText());
        this->team = this->comboBoxTeam->currentText();
        this->vehicle = this->comboBoxVehicle->currentText();
        this->stackedWidget->setCurrentIndex(2);
        this->isGame = true ;
    }
}

//When receive mqtt message on topic /game/properties
void PlayerUi::onRunFind()
{
    qDebug() << "PlayerUi::onRunFind()" ;
    if ( this->isProperties == false ) {
        this->labelNbLaps->setText("<h4> " + QString::number(this->_controller->getNbTurn()) + " laps </h4>");
        this->labelNbTeam->setText("<h4> " + QString::number(this->_controller->getNbTeams()) + " teams </h4>");
        this->updateLabel() ;
        this->isProperties = true ;
        this->comboBoxVehicle->clear();

        for (Vehicle *vehicle : this->_controller->getVehicleOptions()->values())
            this->comboBoxVehicle->addItem(vehicle->getType() + " " +  vehicle->toString());

        for (int i = 1 ; i < this->_controller->getNbTeams()+1 ; i++)
            this->comboBoxTeam->addItem(QString::number(i));

        this->stackedWidget->setCurrentIndex(1);
    }
}

void PlayerUi::onGameModeReceived()
{
    updateLabel();
}

void PlayerUi::onExitRun()
{
    qDebug() << "PlayerUi::onExitRun()" ;
    this->isGame = false ;
    this->isProperties = false ;
    this->stackedWidget->setCurrentIndex(0);
    this->controllerType = "" ;
    this->_controller->setControllerType("");
    this->uuid = QUuid::createUuid().toString();
}

void PlayerUi::onCloseGame()
{
    qDebug() << "PlayerUi::onCloseGame()" ;
    this->isProperties = false ;
    this->close();
}

void PlayerUi::onGamepadUse()
{
    qDebug() << "PlayerUi::onGamepadUse()" ;
    if (this->controllerType == "controller") {
        this->updateLabel();
    }
}

//On action, make message for mqtt
void PlayerUi::makeMqttMessage( int keyAction)
{
    qDebug() << "PlayerUi::makeMqttMessage()";
    this->_controller->sendMessageControl( keyAction);
}

//Function to update label when catching keyboard actions
void PlayerUi::updateLabel()
{
    qDebug() << "PlayerUi::updateLabel()" ;
    this->labelAngle->setText("<h4> Angle : " + QString::number(this->_controller->getAngle()) + " </h4> ");
    this->labelPower->setText("<h4> Power : " + QString::number(this->_controller->getPower()) + " </h4> ");
    this->labelBanana->setText(" <h4> " + QString::number(this->_controller->getNbBananas()) + " banana(s) </h4> ");
    this->labelBomb->setText(" <h4> " + QString::number(this->_controller->getNbBombs()) + " bomb(s) </h4> ");
    this->labelRocket->setText(" <h4> " + QString::number(this->_controller->getNbRocket()) + " rocket(s) </h4>");
}

//Constructor
PlayerUi::PlayerUi(QWidget *parent)
    : QWidget(parent)
{
    //Init parameters
    this->isProperties = false ;
    this->isGame = false ;

    this->resize(500 , 300);
    this->uuid = QUuid::createUuid().toString();
    this->props = Properties::getInstance();
    this->gameMode = GameMode::getInstance();

    //Graphic content for loading page
    this->loadingLayout = new QVBoxLayout ;

    this->labelLoading = new QLabel("<h1> Trying to find a ride... </h1> ");
    this->buttonClose = new QPushButton("Close game");
    this->labelLoading->setAlignment(Qt::AlignCenter);
    this->loadingLayout->addWidget(labelLoading);
    this->loadingLayout->addWidget(buttonClose);
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
    this->labelBanana = new QLabel(" <h4> " + QString::number(this->_controller->getNbBananas()) + " banana(s) </h4> ");
    this->labelBomb = new QLabel(" <h4> " + QString::number(this->_controller->getNbBombs()) + " bomb(s) </h4> ");
    this->labelRocket = new QLabel(" <h4> " + QString::number(this->_controller->getNbRocket()) + " rocket(s) </h4>");
    this->horizontalLayout_7->addWidget(this->labelBanana);
    this->horizontalLayout_7->addWidget(this->labelBomb);
    this->horizontalLayout_7->addWidget(this->labelRocket);

    this->horizontalLayout_8 = new QHBoxLayout ;
    this->labelPower = new QLabel("<h4> Power : " + QString::number(this->_controller->getPower()) + " </h4>") ;
    this->labelAngle = new QLabel("<h4> Angle : " + QString::number(this->_controller->getAngle()) + " </h4> ") ;
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
    this->comboBoxController->addItem("controller");
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

    _controller = new Controller() ;

    props = Properties::getInstance();
    gameMode = GameMode::getInstance();

    //Connect
    this->connect(this->buttonClose , SIGNAL(clicked()) , this , SLOT(onCloseGame()));
    this->connect(this->registerButton , SIGNAL(clicked()) , this , SLOT(buttonPlayPressed()));
    this->connect(this->buttonExit , SIGNAL(clicked()) , this , SLOT(onExitRun()));


    connect(this->_controller , SIGNAL(runFind()) , this , SLOT(onRunFind()));
    connect(this->_controller , SIGNAL(gamemodeFind()) , this , SLOT(onGameModeReceived()));

    //Connect for the gamepad
    this->connect(this->_controller->getGamepad() , SIGNAL(buttonL1Changed(bool)) , this , SLOT(onGamepadUse()));
    this->connect(this->_controller->getGamepad() , SIGNAL(buttonR1Changed(bool)) , this , SLOT(onGamepadUse()));
    this->connect(this->_controller->getGamepad() , SIGNAL(buttonR2Changed(double)) , this , SLOT(onGamepadUse()));
    this->connect(this->_controller->getGamepad() , SIGNAL(buttonL2Changed(double)) , this , SLOT(onGamepadUse()));
    this->connect(this->_controller->getGamepad() , SIGNAL(buttonAChanged(bool)) , this , SLOT(onGamepadUse()));
    this->connect(this->_controller->getGamepad() , SIGNAL(buttonBChanged(bool)) , this , SLOT(onGamepadUse()));
    this->connect(this->_controller->getGamepad() , SIGNAL(buttonXChanged(bool)) , this , SLOT(onGamepadUse()));
    this->connect(this->_controller->getGamepad() , SIGNAL(buttonYChanged(bool)) , this , SLOT(onGamepadUse()));
}


PlayerUi::~PlayerUi()
{
    qDebug() << "Destructeur" ;
}
