#ifndef SNAKE_H
#define SNAKE_H
#include <deque>
#include <algorithm>
#include "position.h"

enum class Direction{
    Up,
    Down,
    Left,
    Right
};

class snake{
public:
    snake(Position start){
        body.push_front(start);
    }
    void changeDir(Direction new_dir){
        if(new_dir == dir){return;}
        if(dir == Direction::Left && new_dir == Direction::Right){return;}
        if(dir == Direction::Down && new_dir == Direction::Up){return;}
        if(dir == Direction::Up && new_dir == Direction::Down){return;}
        if(dir == Direction::Right && new_dir == Direction::Left){return;}
        dir = new_dir;
    };
    void move(bool grow){
        body.push_front(nextHead());

        if(!grow){
            body.pop_back();
        }
    }
    const std::deque<Position>& get_body() const{
        return body;
    }
    bool if_contain(Position pos) const{
        return std::find(body.begin(), body.end(), pos) != body.end();
    }
    Position head() const{
        return body.front();
    }
    Position nextHead() const{
        Position newHead = body.front();

        if(dir == Direction::Up){
            newHead.y--;
        }else if(dir == Direction::Down){
            newHead.y++;
        }else if(dir == Direction::Left){
            newHead.x--;
        }else if(dir == Direction::Right){
            newHead.x++;
        }

        return newHead;
    };
    bool hitSelf() const{
        if(body.size() == 1){return false;}
        return std::find(body.begin() + 1, body.end(), body.front()) != body.end();
    };
private:
    std::deque<Position> body;
    Direction dir = Direction::Right;
};

#endif