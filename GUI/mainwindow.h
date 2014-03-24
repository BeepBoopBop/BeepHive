#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <vector>
#include <QDebug>
#include <QPropertyAnimation>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void moveAgents();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    std::vector <QGraphicsRectItem*> ellipse;
    std::vector <int> xPosition;
    std::vector <int> yPosition;
    std::vector <int> xVelocity;
    std::vector <int> yVelocity;
    QGraphicsRectItem *rectangle;

};

#endif // MAINWINDOW_H
