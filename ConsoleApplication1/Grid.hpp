#pragma once

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include <iostream>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <list>
#include <vector>
#include <algorithm>
#include <thread>

using namespace sf;
using namespace std;

const int matrixSize = 14;
const int ROWS = 14;
const int COLS = 14;
const int COLORS = 6;
const int MAX_MOVES = 27;
namespace ColorRush {
    class NODE {
    public:
        int number;
        vector<pair<int, int>> connectedTiles;
        vector<NODE*> connectedTo;
        NODE() {
            number = 0;
        }
    };

    class GRID {
    private:
        GameDataRef _data;
        int grid[ROWS][COLS];
        vector<int> sequenceAnswer;
        vector<int> playerSequenceAnswer;
        vector<NODE*> allNodes;

    public:
        GRID(GameDataRef data);
        std::vector<std::vector<int>> originalGrid;
        vector<int> getAnswer();
        vector<int> getPlayerSequence();
        void initializeGrid();
        void printGrid();
        void drawGrid(float cellSize, float offsetX, float offsetY);
        int floodFill(int replacementColor);
        void deleteGrid();
        int countSameCell(int row, int col);
        bool isGameWon();
        NODE* nodeMaker(int row, int col);
        bool neighbor(vector<pair<int, int>> vec, pair<int, int> valueToFind);
        bool isInVector(const vector<NODE*>& vec, const NODE* item);
        void removeItemV(NODE* item, vector<NODE*>& vec);
        int colorChange(int color, vector<NODE*>& visited, vector<NODE*>& neighbors);
        void recursiveExaluation(vector<NODE*>& neighbors, vector<int>& sequence, vector<NODE*>& visited, int& change, int calls, int called);
        void solver();
    };

    class loadingGRID {
    private:
        GameDataRef _data;
        int rows, cols;
        int grid[5][5];

    public:
        void initializeGrid();
        void drawGrid(float cellSize, float offsetX, float offsetY);
        loadingGRID(GameDataRef _data);
    };
}





