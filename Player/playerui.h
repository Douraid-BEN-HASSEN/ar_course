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
    QString pseudo ;
    QString team ;
    QString vehicle ;

    //Graphic component for game
    QVBoxLayout *gameLayout ;

    QLabel *labelAngle ;
    QLabel *labelPower ;
    QLabel *labelSelectionPseudo ;
    QLabel *labelSelectionTeam ;
    QLabel *labelSelectionController;
    QLabel *labelSelectionVehicle ;
    QLabel *labelBanana ;
    QLabel *labelBomb ;
    QLabel *labelRocket ;

    //Component for the first modale ( select pseudo, select vehicle , select team )
    QVBoxLayout *registerLayout ;
    QHBoxLayout *horizontalLayout_1 ;
    QHBoxLayout *horizontalLayout_2 ;
    QHBoxLayout *horizontalLayout_3 ;
    QHBoxLayout *horizontalLayout_4 ;
    QHBoxLayout *horizontalLayout_5 ;
    QHBoxLayout *horizontalLayout_6 ;
    QHBoxLayout *horizontalLayout_7 ;
    QHBoxLayout *horizontalLayout_8 ;

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
    QPushButton *registerButton ;

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
