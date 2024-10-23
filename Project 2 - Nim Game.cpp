#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <unistd.h> //for the delay, the windows one was returning 
                    //an error message so I looked it up and 
                    //used this alternative, works on most online compilers.

using namespace std;

void gameRules() {
    cout << "Rules: " << endl;
    cout << "1. Each player can remove 1, 2, or 3 stones from the pile." << endl;
    cout << "2. Whoever makes the last move loses." << endl; 
}

int pileSize() {
    return rand() % 12 + 10; //chooses a random # from 10-21
}

//easy mode, the bot simply picks at random
int ezMode(int numStones) { 
    int stonesTaken = rand() % 3 + 1;
    if (stonesTaken > numStones) {
        stonesTaken = numStones;
    }
    return stonesTaken;
}

int hardMode(int numStones) {
    if ((numStones - 1) % 4 == 0) {
        return 1;
    } else {
        //takes enough stones to leave a multiple of 4 plus 1, best winning strategy
        return (numStones - 1) % 4;
    }
}

//function for the human user's turn
void userTurn(int& numStones) {
    int stonesTaken; 
    while (true) {
        cout << "There are " << numStones << " stones in the pile."
             << endl;
        cout << "How many do you wish to take: ";
        cin >> stonesTaken;
        cout << endl;
        
        if (stonesTaken < 1 || stonesTaken > 3 || stonesTaken > numStones) {
            cout << "Invalid move, please follow the rules." 
                 << endl;
        } else {
            numStones -= stonesTaken;
            cout << "You removed " << stonesTaken << " " << (stonesTaken == 1 ? "stone." : "stones.") << endl; //picks correct grammar
            if (numStones == 1) {
                cout << "There is one stone remaining." << endl;
            } else {
                cout << "There are " << numStones << " stones remaining." << endl;
            }
            cout << endl;
            break;
        }
    }
}

void computerTurn(int& numStones, bool hardModeEnabled) {
    int stonesTaken;
    if (hardModeEnabled) {
        stonesTaken = hardMode(numStones);
    } else {
        stonesTaken = ezMode(numStones);
    }
    numStones -= stonesTaken;
    cout << "The computer removed " << stonesTaken << " " << (stonesTaken == 1 ? "stone." : "stones.") << endl;
            if (numStones == 1) {
                cout << "There is one stone remaining." << endl;
            } else {
                cout << "There are " << numStones << " stones remaining." << endl;
            }
    cout << endl;
}

int main() {
    
    cout << "------------- The Game of Nim -------------" << endl;
     
    srand(static_cast<unsigned int>(time(0))); //generates random seed for game
    
    gameRules();
    cout << endl;
    cout << "Choose Difficulty: " << endl;
    cout << "1. Easy" << endl;
    cout << "2. Hard" << endl;
    
    int mode;
    cin >> mode;
    bool hardModeEnabled = (mode == 2); 
    
    int numStones = pileSize();
    cout << "Starting with " << numStones << " stones in the pile."  << endl;
    
    bool userStarts = rand() % 2 == 0; // 50/50 chance
    cout << (userStarts ? "You start!" : "Computer starts!") //depends on boolean above
         << endl;
    
    cout << endl;
         
    while (numStones > 0) {
        if (userStarts) {
            userTurn(numStones);
            if (numStones == 0) { 
                cout << "You lose!" << endl; 
                break;
            }
        } else {
            computerTurn(numStones, hardModeEnabled);
            if (numStones == 0) {
                cout << "You win!" << endl;
                break;
            }
        }
        sleep(1); // delay for 1 second
        userStarts = !userStarts; //switches turns
    }
    
    cout << "------------- Game Over -------------" << endl;

    return 0;
} 