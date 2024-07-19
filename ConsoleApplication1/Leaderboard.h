#pragma once
#include <fstream>
#include <vector>
#include <string>


using namespace std;

class Player {
public:
    string name;
    int classicBestScore;
    Player* next, * prev;

    Player(string n) {
        name = n;
        next = prev = NULL;
        classicBestScore = 1;
    }
};

class Leaderboard {
private:
    Player* root, * tail, * currentUser;
    Leaderboard() {
        root = tail = currentUser = NULL;
        loggedIn = false;
        ifstream file("GameMemory.txt");
        string playerName;
        int classicBestScore;
        while (file >> playerName >> classicBestScore) {
            retrievePlayer(playerName, classicBestScore);
        }
        file.close();
    }

    ~Leaderboard() = default;
    Leaderboard(const Leaderboard&) = delete;
    Leaderboard& operator=(const Leaderboard&) = delete;

public:
    static Leaderboard& getInstance() {
        static Leaderboard instance;
        return instance;
    }

    Player* findUser(string playerName);
    Player* createPlayer(string playerName);
    void retrievePlayer(string playerName, int level);
    void currentlyUsing(string playerName);
    void updateRanking();
    void updateClassicBestScore(int level);
    Player* getCurrentUser();
    Player* getRoot();
    bool loggedIn;
};
