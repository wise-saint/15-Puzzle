//15 - Puzzle Problem Using A* Algorithm.
#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

//Puzzle class to store a state of the puzzle.  
class Puzzle{
    public:
        int A[4][4];
};

//Typedef for the information related to a state.
typedef pair<long long int, tuple<int, int, int, Puzzle*>> pi;

int cnt  = 0; //To count the number of states generated
Puzzle *goal = new Puzzle(); //To store the goal state.
priority_queue<pi, vector<pi>, greater<pi>> pq; //To store the states.
unordered_map<long long int, int> u; //To store the hash key of the states.

//Polynomial Rolling Hash function to convert the states in a hash key. 
long long int HashKeyGenerator(Puzzle *curr) {
    int x17 = 1;
    long long int key = 0;
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            key += curr->A[i][j]*x17;
            x17 *= 17;
        }
    }
    return key;
}

/*Function to check whether the state under 
consideration was discovered earlier or not*/
bool isDiscovered(long long int key) {
    auto itr = u.find(key);
    if(itr == u.end()) {u[key]++; return false;}
    return true;
}

/*Cost to next state calculator*/
int Heuristic(Puzzle *curr) {
    int cost = 0;
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            if(curr->A[i][j] != goal->A[i][j]) cost++;
    return cost;
}

/*Function to check whteher the current state
is the goal state or not*/
bool Match(Puzzle *curr) {
    bool ans = true;
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            if(curr->A[i][j] != goal->A[i][j]) 
                {ans = false; break;}
        }
        if(ans == false) break;
    }
    return ans;
}

//Function to copy the current state.
Puzzle* NewNode(Puzzle *curr) {
    Puzzle *temp = new Puzzle();
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++) 
            temp->A[i][j] = curr->A[i][j];
    return temp;
}

//Function to generate next states from a given state.
void Search() {
    if(pq.empty()) {cout<<"\nNot Solvable."<<endl; return;}
    pi pr = pq.top(); pq.pop();
    long long int fn = pr.first;
    int x = get<0>(pr.second), y = get<1>(pr.second), gn = get<2>(pr.second);
    Puzzle *curr = get<3>(pr.second);
    cnt++;
    if(Match(curr)) {cout<<"\nGoal state achieved!"<<endl; return;}
    if(y-1 >= 0) { //Left call.
        Puzzle *temp = NewNode(curr);
        swap(temp->A[x][y], temp->A[x][y-1]); //Next state creation.
        long long int key = HashKeyGenerator(temp);
        if(!isDiscovered(key)) {
            int hn = Heuristic(temp);
            pq.push(make_pair(hn+gn+1,make_tuple(x,y-1,gn+1,temp)));
        }
    }
    if(x+1 <= 3) { //Bottom call.
        Puzzle *temp = NewNode(curr);
        swap(temp->A[x][y], temp->A[x+1][y]);  //Next state creation.
        long long int key = HashKeyGenerator(temp);
        if(!isDiscovered(key)) {
            int hn = Heuristic(temp);
            pq.push(make_pair(hn+gn+1,make_tuple(x+1,y,gn+1,temp)));
        }
    }
    if(y+1 <= 3) { //Right call.
        Puzzle *temp = NewNode(curr);
        swap(temp->A[x][y], temp->A[x][y+1]);  //Next state creation.
        long long int key = HashKeyGenerator(temp);
        if(!isDiscovered(key)) {
           int hn = Heuristic(temp);
            pq.push(make_pair(hn+gn+1,make_tuple(x,y+1,gn+1,temp)));
        }
    }
    if(x-1 >= 0) { //Top call.
        Puzzle *temp = NewNode(curr);
        swap(temp->A[x][y], temp->A[x-1][y]);  //Next state creation.
        long long int key = HashKeyGenerator(temp);
        if(!isDiscovered(key)) {
            int hn = Heuristic(temp);
            pq.push(make_pair(hn+gn+1,make_tuple(x-1,y,gn+1,temp)));
        }
    }
    Search();
}

//Function to input current state.
void InputCurrentState() {
    Puzzle *curr = new Puzzle();
    int x, y;
    cout<<"\nEnter current state: ";
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) { 
            cin>>curr->A[i][j];
            if(curr->A[i][j] == 0) {x = i; y = j;}
        }
    }
    u[HashKeyGenerator(curr)]++;
    int hn = Heuristic(curr);
    pq.push(make_pair(hn,make_tuple(x,y,0,curr)));
}

//Function to input goal state.
void InputGoalState() {
    cout<<"Enter goal state: ";
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            cin>>goal->A[i][j];
}

//Main function.
int main(void) {
    cout<<"\n8 Puzzle solution using the A* algorithm."<<endl;
    InputGoalState();
    InputCurrentState();
    auto start = high_resolution_clock::now(); //Timer
    Search();
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout<<"Total time taken (including the file writing time) = "
        <<duration.count()<<" microseconds"<<endl;
    cout<<"Total number of states examined = "<<cnt<<endl<<endl;
    return 0;
}