#include "Checkpoint.h"

Checkpoint::Checkpoint(QObject *parent)
    : QObject{parent}
{

}

void Checkpoint::deserialize(const QJsonObject &jsonObject) {
    id = jsonObject["id"].toInt();
    x = jsonObject["x"].toInt();
    y = jsonObject["y"].toInt();
}
