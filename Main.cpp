#include <iostream>
#include <stdexcept>
#include "GameMap.h"

int main() {
    std::pair<int, int> start_point;
    std::pair<int, int> end_point;

    std::cout << "A redak: ";
    std::cin >> start_point.first;
    std::cout << "A stupac: ";
    std::cin >> start_point.second;

    std::cout << "B redak: ";
    std::cin >> end_point.first;
    std::cout << "B stupac: ";
    std::cin >> end_point.second;

    start_point.first--;
    start_point.second--;
    end_point.first--;
    end_point.second--;

    try {
        GameMap new_map(start_point, end_point);
        new_map.run();
    }catch(const std::out_of_range& e) {
        std::cout << "Nije dobar doseg: " << e.what() << std::endl;
    }

    return 0;
}