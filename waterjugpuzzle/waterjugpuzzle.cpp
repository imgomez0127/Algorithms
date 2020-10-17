/*******************************************************************************
 * Name        : waterjugpuzzle.cpp
 * Author      : Ian Gomez
 * Date        : 10/18/2018
 * Description : Tries to solve the water jug problem with 3 jugs using a breadth first search
 * Pledge      : "I pledge my honor that I have abided by the Stevens honor system"-igomez1
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <memory>
using namespace std;
// Struct to represent state of water in the jugs.
enum Bucket{A, B, C};

struct State {
    public:
    int buckets[3];
    shared_ptr<State> parent;
    string directions;

    State(int _a, int _b, int _c) {
        buckets[0] = _a;
        buckets[1] = _b;
        buckets[2] = _c;
        parent = nullptr;
        directions = "";
    }

    // String representation of state in tuple form.
    string to_string() {
        ostringstream oss;
        oss << directions << " (" << buckets[A] << ", " << buckets[B] << ", " << buckets[C] << ")";
        return oss.str();
    }

    int operator[](int index) const{
        if(index < 0 || index > 3){
            cout << "tried index " << index << endl;
            cerr << "Index out of bounds" << endl;
            exit(1);
        }
        return buckets[index];
    }

    bool operator==(const State& state){
        return buckets[A] == state[A] && buckets[B] == state[B] && buckets[C] == state[C];
    }

};

class WaterJugPuzzle{
    /**
    * This class takes in the values for the max of each jug and the respective goals for each jug
    * It has a function which handels the pouring between jugs and also has a function which solves the problem
    * using a breadth first search approach through all the possible options
    */
    private:
        int bucket_max[3];
        State goal_state;
        int pours_directions[6][2]{
            {C, A},
            {B, A},
            {C, B},
            {A, B},
            {B, C},
            {A, C}
        };
        vector<vector<bool>> been_traversed;

    public:
        // takes in the input for the jugs max and goals and creates a matrix with an empty state
        WaterJugPuzzle(int * args): goal_state{State(args[3],args[4],args[5])}{
            bucket_max[A] = args[A];
            bucket_max[B] = args[B];
            bucket_max[C] = args[C];
            been_traversed = vector<vector<bool>>(bucket_max[A]+1,vector<bool>(bucket_max[B]+1, false));
        }

        void pour(shared_ptr<State> &s, int* pourType){
            /**
            * Takes in a refrence to an input state s and an int which specifies which pour is being perfomed it first checks whether or not
            * the pour can be performed if it cannot be performed then it returns false else if it is true it modifies that state according to the pour
            * and returns true
            */
            State state = *s;
            string names[3]{"A", "B", "C"};
            int start = pourType[0];
            int end = pourType[1];
            int pour_amt = max(min(bucket_max[end] - state[end], state[start]),0);
            s->buckets[end] += pour_amt;
            s->buckets[start] -= pour_amt;
            ostringstream oss;
            oss << "Pour " << pour_amt << (pour_amt > 1 ? " gallons" : " gallon")
                << " from " << names[start] << " to " << names[end] << ".";
            s->directions = oss.str();
        }

        string SolveWaterJug(){
            /**
            * This function returns the string which contains the steps to reach the solution.
            * The solution is found using a breadth first search through the possible types of pours
            */
            shared_ptr<State> start = make_shared<State>(0,0,bucket_max[C]);
            start->directions = "Initial state.";
            been_traversed[0][0] = true;
            queue<shared_ptr<State>> q;
            q.push(start);
            string S = "";
            shared_ptr<State> cur_state = nullptr;
            do{
                cur_state = q.front();
                q.pop();
                if (*cur_state == goal_state){
                    break;
                }
                for(int i = 0; i < 6; i++){
                    shared_ptr<State> new_state = make_shared<State>((*cur_state)[A], (*cur_state)[B], (*cur_state)[C]);
                    new_state->parent = cur_state;
                    pour(new_state, pours_directions[i]); //side affecting opeartion changes values of state
                    State new_state_val = *new_state;
                    if(!been_traversed[new_state_val[A]][new_state_val[B]]){
                        q.push(new_state);
                        been_traversed[new_state_val[A]][new_state_val[B]] = true;
                    }
                }
            }while(!q.empty());
            if(!(*cur_state == goal_state)){
                return "No solution.";
            }
            while(cur_state != nullptr){
                S = cur_state->to_string() + '\n' + S;
                cur_state = cur_state->parent;
            }
            return S;
        }
};

int main(int argc, char * const argv[]) {
    /**
    * This main function process all the strings and checks whether they are valid problems to attempt to solve
    * it then creates an instance of the WaterJugPuzzle and tries to solve the problem. It then either outputs the steps to and each state for the solution
    * or it returns that there is no solution for the problem
    */
    int arr[6] = {0,0,0,0,0,0};
    istringstream iss;
    if(argc != 7){
        cerr << "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
        return 1;
    }
    for(int i = 1; i < 4; ++i){
        iss.str(argv[i]);
        if(!(iss >> arr[i-1]) || (arr[i-1] <= 0)){
            cerr << "Error: Invalid capacity '" << argv[i] << "' for jug " << char(64+i) << "."<< endl;
            return 1;
        }
        iss.clear();
    }
    for(int i = 4; i < 7; ++i){
        iss.str(argv[i]);
        if(!(iss >> arr[i-1])|| (arr[i-1] <0)){
            cerr << "Error: Invalid goal '" << argv[i] << "' for jug " << char(61+i) << "." << endl;
            return 1;
        }
        iss.clear();
    }
    for(int i = 0; i < 3; ++i){
        if(arr[i+3] > arr[i]){
            cerr << "Error: Goal cannot exceed capacity of jug "<< char(65+i) << "."<< endl;
            return 1;
        }
    }
    if((arr[3] + arr[4] + arr[5]) != arr[2]){
        cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C."<< endl;
         return 1;
    }
    WaterJugPuzzle p(arr);
    cout << p.SolveWaterJug();
    return 0;
}
