#pragma once

typedef struct Vector2
{
    float x;
    float y;
};

typedef struct Rect
{
    Vector2 pos;
    Vector2 scale;
} Rect;

int Rect_Contains(Rect self, float x, float y);
Rect Rect_Zero();

Vector2 Vector2_Zero();
