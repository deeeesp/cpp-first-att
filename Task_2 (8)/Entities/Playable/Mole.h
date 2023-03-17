
#ifndef TASK_2_MOLE_H
#define TASK_2_MOLE_H

#include "../Character.h"
#include "../../Utils/Vector2.h"
#include "../../Game.h"



class Game;

class Mole :public Character
{
public:
    Mole() = default;
    Mole(Gender gender, Vector2 *location, Game *game);

    ~Mole();

public:
    Vector2 *getLocation();
    void setLocation(Vector2 *location);

    Gender getGender() override;
    Status getStatus() override;

    void setGender(Gender gender) override;
    void setStatus(Status status) override;

    bool isUnderGround();
    bool isOnTheGround();
    bool isAttacked();
    bool isMale();
    bool isFemale();
    bool isRest();

    void execAction() override;
private:
    Vector2* chooseTile();
    std::vector<Vector2*>& getTilesAround(std::vector<Vector2*> &tiles);
    void filterTiles(std::vector<Vector2*> &tiles);
    void filterTilesForAttack(std::vector<Vector2*> &tiles);
    void reProduct();

    void move();
    void eat();

private:
    Vector2 *location;
    Gender gender;
    Status status = Status::UnderGround;
    Game *game;
};

#endif //TASK_2_MOLE_H
