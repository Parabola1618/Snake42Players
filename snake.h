#ifndef SNAKE_H
#define SNAKE_H

#include <QWidget>
#include "gameoverform.h"

namespace Ui {
class snake;
}

class snake : public QWidget
{
    Q_OBJECT

public:
    explicit snake(QWidget *parent = 0);
    ~snake();

    gameOverForm gameOverWin;

private:
    Ui::snake *ui;

    QImage* dot1;
    QImage* food;
    QImage* dot2;

    int timerId;
    int dots1, dots2;

    static const int B_WIDTH = 600;
    static const int B_HEIGHT = 600;
    static const int DOT_SIZE = 25;
    static const int ALL_DOTS = 14400;
    static int DELAY;
    static const int RAND_POS = 24;
    enum e_direction{ left, right, down, up};
    e_direction direction1, direction2;

    bool inGame;
    bool isChangePaint1, isChangePaint2;

    QPair<int, int> coordinatesDots1[ALL_DOTS];
    QPair<int, int> coordinatesDots2[ALL_DOTS];
    QPair<int, int> coordinatesFood;

    void loadImages();
    void initGame();
    void locateFood();
    void doDrawing();
    void move();
    void move1();
    void move2();
    void checkFood();
    void checkCollision();
    void gameOver(int res);
    void pause();
    void unpause();
    void newGame();
    void speedUp();

    void paintEvent(QPaintEvent *e);
    void timerEvent(QTimerEvent *e);
    void keyPressEvent(QKeyEvent *e);
};

#endif // SNAKE_H
