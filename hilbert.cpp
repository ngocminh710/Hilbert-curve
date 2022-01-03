
#include "turtle.h"
#include "instruction_list.h"
#include "hilbert.h"
#include <iostream>
#include <unordered_map>

using namespace std;

HilbertCurve::HilbertCurve(int level, int size):turtle(size,size){
    unordered_map<hilbert_t, const InstructionList*> subMap;
    InstructionList* oddList = new InstructionList();
    InstructionList* evenList = new InstructionList();
    //create odd instruction list
    oddList->append(TURN_LEFT);
    oddList->append(EVEN);
    oddList->append(FORWARD);
    oddList->append(TURN_RIGHT);
    oddList->append(ODD);
    oddList->append(FORWARD);
    oddList->append(ODD);
    oddList->append(TURN_RIGHT);
    oddList->append(FORWARD);
    oddList->append(EVEN);
    oddList->append(TURN_LEFT);

    // create even instruction list
    evenList->append(TURN_RIGHT);
    evenList->append(ODD);
    evenList->append(FORWARD);
    evenList->append(TURN_LEFT);
    evenList->append(EVEN);
    evenList->append(FORWARD);
    evenList->append(EVEN);
    evenList->append(TURN_LEFT);
    evenList->append(FORWARD);
    evenList->append(ODD);
    evenList->append(TURN_RIGHT);

    // create substitution map
    subMap[ODD] = oddList;
    subMap[EVEN] = evenList;
    
    // substitute rules for the given levels.
    rules.append(ODD); //start from the list [ODD]
    for(int i=0; i<level; i++){
        rules.substitute(subMap);
    }
    // each successive level moves forward half the size 
    double distance = size;
    for(int i=0; i<level; i++){
        distance = distance/2;
    }
    //specify distance Turtle moves on a FORWARD instruction
    rules.setDistance(distance); 
    
    //Initialize Turtle to draw a Hilbert curve
    InstructionList::iterator it = rules.begin();
    while(it!=rules.end()){
        hilbert_t move = *it;
        switch(move){
            // draw forward
            case FORWARD:
                turtle.forward(rules.getDistance());
                break;

            // draw left
            case TURN_LEFT:
                turtle.turnLeft();
                break;

            // draw right
            case TURN_RIGHT:
                turtle.turnRight();
                break;
            
            case ODD:
                break;
            case EVEN:
                break;
        }
        ++it;
    }  
}