
#ifndef TASK_2_PAINTER_H
#define TASK_2_PAINTER_H

#include <vector>
#include "../GameField.h"
#include "../Entities/Playable/Farmer.h"
#include "../Entities/Playable/Mole.h"



class Painter
{
public:
    Painter();
    Painter(int x, int y);

    ~Painter();

public:
    void paint(GameField *gameField, std::vector<Character*> &characters);

private:
    void fillField(int **field, const Vector2 *size, std::vector<Character*> &characters);

private:
    std::string **paintedField;
    int rows;
};



#endif //TASK_2_PAINTER_H
