#ifndef MINESWEEPER_SRC_GAME_CPP
#define MINESWEEPER_SRC_GAME_CPP

#include "game.hpp"
#include <iostream>

Game::Game(int sizeX, int sizeY, int bombs, int grid, int outline) :
    grid(grid),
    outline(outline),
    EMPTY(15),
    HOVERED(0),
    FLAG(14),
    BOMB(12),
    NOT_BOMB(11),
    REST_BOMB(10)
{
    // Seed init
    srand(time(NULL));

    // Window init
    window.create(sf::VideoMode(grid * sizeY, grid * sizeX), "Minesweeper SFML");

    // Utility init
    board_size.x = sizeX; board_size.y = sizeY;

    // Board init
    for (int i = 0; i < board_size.x; i++)
    {
        std::vector<Tile> temp;
        for (int j = 0; j < board_size.y; j++)
        {
            temp.push_back(std::move(
                Tile(0, this->grid, this->outline)
            ));
        }
        board.push_back(std::move(temp));
    }

    // Load textures
    texture.loadFromFile("../texture/minesweepertextures.png");
    for (int i = 240; i >= 0; i -= 16)
    {
        sprites.emplace_back(texture, sf::IntRect(0, i, 16, 16));
    }

    // Graphic init
    for (int i = 0; i < board_size.x; i++)
        for (int j = 0; j < board_size.y; j++)
        {
            board[i][j].setSpriteCopy(sprites[EMPTY]);

            // Array's coord is inverse to screen's coord.
            board[i][j].setSpritePosition(sf::Vector2f(j * this->grid, i * this->grid));
            board[i][j].setPos(sf::Vector2f(j * this->grid, i * this->grid));

            float ratio = (float(this->grid) - float(this->outline)) / 16;
            board[i][j].setSpriteScale(ratio, ratio);
        }
    
    //buttons.push_back(std::move(Button(40)));

    remaining_bomb = 0; 
    remaining_flag = 0; 
    remaining_tile = board_size.x * board_size.y;
    hovered_pos.x = 0;
    hovered_pos.y = 0;

    setupMines(bombs);
}

void Game::setupMines(int bombs)
{
    // Set up mines
    while (remaining_bomb < bombs)
    {
        int x = rand() % board_size.x;
        int y = rand() % board_size.y;

        if (board[x][y].isBomb() == false)
        {
            board[x][y].placeBomb();
            remaining_bomb++; remaining_flag++;
        }
    }

    // Init value to remaining
    for (int i = 0; i < board_size.x; i++)
    {
        for (int j = 0; j < board_size.y; j++)
        {
            if (board[i][j].isBomb()) continue;
            
            // Up
            if (
                j - 1 >= 0
            )
            {
                if (board[i][j - 1].isBomb())
                    board[i][j].inc_value();
            }
            // Up right
            if (
                j - 1 >= 0 &&
                i + 1 <= board_size.x - 1
            )
            {
                if (board[i + 1][j - 1].isBomb())
                    board[i][j].inc_value();
            }
            // Right
            if (
                i + 1 <= board_size.x - 1
            )
            {
                if (board[i + 1][j].isBomb())
                    board[i][j].inc_value();
            }
            // Down right
            if (
                j + 1 <= board_size.y - 1 &&
                i + 1 <= board_size.x - 1
            )
            {
                if (board[i + 1][j + 1].isBomb())
                    board[i][j].inc_value();
            }
            // Down
            if (
                j + 1 <= board_size.y - 1
            )
            {
                if (board[i][j + 1].isBomb())
                    board[i][j].inc_value();
            }
            // Down left
            if (
                j + 1 <= board_size.y - 1 &&
                i - 1 >= 0
            )
            {
                if (board[i - 1][j + 1].isBomb())
                    board[i][j].inc_value();
            }
            // Left
            if (
                i - 1 >= 0
            )
            {
                if (board[i - 1][j].isBomb())
                    board[i][j].inc_value();
            }
            // Up left
            if (
                j - 1 >= 0 &&
                i - 1 >= 0
            )
            {
                if (board[i - 1][j - 1].isBomb())
                    board[i][j].inc_value();
            }
        }
    }

    gameState = 0;
}

void Game::selectTile(sf::Mouse::Button button)
{
    if (gameState == 1 || gameState == -1)
        return;
    if (button == sf::Mouse::Button::Left)
    {
        if (gameState != -1 && board[hovered_pos.x][hovered_pos.y].isBomb())
        {
            gameState = -1;
            revealMines();
        }
        else
        {
            openTiles(hovered_pos.x, hovered_pos.y);
        }
    }
    else if (button == sf::Mouse::Button::Right)
    {
        if (board[hovered_pos.x][hovered_pos.y].isFlag())
        {
            if (board[hovered_pos.x][hovered_pos.y].isBomb())
            {
                remaining_bomb++;
            }

            board[hovered_pos.x][hovered_pos.y].toggleFlag(); // flag is now false.
            remaining_flag++;
        }
        else
        {
            // If the player ran out of flag, don't let them set more.
            if (remaining_flag != 0)
            {
                if (board[hovered_pos.x][hovered_pos.y].isBomb())
                {
                    remaining_bomb--;
                }

                board[hovered_pos.x][hovered_pos.y].toggleFlag(); // flag is now true.
                remaining_flag--;
            }

        }
    }

    if (isWin())
        gameState = 1;
}

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (int i = 0; i < board_size.x; i++)
        for (int j = 0; j < board_size.y; j++)
        {
            target.draw(board[i][j]);
        }
}

void Game::openTiles(int x, int y)
{
    // First we check if the current tile is "legit", then we check if the tile is a normal one and it's not revealed.

    if (x >= 0 && x < board_size.x && y >= 0 && y < board_size.y)
        if (!board[x][y].isBomb() && !board[x][y].isFlag() && !board[x][y].isRevealed())
        {
            board[x][y].revealTile();
            remaining_tile--;

            if (board[x][y].value() == 0)
            {
                // Up
                openTiles(x, y - 1);
                // Up right
                openTiles(x + 1, y - 1);
                // Right
                openTiles(x + 1, y);
                // Down right
                openTiles(x + 1, y + 1);
                // Down
                openTiles(x, y + 1);
                // Down left
                openTiles(x - 1, y + 1);
                // Left
                openTiles(x - 1, y);
                // Up left
                openTiles(x - 1, y - 1);
            }
        }
}

void Game::update()
{
    for (int i = 0; i < board_size.x; i++)
    {
        for (int j = 0; j < board_size.y; j++)
        {
            if (board[i][j].isRevealed())
            {
                if (!board[i][j].isBomb())
                    board[i][j].setSpriteCopy(sprites[board[i][j].value()]);
                else
                {
                    // This part is left empty because it is the case for revealMines()
                }
            }
            else if (&board[hovered_pos.x][hovered_pos.y] == &board[i][j])
            {
                board[i][j].setSpriteCopy(sprites[HOVERED]);
            }
            else if (board[i][j].isFlag())
                board[i][j].setSpriteCopy(sprites[FLAG]);
            else
                board[i][j].setSpriteCopy(sprites[EMPTY]);
        }
    }
}

bool Game::isWin()
{
    if (gameState == 1)
        return true;
    if (remaining_bomb == 0)
        return true;
    if (remaining_tile == remaining_bomb)
        return true;
    if (remaining_flag == remaining_bomb && remaining_flag == 0)
        return true;
    return false;
}

void Game::revealMines()
{
    for (int i = 0; i < board_size.x; i++)
        for (int j = 0; j < board_size.y; j++)
            if (board[i][j].isBomb())
            {
                board[i][j].revealTile();
                if (i == hovered_pos.x && j == hovered_pos.y)
                    board[i][j].setSpriteCopy(sprites[BOMB]);
                else
                    board[i][j].setSpriteCopy(sprites[REST_BOMB]);
            }
            else if (board[i][j].isFlag())
            {
                board[i][j].revealTile();
                board[i][j].setSpriteCopy(sprites[NOT_BOMB]);
            }
}

const sf::Vector2i Game::getBoardSize() { return board_size; }

void Game::event()
{
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
            {
                window.close();
                break;
            }
            case sf::Event::KeyPressed:
            {
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
                break;
            }
            case sf::Event::MouseMoved:
            {
                if (!board[hovered_pos.x][hovered_pos.y].isHovered(window))
                {
                    //hovered_pos.x = -1;
                    //hovered_pos.y = -1;

                    for (int i = 0; i < board_size.x; i++)
                        for (int j = 0; j < board_size.y; j++)
                            if (board[i][j].isHovered(window))
                            {
                                hovered_pos.x = i;
                                hovered_pos.y = j;
                                break;
                            }
                }
                break;
            }
            case sf::Event::MouseButtonPressed:
            {
                selectTile(event.mouseButton.button);
                break;
            }
            case sf::Event::Resized:
            {
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }
            }
        }

        update();

        window.clear();
        window.draw(*this);
        window.display();

        if (gameState == 1)
            std::cout << "You win!" << '\n';
        else if (gameState == -1)
            std::cout << "You lost!" << '\n';
        
    }
}

#endif