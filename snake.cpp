#include "snake.h"
#include "ui_snake.h"
#include <QPainter>
#include <QKeyEvent>

int snake::DELAY = 500;


snake::snake(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::snake)
{
    ui->setupUi(this);
    setStyleSheet("background-color:black");
        resize(B_WIDTH, B_HEIGHT);
        setFixedSize(B_WIDTH, B_HEIGHT);

        inGame = false;
        isChangePaint1 = true;
        isChangePaint2 = true;

        direction1 = right;
        direction2 = left;

        dots1 = 0;
        dots2 = 0;

        loadImages();
        initGame();
}

snake::~snake()
{
    delete ui;
}

void snake::loadImages()
{
    dot1 = new QImage(20, 20, QImage::Format_RGB32);
    dot1->fill(Qt::green);

    dot2 = new QImage(20, 20, QImage::Format_RGB32);
    dot2->fill(QColor("orange") );

    food = new QImage(20, 20, QImage::Format_RGB32);
    food->fill(Qt::red);
}

void snake::initGame()
{
    dots1 = 3;
    dots2 = 3;

    for(int i = 0; i < dots1; ++i)
    {
        coordinatesDots1[i].first = 100 - i * DOT_SIZE;
        coordinatesDots1[i].second = 100;
    }

    for(int i = 0; i < dots2; ++i)
    {
        coordinatesDots2[i].first = 500 + i * DOT_SIZE;
        coordinatesDots2[i].second = 400;
    }


    locateFood();

    timerId = startTimer(DELAY);
}

void snake::locateFood()
{

    coordinatesFood.first = (qrand() % RAND_POS) * DOT_SIZE;
    coordinatesFood.second = (qrand() % RAND_POS) * DOT_SIZE;
}

void snake::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    doDrawing();
}

void snake::doDrawing()
{
    QPainter qp(this);
    qp.drawImage(coordinatesFood.first, coordinatesFood.second, *food);
    for(int i = 0; i < dots1; ++i)
        qp.drawImage(coordinatesDots1[i].first, coordinatesDots1[i].second, *dot1);

    for(int i = 0; i < dots2; ++i)
        qp.drawImage(coordinatesDots2[i].first, coordinatesDots2[i].second, *dot2);
}

void snake::checkFood()
{
    if(coordinatesDots1[0].first == coordinatesFood.first && coordinatesDots1[0].second == coordinatesFood.second)
    {
        ++dots1;
        locateFood();
        speedUp();
    }

    if(coordinatesDots2[0].first == coordinatesFood.first && coordinatesDots2[0].second == coordinatesFood.second)
    {
        ++dots2;
        locateFood();
        speedUp();
    }
}

void snake::move()
{
    move1();
    move2();
}

void snake::move1()
{

    for(int i = dots1; i > 0; i--)
    {
        coordinatesDots1[i].first = coordinatesDots1[i - 1].first;
        coordinatesDots1[i].second = coordinatesDots1[i - 1].second;
    }


    if(direction1 == left)
    {
        coordinatesDots1[0].first -= DOT_SIZE;
    }

    if(direction1 == right)
    {
        coordinatesDots1[0].first += DOT_SIZE;
    }

    if(direction1 == down)
    {
        coordinatesDots1[0].second += DOT_SIZE;
    }

    if(direction1 == up)
    {
        coordinatesDots1[0].second -= DOT_SIZE;
    }

    if(coordinatesDots1[0].first < 0)
    {
        coordinatesDots1[0].first = B_WIDTH;
    }

    if(coordinatesDots1[0].first > B_WIDTH)
    {
        coordinatesDots1[0].first = 0;
    }

    if(coordinatesDots1[0].second > B_HEIGHT)
    {
        coordinatesDots1[0].second = 0;
    }

    if(coordinatesDots1[0].second < 0)
    {
        coordinatesDots1[0].second = B_HEIGHT;
    }


}

void snake::move2()
{

    for(int i = dots2; i > 0; i--)
    {
        coordinatesDots2[i].first = coordinatesDots2[i - 1].first;
        coordinatesDots2[i].second = coordinatesDots2[i - 1].second;
    }


    if(direction2 == left)
    {
        coordinatesDots2[0].first -= DOT_SIZE;
    }

    if(direction2 == right)
    {
        coordinatesDots2[0].first += DOT_SIZE;
    }

    if(direction2 == down)
    {
        coordinatesDots2[0].second += DOT_SIZE;
    }

    if(direction2 == up)
    {
        coordinatesDots2[0].second -= DOT_SIZE;
    }

    if(coordinatesDots2[0].first < 0)
    {
        coordinatesDots2[0].first = B_WIDTH;
    }

    if(coordinatesDots2[0].first > B_WIDTH)
    {
        coordinatesDots2[0].first = 0;
    }

    if(coordinatesDots2[0].second > B_HEIGHT)
    {
        coordinatesDots2[0].second = 0;
    }

    if(coordinatesDots2[0].second < 0)
    {
        coordinatesDots2[0].second = B_HEIGHT;
    }

}

void snake::timerEvent(QTimerEvent *e)
{
    Q_UNUSED(e);
     if(inGame)
     {
         move();
         checkFood();
         checkCollision();
         repaint();
         isChangePaint1 = true;
         isChangePaint2 = true;
     }

}

void snake::checkCollision()
{
    for(int i = 1; i < dots1; ++i)
    {
        if(coordinatesDots1[0].first == coordinatesDots1[i].first && coordinatesDots1[0].second == coordinatesDots1[i].second)
        {
            gameOver(-1);
        }
    }

    for(int i = 1; i < dots2; ++i)
    {
        if(coordinatesDots1[0].first == coordinatesDots2[i].first && coordinatesDots1[0].second == coordinatesDots2[i].second)
        {
            gameOver(-1);
        }
    }



    for(int i = 1; i < dots2; ++i)
    {
        if(coordinatesDots2[0].first == coordinatesDots2[i].first && coordinatesDots2[0].second == coordinatesDots2[i].second)
        {
            gameOver(1);
        }
    }

    for(int i = 1; i < dots1; ++i)
    {
        if(coordinatesDots2[0].first == coordinatesDots1[i].first && coordinatesDots2[0].second == coordinatesDots1[i].second)
        {
            gameOver(1);
        }
    }


    if(coordinatesDots1[0].first == coordinatesDots2[0].first && coordinatesDots1[0].second == coordinatesDots2[0].second)
    {
        gameOver(0);
    }
}

void snake::gameOver(int res)
{
    inGame = false;
    killTimer(timerId);

    gameOverWin.setResult(res);
    gameOverWin.changeForm();
    gameOverWin.exec();

    if(gameOverWin.exitFlag)
    {
        close();
    }

    if(gameOverWin.newGameFlag)

    {
        newGame();
    }
}

void snake::keyPressEvent(QKeyEvent *e)
{

    int key = e->key();

    if(isChangePaint1)
    {

    if( (key == Qt::Key_D) && (direction1 != left) )
    {
        direction1 = right;
        isChangePaint1 = false;
    }

    if( (key == Qt::Key_A) && (direction1 != right) )
    {
        direction1 = left;
        isChangePaint1 = false;
    }

    if( (key == Qt::Key_W) && (direction1 != down) )
    {
        direction1 = up;
        isChangePaint1 = false;
    }

    if( (key == Qt::Key_S) && (direction1 != up) )
    {
        direction1 = down;
        isChangePaint1 = false;
    }
    }

    if(isChangePaint2)
    {

    if( (key == Qt::Key_Right) && (direction2 != left) )
    {
        direction2 = right;
        isChangePaint2 = false;
    }

    if( (key == Qt::Key_Left) && (direction2 != right) )
    {
        direction2 = left;
        isChangePaint2 = false;
    }

    if( (key == Qt::Key_Up) && (direction2 != down) )
    {
        direction2 = up;
        isChangePaint2 = false;
    }

    if( (key == Qt::Key_Down) && (direction2 != up) )
    {
        direction2 = down;
        isChangePaint2 = false;
    }

    }

    if(key == Qt::Key_Enter || key == Qt::Key_Space || key == Qt::Key_Return)
    {
        if(inGame)
        {
            pause();
        }
        else
        {
            unpause();
        }
    }

    QWidget::keyPressEvent(e);
}

void snake::pause()
{
    inGame = false;
}

void snake::unpause()
{
    inGame = true;
}

void snake::newGame()
{
    killTimer(timerId);
    DELAY = 500;

    inGame = false;
    isChangePaint1 = true;
    isChangePaint2 = true;

    direction1 = right;
    direction2 = left;

    initGame();
}

void snake::speedUp()
{
    if(DELAY <= 400) return;
    else
    {
        DELAY -= 30;
        killTimer(timerId);
        timerId = startTimer(DELAY);
    }
}


