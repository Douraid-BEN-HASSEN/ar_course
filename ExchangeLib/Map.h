#ifndef MAP_H
#define MAP_H

#include <QObject>

#if defined MAP_LIB
    #define MAP_LIB_EXPORT Q_DECL_EXPORT
#else
    #define MAP_LIB_EXPORT Q_DECL_IMPORT
#endif

class MAP_LIB_EXPORT Map : public QObject
{
    Q_OBJECT
public:
    explicit Map(QObject *parent = nullptr);

signals:

};

#endif // MAP_H
