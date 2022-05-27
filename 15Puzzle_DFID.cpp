//15 - Puzzle Problem Using DFID Algorithm.
#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

//Puzzle class to store a state of the puzzle.  
class Puzzle{
    public:
        int A[4][4];
};

int cnt = 0; //To count the number of states generated.
int ii, jj; //To store the position of zero in the puzzle. 
int bound = 0; //To store the bound level in each iteration.
Puzzle *initial = new Puzzle(); //To store the initial state.
Puzzle *goal = new Puzzle(); //To store the goal state.
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

//Function to check whteher the current state is the goal state or not.
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

//Function to generate next states from a given state.
bool Search(Puzzle *curr, int level, int i, int j) {
    long long int key; bool flag = false;
    if(level == bound) {
        flag = true;
        key = HashKeyGenerator(curr);
    }
    if(flag == true) {
        if(u.find(key) == u.end()) {
            u[key]++;
            if(Match(curr)) {
                cout<<"\n\tWe achieved the goal state!"<<endl; 
                return true;
            }
        }
    }
    bool ans = false;
    if(!ans and j-1 >= 0 and level < bound) { 
        swap(curr->A[i][j], curr->A[i][j-1]); //Next state creation.
        ans = Search(curr, level+1, i, j-1); //Left call.
        swap(curr->A[i][j], curr->A[i][j-1]); //Bactrack.
    }
    if(!ans and i+1 <= 3 and level < bound) { 
        swap(curr->A[i][j], curr->A[i+1][j]); //Next state creation.
        ans = Search(curr, level+1, i+1, j); //Bottom call.
        swap(curr->A[i][j], curr->A[i+1][j]); //Bactrack.
    }
    if(!ans and j+1 <= 3 and level < bound) { 
        swap(curr->A[i][j], curr->A[i][j+1]); //Next state creation.
        ans = Search(curr, level+1, i, j+1); //Right call.
        swap(curr->A[i][j], curr->A[i][j+1]); //Bactrack.
    }
    if(!ans and i-1 >= 0 and level < bound) { 
        swap(curr->A[i][j], curr->A[i-1][j]); //Next state creation.
        ans = Search(curr, level+1, i-1, j); //Top call.
        swap(curr->A[i][j], curr->A[i-1][j]); //Bactrack.
    }
    return ans;
}

//Function to input current state.
void InputCurrentState() {
    cout<<"\n\tEnter current state: ";
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            cin>>initial->A[i][j];
            if(initial->A[i][j] == 0) {ii = i; jj = j;}
        }
    }
}

//Function to input goal state.
void InputGoalState() {
    cout<<"\tEnter goal state: ";
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            cin>>goal->A[i][j];
}

//Main function.
int main(void) {
    cout<<"\n\t8 Puzzle solution using the DFID algorithm."<<endl;
    InputGoalState();
    InputCurrentState();
    bool ans = true;
    auto start = high_resolution_clock::now(); //Timer
    while(ans) {
        ans = !Search(initial, 0, ii, jj);
        bound++;
        cnt += u.size();
    } 
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout<<"\tTotal time taken = "<<duration.count()<<" microseconds"<<endl;
    cout<<"\tTotal number of states generated = "<<cnt<<endl<<endl;
    return 0;
}