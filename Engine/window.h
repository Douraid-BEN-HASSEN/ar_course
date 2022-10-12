#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QVBoxLayout>
#include <QDesktopServices>

#include "Engine.h"
#include "PlayerScoreItem.h"
#include "2DGraphics/GEngine.h"
#include "EndGame.h"

namespace Ui {
class Window;
}

class Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = nullptr);
    ~Window();

private:
    Ui::Window *ui;

    QMap<QString, PlayerScoreItem*> *scorebordItem;

    QVBoxLayout *scorebordLayout;
    void clearLayout(QLayout *layout);

    Engine *engine;
    QTimer *timer;
    EndGame *popUpEnd;


    void chronoTimer();
    void init();

private slots:
    void startGame();
    void reset();
    void reload();
    void gameInfoUpdated();
    void teamNumberUpdated(int);
    void openPropertiesFileConf();
    void CDragUpdated(double);
    void CRRUpdated(double);
    void GravityUpdated(double);
    void openGameEndModel();

};

#endif // WINDOW_H
