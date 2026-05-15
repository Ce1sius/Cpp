#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <vector>
#include "position.h"
class board{
public:
    board(int xx, int yy)
        : width(xx + 2), height(yy + 2), cells(height, std::vector<char>(width, ' ')) {
        createBoundary();
    }

    void createBoundary(){
        for(int i = 0; i < height; i++){
            for(int j = 0; j < width; j++){
                if(i == 0 || i == height - 1 || j == 0 || j == width - 1){
                    cells[i][j] = '#';
                }else{
                    cells[i][j] = ' ';
                }
            }
        }
    }

    void clearInside(){
        for(int i = 1; i < height - 1; i++){
            for(int j = 1; j < width - 1; j++){
                cells[i][j] = ' ';
            }
        }
    }

    void setCell(Position pos, char ch){
        if(pos.x >= 0 && pos.x < width && pos.y >= 0 && pos.y < height){
            cells[pos.y][pos.x] = ch;
        }
    }

    void render() const{
        for(int i = 0; i < height; i++){
            for(int j = 0; j < width; j++){
                std::cout << cells[i][j];
            }
            std::cout << std::endl;
        }
    }

    bool isWall(int x, int y) const{
        return cells[y][x] == '#';
    }

    int get_height() const{
        return height;
    }

    int get_width() const{
        return width;
    }

private:
    const int width, height;
    std::vector<std::vector<char>> cells;
};

#endif