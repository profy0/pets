#include <iostream>
#include <vector>
#include <algorithm>                                                                  
#include <set>
#include <deque>
#include <stack>
#include <queue>
#include <map>
#include <iomanip>
#include <cmath>
#include <sstream>
#include <stdio.h>
#include <assert.h>
#include <intrin.h>
#include <fstream>
#include <cstdlib>

using namespace std;

struct info {
    string type, name;
    int age;
    info(string type, string name, int age) {
        this->type = type;
        this->name = name;
        this->age = age;
    }
};

struct names {
    set <string> human, animal;
};

struct old {
    int mini = 1e9, maxi = 0;
};

bool check(string s) {
    bool ok = 0;
    for (int i = 0; i < s.size(); i++) {
        ok |= !(s[i] >= '0' && s[i] <= '9');
    }
    return ok;
}

void solve() {
    ifstream in("input.txt");
    string s;
    map <string, vector <info> > humans;
    map <string, names> type_of_pet;
    map <string, set <string> > how_many_names;
    map <string, old> how_old;
    set <string> types;
    int line = 0;
    set <string> all_kinds;
    while (getline(in,s)) {
        line++;
        string par[4];
        int cnt = 0;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == ',') {
                cnt++;
                continue;
            }
            par[cnt] += s[i];
        }
        if (par[2] == "") par[2] += " ";
        if (check(par[3])) {
            cout << "Error!!! Enter the correct age! Line " << line << "\n";
            exit(0);
        }
        humans[par[0]].push_back(info(par[1], par[2], stoi(par[3])));
        type_of_pet[par[1]].human.insert(par[0]);
        type_of_pet[par[1]].animal.insert(par[2]);
        how_many_names[par[2]].insert(par[1]);
        all_kinds.insert(par[1]);
        if (how_old[par[1]].mini > stoi(par[3])) how_old[par[1]].mini = stoi(par[3]);
        if (how_old[par[1]].maxi < stoi(par[3])) how_old[par[1]].maxi = stoi(par[3]);
        types.insert(par[1]);
    }

    /// types of questions
    
    cout << "Enter request type:\n";
    cout << "    1. Number of animal kind for each owner.\n";
    cout << "    2. Get all owners and nicknames for a specific kind of animal(enter by you).\n";
    cout << "    3. How many kinds of animals have a certain nickname(enter by you).\n";
    cout << "    4. Get information about the age of the oldest and youngest animal of each kinds.\n";
    
    int type;
    cin >> type;
    cin.ignore(256, '\n');

    string tp, nm;
    vector <string> tpe;

    switch (type) {
    case 1:
        for (auto human : humans) {
                set <string> for_this_human;
                for (auto now : human.second) {
                    for_this_human.insert(now.type);
                }
                cout << human.first << " has " << for_this_human.size() << " different type" << ((for_this_human.size()>1)?"s":"") << " of pets\n";
            }
        break;
    case 2:
        cout << "Enter kind of animal: ";
        getline(cin, tp);
        if (!all_kinds.count(tp)) {
            cout << "There are no animals of this type!\n";
            exit(0);
        }
        cout << "\nowners: ";
        for (auto now : type_of_pet[tp].human) {
            if (now == " ") continue;
            tpe.push_back(now);
        }
        for (int i = 0; i < tpe.size() - 1; i++) {
            cout << tpe[i] << ", ";
        }
        cout << tpe.back() << "\n";
        tpe.clear();
        cout << "\nnames: ";
        for (auto now : type_of_pet[tp].animal) {
            if (now == " ") continue;
            tpe.push_back(now);
        }
        for (int i = 0; i < tpe.size() - 1; i++) {
            cout << tpe[i] << ", ";
        }
        cout << tpe.back() << "\n";
        break;
    case 3:
        cout << "Enter nickname(if you want information about animals without nicknames, enter a space): ";
        getline(cin, nm);
        cout << "\nthis name is worn by " << how_many_names[nm].size() << " type of animals\n";
        break;
    case 4:
        for (auto now : types) {
            cout << "for " << now << ", the youngest has an age of " << how_old[now].mini << "\n";
            cout << "for " << now << ", the oldest has an age of " << how_old[now].maxi << "\n";
        }
        break;
    default:
        cout << "Enter the correct request number!\n";
        break;
    }
    in.close();
}

int main() {
    
    solve();

    return 0;
}
