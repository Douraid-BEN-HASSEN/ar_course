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

    ui->tabWidget_scoreboard->widget(0)->setLayout(new QVBoxLayout());

    scorebordItem = new QMap<QString, PlayerScoreItem*>;

//    QAbstractItemModel *model = new QStandardItemModel(4, 2, this);
//    ui->tabWidget_scorebord->setModel(model);

//    model->ins

    connect(ui->pushButton_start, SIGNAL(clicked()), this, SLOT(startGame()));
    connect(ui->pushButton_reset, SIGNAL(clicked()), this, SLOT(reset()));
    connect(ui->pushButton_reload, SIGNAL(clicked()), this, SLOT(reload()));

    connect(ui->spinBox_teamNumber, SIGNAL(valueChanged(int)), this, SLOT(teamNumberUpdated(int)));

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
}

void Window::gameInfoUpdated()
{
    ui->spinBox_playersCount->setValue(engine->getGameMode()->_players->count());

    for (Player *player : engine->getGameMode()->_players->values()) {

        PlayerScoreItem *playerScoreItem = scorebordItem->value(player->getUuid());

        if (playerScoreItem == nullptr) {
            playerScoreItem = new PlayerScoreItem(player);

            scorebordItem->insert(player->getUuid(), playerScoreItem);
            ui->tabWidget_scoreboard->widget(0)->layout()->addWidget(playerScoreItem);
        }
    }

//    QAbstractItemModel *model = new QStandardItemModel(4,2,this);


//    ui->tableView_scoreboard->setModel(model);
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
    ui->pushButton_start->setDisabled(false);

    this->timer->stop();
    engine->reset();
    ui->label_timer->setText("0:00:000");

    ui->spinBox_teamNumber->setDisabled(false);
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

    qDebug() << timeText;

    ui->label_timer->setText(timeText);
}
