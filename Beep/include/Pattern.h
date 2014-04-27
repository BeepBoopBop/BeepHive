#ifndef PATTERN_H
#define PATTERN_H 

#include "Factory.h"
#include "Command.h"

/*!
 * An abstract class for createing patterns of objects
 *
 * Returns parameters to be used when creating some object
 */
class Pattern
{
  public:
    //! returns the number of elements in the pattern, -1 for infinite
    virtual long int size() = 0;

    //! returns the next element of the pattern
    virtual FactoryParams getNext() = 0;

    virtual bool isEmpty() = 0;
};

/*!
 * Command for creating things with pattern args tagged on
 *
 * args:
 * pattern, pattern arg, command, command args
 */
class CreateWithPatternCommand : public CreateCommand
{
  public:
    CreateWithPatternCommand(FactoryParams params);

    virtual void run(World* world);
};



DEFINE_FACTORY(CreateWithPatternCommand, Command);

#endif /* PATTERN_H */
