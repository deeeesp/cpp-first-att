#ifndef TASK_2_CHARACTER_H
#define TASK_2_CHARACTER_H


#include "../Utils/Vector2.h"

enum Gender
{
    Male,
    Female
};

enum Status
{
    OnTheGround,
    UnderGround,
    Attacked,
    Rest
};

class Character
{
public:
    virtual void execAction() = 0;
    virtual Vector2* getLo2cation() = 0;

    virtual Status getStatus() = 0;
    virtual Gender getGender() = 0;

    virtual void setStatus(Status status) = 0;
    virtual void setGender(Gender gender) = 0;

private:
//    MoleStatus status = MoleStatus::UnderGround;
//    MoleGender gender;
};



#endif //TASK_2_CHARACTER_H
