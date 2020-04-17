//
//  main.cpp
//  Scoring
//
//  Created by Aman Jalan on 4/17/20.
//  Copyright © 2020 Aman Jalan. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <deque>
#include <sstream>
#include <cassert>
#include <unordered_map>
#include <utility>
 
using namespace std;

bool sortByVal(const pair<string, unsigned int> &a, const pair<string, unsigned int> &b) {
    return (a.second > b.second);
}

class Scoring {
    public:
    
    void checkNewPlayer (string input) {
        if (hash_table[input] == 0) { //could also be that wrong player has been initalized and made 0
            cout << "New Player named " << input << " has been created!" << "\n";
        }
    }
    
    void trackRound (string first, string second, string third) {
        roundInfo[roundNumber].push_back(first);
        roundInfo[roundNumber].push_back(second);
        roundInfo[roundNumber].push_back(third);
        ++roundNumber;
    }
    
    void comeTogether () {
            roundInfo.resize(100);
            string cmd;
        
            do {
                cout << "Enter Command: ";
                cin >> cmd;
                
                if (cmd != "undo" && cmd != "info" && cmd != "help" && cmd != "play" && cmd != "quit" && cmd != "edit" && cmd != "print") {
                    cout << "Invalid Command entered: Please try again" << "\n";
                }
                
                if (cmd == "help") {
                    cout << "Commands are play, quit, edit (add, subtract, remove), info, print, undo" << "\n";
                }
                
                if (cmd == "play") {
                    string first, second, third;
                    cout << "Enter names of the winners of this round: ";
                    cin >> first >> second >> third;
                    
                    trackRound(first, second, third);
                    
                    checkNewPlayer(first);
                    hash_table[first] += 3;
                    
                    checkNewPlayer(second);
                    hash_table[second] += 2;
                    
                    checkNewPlayer(third);
                    hash_table[third] += 1;
                }
                
                if (cmd == "edit") {
                    string name, operation;
                    unsigned int number;
                    cout << "Enter name to be edited and operation to be done: ";
                    cin >> name >> operation;
                    
                    if (operation == "add") {
                        cout << "Enter how much to add: ";
                        cin >> number;
                        hash_table[name] += number;
                    }
                    
                    else if (operation == "subtract") {
                        cout << "Enter how much to subtract: ";
                        cin >> number;
                        if (number > hash_table[name]) {
                            cout << "Cant have negative score!" << "\n";
                        }
                        else {
                            hash_table[name] -= number;
                        }
                    }
                    
                    else if (operation == "remove") {
                        hash_table.erase(name);
                    }
                    
                    else {
                        cout << "Invalid operation entered" << "\n";
                    }
                }
                
                if (cmd == "print") {
                   unordered_map<string, unsigned int> :: iterator it;
                    for (it = hash_table.begin(); it != hash_table.end(); ++it) {
                        sortVector.push_back(make_pair(it->first, it->second));
                    }
                    
                    sort(sortVector.begin(), sortVector.end(), sortByVal);
                    
                    cout << "Current Leaderboard" << "\n";
                    
                    vector <pair<string, unsigned int>> :: iterator it2;
                    for (it2 = sortVector.begin(); it2 != sortVector.end(); ++it2) {
                        cout << it2->first << " " << it2->second << "\n";
                    }
                    sortVector.clear();
                }
                
                if (cmd == "info") {
                    for (unsigned int i = 0; i < roundNumber; ++i) {
                        cout << "Round " << i+1 << ": " << roundInfo[i][0] << " " << roundInfo[i][1] << " " << roundInfo[i][2] << "\n";
                    }
                }
                
                if (cmd == "undo") {
                    if (roundNumber > 0) {
                        hash_table[roundInfo[roundNumber-1][0]]-= 3;
                        if (hash_table[roundInfo[roundNumber-1][0]] == 0) {
                            hash_table.erase(roundInfo[roundNumber-1][0]);
                        }
                        hash_table[roundInfo[roundNumber-1][1]]-= 2;
                        if (hash_table[roundInfo[roundNumber-1][1]] == 0) {
                            hash_table.erase(roundInfo[roundNumber-1][1]);
                        }
                        hash_table[roundInfo[roundNumber-1][2]]-= 1;
                        if (hash_table[roundInfo[roundNumber-1][2]] == 0) {
                            hash_table.erase(roundInfo[roundNumber-1][2]);
                        }
                        --roundNumber;
                    }
                    else {
                        cout << "Can't undo when no rounds have passed" << "\n";
                    }
                }
                
               } while (cmd != "quit");
        }
    
    
    private:
        unordered_map<string, unsigned int> hash_table;
        vector <pair<string, unsigned int>> sortVector;
        vector <vector<string>> roundInfo;
        unsigned int roundNumber = 0;
        
};

int main() {
    Scoring s;
    s.comeTogether();
    return 0;
}
