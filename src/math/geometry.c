#include <stdio.h>

#include "geometry.h"

Vector2 Vector2_Zero()
{
    return (Vector2){0, 0};
}

int Rect_Contains(Rect self, Vector2 pos)
{
    return (self.pos.x <= pos.x && self.pos.y <= pos.y) &&
           (self.scale.x + self.pos.x > pos.x && self.scale.y + self.pos.y > pos.y);
}

Rect Rect_Zero()
{
    return (Rect){Vector2_Zero(), Vector2_Zero()};
}
