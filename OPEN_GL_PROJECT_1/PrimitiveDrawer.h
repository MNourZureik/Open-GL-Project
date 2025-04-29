#ifndef PRIMITIVEDRAWER_H
#define PRIMITIVEDRAWER_H

#include "Point.h"
#include <string>
#include <iostream>
using namespace std;

class PrimitiveDrawer {
public:
	PrimitiveDrawer();
	void DrawPoint(Point point);
	void DrawLine(Point start, Point end);
	void DrawTriangle(Point v1, Point v2, Point v3);
	void DrawQuad(Point v1, Point v2, Point v3, Point v4);
	void DrawTexturedQuad(GLuint texture, Point v1, Point v2, Point v3, Point v4, int repeat);
	void DrawRectangularPrism(Point start , float width , float height , float depth);
	void DrawOpenRectangularPrism(Point start , float width , float height , float depth , string distination);
	void DrawTextureRectangularPrism(GLuint texture ,Point start , float width , float height , float depth, int repeat);
	void DrawOpenTextureRectangularPrism(GLuint texture ,Point start , float width , float height , float depth, int repeat , string distination);
	void DrawTextureTreasuryHandle(GLuint texture , Point start, float width , float height, bool isPos);
	void DrawCircle(Point center, float radius, int segments);
	void DrawCircleTexture(GLuint texture, Point center, float radius, int segments);
	void DrawPictureFrame(GLuint frameTexture, GLuint pictureTexture, Point startPos, float width, float height, float frameThickness);
	void DrawWindowWithCurtains(GLuint windowTexture, GLuint curtainTexture, Point startPos, float width, float height, float frameThickness);
	void DrawTV(GLuint screenTexture, GLuint bodyTexture, Point startPos, float width, float height, float depth);
	void DrawPot(GLuint potTexture, Point startPos, float potRadius, float potHeight);
	void DrawDoor(GLuint doorTexture, Point startPos, float width, float height, float depth);
	void DrawChandelier(GLuint baseTexture, GLuint chainTexture, GLuint bulbTexture, Point startPos, float baseRadius, float baseHeight, float hangingLength, int numChains) ;
	void DrawLibrary(GLuint shelfTexture, GLuint bookTexture, GLuint outerBoxTexture, Point startPos, float width, float height, float depth, int numShelves);
};

#endif
