#ifndef FOOD_H
#define FOOD_H
#include <random>
#include "position.h"
#include "snake.h"

class food{
public:
    food(int h, int w) : height(h), width(w), pos{1,1}, gen(std::random_device{}()){
        
    }
    Position get_position() const{
        return pos;
    }
    void respawn(const snake& s){
        std::uniform_int_distribution<int> distX(1, width - 2);
        std::uniform_int_distribution<int> distY(1, height - 2);
        do {
            pos.x = distX(gen);
            pos.y = distY(gen);
        } while (s.if_contain(pos));
    }
private:
    int height;
    int width;
    Position pos;
    std::mt19937 gen;
};

#endif