/********************************************************************************
** Form generated from reading UI file 'createagent.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATEAGENT_H
#define UI_CREATEAGENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_CreateAgent
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QLabel *label;
    QLineEdit *lineEdit_2;
    QComboBox *comboBox;
    QLabel *label_3;

    void setupUi(QDialog *CreateAgent)
    {
        if (CreateAgent->objectName().isEmpty())
            CreateAgent->setObjectName(QStringLiteral("CreateAgent"));
        CreateAgent->resize(408, 303);
        buttonBox = new QDialogButtonBox(CreateAgent);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label_2 = new QLabel(CreateAgent);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(146, 100, 61, 20));
        lineEdit = new QLineEdit(CreateAgent);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(210, 70, 171, 23));
        label = new QLabel(CreateAgent);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(146, 70, 61, 20));
        lineEdit_2 = new QLineEdit(CreateAgent);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(210, 100, 171, 23));
        comboBox = new QComboBox(CreateAgent);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(210, 130, 171, 23));
        label_3 = new QLabel(CreateAgent);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(146, 130, 61, 20));

        retranslateUi(CreateAgent);
        QObject::connect(buttonBox, SIGNAL(accepted()), CreateAgent, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), CreateAgent, SLOT(reject()));

        QMetaObject::connectSlotsByName(CreateAgent);
    } // setupUi

    void retranslateUi(QDialog *CreateAgent)
    {
        CreateAgent->setWindowTitle(QApplication::translate("CreateAgent", "Dialog", 0));
        label_2->setText(QApplication::translate("CreateAgent", "Y center", 0));
        label->setText(QApplication::translate("CreateAgent", "X center", 0));
        label_3->setText(QApplication::translate("CreateAgent", "Behavior", 0));
    } // retranslateUi

};

namespace Ui {
    class CreateAgent: public Ui_CreateAgent {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEAGENT_H
