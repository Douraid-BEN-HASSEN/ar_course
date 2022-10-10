#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QVBoxLayout>

#include "Engine.h"
#include "PlayerScoreItem.h"
#include "2DGraphics/GEngine.h"

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

    Engine *engine;
    QTimer *timer;
    void chronoTimer();
    void init();

private slots:
    void startGame();
    void reset();
    void reload();
    void gameInfoUpdated();
    void teamNumberUpdated(int);

};

#endif // WINDOW_H
