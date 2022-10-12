#ifndef CLIENT3DPLAYER_H
#define CLIENT3DPLAYER_H

#include <QWidget>

class Client3DPlayer : public QWidget
{
    Q_OBJECT

public:
    Client3DPlayer(QWidget *parent = nullptr);
    ~Client3DPlayer();
};
#endif // CLIENT3DPLAYER_H
