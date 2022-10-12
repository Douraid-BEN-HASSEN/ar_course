#ifndef ENDGAMEDIALOG_H
#define ENDGAMEDIALOG_H

#include <QDialog>
#include <QDebug>

namespace Ui {
class EndGameDialog;
}

class EndGameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EndGameDialog(QWidget *parent = nullptr);
    ~EndGameDialog();

    void setScoreboard(QWidget *);
    QWidget *scoreBoard;

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::EndGameDialog *ui;

private slots:
    void closeDialog();

public: signals:
    void closed();
};

#endif // ENDGAMEDIALOG_H
