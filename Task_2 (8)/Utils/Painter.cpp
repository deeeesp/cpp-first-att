
#include "Painter.h"
#include <iostream>
#include <vector>

Painter::Painter() {}

Painter::Painter(int x, int y)
{
    paintedField = new std::string *[x];
    for(int i = 0; i < x; ++i)
    {
        paintedField[i] = new std::string[y];
    }
    this->rows = x;
}

Painter::~Painter()
{
    for(int i = rows - 1; i >= 0; --i)
    {
        delete[] paintedField[i];
    }
    delete[] paintedField;
}

void Painter::paint(GameField *gameField, std::vector<Character*> &characters)
{
    int **field = gameField->getField();
    const Vector2 *size = gameField->getSize();
    fillField(field, size, characters);
    std::cout << "--------------------------------------------------------------------------------" << std::endl;
    for(int i = 0; i < size->getX(); ++i)
    {
        for(int j = 0; j < size->getY(); ++j)
        {
            std::cout << paintedField[i][j];
        }
        std::cout << std::endl;
    }
}

void Painter::fillField(int **field, const Vector2 *size, std::vector<Character*> &characters)
{

    for(int i = 0; i < size->getX(); ++i)
    {
        for(int j = 0; j < size->getY(); ++j)
        {
            if(field[i][j] == 1)
            {
                paintedField[i][j] = "P     ";
            }
            else if(field[i][j] == 0)
            {
                paintedField[i][j] = "X     ";
            }
        }
    }
    for(int i = 1; i < characters.size(); ++i)
    {
        if(characters[i]->getStatus() == UnderGround)
        {
            paintedField[characters[i]->getLocation()->getX()][characters[i]->getLocation()->getY()] = "U";
        }
        else if(characters[i]->getStatus() == OnTheGround)
        {
            paintedField[characters[i]->getLocation()->getX()][characters[i]->getLocation()->getY()] = "M";
        }
        else if(characters[i]->getStatus() == Attacked)
        {
            paintedField[characters[i]->getLocation()->getX()][characters[i]->getLocation()->getY()] = "A";
        }
        else if(characters[i]->getStatus() == Rest)
        {
            paintedField[characters[i]->getLocation()->getX()][characters[i]->getLocation()->getY()] = "R";
        }
        if(characters[i]->getGender() == Male)
        {
            paintedField[characters[i]->getLocation()->getX()][characters[i]->getLocation()->getY()] += "_M   ";
        }
        else if(characters[i]->getGender() == Female)
        {
            paintedField[characters[i]->getLocation()->getX()][characters[i]->getLocation()->getY()] += "_W   ";
        }

    }
    paintedField[characters[0]->getLocation()->getX()][characters[0]->getLocation()->getY()] = "FARM  ";
}
