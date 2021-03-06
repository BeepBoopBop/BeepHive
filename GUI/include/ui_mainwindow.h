/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionSave;
    QAction *actionOpen;
    QAction *actionExit;
    QAction *actionAgent;
    QAction *actionObject;
    QAction *actionWall;
    QAction *actionStep;
    QAction *actionEnvironment;
    QAction *actionStart;
    QAction *actionPause;
    QAction *actionContinue;
    QAction *actionTest;
    QAction *actionAgent_2;
    QAction *actionCreate_New_Beep;
    QAction *actionAdd_Environment;
    QWidget *centralWidget;
    QGraphicsView *graphicsView;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuAgents;
    QMenu *menuEnvironments;
    QMenu *menuResults;
    QMenu *menuSimulation;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(499, 356);
        MainWindow->setAnimated(true);
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionAgent = new QAction(MainWindow);
        actionAgent->setObjectName(QStringLiteral("actionAgent"));
        actionObject = new QAction(MainWindow);
        actionObject->setObjectName(QStringLiteral("actionObject"));
        actionWall = new QAction(MainWindow);
        actionWall->setObjectName(QStringLiteral("actionWall"));
        actionStep = new QAction(MainWindow);
        actionStep->setObjectName(QStringLiteral("actionStep"));
        actionEnvironment = new QAction(MainWindow);
        actionEnvironment->setObjectName(QStringLiteral("actionEnvironment"));
        actionStart = new QAction(MainWindow);
        actionStart->setObjectName(QStringLiteral("actionStart"));
        actionPause = new QAction(MainWindow);
        actionPause->setObjectName(QStringLiteral("actionPause"));
        actionPause->setCheckable(false);
        actionContinue = new QAction(MainWindow);
        actionContinue->setObjectName(QStringLiteral("actionContinue"));
        actionContinue->setCheckable(false);
        actionTest = new QAction(MainWindow);
        actionTest->setObjectName(QStringLiteral("actionTest"));
        actionAgent_2 = new QAction(MainWindow);
        actionAgent_2->setObjectName(QStringLiteral("actionAgent_2"));
        actionCreate_New_Beep = new QAction(MainWindow);
        actionCreate_New_Beep->setObjectName(QStringLiteral("actionCreate_New_Beep"));
        actionAdd_Environment = new QAction(MainWindow);
        actionAdd_Environment->setObjectName(QStringLiteral("actionAdd_Environment"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(40, 30, 391, 191));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(graphicsView->sizePolicy().hasHeightForWidth());
        graphicsView->setSizePolicy(sizePolicy1);
        graphicsView->setAutoFillBackground(false);
        graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 499, 20));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QStringLiteral("menuEdit"));
        menuAgents = new QMenu(menuBar);
        menuAgents->setObjectName(QStringLiteral("menuAgents"));
        menuEnvironments = new QMenu(menuBar);
        menuEnvironments->setObjectName(QStringLiteral("menuEnvironments"));
        menuResults = new QMenu(menuBar);
        menuResults->setObjectName(QStringLiteral("menuResults"));
        menuSimulation = new QMenu(menuBar);
        menuSimulation->setObjectName(QStringLiteral("menuSimulation"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuBar->addAction(menuAgents->menuAction());
        menuBar->addAction(menuEnvironments->menuAction());
        menuBar->addAction(menuResults->menuAction());
        menuBar->addAction(menuSimulation->menuAction());
        menuFile->addAction(actionSave);
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionExit);
        menuEdit->addAction(actionStep);
        menuAgents->addAction(actionAgent_2);
        menuAgents->addAction(actionCreate_New_Beep);
        menuEnvironments->addAction(actionAdd_Environment);
        menuSimulation->addAction(actionStart);
        menuSimulation->addAction(actionPause);
        menuSimulation->addAction(actionContinue);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionSave->setText(QApplication::translate("MainWindow", "Save", 0));
        actionOpen->setText(QApplication::translate("MainWindow", "Open", 0));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", 0));
        actionAgent->setText(QApplication::translate("MainWindow", "Agent", 0));
        actionObject->setText(QApplication::translate("MainWindow", "Object", 0));
        actionWall->setText(QApplication::translate("MainWindow", "Wall", 0));
        actionStep->setText(QApplication::translate("MainWindow", "Step", 0));
        actionEnvironment->setText(QApplication::translate("MainWindow", "Environment", 0));
        actionStart->setText(QApplication::translate("MainWindow", "Start", 0));
        actionPause->setText(QApplication::translate("MainWindow", "Pause", 0));
        actionContinue->setText(QApplication::translate("MainWindow", "Continue", 0));
        actionTest->setText(QApplication::translate("MainWindow", "test", 0));
        actionAgent_2->setText(QApplication::translate("MainWindow", "Add Beep", 0));
        actionCreate_New_Beep->setText(QApplication::translate("MainWindow", "New Beep Type", 0));
        actionAdd_Environment->setText(QApplication::translate("MainWindow", "Add Object", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
        menuEdit->setTitle(QApplication::translate("MainWindow", "Edit", 0));
        menuAgents->setTitle(QApplication::translate("MainWindow", "Agents", 0));
        menuEnvironments->setTitle(QApplication::translate("MainWindow", "Environments", 0));
        menuResults->setTitle(QApplication::translate("MainWindow", "Results", 0));
        menuSimulation->setTitle(QApplication::translate("MainWindow", "Simulation", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
