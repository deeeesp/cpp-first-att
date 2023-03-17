
#include <iostream>
#include <cstdlib>
#include <thread>
#include <chrono>
#include "Game.h"
#include "Utils/Painter.h"


Game::Game() {}

Game::Game(GameField *gameField, std::vector<Character*> characters)
{
    this->gameField = gameField;
    this->characters = characters;
}

Game::~Game()
{
    delete gameField;
    for(int i = 0; i < characters.size(); ++i)
    {
        delete characters[i];
    }
    //delete randomer;
//    delete characters;
}

GameField *Game::getGameField()
{
    return gameField;
}

Randomer *Game::getRandomer()
{
    return randomer;
}

std::vector<Character *> &Game::getCharacters()
{
    return characters;
}

bool Game::molesAlive()
{
    return characters.size() > 1;
}

void Game::run()
{
    std::cout << "Input size of game field: x and y" << std::endl;
    int x, y;
    std::cin >> x >> y;
    std::cout << "Input parameters for Farmer: speed, hit radius, location(x) and location(y)" << std::endl;
    int speed, hitRadius, locationX, locationY;
    std::cin >> speed >> hitRadius >> locationX >> locationY;
    std::cout << "Input number of Male characters and Female characters" << std::endl;
    int maleMole, femaleMole;
    std::cin >> maleMole >> femaleMole;

    gameField = new GameField(x, y);
    characters.push_back(new Farmer(speed, hitRadius, new Vector2(locationX, locationY), this));
    createInitMoles(maleMole, femaleMole);
    Painter *painter = new Painter(x, y);
    std::cout << "Start";
    painter->paint(gameField, characters);

    while(!gameField->isClear() && molesAlive())
    {
        switch(gameStage)
        {
            case GameStage::FarmerTurn:
                characters[0]->execAction();
                std::cout << "Farmer Turn";
                gameStage = GameStage::MolesTurn;
                break;
            case GameStage::MolesTurn:
                std::cout << "Moles Turn";
                execMolesAction();
                //findTwoMolesInOneTile();
                gameStage = GameStage::FarmerTurn;
                break;
            default:
                std::cout << "Incorrect game stage";
                break;
        }
        std::this_thread::sleep_for(std::chrono::nanoseconds(3000000000));
        painter->paint(gameField, characters);
        std::cout << characters.size() - 1 << std::endl;
    }

    delete painter;
}

void Game::createInitMoles(int maleMoles, int femaleMoles)
{
    int number;
    for(number = 0; number < maleMoles; ++number)
    {
        characters.push_back(new Mole(Gender::Male, createMoleLocation(), this));
    }
    for(; number < maleMoles + femaleMoles; ++number)
    {
        characters.push_back(new Mole(Gender::Female, createMoleLocation(), this));
    }
}

Vector2* Game::createMoleLocation()
{
    int x = randomer->random(gameField->getSize()->getX() - 1);
    int y = randomer->random(gameField->getSize()->getY() - 1);
    return new Vector2(x, y);
}

void Game::execMolesAction()
{
    for(int i = 1; i < characters.size(); ++i)
    {
        characters[i]->execAction();
    }
}

//void Game::findTwoMolesInOneTile()
//{
//    for(int i = 0; i < characters.size(); ++i)
//    {
//        if(characters[i]->isUnderGround())
//        {
//            for(int j = i + 1; j < characters.size(); ++j)
//            {
//                if(characters[j]->isUnderGround())
//                {
//                    if(*characters[i]->getLocation() == *(characters[j]->getLocation())
//                       && characters[i]->getGender() != characters[j]->getGender())
//                    {
//                        characters[i]->setStatus(Rest);
//                        characters[j]->setStatus(Rest);
//                    }
//                }
//            }
//        }
//    }
//}

void Game::createNewMole(Vector2 *location)
{
    int gender = randomer->random(2);
    if(gender == 2)
    {
        characters.push_back(new Mole(Gender::Female, new Vector2(location->getX(), location->getY()), this));
    }
    else
    {
        characters.push_back(new Mole(Gender::Male, new Vector2(location->getX(), location->getY()), this));
    }
}

void Game::killMole(Vector2 *location)
{
    for(int i = 1; i < characters.size(); ++i)
    {
        if(*characters[i]->getLocation() == *location)
        {
            delete characters[i];
            characters.erase(characters.begin() + i);
            break;
        }
    }
}
