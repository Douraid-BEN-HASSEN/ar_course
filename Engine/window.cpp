#include "window.h"
#include "ui_window.h"

Window::Window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Window)
{
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Window::chronoTimer);

    engine = new Engine(this);

    ui->setupUi(this);
    ui->verticalLayout_main->addWidget(engine->getGEngine());

    scorebordLayout = new QVBoxLayout();

    QVBoxLayout *main_scorebordLayout = new QVBoxLayout();

    QWidget *widget = new QWidget();
    widget->setLayout(new QHBoxLayout());

    widget->layout()->addWidget(new QLabel("player"));
    widget->layout()->addWidget(new QLabel("checkpoint"));
    widget->layout()->addWidget(new QLabel("tour"));
    widget->layout()->addWidget(new QLabel("time"));
    widget->layout()->addWidget(new QLabel("state"));
    widget->layout()->addWidget(new QLabel("controller"));

    main_scorebordLayout->addWidget(widget);
    main_scorebordLayout->addLayout(scorebordLayout);
    main_scorebordLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));

    ui->tabWidget_scoreboard->widget(0)->setLayout(main_scorebordLayout);

    scorebordItem = new QMap<QString, PlayerScoreItem*>;

    connect(ui->pushButton_start, SIGNAL(clicked()), this, SLOT(startGame()));
    connect(ui->pushButton_reset, SIGNAL(clicked()), this, SLOT(reset()));
    connect(ui->action_reload, SIGNAL(triggered()), this, SLOT(reload()));
    connect(ui->action_openConfig, SIGNAL(triggered()), this, SLOT(openPropertiesFileConf()));

    connect(ui->spinBox_teamNumber, SIGNAL(valueChanged(int)), this, SLOT(teamNumberUpdated(int)));

    // force
    connect(ui->doubleSpinBox_CDrag, SIGNAL(valueChanged(double)), this, SLOT(CDragUpdated(double)));
    connect(ui->doubleSpinBox_CRR, SIGNAL(valueChanged(double)), this, SLOT(CRRUpdated(double)));
    connect(ui->doubleSpinBox_Gravite, SIGNAL(valueChanged(double)), this, SLOT(GravityUpdated(double)));

    connect(engine, SIGNAL(updated()), this, SLOT(gameInfoUpdated()));

    init();
}

Window::~Window()
{
    delete ui;
}

void Window::init()
{
    ui->spinBox_teamNumber->setValue(engine->getProperties()->getTeam());


    ui->doubleSpinBox_CDrag->setValue(engine->CDRAG);
    ui->doubleSpinBox_CRR->setValue(engine->CRR);
    ui->doubleSpinBox_Gravite->setValue(engine->GRAVITY);


}

void Window::gameInfoUpdated()
{
    ui->spinBox_playersCount->setValue(engine->getGameMode()->_players->count());

    for (GPlayer *g_player : engine->getPlayersGraphics().values()) {

        PlayerScoreItem *playerScoreItem = scorebordItem->value(g_player->getPlayer()->getUuid());

        if (playerScoreItem == nullptr) {
            playerScoreItem = new PlayerScoreItem(g_player);

            scorebordLayout->addWidget(playerScoreItem);
            scorebordItem->insert(g_player->getPlayer()->getUuid(), playerScoreItem);
        }
    }
}

void Window::teamNumberUpdated(int team)
{
    engine->getProperties()->setTeam(team);
}

void Window::startGame()
{
    ui->pushButton_start->setDisabled(true);

    engine->startGame();
    this->timer->start(100);

    ui->spinBox_teamNumber->setDisabled(true);
}

void Window::reset()
{
    this->timer->stop();

    ui->pushButton_start->setDisabled(false);
    clearLayout(scorebordLayout);

    scorebordItem->clear();

    ui->label_timer->setText("0:00:000");
    ui->spinBox_teamNumber->setDisabled(false);

    engine->reset();
}

void Window::clearLayout(QLayout *layout) {
    if (layout == NULL)
        return;
    QLayoutItem *item;
    while((item = layout->takeAt(0))) {
        if (item->layout()) {
            clearLayout(item->layout());
            delete item->layout();
        }
        if (item->widget()) {
           delete item->widget();
        }
        delete item;
    }
}

void Window::reload()
{
    engine->getProperties()->loadFile();
    init();
}

void Window::chronoTimer()
{
    double time = QDateTime::currentDateTime().toMSecsSinceEpoch() - engine->getGameStartAt().toMSecsSinceEpoch();

    QString timeText = QTime::fromMSecsSinceStartOfDay(time).toString("m:ss:zzz");

    ui->label_timer->setText(timeText);
}
void Window::openPropertiesFileConf()
{
    QString filePath = QFileInfo(engine->getProperties()->getPath()).canonicalFilePath();
    QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));
}

void Window::CDragUpdated(double cdrag)
{
    Engine::CDRAG = float(cdrag);
}

void Window::CRRUpdated(double crr)
{
    Engine::CRR = float(crr);
}


void Window::GravityUpdated(double Gravity)
{
    Engine::GRAVITY = float(Gravity);
    qDebug() << "gravité change" <<  Gravity;
}
