#include "mainwindow.h"
#include "ui_mainwindow.h"


int randInt(int low, int high)
{
    // Random number between low and high
    return qrand() % ((high + 1) - low) + low;
}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    setCentralWidget(ui->graphicsView);

    QBrush greenBrush(Qt::green);
    QPen outlinePen(Qt::black);
    outlinePen.setWidth(2);


    /*QGraphicsRectItem* tempEllipse = new QGraphicsRectItem();
    for(int i = 0; i < 10; i++){

        //generate starting locations
        int tempX = randInt(0,400);
        xPosition.push_back(tempX);
        int tempY = randInt(0,400);
        yPosition.push_back(tempY);

        //draw the agents
        tempEllipse= scene->addRect(tempX, tempY, 10, 10, outlinePen, greenBrush);
        tempEllipse->setFlag(QGraphicsItem::ItemIsMovable);
        ellipse.push_back(tempEllipse);

        //generate starting velocities
        int randomNumber = randInt(0, 2) - 1;
        xVelocity.push_back(randomNumber);
        randomNumber = randInt(0,2) - 1;
        yVelocity.push_back(randomNumber);
    }*/

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::moveAgents(){
    scene->clear();
}
