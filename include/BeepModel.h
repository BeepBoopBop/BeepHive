#ifndef BEEPMODEL_H

#include "DiscreteTimeModel.h"

typedef char BeepTree;

class BeepModel : public DiscreteTimeModel {
  public:
    BeepModel();
    BeepModel(double event_frequency);
    virtual ~BeepModel();

    virtual void update(Event* event);

  private:
    BeepTree beep_tree;
};

#define BEEPMODEL_H 
#endif /* BEEPMODEL_H */
