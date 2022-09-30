#ifndef CONTROL_H
#define CONTROL_H

#if defined(CONTROL_LIBRARY)
#  define CONTROL_EXPORT Q_DECL_EXPORT
#else
#  define CONTROL_EXPORT Q_DECL_IMPORT
#endif


#include <QString>
#include <QMap>

class CONTROL_EXPORT Control
{
public:
    Control();

    void setUuid(QString pUuid);
    void setAngle(float pAngle);
    void setPower(int pPower);
    void setButtonsVal(QString pKey, bool pVal);
    void setButtons(QMap<QString, bool> pButtons);

    QString getUuid();
    float getAngle();
    int getPower();
    bool getButtonsVal(QString pKey);
    QMap<QString, bool> getButtons();

private:
    QString _uuid;
    float _angle;
    int _power;
    QMap<QString, bool> _buttons;

};

#endif // CONTROL_H
