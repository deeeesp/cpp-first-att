
#ifndef TASK_2_FARMER_H
#define TASK_2_FARMER_H

#include "../Character.h"
#include "../../Utils/Vector2.h"
#include "../../Game.h"
#include <vector>


class Game;

class Farmer :public Character
{
public:
    Farmer() = default;
    Farmer(const int speed, const int hitRadius, Vector2 *location, Game *game);

    ~Farmer();

public:
    const int getSpeed() const;
    void setSpeed(const int speed);

    const int getHitRadius() const;
    void setHitRadius(const int hitRadius);

    Vector2 *getLocation() override;
    void setLocation(Vector2 *location);

    const Vector2 *getGoalLocation();
    void setGoalLocation(Vector2 *goalLocation);

    void sortMoles(std::vector<Vector2*> &deltas);

    void execAction() override;

    Gender getGender() override;
    Status getStatus() override;

    void setGender(Gender gender) override;
    void setStatus(Status status) override;

private:
    void findClosestMole();
    void move();
    void attack();

private:
    int speed;
    int hitRadius;
    Vector2 *location;
    Vector2 *goalLocation = nullptr;
    Gender gender = Male;
    Status status = OnTheGround;

    Game *game;
};



#endif //TASK_2_FARMER_H
