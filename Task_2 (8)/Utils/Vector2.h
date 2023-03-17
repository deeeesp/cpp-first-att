#ifndef TASK_2_VECTOR2_H
#define TASK_2_VECTOR2_H


class Vector2
{
private:
    int x;
    int y;

public:
    Vector2();
    Vector2(const int x, const int y);

    ~Vector2();

public:
    bool operator == (Vector2 &v1)
    {
        return x == v1.x && y == v1.y;
    };

    Vector2 *operator - (Vector2 &v1)
    {
        return new Vector2(x - v1.x, y - v1.y);
    }

public:
    const int getX() const;
    void setX(const int x);

    const int getY() const;
    void setY(const int y);

    void setXY(int x, int y);
};


#endif //TASK_2_VECTOR2_H
