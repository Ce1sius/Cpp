#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <chrono>
#include <thread>
#include "snake.h"
#include "position.h"
#include "food.h"
#include "board.h"
#include "input.h"

class game
{
public:
    game(int h, int w)
        : width(w), height(h), gameboard(w, h), player({w / 2, h / 2}), apple(h + 2, w + 2)
    {
        apple.respawn(player);
    }

    void run()
    {
        while (!isGameOver)
        {
            handleInput();
            update();
            render();
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }

        showGameOver();
    }

private:
    int width;
    int height;
    bool isGameOver = false;
    int score = 0;

    Input input;
    board gameboard;
    snake player;
    food apple;

    void handleInput(){
        if(input.kbhit()){
            char ch = input.getch();

            if(ch == 'w' || ch == 'W'){
                player.changeDir(Direction::Up);
            }else if(ch == 's' || ch == 'S'){
                player.changeDir(Direction::Down);
            }else if(ch == 'a' || ch == 'A'){
                player.changeDir(Direction::Left);
            }else if(ch == 'd' || ch == 'D'){
                player.changeDir(Direction::Right);
            }
        }
    }

    void update()
    {
        Position next = player.nextHead();

        if (gameboard.isWall(next.x, next.y))
        {
            isGameOver = true;
            return;
        }

        bool grow = next == apple.get_position();
        player.move(grow);

        if (player.hitSelf())
        {
            isGameOver = true;
            return;
        }

        if (grow)
        {
            score++;
            apple.respawn(player);
        }
    }
    void render(){
        std::cout << "\033[2J\033[H";
        gameboard.clearInside();
        for(const Position& pos : player.get_body()){
            gameboard.setCell(pos, 'O');
        }
        gameboard.setCell(player.head(), '@');
        gameboard.setCell(apple.get_position(), '*');
        gameboard.render();
        std::cout << "Score: " << score << std::endl;

    }

    void showGameOver()
    {
        std::cout << "You Lost! Your score is " << score << std::endl;
    }
};

#endif