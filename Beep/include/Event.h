#ifndef EVENT_H
#define EVENT_H 

class Layer;

/*!
 * Event class for use in discrete time simulator.
 */
class Event {
  public:
    Event(Layer* layer, double time);

    bool operator<(const Event& event) const;

    Layer* getLayer();

    void setTime(double time);
    double getTime() const;

  private:
    double time;
    Layer* layer;
};

/*!
 * Comparison operator for Events
 *
 * Compares Events by time
 */
class EventComparator
{
  public:
    bool operator()(const Event first, const Event second) const;
};

#endif /* EVENT_H */
