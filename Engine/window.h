#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>

#include "Engine.h"
#include "GEngine.h"

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
};

#endif // WINDOW_H
