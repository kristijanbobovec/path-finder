#include <iostream>
#include <vector>
#include <map>

class GameMap {
    private:
        std::map<std::pair<int, int>, std::pair<int, int>> parent;
        std::pair<int, int> start_point;
        std::pair<int, int> end_point;
        static const int ROWS = 20;
        static const int COLS = 40;
        int map[ROWS][COLS];
        bool checkBounds(std::pair<int, int> point);
        bool checkBarrier(std::pair<int, int> point);
        bool createMap(std::pair<int, int> startPoint, std::pair<int, int> endPoint);
        void drawMap();
        void BFS();
        void updateMap(std::pair<int, int> x_loc);
        int generate_value();
        void clearScreen();
    public:
        GameMap(std::pair<int, int> startPoint, std::pair<int, int> endPoint);
        void run();
};