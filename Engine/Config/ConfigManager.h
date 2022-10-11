#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <QObject>
#include <QFileSystemWatcher>
#include <QUrl>

#include <Kart/Game/Properties.h>

class ConfigManager : public QObject
{
    Q_OBJECT
public:
    explicit ConfigManager(QObject *parent = nullptr);

    static void watchProperties(Properties *);

signals:

};

#endif // CONFIGMANAGER_H
