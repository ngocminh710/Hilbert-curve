
#include "instruction_list.h"

// 1. print the instruction list
ostream& operator<<(ostream& out, const InstructionList& list){
    InstructionList::node_t* ptr = list.head;
    // iterate through the given list
    while(ptr!=nullptr){
        hilbert_t move = ptr->move;
        switch(move){
            // print "F " for FORWARD
            case FORWARD:
                out<<"F ";
                break;
            // print "L " for TURN_LEFT
            case TURN_LEFT:
                out<<"L ";
                break;
            // print "R" for TURN_RIGHT
            case TURN_RIGHT:
                out<<"R ";
                break;
            // print "O " for ODD
            case ODD:
                out<<"O ";
                break;
            // print "E " for EVEN
            case EVEN:
                out<<"E ";
                break;
            // default
            default:
                out<<"";;
        }
        ptr=ptr->next;//move to the next
    }
    return out;
}

// 2. add given instruction to the end of list
void InstructionList::append(hilbert_t h){
    node* newNode = new node; //allocate new node
    newNode->move = h; //put in the move
    newNode->next = nullptr; //set node to point to Null 
    if(head==nullptr){ //if head is Null, it is an empty list
        head = tail = newNode;
    } else { //else add new node at the end of the list
        tail->next = newNode;
        tail = newNode;
    }
}

// 3. Substitute the list according to the rules given
void InstructionList::substitute(const unordered_map<hilbert_t, const InstructionList*>& umap){
    if(head==nullptr) return;
    // create a new instruction list as the new rule
    InstructionList newRules;
    node_t* ptr = head;
    while(ptr!=nullptr){
        bool sub = false;
        // check every pairs in the given map
        for(auto x: umap){
            // if the move matches the key in the map
            // insert the corresponding instruction list
            if(ptr->move==x.first){
                sub = true;
                node_t* p = x.second->head;
                while(p!=nullptr){
                    newRules.append(p->move);
                    p = p->next;
                }
            } 
        }
        // if the move doesn't match any key
        // add the origiinal move into the new rule
        if(!sub) newRules.append(ptr->move);
        ptr = ptr->next;
    }
    // copy the new rule list to this list
    node_t* newP = newRules.head;
    node_t* oldP = head;
    while(newP!=nullptr){
        if(oldP==nullptr){
            append(newP->move);
        } else {
            oldP->move = newP->move;
            oldP = oldP->next;
        }
        newP = newP->next;
    }
}

// 4. Destructor for instructionList
InstructionList::~InstructionList(){
    if(head==nullptr) return;
    while(head!=nullptr){
        //delete the node pointed to by head
        node_t* p = head->next; //move head to the next node
        delete head; //deallocate memory
        head = p; //make p point to the new head
    }
}