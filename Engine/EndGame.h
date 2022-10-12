#ifndef ENDGAME_H
#define ENDGAME_H

#include <QDialog>

namespace Ui {
class EndGame;
}

class EndGame : public QDialog
{
    Q_OBJECT

public:
    explicit EndGame(QWidget *parent = nullptr);
    ~EndGame();

    void setScoreboard(QWidget *);
    QWidget *scoreBoard;

private slots:
    void on_pushButton_clicked();
    void closeEvent(QCloseEvent *);


private:
    Ui::EndGame *ui;

public: signals:
    void closeEndScore();
};

#endif // ENDGAME_H
