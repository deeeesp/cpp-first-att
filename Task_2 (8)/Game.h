
#ifndef TASK_2_GAME_H
#define TASK_2_GAME_H

#include <vector>
#include "GameField.h"
#include "Entities/Playable/Farmer.h"
#include "Entities/Playable/Mole.h"
#include "Utils/Randomer.h"


enum GameStage
{
    FarmerTurn,
    MolesTurn
};

class Farmer;
class Mole;

class Game
{
public:
    Game();
    Game(GameField *gameField, std::vector<Character*> characters);

    ~Game();
public:
    void run();

    GameField* getGameField();

    std::vector<Character*> &getCharacters();

    Randomer* getRandomer();

    void killMole(Vector2 *location);

    void createNewMole(Vector2 *location);


private:
    void createInitMoles(int maleMoles, int femaleMoles);
    Vector2 *createMoleLocation();
    void execMolesAction();
    void findTwoMolesInOneTile();
    bool molesAlive();

private:
    GameField *gameField;
    std::vector<Character*> characters;
    GameStage gameStage = GameStage::FarmerTurn;
    Randomer *randomer;
};



#endif //TASK_2_GAME_H
