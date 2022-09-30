#include "Control.h"

Control::Control()
{

}

void Control::setUuid(QString pUuid)
{
     _uuid = pUuid;
}

void Control::setAngle(float pAngle)
{
    _angle = pAngle;
}

void Control::setPower(int pPower)
{
    _power = pPower;
}

void Control::setButtonsVal(QString pKey, bool pVal)
{
    _buttons[pKey] = pVal;
}

void Control::setButtons(QMap<QString, bool> pButtons)
{
    this->_buttons = pButtons;
}

QString Control::getUuid()
{
    return _uuid;
}

float Control::getAngle()
{
    return _angle;
}

int Control::getPower()
{
    return _power;
}

bool Control::getButtonsVal(QString pKey)
{
    return _buttons[pKey];
}

QMap<QString, bool> Control::getButtons()
{
    return _buttons;
}
