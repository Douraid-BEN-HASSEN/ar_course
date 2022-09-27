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

class PlayerUi : public QWidget
{
    Q_OBJECT

private :
    QString uuid ;
    float angle ;
    int power ;

    //Graphic component for debuging
    QLabel *labelAngle ;
    QLabel *labelPower ;
    QVBoxLayout *mainLayout ;

    //Component for the first modale ( select pseudo, select vehicle , select team )
    QVBoxLayout *intialLayout ;
    QLabel *labelPseudo ;
    QDialog *dialogInitial ;
    QLineEdit *lineEditPseudo ;
    QLabel *labelController ;
    QComboBox *comboBoxController ;
    QLabel *labelVehicle ;
    QComboBox *comboBoxVehicle ;
    QLabel *labelTeam ;
    QSpinBox *spinBoxTeam ;

    QPushButton *initialButton ;

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
