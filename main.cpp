//////////////////////
//Powered by VisTzem//
//////////////////////

#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <time.h>
#include <vector>
#include <limits>
using namespace std;

///////////////////////////////////////////////////
// FOR DEBUGGING
//
// for(int i=1; i<=N; i++){
//     for(int j=1; j<=N; j++){
//         if(Space[i][j]!=-1){
//             cout<<Space[i][j]<<" ";
//         }else{
//             cout<<"*"<<" ";
//         }
//     }
//     cout<<endl;
// }
///////////////////////////////////////////////////

// change state ///////////////////////////////////////////
void ChangeState(int N, int x, int y, vector<vector<int>> &SpaceState, vector<vector<int>> &Space){
    if (SpaceState[x][y] == 1 || SpaceState[x][y] == 2){
        return;
    }

    SpaceState[x][y] = 1;
    if (Space[x][y] == 0){
        for (int i = x - 1; i <= x + 1; i++){
            for (int j = y - 1; j <= y + 1; j++){
                if (i >= 1 && i <= N && j >= 1 && j <= N){
                    ChangeState(N, i, j, SpaceState, Space);
                }
            }
        }
    }else{
        return;
    }
}
// change state ///////////////////////////////////////////

// Check the game(lose=1, win=2, nothing=0) ///////////////
int GameCheck(int N, vector<vector<int>> &SpaceState, vector<vector<int>> &Space){
    // Lose?
    for (int i = 1; i <= N; i++){
        for (int j = 1; j <= N; j++){
            if (Space[i][j] == -1 && SpaceState[i][j] == 1){
                return 1;
            }
        }
    }
    // Nothing?
    for (int i = 1; i <= N; i++){
        for (int j = 1; j <= N; j++){
            if (Space[i][j] == -1 && SpaceState[i][j] == 0){
                return 0;
            }
        }
    }
    return 2;
}
// Check the game(lose=1, win=2, nothing=0) ///////////////

// ShowTheCurrentBoard ////////////////////////////////////
void ShowTheCurrentBoard(int N, vector<vector<int>> &SpaceState, vector<vector<int>> &Space){
    for (int i = 1; i <= N; i++){
        cout<<(N+1-i)%10<<"|";

        for (int j = 1; j <= N; j++){
            if (SpaceState[i][j] == 0){
                if((N+1-i)%5==0||j%5==0){
                    cout<<"。";
                }else{
                    cout << "．";
                }
            }else if (SpaceState[i][j] == 1){
                if (Space[i][j] == -1){
                    cout << "*"<<" ";
                }else{
                    cout<<Space[i][j]<<" ";
                }
            }else if (SpaceState[i][j] == 2){
                cout << "^"<<" ";
            }
        }
        cout << endl;
    }
        cout<<"-+";

    for(int i=1; i<=N; i++){
        cout<<"--";
    }
        cout<<endl;

    cout<<"0|";

    for(int i=1; i<=N; i++){
        cout<<i%10<<" ";
    }
        cout<<endl
            <<endl;
}
// ShowTheCurrentBoard ////////////////////////////////////


// Run Program ////////////////////////////////////
void RunProgram(){
    // Set the random number
    srand(time(NULL));

    // Ask for the space range
    int N;
    cout << "How Big?(5~30):";
    while (cin >> N){
        if (N >= 5 && N <= 30){
            break;
        }else{
            cout << "Please enter again(5~30):";
        }
    }

    // Ask for how hard it is
    int ModeAsk;
    string Mode;
    cout << "How Hard?(Easy, Normal, Hard):";
    while (cin >> Mode){
        if (Mode == "Easy"){
            ModeAsk = 8;
            break;
        }else if (Mode == "Normal"){
            ModeAsk = 6;
            break;
        }else if (Mode == "Hard"){
            ModeAsk = 4;
            break;
        }else{
            cout << "Please enter again(Easy, Normal, Hard):";
        }
    }

    // Game Started
    cout << endl
        << endl
        << "Let's start the game!" << endl
        << endl;

    // Set every spaces' state(0=close, 1=open, 2=flag), and show;
    vector<vector<int>> SpaceState(N + 2, vector<int>(N + 2, 0));

    // fake board
    for (int i = 1; i <= N; i++){
        cout<<(N+1-i)%10<<"|";

        for (int j = 1; j <= N; j++){
            if((N+1-i)%5==0||j%5==0){
                cout<<"。";
            }else{
                cout <<"．";
            }
        }
        cout<<endl;
    }
    cout<<"-+";

    for(int i=1; i<=N; i++){
        cout<<"--";
    }
        cout<<endl;

    cout<<"0|";

    for(int i=1; i<=N; i++){
        cout<<i%10<<" ";
    }
        cout<<endl
            <<endl;

    // First time to choose which to dig
    int x, y;
    string WhatToDo;

    cout << "Where? (Enter x, y):";

    while (cin >> y >> x){
        if (x >= 1 && x <= N && y >= 1 && y <= N){
            x=N+1-x;
            cout << endl;
            break;
        }else{
            cout << "Try again (Enter x, y):";
        }
    }

    // Build the space and find the mines
    vector<vector<int>> Space(N + 2, vector<int>(N + 2, 9));

    for (int i = 1; i <= N; i++){
        for (int j = 1; j <= N; j++){
            Space[i][j] = 0;
        }
    }

    for (int i = 1; i <= N; i++){
        for (int j = 1; j <= N; j++){
            int Rand = rand() % ModeAsk;
            if (Rand == 0){
                Space[i][j] = -1;
            }
        }
    }

    // Change the 3*3 place around the place where the player chose from maybe -1 to 0
    for (int i = x - 1; i <= x + 1; i++){
        for (int j = y - 1; j <= y + 1; j++){
            if (Space[i][j] == -1){
                Space[i][j] = 0;
            }
        }
    }

    // Scan and Edit the numbers
    for (int i = 1; i <= N; i++){
        for (int j = 1; j <= N; j++){

            if (Space[i][j] != -1){
                for (int m = i - 1; m <= i + 1; m++){
                    for (int n = j - 1; n <= j + 1; n++){
                        if (Space[m][n] == -1){
                            Space[i][j]++;
                        }
                    }
                }
            }
        }
    }

    // reveal the place where the player chose
    ChangeState(N, x, y, SpaceState, Space);

    ShowTheCurrentBoard(N, SpaceState, Space);

    // GameCheck for the first time
    if (GameCheck(N, SpaceState, Space) == 2){
        cout << "You Win OMGGG you're so lucky Bruhhh";
    }

    // Player move
    while (GameCheck(N, SpaceState, Space) == 0){
        int x, y;
        string WhatToDo;

        cout << "Where? (Enter x, y):";
        while (cin >> y >> x){
            int tx=N+1-x;
            if (tx < 1 || tx > N || y < 1 || y > N){
                cout << endl
                        << "Wrong place :(" << endl
                        << "Try again (Enter x, y):";
            }else{
                x=tx;
                cout << endl;
                break;
            }
        }

        cout << "What to do? (Enter movement(d for dig, f for flag)):";
        while (cin >> WhatToDo){
            if (WhatToDo != "d" && WhatToDo != "f"){
                cout << "Try again (Enter movement(d for dig, f for flag)):";
            }else{
                cout << endl;
                break;
            }
        }

        if (WhatToDo == "d"){
            if(SpaceState[x][y]==0){
                ChangeState(N, x, y, SpaceState, Space);
            }else if(SpaceState[x][y]==1){
                int count=Space[x][y];
                for(int m=x-1; m<=x+1; m++){
                    for(int n=y-1; n<=y+1; n++){
                        if(SpaceState[m][n]==2){
                            count--;
                        }
                    }
                }
                if(count==0){
                    for(int m=x-1; m<=x+1; m++){
                        for(int n=y-1; n<=y+1; n++){
                            ChangeState(N, m, n, SpaceState, Space);
                        }
                    }
                }
            }
        }
        else if (WhatToDo == "f"){
            if (SpaceState[x][y] == 2){
                SpaceState[x][y] = 0;
            }else if (SpaceState[x][y] == 0){
                SpaceState[x][y] = 2;
            }
        }
        ShowTheCurrentBoard(N, SpaceState, Space);
    }

    // GameCheck
    if (GameCheck(N, SpaceState, Space) == 2){
        cout << "You Win" << endl;
    }else{
        cout << "The whole map:" << endl;

            for (int i = 1; i <= N; i++){
                cout<<(N+1-i)%10<<"|";

                for (int j = 1; j <= N; j++){
                    if (Space[i][j] == -1){
                        cout<<"*"<<" ";
                    }else{
                        cout<<Space[i][j]<<" ";
                    }
                }
                cout << endl;
            }
                cout<<"-+";

            for(int i=1; i<=N; i++){
                cout<<"--";
            }
                cout<<endl;

            cout<<"0|";

            for(int i=1; i<=N; i++){
                cout<<i%10<<" ";
            }

                cout<<endl
                    <<endl
                    << "You Lose :)" << endl;    
    }
}
// Run Program ////////////////////////////////////


int main(){
    RunProgram();

    // Play again?
    cout <<"Wanna play again? (y for yes, n for no):";
    string PlayAgain;
    while(cin >> PlayAgain){
        if(PlayAgain=="y"){
            RunProgram();
            cout <<"Wanna play again? (y for yes, n for no):";
        }else if(PlayAgain=="n"){
            return 0;
        }else{
            cout<<endl
            <<"Please enter again (y for yes, n for no):";
        }
    }
}