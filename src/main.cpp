#include "../ANSI-Library/ansi_lib.h"

#include "snake.h"
#include "apple.h"

#include <future>
#include <chrono>
#include <conio.h>
#include <iostream>
#include <thread>

char readInput()
{
    char ch = getch();

    return ch;
}


int main(int argc, char const *argv[])
{
    setupConsole();

    const int FPS = 2;

    const double frameDelay = 1000.00 / (double)FPS;


    Coords title_start = Coords(10, 5);
    Coords board_size = Coords(30, 15);
    Coords board_start = Coords(5, 10);
    Coords debug_line = Coords(5, 25);

    Snake snake(board_size);
    Apple apple(board_size);

    std::future input_future = std::async(std::launch::async, readInput); 

    int score = 0;

    while (true)
    {
        auto frameStart = std::chrono::system_clock::now();

        ERASE_SCREEN;

        MOVE_CURSOR_TO_POS(title_start.y, title_start.x);
        printf("SNAKE GAME             Score: %d", score);

        MOVE_CURSOR_TO_POS(board_start.y, board_start.x);
        for (int y = 0; y < board_size.y; y++)
        {
            for (int x = 0; x < board_size.x; x++)
                printf("*");

            MOVE_CURSOR_TO_POS(board_start.y + y, board_start.x);
        }

        if (input_future.wait_for(std::chrono::duration<double, std::milli>(1)) == std::future_status::ready)
        {
            char ch = input_future.get();

            switch (ch)
            {
            case 'w':
                snake.setDir(1);
                break;
            case 'd':
                snake.setDir(2);
                break;
            case 's':
                snake.setDir(3);
                break;
            case 'a':
                snake.setDir(4);
                break;
            case 'q':
                exit(0);
                break;
            default:
                break;
            }

            input_future = std::async(std::launch::async, readInput);
        }

        if(snake.collides(snake.getHead(), 1))
        {
            ERASE_SCREEN;

            MOVE_CURSOR_TO_POS(20, 20);
            printf("GAME OVER, YOU LOST! SCORE: %d", score);
            MOVE_CURSOR_TO_POS(board_start.y + board_size.y, board_start.x + board_size.x);

            exit(0);
        }

        if (snake.collides(apple.getCoords()))
        {
            score++;
            snake.eat();
            while(snake.collides(apple.getCoords()))
                apple.spawn();
        }

        snake.step();

        apple.draw(board_start);
        snake.draw(board_start);
        
        MOVE_CURSOR_TO_POS(board_start.y + board_size.y, board_start.x + board_size.x);

        auto frameEnd = std::chrono::system_clock::now();

        std::chrono::duration<double> elapsed_seconds = frameEnd - frameStart;

        std::chrono::milliseconds elapsed_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed_seconds);

        std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(frameDelay - elapsed_milliseconds.count()));
    }

    resetConsole();

    return 0;
}
