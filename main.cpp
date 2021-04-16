#include <iostream>
#include <set>
#include "MuhleState.h"

void search(
        MuhleState & muhleState,
        std::set<MuhleState> & visited_nodes,
        int depth = 0/*,
        double already_solved = 0,
        double fraction = 100*/
){
    //double current_already_solved = already_solved;
    //std::cout << current_already_solved << std::endl;
    /*if (depth > 100){
        return;
    }*/
    visited_nodes.insert(muhleState);
    std::vector< Action> legalActions = muhleState.getLegalActions();
    for(Action action : legalActions){
        MuhleState newState = muhleState.playAction(action);

        if (visited_nodes.find(newState) != visited_nodes.end()){
            continue;
        }

        if(newState.isFinal()){
            std::cout << depth << std::endl;
            continue;
        }
        search(newState, visited_nodes, depth + 1/*, current_already_solved, fraction / (double)legalActions.size()*/);
        //current_already_solved += fraction/(double)legalActions.size();
    }
    visited_nodes.erase(muhleState);

}

int main() {
    std::cout << "start of code "<<std::endl;
    MuhleState initialState = MuhleState();
    std::cout << "start of searching "<<std::endl;
    std::set<MuhleState> visited_nodes;
    search(initialState, visited_nodes);
    return 0;
}
