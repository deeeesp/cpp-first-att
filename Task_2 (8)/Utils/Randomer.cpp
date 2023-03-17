#include <ctime>

#include "Randomer.h"

std::default_random_engine randomEngine(time(NULL));

Randomer::Randomer() {}

int Randomer::random(int param)
{
    std::uniform_int_distribution<int> randomNum(0, param);
    return randomNum(randomEngine);
}
