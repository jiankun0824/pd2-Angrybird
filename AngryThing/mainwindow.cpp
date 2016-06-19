#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsPixmapItem>
#include <ctime>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);

    //enable the event Filter
    qApp->installEventFilter(this);
    ui->graphicsView->setBackgroundBrush(QPixmap(":/background.jpg").scaled(960, 540)); //create background
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //disable scrollbar (horizontal)
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //disable scrollbar (vertical)

    //set scoreboard
    lblScore = new QLabel(this);
    lblScore->setStyleSheet("color:black; background-color: transparent; font: bold 25px;");
    lblScore->setText("Score : 0");
    lblScore->setGeometry(120, 0, 200, 60);
    lblScore->show();

}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::showEvent(QShowEvent *){

    NewObject();
    //timer
    connect(&timer, SIGNAL(timeout()), this, SLOT(tick()));
    connect(this, SIGNAL(quitGame()), this, SLOT(QUITSLOT()));
    timer.start(100/6);

}

bool MainWindow::eventFilter(QObject *, QEvent *event)
{
    if(event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent *mouse_event = static_cast<QMouseEvent*>(event);

        if (mouse_event->button() == Qt::LeftButton)
        {
             leftbutton++;

            if(leftbutton>=5)
            {
                if(b_count<=3)
                {
                    leftclick=true;
                    leftbutton=0;

                    BBird[b_count]->set_transform(b2Vec2(6.0f,6.0f),0);

                    x_start = QCursor::pos().x();
                    y_start = QCursor::pos().y();
                    x_lenght = QCursor::pos().x();
                    y_lenght = QCursor::pos().y();
                }
            }
        }
        else if (mouse_event->button() == Qt::RightButton)
        {
            rightbutton++;

            if(rightbutton>=5 && fireconfrim==true && b_count<=3)
            {
                rightbutton=0;
                BBird_fly[b_count]->skill();;
                fireconfrim=false;
                b_count++;
            }
        }
    }
    else if(event->type() == QEvent::MouseButtonRelease)
    {
        QMouseEvent *mouse_event = static_cast<QMouseEvent*>(event);

        if (mouse_event->button() == Qt::LeftButton)
        {
            leftbutton++;
             if(leftbutton>1)
             {
                leftbutton=0;
                if(b_count<=3)
                {
                    bird_start_x=BBird[b_count]->get_position().x;
                    bird_start_y=BBird[b_count]->get_position().y;

                    BBird[b_count]->set_transform(b2Vec2(32.0f,32.0f),0);
                    BBird_fly[b_count]->set_transform(b2Vec2(bird_start_x,bird_start_y),0);

                    x_end = QCursor::pos().x();
                    y_end = QCursor::pos().y();

                    x_diff=x_start -x_end;
                    y_diff= y_end-y_start;

                    x_diff=x_diff/30;
                    y_diff=y_diff/30;
                    float a=18.5;
                    if (x_diff>3.0)
                    {
                        vx=a;
                    }
                    else if (x_diff < -3.0)
                    {
                        vx=-a;
                    }
                    else
                    {
                        vx=(x_diff/3.0)*a;
                    }

                    if (y_diff>3.0)
                    {
                        vy=a;
                    }
                    else if (y_diff < -3.0)
                    {
                        vy=-a;
                    }
                    else
                    {
                        vy=(y_diff/3.0)*a;
                    }

                    BBird_fly[b_count]->setLinearVelocity(b2Vec2(vx, vy));
                    fireconfrim=true;
                    leftclick=false;
                }
            }
         }
    }
    else if(event->type() == QEvent::MouseMove)
    {
        if(leftclick==true)
       {
            float A= BBird[b_count]->get_position().x + (QCursor::pos().x() - x_lenght)/30;
            float B= BBird[b_count]->get_position().y - (QCursor::pos().y() - y_lenght)/30;
            BBird[b_count]->set_transform(b2Vec2( A , B ), 0);
            x_lenght = QCursor::pos().x();
            y_lenght = QCursor::pos().y();
        }
    }
    return false;
}

void MainWindow::closeEvent(QCloseEvent *){
    //close event
    emit quitGame();
}

void MainWindow::tick(){

    world->Step(1.0/60.0,6,2);
    scene->update();

    //kill PPig
    for(int i = 0 ; i < 3 ; i++)
    {
        if((PPig[i]->get_velocity().x+PPig[i]->get_velocity().y)>=3)
        {
            PPig[i]->set_transform(b2Vec2(32.0f,32.0f),0);
            count[i]=1;
        }
    }
    score=count[0]*1000+count[1]*1000+count[2]*1000;
    //update scoreboard
    lblScore->setText("Score :  " + QString::number(score));
}

void MainWindow::QUITSLOT(){
    //send output signal (for debug)
    std::cout << "Quit Game Signal receive !" << std::endl ;
}

void MainWindow::NewObject()
{
    //setting QGraphicsScene
    scene = new QGraphicsScene(0, 0, 960, 540);
    ui->graphicsView->setScene(scene);

    QGraphicsPixmapItem *LifeRemainder1;

    QPixmap LifeImg(":/sling.png");
    LifeImg=LifeImg.scaled(50,100);

    LifeRemainder1=new QGraphicsPixmapItem();
    LifeRemainder1->setPixmap(LifeImg);
    LifeRemainder1->setPos(150,350);
    scene->addItem(LifeRemainder1);

    //create world
    world = new b2World(b2Vec2(0.0f, -10.0f));
    world2=new b2World(b2Vec2(0.0f, -10.0f));

    //setting Size
    GameItem::setGlobalSize(QSizeF(32.0f, 18.0f),size());

    //create ground
    itemList.push_back(new Land(16.0f, 1.5f, 32.0f, 3.0f, QPixmap(":/ground.png").scaled(960,90), world, scene));
    block2=new Land(2.0f, 16.0f, 4.0f, 1.0f, QPixmap(":/ground.png").scaled(0,0), world, scene);

    //create bird
    BBird[0] = new redbird(3.5f, 17.0f, 0.5f, &timer, QPixmap(":/birdred").scaled(30, 30), world2, scene);
    BBird[3] = new bluebird(0.5f, 17.0f, 0.5f, &timer, QPixmap(":/birdblue").scaled(30, 30), world2, scene);
    BBird[2] = new whitebird(1.5f, 17.0f, 0.5f, &timer, QPixmap(":/birdwhite").scaled(30, 30), world2, scene);
    BBird[1] = new yellowbird(2.5f, 17.0f, 0.5f, &timer, QPixmap(":/birdyellow").scaled(30, 30), world2, scene);

    BBird_fly[0] = new redbird(3.5f, 17.0f, 0.5f, &timer, QPixmap(":/birdred").scaled(30, 30), world, scene);
    BBird_fly[3] = new bluebird(0.5f, 17.0f, 0.5f, &timer, QPixmap(":/birdblue").scaled(30, 30), world, scene);
    BBird_fly[2] = new whitebird(1.5f, 17.0f, 0.5f, &timer, QPixmap(":/birdwhite").scaled(30, 30), world, scene);
    BBird_fly[1] = new yellowbird(2.5f, 17.0f, 0.5f, &timer, QPixmap(":/birdyellow").scaled(30, 30), world, scene);

    for (int i=0 ; i<4 ; i++)
    {
        itemList.push_back(BBird[i]);
        itemList.push_back(BBird_fly[i]);
    }

    x_oriposition=BBird[0]->get_position().x;
    y_oriposition=BBird[0]->get_position().y;

    //create pig
    PPig[0] = new pig(28.0f, 3.5f, 0.5f, &timer, QPixmap(":/pig.png").scaled(30, 30), world, scene);
    PPig[1] = new pig(23.0f, 3.5f, 0.5f, &timer, QPixmap(":/pig.png").scaled(30, 30), world, scene);
    PPig[2] = new pig(25.5f, 9.5f, 0.5f, &timer, QPixmap(":/pig.png").scaled(30, 30), world, scene);

    for (int i=0 ; i <3;i++)
    itemList.push_back(PPig[i]);

    //create brick
    BBrick[0]=new brick(26.5f, 4.5f, 1.0f, 3.0f,  &timer, QPixmap(":/brickrow").scaled(30, 90), world, scene); //PPig[0]
    BBrick[1]=new brick(29.5f, 4.5f, 1.0f, 3.0f, &timer, QPixmap(":/brickrow").scaled(30, 90), world, scene); //PPig[0]
    BBrick[2]=new brick(28.0f, 6.5f, 4.0f, 1.0f, &timer, QPixmap(":/brickcol").scaled(120, 30), world, scene); //PPig[0]

    BBrick[3]=new brick(21.5f, 4.5f, 1.0f, 3.0f,  &timer, QPixmap(":/brickrow").scaled(30, 90), world, scene); //PPig[1]
    BBrick[4]=new brick(24.5f, 4.5f, 1.0f, 3.0f, &timer, QPixmap(":/brickrow").scaled(30, 90), world, scene); //PPig[1]
    BBrick[5]= new brick(23.0f, 6.5f, 4.0f, 1.0f, &timer, QPixmap(":/brickcol").scaled(120, 30), world, scene); //PPig[1]

    BBrick[6]=new brick(25.5f, 7.5f, 4.0f, 1.0f, &timer, QPixmap(":/brickcol").scaled(120, 30), world, scene); //PPig[2]
    BBrick[7]=new brick(24.0f, 9.5f, 1.0f, 3.0f,  &timer, QPixmap(":/brickrow").scaled(30, 90), world, scene); //PPig[2]
    BBrick[8]=new brick(27.0f, 9.5f, 1.0f, 3.0f, &timer, QPixmap(":/brickrow").scaled(30, 90), world, scene);  //PPig[2]
    BBrick[9]=new brick(25.5f, 11.5f, 4.0f, 1.0f, &timer, QPixmap(":/brickcol").scaled(120, 30), world, scene); //PPig[2]

    for (int i=0 ; i <10 ; i ++)
        itemList.push_back(BBrick[i]);


    //create exit button
    btnExit = new QPushButton;
    btnExit->setText("EXIT");
    btnExit->setGeometry(850, 10, 100, 50);
    btnExit->setStyleSheet("color:black; background-color: transparent; font: bold 20px;");
    connect(btnExit, SIGNAL(clicked(bool)), this, SLOT(ExitGame()));
    scene->addWidget(btnExit);

    //create restart button
    btnRestart = new QPushButton;
    btnRestart->setText("RESTART");
    btnRestart->setGeometry(740, 10, 100, 50);
    btnRestart->setStyleSheet("color:black; background-color: transparent; font: bold 20px;");
    connect(btnRestart, SIGNAL(clicked(bool)), this, SLOT(RestartGame()));
    scene->addWidget(btnRestart);
}

void MainWindow::ExitGame()
{
    close();
    printf("exit\n");
}

void MainWindow::RestartGame()
{
    score=0;
    b_count=0;
    count[0]=0;
    count[1]=0;
    count[2]=0;

    NewObject();
    printf("exi2323t\n");
}
