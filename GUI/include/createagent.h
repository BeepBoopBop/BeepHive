#ifndef CREATEAGENT_H
#define CREATEAGENT_H

#include <QDialog>
#include "gui_includes.h"

namespace Ui {
class CreateAgent;
}

class CreateAgent : public QDialog
{
    Q_OBJECT

public:
    explicit CreateAgent(QWidget *parent = 0);
    ~CreateAgent();
    int getX();
    int getY();

private:
    Ui::CreateAgent *ui;
};

#endif // CREATEAGENT_H
