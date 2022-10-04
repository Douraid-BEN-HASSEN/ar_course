#include "Control.h"

Control::Control(QObject *parent): QObject{parent}
{
    _buttons.insert("banana", false);
    _buttons.insert("bomb", false);
    _buttons.insert("rocket", false);
}

Control::Control(QString uuid, QObject *parent): QObject{parent}
{
    this->_uuid = uuid;
    _buttons.insert("banana", false);
    _buttons.insert("bomb", false);
    _buttons.insert("rocket", false);
}

void Control::publish() {
    MqttService::instance()->publish(this->topic, this->serialize());
}

QString Control::toString()
{
    return QString("uuid : %1, angle : %2, power : %3").arg(this->_uuid, QString::number(_angle), QString::number(_power));
}

void Control::deserialize(const QJsonObject &jsonObject)
{
    this->_uuid = jsonObject["uuid"].toString();
    this->_angle = jsonObject["angle"].toDouble();
    this->_power = jsonObject["power"].toInt();

    QJsonObject itemsJObject = jsonObject["items"].toObject();

    this->_buttons.insert("banana", itemsJObject["banana"].toBool());
    this->_buttons.insert("bomb", itemsJObject["bomb"].toBool());
    this->_buttons.insert("rocket", itemsJObject["rocket"].toBool());
}

QString Control::serialize() {
    QJsonDocument doc(this->toJson());
    return QString(doc.toJson(QJsonDocument::Compact));
}

QJsonObject Control::toJson() {
    QJsonObject jsonObject;

    jsonObject["uuid"] = this->_uuid;
    jsonObject["angle"] = this->_angle;
    jsonObject["power"] = this->_power;

    QJsonObject itemsJO;

    itemsJO.insert("banana", this->_buttons.value("banana"));
    itemsJO.insert("bomb", this->_buttons.value("bomb"));
    itemsJO.insert("rocket", this->_buttons.value("rocket"));

    jsonObject["buttons"] = itemsJO;


    return jsonObject;
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
