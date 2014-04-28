/********************************************************************************
** Form generated from reading UI file 'newbeeptype.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWBEEPTYPE_H
#define UI_NEWBEEPTYPE_H

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

class Ui_newBeepType
{
public:
    QDialogButtonBox *buttonBox;
    QLineEdit *lineEdit;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QComboBox *comboBox;
    QComboBox *comboBox_2;
    QLabel *label_4;
    QComboBox *comboBox_3;

    void setupUi(QDialog *newBeepType)
    {
        if (newBeepType->objectName().isEmpty())
            newBeepType->setObjectName(QStringLiteral("newBeepType"));
        newBeepType->resize(400, 277);
        buttonBox = new QDialogButtonBox(newBeepType);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(30, 230, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        lineEdit = new QLineEdit(newBeepType);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(220, 20, 161, 23));
        label = new QLabel(newBeepType);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(100, 20, 111, 20));
        label_2 = new QLabel(newBeepType);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(100, 70, 111, 20));
        label_3 = new QLabel(newBeepType);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(100, 120, 121, 20));
        comboBox = new QComboBox(newBeepType);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(220, 70, 161, 23));
        comboBox_2 = new QComboBox(newBeepType);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));
        comboBox_2->setGeometry(QRect(220, 120, 161, 23));
        label_4 = new QLabel(newBeepType);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(100, 170, 121, 20));
        comboBox_3 = new QComboBox(newBeepType);
        comboBox_3->setObjectName(QStringLiteral("comboBox_3"));
        comboBox_3->setGeometry(QRect(220, 170, 161, 23));

        retranslateUi(newBeepType);
        QObject::connect(buttonBox, SIGNAL(accepted()), newBeepType, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), newBeepType, SLOT(reject()));

        QMetaObject::connectSlotsByName(newBeepType);
    } // setupUi

    void retranslateUi(QDialog *newBeepType)
    {
        newBeepType->setWindowTitle(QApplication::translate("newBeepType", "Dialog", 0));
        label->setText(QApplication::translate("newBeepType", "Beep name", 0));
        label_2->setText(QApplication::translate("newBeepType", "Beep sensor", 0));
        label_3->setText(QApplication::translate("newBeepType", "Beep controller", 0));
        label_4->setText(QApplication::translate("newBeepType", "Beep manipulator", 0));
    } // retranslateUi

};

namespace Ui {
    class newBeepType: public Ui_newBeepType {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWBEEPTYPE_H
