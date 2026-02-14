#pragma once

typedef struct Vector2
{
    float x;
    float y;
} Vector2;

typedef struct Rect
{
    Vector2 pos;
    Vector2 scale;
} Rect;

Vector2 Vector2_Zero();

int Rect_Contains(Rect self, Vector2 pos);
Rect Rect_Zero();
