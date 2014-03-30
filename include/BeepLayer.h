#ifndef BEEPMODEL_H

#include "DiscreteTimeLayer.h"

typedef char BeepTree;

class BeepLayer : public DiscreteTimeLayer {
  public:
    BeepLayer();
    BeepLayer(double event_frequency);
    virtual ~BeepLayer();

    virtual void update(const Event* event);

  private:
    BeepTree beep_tree;
};

#define BEEPMODEL_H 
#endif /* BEEPMODEL_H */
