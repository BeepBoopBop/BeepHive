#ifndef NEWBEEPTYPE_H
#define NEWBEEPTYPE_H

#include "ui_newbeeptype.h"
#include "gui_includes.h"

class newBeepType : public QDialog
{
    Q_OBJECT

public:
    explicit newBeepType(QWidget *parent = 0);
    void createNewBeepType();

private:
    Ui::newBeepType ui;
};

#endif // NEWBEEPTYPE_H
