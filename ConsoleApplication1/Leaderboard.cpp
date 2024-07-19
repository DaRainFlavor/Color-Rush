#include "LeaderBoard.h"
#include <SFML/Graphics.hpp>


using namespace sf;
using namespace std;


Player* Leaderboard::findUser(string playerName) {
    Player* tmp = root;
    if (root == NULL) {
        return root;
    }
    while (tmp != NULL) {
        if (tmp->name == playerName) {
            return tmp;
        }
        tmp = tmp->next;
    }
    return tmp;
}

Player* Leaderboard::createPlayer(string playerName) {
    Player* newPlayer = new Player(playerName);
    if (root == NULL) {
        root = tail = newPlayer;
    }
    else {
        tail->next = newPlayer;
        newPlayer->prev = tail;
        tail = newPlayer;
    }
    return newPlayer;
}


void Leaderboard::retrievePlayer(string playerName, int level) {
    Player* newPlayer = new Player(playerName);
    newPlayer->classicBestScore = level;
    if (root == NULL) {
        root = tail = newPlayer;
    }
    else {
        tail->next = newPlayer;
        newPlayer->prev = tail;
        tail = newPlayer;
    }
}

void Leaderboard::currentlyUsing(string playerName) {
    Player* nowUsing = findUser(playerName);
    if (nowUsing == NULL) {
        nowUsing = createPlayer(playerName);
    }
    currentUser = nowUsing;
}

void Leaderboard::updateRanking() {
    std::fstream truncateFile("GameMemory.txt", std::ios::out | std::ios::trunc);
    Player* i, * j;
    string name;
    int level;
    for (i = root; i->next != NULL; i = i->next)
    {
        for (j = i->next; j != NULL; j = j->next)
        {
            if (i->classicBestScore < j->classicBestScore)
            {
                level = j->classicBestScore;
                name = j->name;

                j->classicBestScore = i->classicBestScore;
                j->name = i->name;
                i->classicBestScore = level;
                i->name = name;
            }
        }
    }


    ofstream outputFile("GameMemory.txt");

    if (outputFile.is_open()) {
        Player* tmp = root;
        while (tmp != NULL) {
            outputFile << tmp->name << endl;
            outputFile << tmp->classicBestScore << endl;
            tmp = tmp->next;
        }
        outputFile.close();
    }
}



void Leaderboard::updateClassicBestScore(int level) {
    if (currentUser == NULL) return;
    currentUser->classicBestScore = level;
    updateRanking();
}


Player* Leaderboard::getCurrentUser() {
    return currentUser;
}

Player* Leaderboard::getRoot() {
    return root;
}
