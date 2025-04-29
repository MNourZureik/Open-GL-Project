#ifndef GAMING_H
#define GAMING_H

#include "PrimitiveDrawer.h"

class Gaming {
public:
    void createGamingRoom(float height, float width, float depth,
                          int wall_texture, int floor_texture, int door_texture, int title_texture, int table_texture ,int surface_texture , int leg_texture, int screen , int screen_body 
						  , int sopha);
	void DrawBilliardTable(GLuint tableTexture, GLuint surfaceTexture, GLuint legTexture, 
                       Point tablePos, float tableWidth, float tableHeight, float tableDepth, 
                       float legWidth, float legHeight);
	void DrawTreasury(Point position , Point size , int wood);
	void DrawSofa(GLuint baseTexture, GLuint cushionTexture, GLuint armTexture, 
                      Point sofaPos, float sofaWidth, float sofaDepth, float sofaHeight, 
                      float cushionHeight, float armWidth);

	void DrawTexturedCylinder(GLuint texture, Point baseCenter, float radius, float height, int segments = 36);
};

#endif
