#ifndef BEEPMODEL_H

#include "DiscreteTimeLayer.h"

typedef char BeepTree;

/*!
 * The beep layer is responsible for initiating updates to all beeps
 *
 * This is a special layer that users are not able to instantiate as it relates
 * to the beep data structure within the World class. Having multiple BeepLayers
 * would likely result in buggy execution.
 */
class BeepLayer : public DiscreteTimeLayer {
  friend class World;
  public:
    virtual ~BeepLayer();

    virtual void update(const Event* event);

  private:
    BeepLayer();
    BeepLayer(double event_frequency);
    BeepLayer(const BeepLayer& copy);
    BeepLayer& operator=(const BeepLayer& copy);

    BeepTree beep_tree;
};

#define BEEPMODEL_H 
#endif /* BEEPMODEL_H */
