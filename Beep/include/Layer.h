/*!
 * \class Layer
 * \brief Base layer class for use in discrete time simulator.
 */
#ifndef LAYER_H
#define LAYER_H 

#include "Event.h"
#include "World.h"
#include "Command.h"

class Event;
class World;

/*!
 * Layers are the different kinds of time-stepped components of the
 * environment.
 *
 * Typically a Layer will be responsible for modeling properties of the
 * environment such as heat properties. However, it is also possible for
 * other sorts of time dependent code to be run in a layer such as
 * synchronization with external processes for example the GUI.
 *
 * \warning
 * Updates to layers are not automatically checked for synchronization
 * across processes. Layers not inheriting from DiscreteTimeLayer should
 * ensure that all events are scheduled at the same times. 
 */
class Layer {
  public:
    Layer();
    Layer(double event_frequency);
    virtual ~Layer();

    double getTime() const;
    virtual void setTime(double new_time);

    virtual double timeSinceLastUpdate();

    //! This is the main code for the Layer class
    virtual void update(const Event* event, World* world);

    //! Writes data to the Communicator
    virtual void write() = 0;

    /*!
     * The returned event should be given the time that the layer
     * should next be updated
     */
    virtual Event getNextEvent() = 0;
  
    /*!
     * Get a value at a point in a certian layer. 
     * Only nontrivial for physical layers like HeatLayer.
     * Returns 0 by default.
     */
    virtual double getValue( double x, double y );

  protected:
    double time;
};



class LayerCommand : public Command
{
  public:
    LayerCommand() { frequency = "1"; }
    LayerCommand(FactoryParams params);
    virtual void run(World* world);

    //serialization
    virtual void saveHelper(ptree& tree);
    void load(std::string JSON);
    std::string type() { return "LayerCommand"; }
  private:
    std::string frequency;
    std::string name;
    std::string concrete_type;
};

DEFINE_FACTORY(LayerCommand, Command);

#endif /* LAYER_H */
