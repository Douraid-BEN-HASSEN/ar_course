#ifndef INTERFACE_H
#define INTERFACE_H

#include <QMainWindow>
#include <QObject>
#include <QDebug>

#include "2DGraphics/widget.h"


QT_BEGIN_NAMESPACE
namespace Ui { class interface; }
QT_END_NAMESPACE

class interface : public QMainWindow
{
    Q_OBJECT

public:
    interface(QWidget *parent = nullptr);
    ~interface();

private:
    Ui::interface *ui;
};
#endif // INTERFACE_H
