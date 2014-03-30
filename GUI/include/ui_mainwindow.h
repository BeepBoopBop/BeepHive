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
    QAction *actionSource;
    QAction *actionWall;
    QAction *actionStep;
    QWidget *centralWidget;
    QGraphicsView *graphicsView;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuAdd;
    QMenu *menuEnvironment;
    QMenu *menuAgents;
    QMenu *menuEnvironments;
    QMenu *menuResults;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(509, 407);
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionAgent = new QAction(MainWindow);
        actionAgent->setObjectName(QStringLiteral("actionAgent"));
        actionSource = new QAction(MainWindow);
        actionSource->setObjectName(QStringLiteral("actionSource"));
        actionWall = new QAction(MainWindow);
        actionWall->setObjectName(QStringLiteral("actionWall"));
        actionStep = new QAction(MainWindow);
        actionStep->setObjectName(QStringLiteral("actionStep"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(70, 100, 351, 141));
        graphicsView->setAutoFillBackground(false);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 509, 20));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QStringLiteral("menuEdit"));
        menuAdd = new QMenu(menuEdit);
        menuAdd->setObjectName(QStringLiteral("menuAdd"));
        menuEnvironment = new QMenu(menuAdd);
        menuEnvironment->setObjectName(QStringLiteral("menuEnvironment"));
        menuAgents = new QMenu(menuBar);
        menuAgents->setObjectName(QStringLiteral("menuAgents"));
        menuEnvironments = new QMenu(menuBar);
        menuEnvironments->setObjectName(QStringLiteral("menuEnvironments"));
        menuResults = new QMenu(menuBar);
        menuResults->setObjectName(QStringLiteral("menuResults"));
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
        menuFile->addAction(actionSave);
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionExit);
        menuEdit->addAction(menuAdd->menuAction());
        menuEdit->addAction(actionStep);
        menuAdd->addAction(actionAgent);
        menuAdd->addAction(menuEnvironment->menuAction());
        menuEnvironment->addAction(actionSource);
        menuEnvironment->addAction(actionWall);

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
        actionSource->setText(QApplication::translate("MainWindow", "Source", 0));
        actionWall->setText(QApplication::translate("MainWindow", "Wall", 0));
        actionStep->setText(QApplication::translate("MainWindow", "Step", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
        menuEdit->setTitle(QApplication::translate("MainWindow", "Edit", 0));
        menuAdd->setTitle(QApplication::translate("MainWindow", "Add", 0));
        menuEnvironment->setTitle(QApplication::translate("MainWindow", "Environment", 0));
        menuAgents->setTitle(QApplication::translate("MainWindow", "Agents", 0));
        menuEnvironments->setTitle(QApplication::translate("MainWindow", "Environments", 0));
        menuResults->setTitle(QApplication::translate("MainWindow", "Results", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
