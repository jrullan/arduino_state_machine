#include <LinkedList.h>
#include "state.h"

#ifndef _MACHINE_H
#define _MACHINE_H

class Statemachine
{
  public:
    // Methods
    
    Statemachine();
    ~Statemachine();

    void init();

    void run();

    // When a stated is added we pass the function that represents that state
    State addState(void (*functionPointer)());

    // Attributes
    //LinkedList<void (*)()> stateList;
    LinkedList<State> stateList;
    int currentState = -1;
};

Statemachine::Statemachine(){};

Statemachine::~Statemachine(){};

void Statemachine::init(){
  if(stateList.size() > 0){
    currentState = 0;
  }
}

void Statemachine::run(){
  if(currentState == -1 && stateList.size()>0){
    currentState = 0;
  }
  if(DEBUG) Serial.print("Evaluating S");
  if(DEBUG) Serial.println(currentState);
  
  int next = stateList.get(currentState).execute();

  if(DEBUG) Serial.print(" returns ");
  if(DEBUG) Serial.println(next);
  
  if(next >= 0){
    currentState = next;
  }
}

State Statemachine::addState(void(*functionPointer)()){
  State s = State();
  s.stateLogic = functionPointer;
  stateList.add(s);
  return s;
  //stateList.add(functionPointer);
  //return (void*)functionPointer;
}

#endif
