/*******************************************************************************
 * Name        : waterjugpuzzle.cpp
 * Author      : Ian Gomez
 * Date        : 10/18/2018
 * Description : Tries to solve the water jug problem with 3 jugs using a breadth first search
 * Pledge      : "I pledge my honor that I have abided by the Stevens honor system"-igomez1
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
using namespace std;
// Struct to represent state of water in the jugs.
struct State {
    int a, b, c;
    string directions;
    State(int _a, int _b, int _c) : a(_a), b(_b), c(_c) { }
    // String representation of state in tuple form.
    string to_string() {
        ostringstream oss;
        oss << "(" << a << ", " << b << ", " << c << ")";
        return oss.str();
    }
};
class WaterJugPuzzle{
    /**
    * This class takes in the values for the max of each jug and the respective goals for each jug
    * It has a function which handels the pouring between jugs and also has a function which solves the problem
    * using a breadth first search approach through all the possible options
    */
    private:
        int a_max;
        int b_max;
        int c_max;
        int a_goal;
        int b_goal;
        int c_goal;
        vector<vector<State>> beenTraversed;
    public:
        // takes in the input for the jugs max and goals and creates a matrix with an empty state
        WaterJugPuzzle(int a_,int b_, int c_,int agoal, int bgoal, int cgoal): a_max{a_},b_max{b_},c_max{c_},a_goal{agoal},b_goal{bgoal},c_goal{cgoal}{
            
            for(int i = 0; i <= a_max; i++){
                vector<State> nullList(b_max+1,State(0,0,0));
                beenTraversed.push_back(nullList);
            }
        }
        bool pour(State &s, int pourType){
            /**
            * Takes in a refrence to an input state s and an int which specifies which pour is being perfomed it first checks whether or not
            * the pour can be performed if it cannot be performed then it returns false else if it is true it modifies that state according to the pour
            * and returns true
            */
            if(pourType == 1){
                //Pour C to A
                int contentDiff = a_max - s.a;
                int pourAmt = contentDiff;
                if(contentDiff == 0){
                    return false;
                }
                if(s.c == 0){
                    return false;
                }
                if(contentDiff > s.c){
                    s.a += s.c;
                    pourAmt = s.c;
                    s.c = 0;
                    
                }
                else{
                    s.a = a_max;
                    s.c -= contentDiff;
                }
                s.directions = "Pour " + to_string(pourAmt) + ((pourAmt > 1)?" gallons":" gallon") + " from C to A. " + s.to_string();

                return true;
            }
            if(pourType == 2){
                // Pour B to A
                int contentDiff = a_max - s.a;
                int pourAmt = contentDiff;
                if(contentDiff == 0){
                    return false;
                }
                if(s.b == 0){
                    return false;
                }
                if(contentDiff > s.b){
                    s.a += s.b;
                    pourAmt = s.b;
                    s.b = 0;
                }
                else{
                    s.a = a_max;
                    s.b -= contentDiff;
                }
                s.directions = "Pour " + to_string(pourAmt) + ((pourAmt > 1)?" gallons":" gallon") + " from B to A. " + s.to_string();
                return true;
            }
            if(pourType == 3){
                //Pour C to B
                int contentDiff = b_max - s.b;
                int pourAmt = contentDiff;
                if(contentDiff == 0){
                    return false;
                }
                if(s.c == 0){
                    return false;
                }
                if(contentDiff > s.c){
                    s.b += s.c;
                    pourAmt = s.c;
                    s.c = 0;
                }
                else{
                    s.b = b_max;
                    s.c -= contentDiff;
                }
                s.directions = "Pour " + to_string(pourAmt) + ((pourAmt > 1)?" gallons":" gallon") + " from C to B. " + s.to_string();
                return true;
            }
            if(pourType == 4){
                //pour A to B
                int contentDiff = b_max - s.b;
                int pourAmt = contentDiff;
                if(contentDiff == 0){
                    return false;
                }
                if(s.a == 0){
                    return false;
                }
                if(contentDiff > s.a){
                    s.b += s.a;
                    pourAmt = s.a;
                    s.a = 0;
                }
                else{
                    s.b = b_max;
                    s.a -= contentDiff;
                }
                s.directions = "Pour " + to_string(pourAmt) + ((pourAmt > 1)?" gallons":" gallon") + " from A to B. " + s.to_string();
                return true;
            }
            if(pourType == 5){
                //Pour B to C
                int contentDiff = c_max - s.c;
                int pourAmt = contentDiff;
                if(contentDiff == 0){
                    return false;
                }
                if(s.b == 0){
                    return false;
                }
                if(contentDiff > s.b){
                    s.c += s.b;
                    pourAmt = s.b;
                    s.b = 0;
                }
                else{
                    s.c = c_max;
                    s.b = 0;
                }
                s.directions = "Pour " + to_string(pourAmt) + ((pourAmt > 1)?" gallons":" gallon") + " from B to C. " + s.to_string();
                return true;
            }
            if(pourType == 6){
                //Pour A to C
                int contentDiff = c_max - s.c;
                int pourAmt = contentDiff;
                if(contentDiff == 0){
                    return false;
                }
                if(s.a == 0){
                    return false;
                }
                if(contentDiff > s.a){
                    s.c += s.a;
                    pourAmt = s.a;
                    s.a = 0;
                }
                else{
                    s.c = c_max;
                    s.a = 0;
                }
                s.directions = "Pour " + to_string(pourAmt) + ((pourAmt > 1)?" gallons":" gallon") + " from A to C. " + s.to_string();
                return true;
            }
            return false;
        }
        string SolveWaterJug(){
            /**
            * This function returns the string which contains the steps to reach the solution.
            * The solution is found using a breadth first search through the possible types of pours
            */
            State start(0,0,c_max);
            start.directions = "Initial state. " + start.to_string();
            beenTraversed[0][0] = start;
            queue<State> q;
            q.push(start);
            string S = "";
            do{
                State currState = q.front();
                q.pop();
                if (currState.a == a_goal && currState.b == b_goal && currState.c == c_goal){
                    S = currState.directions;
                    break;
                }
                    for(int i = 1; i < 7; i++){
                        State newState(currState.a,currState.b,currState.c);
                        if(pour(newState,i)){
                            if(beenTraversed[newState.a][newState.b].to_string() == "(0, 0, 0)"){
                                q.push(newState);
                                beenTraversed.at(newState.a).at(newState.b) = currState;     
                        }   
                        
                    }
                }
            }while(!q.empty());
            if(S == ""){
                S = "No solution.";
            } 
            else{
                State currState(a_goal,b_goal,c_goal);
                while(currState.to_string() != start.to_string()){
                    currState = beenTraversed[currState.a][currState.b];
                    S = currState.directions + "\n" + S;
                }
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
    WaterJugPuzzle p(arr[0],arr[1],arr[2],arr[3],arr[4],arr[5]);
    cout << p.SolveWaterJug() << endl;
    return 0;
}
