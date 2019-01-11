#include <cstdlib>
#include "Triangle.hpp"
#include "Octagon.hpp"
#include "Square.hpp"
#include "TTree.hpp"
#include "TList.hpp"
#include "TIterator.h"
#include <future>
#include <functional>
#include <random>
#include <thread>

int main() {
    
    TTree<Figure> tree;
    typedef std::function<void()> command;
    TList<command> list;
    
    command cmd_insert = [&]() {
        uint32_t seed = std::chrono::system_clock::now().time_since_epoch().count();

        std::default_random_engine generator(seed);
        std::uniform_int_distribution<int> distFigureType(1, 3);
        std::uniform_int_distribution<int> distFigureParam(1, 100);
        std::cout << "\nCommand: Insert" << std::endl;
        for (int i = 0; i < 5; ++ i) {
            switch(distFigureType(generator)) {
                case 1: {
                    std::cout << "\tInserted triangle" << std::endl;

                    int32_t side = distFigureParam(generator);
                    int32_t index = distFigureParam(generator);

                    tree.push(new Triangle(side, side, side), index);

                    break;
                }

                case 2: {
                    std::cout << "\tInserted octagon" << std::endl;

                    int32_t side = distFigureParam(generator);
                    int32_t index = distFigureParam(generator);

                    tree.push(new Octagon(side), index);

                    break;
                }

                case 3: {
                    std::cout << "\tInserted square" << std::endl;

                    int32_t side = distFigureParam(generator);
                    int32_t index = distFigureParam(generator);

                    tree.push(new FSquare(side), index);

                    break;
                }
            }
        }
    };
    
    command cmd_print = [&]() {
        std::cout << "\nCommand: Print tree" << std::endl;
        std::cout << tree;
    };
    
    command cmd_delete = [&]() {
        std::cout << "\nCommand: Remove element by SquareValue: ";
        
        uint32_t seed = std::chrono::system_clock::now().time_since_epoch().count();
        
        std::default_random_engine generator(seed);
        std::uniform_int_distribution<int> dist(1, 100);
        int num = dist(generator);
        std::cout << num << std::endl;
        for (int32_t i = 0; i < 12; ++i) {
            auto iter = tree.begin();
            tree.Get();
            for (auto j : tree) {       
                if (iter->Square() < num) {
                    tree.pop(j);
                    break;
                }
                ++iter;
                tree.Change(iter);
            }
        }
    };
    
    list.push(std::shared_ptr<command> (&cmd_insert, [](command*){}));
    list.push(std::shared_ptr<command> (&cmd_print, [](command*){}));
    list.push(std::shared_ptr<command> (&cmd_delete, [](command*){}));
    list.push(std::shared_ptr<command> (&cmd_print, [](command*){}));
    
    while (!list.empty()) {
        std::shared_ptr<command> cmd = list.pop();
        std::future<void> ft = std::async(*cmd);
        ft.get();
    }
    
    
    return 0;
}
