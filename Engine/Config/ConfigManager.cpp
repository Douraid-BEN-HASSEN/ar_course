#include "ConfigManager.h"

ConfigManager::ConfigManager(QObject *parent): QObject{parent}
{

}

void ConfigManager::watchProperties(Properties *properties) {
    QFileSystemWatcher *watcher = new QFileSystemWatcher();

    QString filePath = QFileInfo(properties->getPath()).canonicalFilePath();
    watcher->addPath(filePath);
    QObject::connect(watcher, SIGNAL(fileChanged(const QString&)), properties, SLOT(loadFile(const QString&)));
}
