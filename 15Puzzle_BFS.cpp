//15 - Puzzle Problem Using BFS Algorithm.
#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

//Puzzle class to store a state of the puzzle.  
class Puzzle{
    public:
        int A[4][4];
};

int cnt  = 0; //To count the number of states generated.
Puzzle *goal = new Puzzle(); //To store the goal state.
queue<Puzzle*> states; //To store the states.
queue<pair<int,int>> q; //To store the index of blank cell in the states.
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

/*Function to check whteher the current state
is the goal state or not*/
bool Match() {
    Puzzle *curr = states.front(); 
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
Puzzle* NewNode() {
   Puzzle *temp = new Puzzle(), *curr = states.front();
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++) 
            temp->A[i][j] = curr->A[i][j];
    return temp;
}

//Function to generate next states from a given state.
void Search() {
    if(Match()) {cout<<"\nWe achieved the goal state!"<<endl; return;}
    if(states.empty()) {cout<<"\nNot Solvable."<<endl; return;}
    cnt++;
    int x = q.front().first, y = q.front().second; q.pop();
    if(y-1 >= 0) { //Left call.
        Puzzle *temp = NewNode();
        swap(temp->A[x][y], temp->A[x][y-1]); //Next state creation.
        long long int key = HashKeyGenerator(temp);
        if(!isDiscovered(key)) {states.push(temp); q.push(make_pair(x, y-1));}
    }
    if(x+1 <= 3) { //Bottom call.
        Puzzle *temp = NewNode();
        swap(temp->A[x][y], temp->A[x+1][y]);  //Next state creation.
        long long int key = HashKeyGenerator(temp);
        if(!isDiscovered(key)) {states.push(temp); q.push(make_pair(x+1, y));}
    }
    if(y+1 <= 3) { //Right call.
        Puzzle *temp = NewNode();
        swap(temp->A[x][y], temp->A[x][y+1]);  //Next state creation.
        long long int key = HashKeyGenerator(temp);
        if(!isDiscovered(key)) {states.push(temp); q.push(make_pair(x, y+1));}
    }
    if(x-1 >= 0) { //Top call.
        Puzzle *temp = NewNode();
        swap(temp->A[x][y], temp->A[x-1][y]);  //Next state creation.
        long long int key = HashKeyGenerator(temp);
        if(!isDiscovered(key)) {states.push(temp); q.push(make_pair(x-1, y));}
    }
    states.pop(); Search();
}

//Function to input current state.
void InputCurrentState() {
    Puzzle *curr = new Puzzle();
    cout<<"\nEnter current state: ";
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            cin>>curr->A[i][j];
            if(curr->A[i][j] == 0) {q.push(make_pair(i,j));}
        }
    }
    states.push(curr);
    u[HashKeyGenerator(curr)]++; 
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
    cout<<"\n8 Puzzle solution using the BFS algorithm."<<endl;
    InputGoalState();
    InputCurrentState();
    auto start = high_resolution_clock::now(); //Timer
    Search();
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout<<"Total time taken = "<<duration.count()<<" microseconds"<<endl;
    cout<<"Total number of states examined = "<<cnt<<endl<<endl;
    return 0;
}