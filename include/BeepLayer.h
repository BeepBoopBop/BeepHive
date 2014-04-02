#ifndef BEEPLAYER_H
#define BEEPLAYER_H 

#include <vector>

#include "DiscreteTimeLayer.h"
#include "Beep.h"

class Beep;

typedef std::vector<Beep*> Beeps;

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

    virtual void update(const Event* event, World* world);

  private:
    BeepLayer();
    BeepLayer(double event_frequency);
    BeepLayer(const BeepLayer& copy);
    BeepLayer& operator=(const BeepLayer& copy);

    Beeps beeps;
};

#endif /* BEEPLAYER_H */
