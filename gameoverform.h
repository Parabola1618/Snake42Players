#ifndef GAMEOVERFORM_H
#define GAMEOVERFORM_H

#include <QDialog>

namespace Ui {
class gameOverForm;
}

class gameOverForm : public QDialog
{
    Q_OBJECT

public:
    explicit gameOverForm(QWidget *parent = 0);
    ~gameOverForm();

    int getResult() const { return result; }
    void setResult(int res) { result = res; }
    void changeForm();

    bool newGameFlag;
    bool exitFlag;

private:
    Ui::gameOverForm *ui;

    int result;

private slots:
    void exitGame();
    void newGame();
};

#endif // GAMEOVERFORM_H
