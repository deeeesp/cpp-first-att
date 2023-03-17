
#ifndef TASK_2_GAMEFIELD_H
#define TASK_2_GAMEFIELD_H

#include "Utils/Vector2.h"


class GameField
{
public:
    GameField() = default;
    GameField(int x, int y);

    ~GameField();
public:
    bool isClear();

    int** getField();
    void setField(int **field);
    void setField(int x, int y);

    const Vector2 *getSize();
    void setSize(Vector2 *size);
    bool tileIsAlive(Vector2 &tile);
    void kill(Vector2 &tile);

private:
    void createField(int x, int y);
    void deleteField();

private:
    int **field;
    Vector2 *size;
};



#endif //TASK_2_GAMEFIELD_H
