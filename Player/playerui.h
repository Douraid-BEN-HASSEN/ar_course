#ifndef PLAYERUI_H
#define PLAYERUI_H

#include <QWidget>
#include <QtGamepad>
#include <QKeyEvent>
#include <QDebug>
#include <QString>
#include <QLabel>
#include <QVBoxLayout>
class PlayerUi : public QWidget
{
    Q_OBJECT

private :
    QString uuid ;
    float angle ;
    int power ;

    //graphic component
    QLabel *labelAngle ;
    QLabel *labelPower ;
    QVBoxLayout *mainLayout ;
protected :
    void keyPressEvent(QKeyEvent *e) ;

public:
    PlayerUi(QWidget *parent = nullptr);
    void catchKeyUp() ;
    void catchKeyLeft() ;
    void catchKeyRight();
    void catchKeyDown() ;
    void catchActionKey(int idKey);
    void makeMqttMessage(int angle , int power , int keyAction );
    void updateLabel();
    ~PlayerUi();
};
#endif // PLAYERUI_H
