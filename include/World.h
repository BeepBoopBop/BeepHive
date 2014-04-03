#ifndef WORLD_H
#define WORLD_H 

#include <vector>
#include <queue>
#include <string>

#include "BeepHive.h"
#include "Event.h"
#include "Layer.h"
#include "Beep.h"

class Layer;
class Event;
class Beep;

class EventComparator
{
  public:
    bool operator()(const Event first, const Event second) const;
};

typedef std::vector<Beep*> Beeps;
typedef std::vector<Layer*> LayerArray;
typedef std::priority_queue<Event,std::vector<Event>,EventComparator> EventQueue;
//typedef std::priority_queue<Event,std::vector<Event> > EventQueue;

class World {
  public:
    World();
    virtual ~World();
    int step();
    int start();

    void addLayer(std::string layer_name, Layer* layer, double start_time=0);
    Layer* getLayer(std::string layer_name);

    typedef Beeps::iterator BeepIterator;
    BeepIterator beepBegin();
    BeepIterator beepEnd();
    void addBeep(Beep* beep);

    void addMessageToGui(std::string message);
    const std::string& getMessagesToGui();
    void clearMessagesToGui();

    const std::string& getMessagesFromGui();
    void setMessagesFromGui(std::string messages);

    void quit();
  private:
    Beeps beeps;
    Map<Layer*> layers;
    EventQueue event_queue;

    std::string messages_to_gui;
    std::string messages_from_gui;
    bool running;
};

#endif /* WORLD_H */
