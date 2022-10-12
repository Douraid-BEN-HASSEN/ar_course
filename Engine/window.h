#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QVBoxLayout>
#include <QDesktopServices>

#include "Engine.h"
#include "PlayerScoreItem.h"
#include "2DGraphics/GEngine.h"
#include "EndGameDialog.h"

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

    void clearLayout(QLayout *layout);

    QVBoxLayout *scorebordLayout;
    EndGameDialog *endGameDialog;
    QTabWidget *scorebordTabWidget;

    QMap<QString, PlayerScoreItem*> *scorebordItem;

    Engine *engine;
    QTimer *timer;


    void chronoTimer();
    void init();
    void initScoreboard();

private slots:
    void startGame();
    void reset();
    void reload();
    void endGameDialogClosed();

    void gameInfoUpdated();
    void teamNumberUpdated(int);
    void openPropertiesFileConf();
    void CDragUpdated(double);
    void CRRUpdated(double);
    void GravityUpdated(double);
    void gameEnded();

};

#endif // WINDOW_H
