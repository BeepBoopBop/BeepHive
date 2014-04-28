/********************************************************************************
** Form generated from reading UI file 'createenvironment.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATEENVIRONMENT_H
#define UI_CREATEENVIRONMENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_CreateEnvironment
{
public:
    QDialogButtonBox *buttonBox;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *lineEdit_4;
    QLabel *label_4;
    QCheckBox *checkBox;
    QLabel *label_5;

    void setupUi(QDialog *CreateEnvironment)
    {
        if (CreateEnvironment->objectName().isEmpty())
            CreateEnvironment->setObjectName(QStringLiteral("CreateEnvironment"));
        CreateEnvironment->resize(400, 247);
        buttonBox = new QDialogButtonBox(CreateEnvironment);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(30, 190, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        lineEdit = new QLineEdit(CreateEnvironment);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(200, 20, 171, 23));
        lineEdit_2 = new QLineEdit(CreateEnvironment);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(200, 50, 171, 23));
        lineEdit_3 = new QLineEdit(CreateEnvironment);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(200, 80, 171, 23));
        label = new QLabel(CreateEnvironment);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(140, 20, 57, 15));
        label_2 = new QLabel(CreateEnvironment);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(140, 50, 57, 15));
        label_3 = new QLabel(CreateEnvironment);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(140, 80, 57, 15));
        lineEdit_4 = new QLineEdit(CreateEnvironment);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));
        lineEdit_4->setGeometry(QRect(200, 110, 171, 21));
        label_4 = new QLabel(CreateEnvironment);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(140, 110, 57, 15));
        checkBox = new QCheckBox(CreateEnvironment);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(230, 140, 21, 21));
        label_5 = new QLabel(CreateEnvironment);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(140, 140, 81, 20));

        retranslateUi(CreateEnvironment);
        QObject::connect(buttonBox, SIGNAL(accepted()), CreateEnvironment, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), CreateEnvironment, SLOT(reject()));

        QMetaObject::connectSlotsByName(CreateEnvironment);
    } // setupUi

    void retranslateUi(QDialog *CreateEnvironment)
    {
        CreateEnvironment->setWindowTitle(QApplication::translate("CreateEnvironment", "Dialog", 0));
        label->setText(QApplication::translate("CreateEnvironment", "X center", 0));
        label_2->setText(QApplication::translate("CreateEnvironment", "Y center", 0));
        label_3->setText(QApplication::translate("CreateEnvironment", "Width", 0));
        label_4->setText(QApplication::translate("CreateEnvironment", "Height", 0));
        checkBox->setText(QApplication::translate("CreateEnvironment", "CheckBox", 0));
        label_5->setText(QApplication::translate("CreateEnvironment", "Heatsource", 0));
    } // retranslateUi

};

namespace Ui {
    class CreateEnvironment: public Ui_CreateEnvironment {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEENVIRONMENT_H
