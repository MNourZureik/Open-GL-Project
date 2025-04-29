#ifndef MALL_H
#define MALL_H

#include <windows.h>
#include <gl.h>
#include <glu.h>
#include "PrimitiveDrawer.h"

class Mall {
public:
    Mall(); // Constructor
    void drawMallFloor(Point start, float width, float depth, int floor_texture );
    void createMallLand(float floor_width, float floor_depth, int floor_texture , int street);
    void drawMall(GLuint wall_texture, GLuint floor_texture, GLuint ceiling_texture, GLuint title_texture);
};

#endif // MALL_H
