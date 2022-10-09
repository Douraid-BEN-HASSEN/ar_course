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

    connect(ui->pushButton_reset, SIGNAL(clicked()), this, SLOT(reset()));
    connect(ui->pushButton_start, SIGNAL(clicked()), this, SLOT(startGame()));


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
}

void Window::teamNumberUpdated(int team)
{
    engine->getProperties()->setTeam(team);
}

void Window::startGame()
{
    engine->startGame();
    this->timer->start(100);

    ui->spinBox_teamNumber->setDisabled(true);
}

void Window::reset()
{
    this->timer->stop();
    engine->reset();
    ui->label_timer->setText("0:00");

    ui->spinBox_teamNumber->setDisabled(false);
}

void Window::chronoTimer()
{
    double time = QDateTime::currentDateTime().toMSecsSinceEpoch() - engine->getGameStartAt().toMSecsSinceEpoch();

    QString timeText = QTime::fromMSecsSinceStartOfDay(time).toString("m:ss:zzz");

    qDebug() << timeText;

    ui->label_timer->setText(timeText);
}
