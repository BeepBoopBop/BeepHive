#ifndef NEWBEEPTYPE_H
#define NEWBEEPTYPE_H

#include "GuiIncludes.h"
#include "ui_newbeeptype.h"

class NewBeepType : public QDialog
{
  Q_OBJECT

  public:
    explicit NewBeepType(QWidget *parent = 0);
    void createNewBeepType();

  private:
    Ui::newBeepType ui;
};

#endif // NEWBEEPTYPE_H
