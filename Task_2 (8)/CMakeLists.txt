cmake_minimum_required(VERSION 3.24)
project(Task_2)

set(CMAKE_CXX_STANDARD 17)

set(Entities
        Entities/Character.h
        Entities/Playable/Farmer.cpp
        Entities/Playable/Farmer.h
        Entities/Playable/Mole.cpp
        Entities/Playable/Mole.h
        )

set(Utils
        Utils/Vector2.cpp
        Utils/Vector2.h
        Utils/Painter.cpp Utils/Painter.h Utils/Randomer.cpp Utils/Randomer.h)

add_executable(Task_2 main.cpp ${Entities} ${Utils} Game.cpp Game.h GameField.cpp GameField.h)
