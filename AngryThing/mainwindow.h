#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QList>
#include <QDesktopWidget>
#include <QTimer>
#include <Box2D/Box2D.h>
#include <QMouseEvent>
#include <iostream>
#include <QGraphicsPixmapItem>
#include <QWidget>
#include <cstdlib>
#include <cstdio>
#include <QLabel>
#include <QString>
#include <QPushButton>

#include <gameitem.h>
#include <land.h>
#include <bird.h>
#include <brick.h>
#include <pig.h>
#include <redbird.h>
#include <yellowbird.h>
#include <whitebird.h>
#include <bluebird.h>


namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void showEvent(QShowEvent *);
    bool eventFilter(QObject *,QEvent *event);
    void closeEvent(QCloseEvent *);
    void NewObject();
    int score=0;
    QLabel *lblScore;
    QPushButton *btnExit, *btnRestart;



signals:
    void quitGame();


private slots:
    void tick();
    void QUITSLOT();
    void ExitGame();
    void RestartGame();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    b2World *world;
    b2World *world2;
    QList<GameItem *> itemList;
    QTimer timer;

    Bird *BBird[4];
    Bird *BBird_fly[4];
    pig *PPig[3];
    Land *block1,*block2;
    brick * BBrick[10];

    int b_count=0;
    bool fireconfrim=false,leftclick=false;




    float x_start,y_start,x_end,y_end,x_lenght,y_lenght,x_oriposition,y_oriposition ,x_diff,y_diff,vx,vy;
    float bird_start_x,bird_start_y;
    int leftbutton,rightbutton,count[3]={0,0,0};
        int haha=0;



};

#endif // MAINWINDOW_H
