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

    // When a stated is added we pass the function that represents 
    // that state logic
    State addState(void (*functionPointer)());

    // Attributes
    LinkedList<State> *stateList;
    int currentState = -1;
};

Statemachine::Statemachine(){
  stateList = new LinkedList<State>();
};

Statemachine::~Statemachine(){};

/*
 * Main execution of the machine occurs here in run
 * The current state is executed and it's transitions are evaluated
 * to determine the next state. 
 * 
 * By design, only one state is executed in one loop() cycle.
 */
void Statemachine::run(){
  // Early exit, no states are defined
  if(stateList->size() == 0) return;

  // Initial condition
  if(currentState == -1){
    currentState = 0;
  }
  
  if(DEBUG) Serial.print("Evaluating S");
  if(DEBUG) Serial.println(currentState);
  
  int next = stateList->get(currentState).execute();

  if(DEBUG) Serial.print(" returns ");
  if(DEBUG) Serial.println(next);
  
  if(next >= 0){
    currentState = next;
  }
}

/*
 * Adds a state to the machine
 * It adds the state in sequential order.
 */
State Statemachine::addState(void(*functionPointer)()){
  State s = State();
  s.stateLogic = functionPointer;
  stateList->add(s);
  return s;
}

#endif
