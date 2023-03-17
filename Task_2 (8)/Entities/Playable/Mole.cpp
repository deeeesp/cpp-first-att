
#include <ctime>
#include "Mole.h"



Mole::Mole(Gender gender, Vector2 *location, Game *game)
{
    this->gender = gender;
    this->location = location;
    this->game = game;
}

Mole::~Mole()
{
    delete location;
}

Gender Mole::getGender()
{
    return this->gender;
}

void Mole::setGender(Gender gender)
{
    this->gender = gender;
}

Vector2 *Mole::getLocation()
{
    return location;
}

void Mole::setLocation(Vector2 *location)
{
    this->location = location;
}

Status Mole::getStatus()
{
    return status;
}

void Mole::setStatus(Status status)
{
    this->status = status;
}

void Mole::execAction()
{
    if(this->status == Status::Rest)
    {
        if(gender == Female)
        {
            game->createNewMole(location);
        }
        status = Status::UnderGround;
    }
    else if(this->status == Status::UnderGround)
    {
        int var = game->getRandomer()->random(3);
        if(var == 0)
        {
            this->status = Status::OnTheGround;
        }
        else
        {
            move();
        }
        reProduct();
    }
    else if(this->status == Status::OnTheGround)
    {
        eat();
        this->status = Status::Attacked;
    }
    else if(this->status == Status::Attacked)
    {
       this->status = Status::UnderGround;
    }
}

void Mole::move()
{
    location = chooseTile();
}

void Mole::eat()
{
    if(game->getGameField()->tileIsAlive(*location))
    {
        game->getGameField()->kill(*location);
    }
    std::vector<Vector2*> tiles;
    getTilesAround(tiles);
    filterTiles(tiles);
    filterTilesForAttack(tiles);
    for(int i = 0; i < tiles.size(); ++i)
    {
        if(game->getRandomer()->random(2) == 0)
        {
            game->getGameField()->kill(*tiles[i]);
        }
    }
}

Vector2* Mole::chooseTile()
{
    std::vector<Vector2*> tiles;
    getTilesAround(tiles);
    filterTiles(tiles);
    return tiles[game->getRandomer()->random(tiles.size() - 1)];
}

void Mole::filterTiles(std::vector<Vector2 *> &tiles)
{
    for(int i = 0; i < tiles.size(); ++i)
    {
        if(tiles[i]->getX() < 0 || tiles[i]->getX() > game->getGameField()->getSize()->getX() - 1 ||
           tiles[i]->getY() < 0 || tiles[i]->getY() > game->getGameField()->getSize()->getY() - 1)
        {
            tiles.erase(tiles.begin() + i);
            i--;
        }
    }
}

void Mole::filterTilesForAttack(std::vector<Vector2 *> &tiles)
{
    for(int i = 0; i < tiles.size(); ++i)
    {
        if(!game->getGameField()->tileIsAlive(*tiles[i]))
        {
            tiles.erase(tiles.begin() + i);
            i--;
        }
    }
}

std::vector<Vector2*>& Mole::getTilesAround(std::vector<Vector2*> &tiles)
{
    tiles.push_back(new Vector2(location->getX() - 1, location->getY()));
    tiles.push_back(new Vector2(location->getX() + 1, location->getY()));
    tiles.push_back(new Vector2(location->getX(), location->getY() - 1));
    tiles.push_back(new Vector2(location->getX(), location->getY() + 1));
    return tiles;
}

void Mole::reProduct()
{
    if(isFemale() && isUnderGround())
    {
        for(int i = 1; i < game->getCharacters().size(); ++i)
        {
            if(game->getCharacters()[i]->getGender() == Female && game->getCharacters()[i]->getLocation() == this->getLocation())
            {
                continue;
            }
            if(*location == *game->getCharacters()[i]->getLocation() &&
               game->getCharacters()[i]->getGender() == Gender::Male &&
               game->getCharacters()[i]->getStatus() == UnderGround)
            {
                status = Rest;
                game->getCharacters()[i]->setStatus(Rest);
            }
        }
    }
}

bool Mole::isUnderGround()
{
    return status == Status::UnderGround;
}

bool Mole::isOnTheGround()
{
    return status == Status::OnTheGround;
}

bool Mole::isAttacked()
{
    return status == Status::Attacked;
}

bool Mole::isMale()
{
    return gender == Gender::Male;
}

bool Mole::isFemale()
{
    return gender == Gender::Female;
}

bool Mole::isRest()
{
    return status == Status::Rest;
}




// entity