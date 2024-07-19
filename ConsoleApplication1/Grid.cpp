
#include "Grid.hpp"

namespace ColorRush {
	GRID::GRID(GameDataRef data) : _data(data) {
		initializeGrid();
		//printGrid();
	}

	void GRID::initializeGrid() {
		srand(static_cast<unsigned int>(time(nullptr)));
		for (int i = 0; i < ROWS; ++i) {
			for (int j = 0; j < COLS; ++j) {
				grid[i][j] = rand() % COLORS + 1;
			}
		}

		for (int i = 0; i < 14; ++i) {
			std::vector<int> rowVector;
			for (int j = 0; j < 14; ++j) {
				rowVector.push_back(grid[i][j]);
			}
			originalGrid.push_back(rowVector);
		}

	}

	void GRID::printGrid() {//WORKING
		for (int i = 0; i < ROWS; ++i) {
			for (int j = 0; j < COLS; ++j) {
				cout << grid[i][j] << " ";
			}
			cout << endl;
		}
	}
	void GRID::drawGrid(float cellSize, float offsetX, float offsetY) {
		RectangleShape cell(Vector2f(cellSize, cellSize));
		for (int i = 0; i < ROWS; ++i) {
			for (int j = 0; j < COLS; ++j) {
				int x = i * cellSize + offsetX;
				int y = j * cellSize + offsetY;
				cell.setPosition(x, y);

				switch (grid[i][j]) {
				case 1:
					cell.setFillColor(sf::Color(255, 0, 0, 255));//red
					break;
				case 2:
					cell.setFillColor(sf::Color(255, 255, 0, 255));//yellow
					break;
				case 3:
					cell.setFillColor(sf::Color(51, 76, 203, 255));//blue
					break;
				case 4:
					cell.setFillColor(sf::Color(255, 128, 0, 255));//orange
					break;
				case 5:
					cell.setFillColor(sf::Color(0, 255, 0, 255));//green
					break;
				case 6:
					cell.setFillColor(sf::Color(128, 0, 179, 255)); // violet
					break;
				}
				_data->window.draw(cell);

				int color = grid[i][j];
				float borderSize = 3.5f;

				if ((i < (ROWS - 1) && grid[i + 1][j] != color) || i == COLS - 1) {
					RectangleShape border(Vector2f(borderSize, cellSize + borderSize));
					border.setPosition(x + cellSize - borderSize, y - borderSize);
					border.setFillColor(sf::Color::Black);
					_data->window.draw(border);
				}

				if (i == 0) {
					RectangleShape border(Vector2f(borderSize, cellSize + borderSize));
					border.setPosition(x, y - borderSize);
					border.setFillColor(sf::Color::Black);
					_data->window.draw(border);
				}

				if ((j < (COLS - 1) && grid[i][j + 1] != color) || j == ROWS - 1) {
					RectangleShape border(Vector2f(cellSize, borderSize));
					border.setPosition(x, y + cellSize - borderSize);
					border.setFillColor(sf::Color::Black);
					_data->window.draw(border);
				}

				if (j == 0) {
					RectangleShape border(Vector2f(cellSize, borderSize));
					border.setPosition(x, y - borderSize);
					border.setFillColor(sf::Color::Black);
					_data->window.draw(border);
				}
			}
		}
	}

	int GRID::floodFill(int replacementColor) {
		int targetColor = grid[0][0];
		if (targetColor == replacementColor) {
			//cout << "You entered the same color. Try again." << endl;
			return 0;
		}
		playerSequenceAnswer.push_back(targetColor);
		queue<pair<int, int>> q;
		q.push({ 0, 0 });

		while (!q.empty()) {
			int r = q.front().first;
			int c = q.front().second;
			q.pop();

			if (grid[r][c] == replacementColor) continue;

			grid[r][c] = replacementColor;

			if (r - 1 >= 0 && grid[r - 1][c] == targetColor) q.push({ r - 1, c });
			if (r + 1 < ROWS && grid[r + 1][c] == targetColor) q.push({ r + 1, c });
			if (c - 1 >= 0 && grid[r][c - 1] == targetColor) q.push({ r, c - 1 });
			if (c + 1 < COLS && grid[r][c + 1] == targetColor) q.push({ r, c + 1 });
		}
		return 1;
	}

	vector<int> GRID::getAnswer() {
		return sequenceAnswer;
	}

	vector<int> GRID::getPlayerSequence() {
		return playerSequenceAnswer;
	}

	void GRID::deleteGrid() {
		for (NODE* node : allNodes) {
			delete node;
		}
		allNodes.clear();
	}

	int GRID::countSameCell(int row, int col) {//WORKING
		if (row < 0 || row >= ROWS || col < 0 || col >= COLS)
			return 0;

		int targetColor = grid[row][col];
		bool visited[ROWS][COLS] = { false };

		queue<pair<int, int>> q;
		q.push({ row, col });

		int count = 0;
		while (!q.empty()) {
			int r = q.front().first;
			int c = q.front().second;
			q.pop();

			if (visited[r][c])
				continue;

			visited[r][c] = true;
			count++;


			if (r - 1 >= 0 && grid[r - 1][c] == targetColor) q.push({ r - 1, c });
			if (r + 1 < ROWS && grid[r + 1][c] == targetColor) q.push({ r + 1, c });
			if (c - 1 >= 0 && grid[r][c - 1] == targetColor) q.push({ r, c - 1 });
			if (c + 1 < COLS && grid[r][c + 1] == targetColor) q.push({ r, c + 1 });
		}
		return count;
	}

	bool GRID::isGameWon() {
		int targetColor = grid[0][0];
		for (int i = 0; i < ROWS; ++i) {
			for (int j = 0; j < COLS; ++j) {
				if (grid[i][j] != targetColor) {
					return false;
				}
			}
		}
		return true;
	}

	NODE* GRID::nodeMaker(int row, int col) {//WORKING
		NODE* newNode = new NODE;
		newNode->number = grid[row][col];
		if (row < 0 || row >= ROWS || col < 0 || col >= COLS)
			return 0;

		int targetColor = grid[row][col];
		bool visited[ROWS][COLS] = { false };

		queue<pair<int, int>> q;
		q.push({ row, col });

		while (!q.empty()) {
			int r = q.front().first;
			int c = q.front().second;
			pair<int, int> front = q.front();
			q.pop();

			if (visited[r][c])
				continue;

			newNode->connectedTiles.push_back(front);
			visited[r][c] = true;


			if (r - 1 >= 0 && grid[r - 1][c] == targetColor) q.push({ r - 1, c });
			if (r + 1 < ROWS && grid[r + 1][c] == targetColor) q.push({ r + 1, c });
			if (c - 1 >= 0 && grid[r][c - 1] == targetColor) q.push({ r, c - 1 });
			if (c + 1 < COLS && grid[r][c + 1] == targetColor) q.push({ r, c + 1 });
		}
		return newNode;
	}

	bool GRID::neighbor(vector<pair<int, int>> vec, pair<int, int> valueToFind) {
		if (count(vec.begin(), vec.end(), valueToFind) > 0) {
			return true;
		}
		else {
			return false;
		}
	}

	bool GRID::isInVector(const vector<NODE*>& vec, const NODE* item) {
		return find(vec.begin(), vec.end(), item) != vec.end();
	}

	void GRID::removeItemV(NODE* item, vector<NODE*>& vec) {
		vec.erase(remove(vec.begin(), vec.end(), item), vec.end());
	}

	int GRID::colorChange(int color, vector<NODE*>& visited, vector<NODE*>& neighbors) {
		vector<NODE*> newNeighbors;
		vector<NODE*> neighborsCopy = neighbors;
		int change = 0;


		for (int i = 0; i < neighborsCopy.size(); i++) {
			if (neighborsCopy[i]->number == color) {
				visited.push_back(neighborsCopy[i]);
				change += neighborsCopy[i]->connectedTiles.size();
				removeItemV(neighborsCopy[i], neighbors);
				for (int j = 0; j < neighborsCopy[i]->connectedTo.size(); j++) {
					if (!isInVector(neighbors, neighborsCopy[i]->connectedTo[j]) && !isInVector(visited, neighborsCopy[i]->connectedTo[j])) {
						neighbors.push_back(neighborsCopy[i]->connectedTo[j]);
					}
				}
			}
		}
		return change;
	}

	void GRID::recursiveExaluation(vector<NODE*>& neighbors, vector<int>& sequence, vector<NODE*>& visited, int& change, int calls, int called) {
		if (called >= calls) {
			return;
		}
		vector<int> sequence1;
		vector<NODE*> visited1;
		vector<NODE*> neighbors1;
		int change1 = 0;
		for (size_t k = 0; k < neighbors.size(); k++) {
			if (isInVector(visited, neighbors[k])) {
				continue;
			}
			NODE* n1 = neighbors[k];
			vector<NODE*> visited1a = visited;
			int change1a = change;
			int color = n1->number;
			vector<int> sequence1a = sequence;
			color = n1->number;
			sequence1a.push_back(color);
			vector<NODE*> neighbors1a = neighbors;
			change1a += colorChange(color, visited1a, neighbors1a);
			if (neighbors1a.empty()) {
				sequence.push_back(color);
				visited.push_back(neighbors[k]);
				return;
			}
			recursiveExaluation(neighbors1a, sequence1a, visited1a, change1a, calls, called + 1);
			if (change1a > change1) {
				change1 = change1a;
				sequence1 = sequence1a;
				visited1 = visited1a;
				neighbors1 = neighbors1a;
			}
		}
		change = change1;
		sequence = sequence1;
		visited = visited1;
		neighbors = neighbors1;
		return;
	}

	void GRID::solver() {//WORKING
		vector<NODE*> priorities;
		vector<pair<int, int>> tiles;
		for (int i = 0; i < ROWS; i++)
			for (int j = 0; j < COLS; j++)
				tiles.push_back({ i, j });

		while (!tiles.empty()) {
			NODE* newNode = nodeMaker(tiles.front().first, tiles.front().second);
			for (size_t i = 0; i < newNode->connectedTiles.size(); i++) {
				int x = newNode->connectedTiles[i].first;
				int y = newNode->connectedTiles[i].second;
				auto it = find_if(tiles.begin(), tiles.end(), [x, y](const pair<int, int>& p) {
					return p == make_pair(x, y);
					});

				if (it != tiles.end()) {
					tiles.erase(it);
				}
			}
			allNodes.push_back(newNode);
		}

		//cout << "Size: " << allNodes.size() << endl;
		priorities = allNodes;

		for (size_t i = 0; i < allNodes.size() - 1; i++) {
			for (size_t j = i + 1; j < allNodes.size(); j++) {
				for (size_t k = 0; k < allNodes[j]->connectedTiles.size(); k++) {
					int r = allNodes[j]->connectedTiles[k].first;
					int c = allNodes[j]->connectedTiles[k].second;

					if (r - 1 >= 0) {
						if (neighbor(allNodes[i]->connectedTiles, make_pair(r - 1, c))) {
							allNodes[i]->connectedTo.push_back(allNodes[j]);
							allNodes[j]->connectedTo.push_back(allNodes[i]);
							break;
						}
					}

					if (r + 1 < ROWS) {
						if (neighbor(allNodes[i]->connectedTiles, make_pair(r + 1, c))) {
							allNodes[i]->connectedTo.push_back(allNodes[j]);
							allNodes[j]->connectedTo.push_back(allNodes[i]);
							break;
						}
					}
					if (c - 1 >= 0) {
						if (neighbor(allNodes[i]->connectedTiles, make_pair(r, c - 1))) {
							allNodes[i]->connectedTo.push_back(allNodes[j]);
							allNodes[j]->connectedTo.push_back(allNodes[i]);
							break;
						}
					}

					if (c + 1 < COLS) {
						if (neighbor(allNodes[i]->connectedTiles, make_pair(r, c + 1))) {
							allNodes[i]->connectedTo.push_back(allNodes[j]);
							allNodes[j]->connectedTo.push_back(allNodes[i]);
							break;
						}
					}
				}
			}
		}
		//cout << "Here" << endl;
		//cout << "Address of nodes[0]: " << allNodes[0] << endl;

		vector<int> allSequence;
		vector<NODE*> allVisited;
		allVisited.push_back(allNodes[0]);
		vector<NODE*> allNeighbors = allNodes[0]->connectedTo;
		int numberOfmoves = 6;
		while (!allNeighbors.empty()) {
			vector<int> sequence;
			vector<NODE*> neighbors = allNeighbors;
			int change = 0;
			recursiveExaluation(neighbors, sequence, allVisited, change, numberOfmoves, 0);
			allSequence.insert(allSequence.end(), sequence.begin(), sequence.end());
			allNeighbors = neighbors;

			/*cout << "Sequence: ";
			for (size_t i = 0; i < allSequence.size(); i++) {
				cout << allSequence[i] << " ";
			}
			cout << endl;*/
			numberOfmoves = 4;
			/*
			cout << "neighbors: ";
			for (size_t i = 0; i < neighbors.size(); i++) {
				cout << neighbors[i]->number << " ";
			}
			cout << endl;*/
		}
		sequenceAnswer = allSequence;
		/*cout << "Sequence: ";
		for (size_t i = 0; i < allSequence.size(); i++) {
			cout << allSequence[i] << " ";
		}
		cout << endl;

		cout << "visited: ";
		for (size_t i = 0; i < allVisited.size(); i++) {
			cout << allVisited[i]->number << " ";
		}
		cout << endl;*/
		deleteGrid();
	}

	loadingGRID::loadingGRID(GameDataRef data) : _data(data) {
		rows = cols = 5;
		initializeGrid();

	}

	void loadingGRID::initializeGrid() {
		srand(static_cast<unsigned int>(time(nullptr)));
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				grid[i][j] = rand() % COLORS + 1;
			}
		}
	}

	void loadingGRID::drawGrid(float cellSize, float offsetX, float offsetY) {
		RectangleShape cell(Vector2f(cellSize, cellSize));
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				int x = i * cellSize + offsetX;
				int y = j * cellSize + offsetY;
				cell.setPosition(x, y);
				switch (grid[i][j]) {
				case 1:
					cell.setFillColor(Color(255, 0, 0, 255));//red
					break;
				case 2:
					cell.setFillColor(Color(255, 255, 0, 255));//yellow
					break;
				case 3:
					cell.setFillColor(Color(51, 76, 203, 255));//blue
					break;
				case 4:
					cell.setFillColor(Color(255, 128, 0, 255));//orange
					break;
				case 5:
					cell.setFillColor(Color(0, 255, 0, 255));//green
					break;
				case 6:
					cell.setFillColor(Color(128, 0, 179, 255)); // violet
					break;
				}
				_data->window.draw(cell);

				int color = grid[i][j];
				float borderSize = 3.5f;
				if ((i < (rows - 1) && grid[i + 1][j] != color) || i == cols - 1) {
					RectangleShape border(Vector2f(borderSize, cellSize + borderSize));
					border.setPosition(x + cellSize - borderSize, y - borderSize);
					border.setFillColor(sf::Color::Black);
					_data->window.draw(border);
				}

				if (i == 0) {
					RectangleShape border(Vector2f(borderSize, cellSize + borderSize));
					border.setPosition(x, y - borderSize);
					border.setFillColor(sf::Color::Black);
					_data->window.draw(border);
				}

				if ((j < (cols - 1) && grid[i][j + 1] != color) || j == rows - 1) {
					RectangleShape border(Vector2f(cellSize, borderSize));
					border.setPosition(x, y + cellSize - borderSize);
					border.setFillColor(sf::Color::Black);
					_data->window.draw(border);
				}

				if (j == 0) {
					RectangleShape border(Vector2f(cellSize, borderSize));
					border.setPosition(x, y - borderSize);
					border.setFillColor(sf::Color::Black);
					_data->window.draw(border);
				}

			}
		}
	}
}
