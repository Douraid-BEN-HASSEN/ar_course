#ifndef PLAYERUI_H
#define PLAYERUI_H

#include <QWidget>
#include <QtGamepad>
#include <QKeyEvent>
#include <QDebug>
#include <QString>
#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QSpinBox>
#include <QImage>
#include <MqttService.h>

class PlayerUi : public QWidget
{
    Q_OBJECT

private :
    QString uuid ;
    float angle ;
    int power ;
    int nbBanana ;
    int nbBomb ;
    int nbRocket ;

    //Graphic component for debuging
    QLabel *labelAngle ;
    QLabel *labelPower ;
    QVBoxLayout *mainLayout ;
    QLabel *labelImage ;

    //Component for the first modale ( select pseudo, select vehicle , select team )

    QVBoxLayout *initialLayout ;
    QHBoxLayout *horizontalLayout_1 ;
    QHBoxLayout *horizontalLayout_2 ;
    QHBoxLayout *horizontalLayout_3 ;
    QHBoxLayout *horizontalLayout_4 ;

    QLabel *labelTitle ;
    QLabel *labelPseudo ;
    QDialog *dialogInitial ;
    QLineEdit *lineEditPseudo ;
    QLabel *labelController ;
    QComboBox *comboBoxController ;
    QLabel *labelVehicle ;
    QComboBox *comboBoxVehicle ;
    QLabel *labelTeam ;
    QComboBox *comboBoxTeam ;

    QPushButton *initialButton ;

protected :
    void keyPressEvent(QKeyEvent *e) ;

protected slots :
    //Call when the user validate the initial form
    void buttonPlayPressed() ;
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
