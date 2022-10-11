#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include "2DGraphics/MapWidget.h"
#include "IA.h"

#include <Kart/Player/Register.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Window; }
QT_END_NAMESPACE

class Window : public QMainWindow
{
    Q_OBJECT

public:
    Window(QWidget *parent = nullptr);
    ~Window();

private:
    Ui::Window *ui;

    IA *ia;

private slots:
    void startIA();
    void getPath(QList<QPair<QString, Checkpoint *>> path);
    void changeLabelTarget(QPoint newTarget);

signals:
    void drawPath(QList<QPair<QString, Checkpoint *>> path);
};
#endif // WINDOW_H

