
#include <cmath>
#include "Farmer.h"

Farmer::Farmer(const int speed, const int hitRadius, Vector2  *location, Game *game)
{
    this->speed = speed;
    this->hitRadius = hitRadius;
    this->location = location;
    this->game = game;
}

Farmer::~Farmer()
{
    delete location;
    if(goalLocation != nullptr)
    {
        delete goalLocation;
    }
}

const int Farmer::getSpeed() const
{
    return this->speed;
}

void Farmer::setSpeed(const int speed)
{
    this->speed = speed;
}

const int Farmer::getHitRadius() const
{
    return this->hitRadius;
}

void Farmer::setHitRadius(const int hitRadius)
{
    this->hitRadius = hitRadius;
}

Vector2* Farmer::getLocation()
{
    return location;
}

void Farmer::setLocation(Vector2 *location)
{
    this->location = location;
}

const Vector2 *Farmer::getGoalLocation()
{
    return goalLocation;
}

void Farmer::setGoalLocation(Vector2 *goalLocation)
{
    this->goalLocation = goalLocation;
}

void Farmer::execAction()
{
    findClosestMole();
    if(goalLocation != nullptr)
    {
        move();
    }
}

void Farmer::findClosestMole()
{
    std::vector<Vector2*> deltas;
    for(int i = 1; i < game->getCharacters().size(); ++i)
    {
        if(game->getCharacters()[i]->getStatus() == UnderGround)
        {
            continue;
        }
        deltas.push_back(new Vector2(
                location->getX() - game->getCharacters()[i]->getLocation()->getX(),
                location->getY() - game->getCharacters()[i]->getLocation()->getY())
                );
    }
    sortMoles(deltas);
    if(deltas.size() > 0)
    {
        goalLocation = *location - *deltas[deltas.size() - 1];
    }
}

void Farmer::sortMoles(std::vector<Vector2*> &deltas)
{
    for(int i = 0; i < deltas.size(); ++i)
    {
        for(int j = 0; j < deltas.size() - i - 1; ++j)
        {
            if(abs(deltas[j]->getX() + deltas[j]->getY()) < abs(deltas[j + 1]->getX() + deltas[j + 1]->getY()))
            {
                Vector2 *v1 = deltas[j + 1];
                deltas[j + 1] = deltas[j];
                deltas[j] = v1;
            }
        }
    }
}

void Farmer::move()
{
    attack();
    if(goalLocation == nullptr)
    {
        return;
    }
    Vector2 *delta;
    for(int i = 0; i < speed; ++i)
    {
        delta = *location - *goalLocation;
        if(delta->getX() != 0 && delta->getY() == 0)
        {
            if(delta->getX() > 0)
            {
                location->setX(location->getX() - 1);
            } else
            {
                location->setX(location->getX() + 1);
            }
        }
        else if(delta->getY() != 0 && delta->getX() == 0)
        {
            if(delta->getY() > 0)
            {
                location->setY(location->getY() - 1);
            } else
            {
                location->setY(location->getY() + 1);
            }
        }
        else if(delta->getX() != 0 && delta->getY() != 0)
        {
            if(abs(delta->getX()) <= abs(delta->getY()))
            {
                if(delta->getX() > 0)
                {
                    location->setX(location->getX() - 1);
                } else
                {
                    location->setX(location->getX() + 1);
                }
            }
            else
            {
                if(delta->getY() > 0)
                {
                    location->setY(location->getY() - 1);
                } else
                {
                    location->setY(location->getY() + 1);
                }
            }
        }
        int sizeBefore = game->getCharacters().size();
        attack();
        if(sizeBefore > game->getCharacters().size())
        {
            break;
        }
    }
    delete delta;
}

void Farmer::attack()
{
    if(location->getX() == goalLocation->getX() && abs(location->getY() - goalLocation->getY()) <= hitRadius
    || location->getY() == goalLocation->getY() && abs(location->getX() - goalLocation->getX()) <= hitRadius)
    {
        game->killMole(goalLocation);
        delete goalLocation;
        goalLocation = nullptr;
    }
}

Gender Farmer::getGender()
{
    return gender;
}

Status Farmer::getStatus()
{
    return status;
}

void Farmer::setGender(Gender gender)
{
    this->gender = gender;
}

void Farmer::setStatus(Status status)
{
    this->status = status;
}
