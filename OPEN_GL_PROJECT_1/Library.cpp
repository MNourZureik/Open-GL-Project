#include <windows.h>    // Header File For Windows
#include <gl.h>         // Header File For The OpenGL32 Library
#include <glu.h>        // Header File For The GLu32 Library
#include "Library.h"

void Library::createLibraryRoom(float height, float width, float depth,
                              int wall_texture, int floor_texture, int door_texture, int title_texture , int wood , int wood2 , int books) {
	glPushMatrix();
	glRotated(-180 , 0 , 1 , 0);
	glTranslated(-100.0f , -4.0f ,0.0f);
    PrimitiveDrawer drawer;
    float xTranslation = 0.0f;  // Translate on the x-axis by 100
    float zTranslation = 100.0f; // Translate on the z-axis by -100

    // Draw walls
    drawer.DrawTexturedQuad(wall_texture, 
        Point(0 + xTranslation, 0, depth + zTranslation), 
        Point(width + xTranslation, 0, depth + zTranslation), 
        Point(width + xTranslation, height, depth + zTranslation), 
        Point(0 + xTranslation, height, depth + zTranslation), 
        1); // Front wall (replacing back wall)
    drawer.DrawTexturedQuad(wall_texture, 
        Point(0 + xTranslation, 0, 0 + zTranslation), 
        Point(0 + xTranslation, 0, depth + zTranslation), 
        Point(0 + xTranslation, height, depth + zTranslation), 
        Point(0 + xTranslation, height, 0 + zTranslation), 
        1); // Left wall
    drawer.DrawTexturedQuad(wall_texture, 
        Point(width + xTranslation, 0, 0 + zTranslation), 
        Point(width + xTranslation, 0, depth + zTranslation), 
        Point(width + xTranslation, height, depth + zTranslation), 
        Point(width + xTranslation, height, 0 + zTranslation), 
        1); // Right wall

    // Draw floor
    drawer.DrawTexturedQuad(floor_texture, 
        Point(0 + xTranslation, 0, 0 + zTranslation), 
        Point(width + xTranslation, 0, 0 + zTranslation), 
        Point(width + xTranslation, 0, depth + zTranslation), 
        Point(0 + xTranslation, 0, depth + zTranslation), 
        8);

    // Draw ceiling
    drawer.DrawTexturedQuad(wall_texture, 
        Point(0 + xTranslation, height, 0 + zTranslation), 
        Point(width + xTranslation, height, 0 + zTranslation), 
        Point(width + xTranslation, height, depth + zTranslation), 
        Point(0 + xTranslation, height, depth + zTranslation), 
        1);

    // Back face with the hole and double door design (replacing front face)
    float doorWidth = 3.0f;       // Width of each hole
    float doorHeight = 6.0f;      // Height of each hole
    float holeSpacing = 2.0f;     // Space between the two holes
    float upperHeight = height - doorHeight; // Height of the upper section
    float totalHoleWidth = (2 * doorWidth) + holeSpacing; // Combined width of both holes and spacing
    float sideWallWidth = (width - totalHoleWidth) / 2.0f; // Width of the side walls

    // Left side of the back wall
    drawer.DrawTexturedQuad(
        wall_texture,
        Point(0 + xTranslation, 0, 0 + zTranslation),
        Point(sideWallWidth + xTranslation, 0, 0 + zTranslation),
        Point(sideWallWidth + xTranslation, height, 0 + zTranslation),
        Point(0 + xTranslation, height, 0 + zTranslation),
        1
    );

    // Right side of the back wall
    drawer.DrawTexturedQuad(
        wall_texture,
        Point(sideWallWidth + totalHoleWidth + xTranslation, 0, 0 + zTranslation),
        Point(width + xTranslation, 0, 0 + zTranslation),
        Point(width + xTranslation, height, 0 + zTranslation),
        Point(sideWallWidth + totalHoleWidth + xTranslation, height, 0 + zTranslation),
        1
    );

    // Draw the upper middle section of the back wall
    drawer.DrawTexturedQuad(
        wall_texture,
        Point(sideWallWidth + xTranslation, doorHeight, 0 + zTranslation),
        Point(sideWallWidth + totalHoleWidth + xTranslation, doorHeight, 0 + zTranslation),
        Point(sideWallWidth + totalHoleWidth + xTranslation, height, 0 + zTranslation),
        Point(sideWallWidth + xTranslation, height, 0 + zTranslation),
        1
    );

    // Define dimensions for the title
    float titleWidth = 6.0f;      // Width of the title
    float titleHeight = 2.0f;     // Height of the title
    float titleDepthOffset = -0.3f; // Slight offset to place it behind the back wall
    float titleXStart = (width - titleWidth) / 2.0f; // Center the title horizontally
    float titleYStart = height - titleHeight - 18;       

    // Draw the title quad
    drawer.DrawTexturedQuad(
        title_texture,
        Point(titleXStart + xTranslation, titleYStart, titleDepthOffset + zTranslation),                          // Bottom-left corner
        Point(titleXStart + titleWidth + xTranslation, titleYStart, titleDepthOffset + zTranslation),             // Bottom-right corner
        Point(titleXStart + titleWidth + xTranslation, titleYStart + titleHeight, titleDepthOffset + zTranslation), // Top-right corner
        Point(titleXStart + xTranslation, titleYStart + titleHeight, titleDepthOffset + zTranslation),            // Top-left corner
        1
    );
	for (int i = 0; i < 9; ++i) { 
		float xOffset = i * 8; 
		glPushMatrix();
		glTranslated(10.0f + xOffset, 0.0f, 138.0f);
		glRotated(180, 0, 1, 0); 
		drawer.DrawLibrary(wood, books, wood, Point(1, 0, -10), 7, 14, 2, 10); 
		glPopMatrix();
	}

	for (int i = 0; i < 5; ++i) { 
		float xOffset = i * 8; 
		glPushMatrix();
		glTranslated(15.0f, 0.0f, 146.0f - xOffset);
		glRotated(90, 0, 1, 0); 
		drawer.DrawLibrary(wood, books, wood, Point(1, 0, -10), 7, 14, 2, 10); 
		glPopMatrix();
	}
	for (int i = 0; i < 5; ++i) { 
		float xOffset = i * 8; 
		glPushMatrix();
		glTranslated(63.0f, 0.0f, 136.0f - xOffset);
		glRotated(-90, 0, 1, 0); 
		drawer.DrawLibrary(wood, books, wood, Point(1, 0, -10), 7, 14, 2, 10); 
		glPopMatrix();
	}

	for (int i = 0; i < 2; ++i) { 
		float xOffset = i * 10; 
		glPushMatrix();
		glTranslated(10.0f + xOffset, 0.0f, 111.0f);
		drawer.DrawLibrary(wood, books, wood, Point(1, 0, -10), 7, 14, 2, 10); 
		glPopMatrix();
	}

	for (int i = 0; i < 2; ++i) { 
		float xOffset = i * 10; 
		glPushMatrix();
		glTranslated(50.0f + xOffset, 0.0f, 111.0f);
		drawer.DrawLibrary(wood, books, wood, Point(1, 0, -10), 7, 14, 2, 10); 
		glPopMatrix();
	}

	glPopMatrix();
}


//Draw a simplified Library with 3D shelves and an outer box
    void Library::DrawLibrary(GLuint shelfTexture, GLuint bookTexture, GLuint outerBoxTexture, Point startPos, float width, float height, float depth, int numShelves) {
        float shelfHeight = height / numShelves;
		PrimitiveDrawer drawer;
        // Draw the outer box as a rectangular prism around the shelves and books
        drawer.DrawOpenTextureRectangularPrism(
            outerBoxTexture,
            Point(startPos.x - 0.1f, startPos.y - 0.1f, startPos.z - 0.1f), // Slightly larger than the shelves
            width + 0.2f, // Add some padding to the width
            height + 0.2f, // Add some padding to the height
            depth + 0.2f, // Add some padding to the depth
            1,
        "backward");

        for (int i = 0; i < numShelves; ++i) {
            // Draw shelf as a rectangular prism
            drawer.DrawTextureRectangularPrism(
                shelfTexture,
                Point(startPos.x, startPos.y + i * shelfHeight, startPos.z),
                width,
                shelfHeight * 0.1f, // Thickness of the shelf
                depth,
                1
            );

            // Draw books as a single quad above each shelf
            drawer.DrawTexturedQuad(
                bookTexture,
				Point(startPos.x, startPos.y + i * shelfHeight + shelfHeight * 0.1f, startPos.z + depth * 0.1f + depth - 0.1),
                Point(startPos.x + width, startPos.y + i * shelfHeight + shelfHeight * 0.1f, startPos.z + depth * 0.1f + depth - 0.1),
                Point(startPos.x + width, startPos.y + (i + 1) * shelfHeight - shelfHeight * 0.1f, startPos.z + depth * 0.1f + depth - 0.1),
                Point(startPos.x, startPos.y + (i + 1) * shelfHeight - shelfHeight * 0.1f, startPos.z + depth * 0.1f + depth - 0.1),
                1
            );
        }
    }