#ifndef CLIENT3DPLAYER_H
#define CLIENT3DPLAYER_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "../Player/playerui.h"
#include "../Client3D/3DGraphics/Widget3D.h"
class Client3DPlayer : public QWidget
{
    Q_OBJECT

private :
    QVBoxLayout * main_layout ;
    QHBoxLayout *visuel_layout ;
    QHBoxLayout *playerInterface_layout ;
    QWidget * container_widget_3d ;
    PlayerUi * player_ui ;
    Widget3D * widget_3d ;

protected slots :
    void onRunFind() ;
public:
    Client3DPlayer(QWidget *parent = nullptr);
    void makeConnect() ;
    ~Client3DPlayer();
};
#endif // CLIENT3DPLAYER_H
