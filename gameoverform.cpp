#include "gameoverform.h"
#include "ui_gameoverform.h"

gameOverForm::gameOverForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gameOverForm)
{
    ui->setupUi(this);

    setStyleSheet("background-color : black");
    ui->label->setStyleSheet("background-color : black");
    QFont font = ui->label->font();
    font.setBold(true);
    font.setPointSize(12);
    ui->label->setFont(font);

    ui->exitButton->setStyleSheet("background-color : green");
    ui->newGameButton->setStyleSheet("background-color : green");
    exitFlag = false;
    newGameFlag = false;

    connect(ui->exitButton, SIGNAL(clicked(bool)), this, SLOT(exitGame()) );
    connect(ui->newGameButton, SIGNAL(clicked(bool)), this, SLOT(newGame()) );
}

gameOverForm::~gameOverForm()
{
    delete ui;
}


void gameOverForm::exitGame()
{
    exitFlag = true;
    close();
}

void gameOverForm::newGame()
{
    newGameFlag = true;
    close();
}

void gameOverForm::changeForm()
{
    if(result == -1)
    {
        ui->label->setText(tr("Player 2 wins") );
        ui->label->setStyleSheet("color : orange");
    }

    if(result == 0)
    {
        ui->label->setText(tr("Tied") );
        ui->label->setStyleSheet("color : yellow");
    }

    if(result == 1)
    {
        ui->label->setText(tr("Player 1 wins") );
        ui->label->setStyleSheet("color : green");
    }

}
