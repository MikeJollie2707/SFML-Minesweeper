#ifndef MINESWEEPER_INCLUDE_TILE_HPP
#define MINESWEEPER_INCLUDE_TILE_HPP

#include <SFML/Graphics.hpp>

class Button : public sf::Drawable
{
protected:
    // The size of the button. It's assumed that the button is a square.
    int             size;
    // The actual position of the button on the screen.
    sf::Vector2f    buttonPos;

    // The sprite that will be drawn on the button.
    sf::Sprite      shape;
public:
    Button(int size, sf::Texture* texture = nullptr);

    // Get the position of the button relative to the window.
    sf::Vector2f    getPos();
    // Set the position of the button relative to the window.
    void            setPos(sf::Vector2f newPos);
    // Whether or not the mouse is hovered on the button.
    bool            isHovered(sf::RenderWindow& window);

    // Set the sprite texture.
    void            setSpriteTexture(const sf::Texture& texture);
    void            setSpriteCopy(const sf::Sprite& sprite);
    // Set the sprite size.
    void            setSpriteScale(float scaleX, float scaleY);
    // Set the sprite size.
    void            setSpriteScale(const sf::Vector2f& scale);
    // Set the sprite position. It does not need to be exactly the same as the button's size.
    void            setSpritePosition(float posX, float poxY);
    // Set the sprite position. It does not need to be exactly the same as the button's size.
    void            setSpritePosition(const sf::Vector2f& position);

    void            draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
class Tile : public Button
{
private:
    // Internal value of the tile indicating the number of bombs around it. Range from 0 to 8.
    int     in_value;

    // State variables

    // Whether or not the tile is revealed (or shown on the window).
    bool    revealed;
    // Whether or not the flag is set on this tile.
    bool    flag;
    // Whether or not the tile is a bomb.
    bool    bomb;
public:
    /**
     * @brief Construct a new Tile object
     * 
     * @param value The number of bombs around the tile. Default to 0.
     * @param size The grid size of the tile. Default to 15.
     * @param outline_size The space between each tile. Default to 5.
     */
    Tile(int value = 0, int size = 40, int outline_size = 5);

    // Return the internal value of the tile.
    int     value();
    // Increase the internal value by 1.
    void    inc_value();

    // Flag methods

    // Whether or not the tile is revealed (or shown on the window).
    bool    isRevealed();
    // Whether or not the flag is set on this tile.
    bool    isFlag();
    // Whether or not the tile is a bomb.
    bool    isBomb();

    // A two-way method to set or remove the flag.
    // If the flag is true, it'll be set to false and vice versa.
    void    toggleFlag();
    // A one-way method to reveal a tile.
    void    revealTile();
    // A one-way method to set this tile as a bomb.
    void    placeBomb();
};

#endif