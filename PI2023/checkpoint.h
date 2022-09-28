#ifndef CHECKPOINT_H
#define CHECKPOINT_H

#include <QObject>
#include <qlist.h>

class Checkpoint
{
public:
    Checkpoint();

    void setId(int id);
    int getId();
    void setX(int x);
    int getX();
    void setY(int y);
    int getY();

private:

    int m_id;
    int m_x;
    int m_y;
};

#endif // CHECKPOINT_H

