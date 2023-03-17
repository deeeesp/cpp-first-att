
#include "GameField.h"

GameField::GameField(int x, int y)
{
    createField(x, y);
    size = new Vector2(x, y);
}

GameField::~GameField()
{
    deleteField();
}

int **GameField::getField()
{
    return field;
}

void GameField::setField(int **field)
{
    this->field = field;
}

void GameField::setField(int x, int y)
{
    createField(x, y);
}

const Vector2 *GameField::getSize()
{
    return size;
}

void GameField::setSize(Vector2 *size)
{
    this->size = size;
}

void GameField::createField(int x, int y)
{
    field = new int *[x];
    for(int i = 0; i < x; ++i)
    {
        field[i] = new int [y];
        for(int j = 0; j < y; ++j)
        {
            field[i][j] = 1;
        }
    }
}

void GameField::deleteField()
{
    for(int i = size->getX() - 1; i >= 0; --i)
    {
        delete[] field[i];
    }
}

bool GameField::isClear()
{
    for(int i = 0; i < size->getX(); ++i)
    {
        for(int j = 0; j < size->getY(); ++j)
        {
            if(field[i][j])
            {
                return false;
            }
        }
    }
    return true;
}

bool GameField::tileIsAlive(Vector2 &tile)
{
    return field[tile.getX()][tile.getY()] == 1;
}

void GameField::kill(Vector2 &tile)
{
    field[tile.getX()][tile.getY()] = 0;
}
