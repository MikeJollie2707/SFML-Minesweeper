#ifndef MINESWEEPER_INCLUDE_GAME_HPP
#define MINESWEEPER_INCLUDE_GAME_HPP

#include <vector>
#include <cstdlib>

#include "tile.hpp"

class Game : public sf::Drawable
{
private:
    // The minesweeper's board.
    std::vector<std::vector<Tile>> board;
    // The board size.
    sf::Vector2i board_size;
    // A list of textures used in the game.
    std::vector<sf::Sprite> sprites;
    sf::Texture texture;
    // A list of buttons in the game excluding the tiles.
    std::vector<Button> buttons;

    // Indicate the game current progress.
    int gameState; // -1 : lost, 0 : on-going, 1 : won
    int remaining_bomb;
    int remaining_tile;
    int remaining_flag;

    // Pointer to the current hover tile.
    sf::Vector2i hovered_pos;

    //sf::Clock internal_clock;

    // Graphic variables
    sf::RenderWindow window;
    const int grid;
    const int outline;

    // Texture utility variables
    // These variables are used to access the `textures` easily.

    const int EMPTY; // 15
    const int HOVERED; // 0
    const int FLAG; // 14
    const int BOMB; // 12
    const int NOT_BOMB;
    const int REST_BOMB;

    // Set up the mines and assign values to the remaining tiles.
    void setupMines(int bombs);
    // Open the surrounding tiles.
    void openTiles(int x, int y);

    bool isWin();

    void revealMines();

public:
    // Create the board for playing
    Game(int sizeX, int sizeY, int bombs = 10, int grid = 40, int outline = 5);

    const sf::Vector2i getBoardSize();


    // Choose an action on the hovered tile depends on the mouse clicked.
    void selectTile(sf::Mouse::Button button);

    // Update the state of the board. This is usually called before `draw`.
    void update();

    // Render to the window.
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    void event();
};

#endif
