#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include "Player.h"
#include "math.h"

// constructor
Player::Player(QObject *parent): QObject{parent}
{
    this->_items = new QMap<QString, int>();
    this->_x = 0;
    this->_y = 0;
    this->_angle = 0;
    this->_speed = 0;
}

Player::Player(Register *r, QObject *parent): QObject{parent}
{
    this->_uuid = r->getUuid();
    this->_pseudo = r->getPseudo();
    this->_controller = r->getController();
    this->_vehicle = r->getVehicle();

    this->_items = new QMap<QString, int>();
    this->_x = 0;
    this->_y = 0;
    this->_angle = 0;
    this->_speed = 0;
    this->_lastCheckpoint = 0;
}

// destructor
Player::~Player() {
    delete this->_items;
}

//  +-------+
//  | UTILS |
//  +-------+
void Player::deserialize(const QJsonObject &jsonObject)
{
    this->_uuid = jsonObject["uuid"].toString();
    this->_pseudo = jsonObject["pseudo"].toString();
    this->_color = jsonObject["color"].toString();
    this->_team = jsonObject["team"].toString();
    this->_x = jsonObject["x"].toInt();
    this->_y = jsonObject["y"].toInt();
    this->_angle = jsonObject["angle"].toDouble();
    this->_speed = jsonObject["speed"].toInt();
    this->_vehicle = jsonObject["vehicle"].toString();

    auto itemsJObject = jsonObject["items"].toObject();
    this->_items->insert("banana", itemsJObject["banana"].toInt());
    this->_items->insert("bomb", itemsJObject["bomb"].toInt());
    this->_items->insert("rocket", itemsJObject["rocket"].toInt());

    this->_lastCheckpoint = jsonObject["lastCheckpoint"].toInt();

    this->_currentLap = jsonObject["currentLap"].toInt();
    this->_status = jsonObject["status"].toString();
    this->_controller = jsonObject["controller"].toString();
}

QString Player::toString() {
    return QString("uuid: %1, x: %2, y: %3, angle: %4").arg(_uuid, QString::number(_x), QString::number(_y), QString::number(_angle));
}

QString Player::serialize() {
    QJsonDocument doc(this->toJson());
    return QString(doc.toJson(QJsonDocument::Compact));
}

QJsonObject Player::toJson() {
    QJsonObject jsonObject;

    jsonObject["uuid"] = this->_uuid;
    jsonObject["pseudo"] = this->_pseudo;
    jsonObject["color"] = this->_color;
    jsonObject["team"] = this->_team;
    jsonObject["x"] = this->_x;
    jsonObject["y"] = this->_y;
    jsonObject["angle"] = this->_angle;
    jsonObject["speed"] = this->_speed;
    jsonObject["vehicle"] = this->_vehicle;

    QJsonObject itemsJO;

    itemsJO.insert("banana", this->_items->value("banana"));
    itemsJO.insert("bomb", this->_items->value("bomb"));
    itemsJO.insert("rocket", this->_items->value("rocket"));

    jsonObject["items"] = itemsJO;

    jsonObject["lastCheckpoint"] = this->_lastCheckpoint;

    jsonObject["currentLap"] = this->_currentLap;
    jsonObject["status"] = this->_status;
    jsonObject["controller"] = this->_controller;

    return jsonObject;
}

//  +--------+
//  | SETTER |
//  +--------+
void Player::setUuid(QString pUuid)
{
    this->_uuid = pUuid;
}

void Player::setPseudo(QString pPseudo)
{
    this->_pseudo = pPseudo;
}

void Player::setColor(QString pColor)
{
    this->_color = pColor;
}

void Player::setTeam(QString pTeam)
{
    this->_team = pTeam;
}

void Player::setX(int pX)
{
    this->_x = pX;
}

void Player::setY(int pY)
{
    this->_y = pY;
}

void Player::setAngle(float pAngle)
{
    this->_angle = pAngle;
}


void Player::setSpeed(int pSpeed)
{
    this->_speed = pSpeed;
}

void Player::setVehicule(QString pVehicule)
{
    this->_vehicle = pVehicule;
}

void Player::setLastCheckpoint(int pLastCheckpoint)
{
    this->_lastCheckpoint = pLastCheckpoint;
}

void Player::setCurrentLap(int pCurrentLap)
{
    this->_currentLap = pCurrentLap;
}

void Player::setStatus(QString pStatus)
{
    this->_status = pStatus;
}

void Player::setController(QString pController)
{
    this->_controller = pController;
}

//  +--------+
//  | GETTER |
//  +--------+
QString Player::getUuid()
{
    return this->_uuid;
}

QString Player::getPseudo()
{
    return this->_pseudo;
}

QString Player::getColor()
{
    return this->_color;
}

QString Player::getTeam()
{
    return this->_team;
}

int Player::getX()
{
    return this->_x;
}

int Player::getY()
{
    return this->_y;
}

float Player::getAngle()
{
    return this->_angle;
}

int Player::getSpeed()
{
    return this->_speed;
}

QString Player::getVehicule()
{
    return this->_vehicle;
}

QMap<QString, int>* Player::getItems()
{
    return this->_items;
}

int Player::getLastCheckpoint()
{
    return this->_lastCheckpoint;
}

int Player::getCurrentLap()
{
    return this->_currentLap;
}

QString Player::getStatus()
{
    return this->_status;
}

QString Player::getController()
{
    return this->_controller;
}

QPoint Player::getPosition()
{
    return QPoint(_x, _y);
}

void Player::update(Control *control)
{
    //qDebug() << this->getX() << " " << this->getY() << " " << this->getAngle() << " " << control->getAngle() << " " << control->getPower();
    /*this->_angle += control->getAngle()/10;
    this->_x += control->getPower() * cos(this->_angle);
    this->_y += -control->getPower() * sin(this->_angle);*/



    int newX = control->getPower() * cos(this->_angle);
    int newY = -control->getPower() * sin(this->_angle);
    this->_angle += control->getAngle()/10;
    this->_x += newX;
    this->_y += newY;


    /*if((newX >= 0 && newX <= this->_map->getMapWidth()) && (newY >= 0 && newY <= this->_map->getMapHeight())) {
        this->_x += newX;
        this->_y += newY;
    }*/

}

Player *Player::newPos(Control *control)
{
     Player *player = new Player();
     return player;
}


