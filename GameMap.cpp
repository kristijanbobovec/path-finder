#include "GameMap.h"
#include <ctime>
#include <stdexcept>
#include <queue>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <set>
#include <map>

GameMap::GameMap(std::pair<int, int> startPoint, std::pair<int, int> endPoint) {
    if (!createMap(startPoint, endPoint)) 
        throw std::out_of_range("Start point ili end point nisu dobri. Mapa je velika 40x20. Također start i end point nesmiju biti jednaki.");
    else {
        start_point = startPoint;
        end_point = endPoint;
        srand(time(nullptr));
    }
}

int GameMap::generate_value() {
    int random_num = rand() % (100) + 1;
    return random_num <= 95 ? 0 : 4;
}

bool GameMap::createMap(std::pair<int, int> startPoint, std::pair<int, int> endPoint) {
    if (!checkBounds(startPoint) || !checkBounds(endPoint)) return false;
    if (startPoint.first == endPoint.first && startPoint.second == endPoint.second) return false;
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            if (startPoint.first == row && startPoint.second == col) {
                map[row][col] = 1;
            }else if(endPoint.first == row && endPoint.second == col) {
                map[row][col] = 2;
            }else {
                int random_gen = generate_value();
                if (random_gen == 4) {
                    bool is_valid = true;
                    int dX[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
                    int dY[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
                    for (int i = 0; i < 8; i++) {
                        if ((row + dX[i] == startPoint.first && col + dY[i] == startPoint.second)
                                || (row + dX[i] == endPoint.first && col + dY[i] == endPoint.second)) {
                                is_valid = false;
                                break;
                        }
                    }
                    if (is_valid) map[row][col] = random_gen;
                    else map[row][col] = 0;
                }else {
                    map[row][col] = 0;
                }
            }
        }
    }
    return true;
}

bool GameMap::checkBounds(std::pair<int, int> point) {
    return !(point.first >= ROWS || point.second >= COLS || point.first < 0 || point.second < 0);
}

bool GameMap::checkBarrier(std::pair<int, int> point) {
    if (map[point.first][point.second] == 4) return true;
    return false;
}

void GameMap::BFS() {
    int dX[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dY[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
    std::queue<std::pair<int, int>> to_handle;
    to_handle.emplace(start_point);

    std::set<std::pair<int, int>> visited;
    visited.emplace(start_point);

    while (!to_handle.empty()) {
        std::pair<int, int> old_pair = to_handle.front(); to_handle.pop();
        for (int i = 0; i < 8; i++) {
            std::pair<int, int>new_pair = {old_pair.first + dX[i], old_pair.second + dY[i]};

            if (!checkBounds(new_pair) || checkBarrier(new_pair)) continue;

            if (new_pair.first == end_point.first && new_pair.second == end_point.second) {
                parent[new_pair] = old_pair;
                return;
            }

            if (visited.emplace(new_pair).second == true) {
                to_handle.emplace(new_pair);
                parent[new_pair] = old_pair;
            } 
        }
    }
}

void GameMap::clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}
 
void GameMap::drawMap() {
    clearScreen();
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            int symbol = map[row][col];
            switch (symbol) {
                case 0:
                    std::cout << "-";
                    break;
                case 1:
                    std::cout << "A";
                    break;
                case 2:
                    std::cout << "B";
                    break;
                case 3:
                    std::cout << "X";
                    break;
                case 4:
                    std::cout << "#";
                    break;
                default:
                    std::cout << "-";
            }
        }
        std::cout << std::endl;
    }
}

void GameMap::updateMap(std::pair<int, int> x_loc) {
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            if (x_loc.first == row && x_loc.second == col) {
                map[row][col] = 3;
            }
        }
    }
}

void GameMap::run() {
    BFS();
    std::vector<std::pair<int, int>> path;
    for (auto p = end_point; p != start_point; p = parent[p]) {
        path.push_back(p);
    }
    path.push_back(start_point);
    std::reverse(path.begin(), path.end());

    for (std::pair<int, int> pair : path) {
        updateMap(pair);
        drawMap();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}