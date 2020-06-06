#ifndef MINESWEEPER_SRC_TILE_CPP
#define MINESWEEPER_SRC_TILE_CPP

#include "tile.hpp"
#include <iostream>

Button::Button(int size, sf::Texture* texture) :
    size(size)
{
    if (texture != nullptr)
        shape.setTexture(*texture);
}

sf::Vector2f Button::getPos() { return buttonPos; }
void Button::setPos(sf::Vector2f newPos) { buttonPos = newPos; }

bool Button::isHovered(sf::RenderWindow& window)
{
    int mouseX = sf::Mouse::getPosition(window).x;
    int mouseY = sf::Mouse::getPosition(window).y;

    return (
        buttonPos.x <= mouseX && mouseX <= buttonPos.x + size &&
        buttonPos.y <= mouseY && mouseY <= buttonPos.y + size
    );
}

void Button::setSpriteTexture(const sf::Texture& texture)
{
    shape.setTexture(texture);
}
void Button::setSpriteCopy(const sf::Sprite& sprite)
{
    shape.setTexture(*sprite.getTexture());
    shape.setTextureRect(sprite.getTextureRect());
}
void Button::setSpriteScale(const sf::Vector2f& scale)
{
    shape.setScale(scale);
}
void Button::setSpriteScale(float scaleX, float scaleY)
{
    setSpriteScale(sf::Vector2f(scaleX, scaleY));
}
void Button::setSpritePosition(const sf::Vector2f& position)
{
    shape.setPosition(position);
}
void Button::setSpritePosition(float posX, float posY)
{
    setSpritePosition(sf::Vector2f(posX, posY));
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(shape);
}

Tile::Tile(int value, int size, int outline_size) :
    Button(size - outline_size),
    in_value(value),
    revealed(false),
    flag(false),
    bomb(false)
{
}

int Tile::value() { return in_value; }
void Tile::inc_value() { in_value++; }

bool Tile::isRevealed() { return revealed; }
bool Tile::isFlag() { return flag; }
bool Tile::isBomb() { return bomb; }

void Tile::toggleFlag() { flag = !flag; }
void Tile::revealTile() { revealed = true; }
void Tile::placeBomb() { bomb = true; }


#endif
