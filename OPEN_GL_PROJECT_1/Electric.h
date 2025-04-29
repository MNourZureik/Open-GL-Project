#ifndef ELECTRIC_ROOM_H
#define ELECTRIC_ROOM_H

#include "PrimitiveDrawer.h"
#include "Point.h"

class Electric {
public:
    void createElectricRoom(float height, float width, float depth,
                            int wall_texture, int floor_texture, int door_texture, int title_texture , int wood , int screen , int screen_body , int keys, int fifa);
	void DrawTable(GLuint tableTexture, GLuint surfaceTexture, GLuint legTexture, 
                       Point tablePos, float tableWidth, float tableHeight, float tableDepth, 
                       float legWidth, float legHeight) ;
void DrawLaptop(GLuint baseTexture, GLuint screenTexture, GLuint keyboardTexture, 
                        Point laptopPos, float baseWidth, float baseDepth, float baseHeight, 
                        float screenWidth, float screenHeight, float screenThickness);

};

#endif // ELECTRIC_ROOM_H
