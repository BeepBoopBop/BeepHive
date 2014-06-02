#ifndef CREATEENVIRONMENT_H
#define CREATEENVIRONMENT_H

#include <QDialog>

namespace Ui {
  class CreateEnvironment;
}

class CreateEnvironment : public QDialog
{
  Q_OBJECT

  public:
    explicit CreateEnvironment(QWidget *parent = 0);
    ~CreateEnvironment();
    Ui::CreateEnvironment *ui;
    int getX();
    int getY();
    int getWidth();
    int getHeight();
    bool getSource();
};

#endif // CREATEENVIRONMENT_H
