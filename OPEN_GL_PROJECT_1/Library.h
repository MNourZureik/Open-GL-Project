#ifndef LIBRARY_H
#define LIBRARY_H

#include "PrimitiveDrawer.h"

class Library {
public:
    void createLibraryRoom(float height, float width, float depth,
                          int wall_texture, int floor_texture, int door_texture, int title_texture, int wood , int wood2 , int books);
	void DrawLibrary(GLuint shelfTexture, GLuint bookTexture, GLuint outerBoxTexture, Point startPos, float width, float height, float depth, int numShelves);
};

#endif
