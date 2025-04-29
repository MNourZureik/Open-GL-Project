#include <windows.h>		// Header File For Windows
#include <gl.h>			// Header File For The OpenGL32 Library
#include <glu.h>			// Header File For The GLu32 Library
#include "Electric.h"
#include "vector"

void Electric::createElectricRoom(float height, float width, float depth,
                                  int wall_texture, int floor_texture, int door_texture, int title_texture , int wood , int screen , int screen_body , int keys , int fifa) {
	glPushMatrix();
	glRotated(180 , 0 , 1 , 0);
	glTranslated(-300.0f , -4.0f ,0.0f);
    PrimitiveDrawer drawer;
    float xTranslation = 100.0f; // Translate on the x-axis by 100

    // Draw walls
    drawer.DrawTexturedQuad(wall_texture, 
        Point(0 + xTranslation, 0, 0), 
        Point(width + xTranslation, 0, 0), 
        Point(width + xTranslation, height, 0), 
        Point(0 + xTranslation, height, 0), 
        2); // Back wall
    drawer.DrawTexturedQuad(wall_texture, 
        Point(0 + xTranslation, 0, 0), 
        Point(0 + xTranslation, 0, depth), 
        Point(0 + xTranslation, height, depth), 
        Point(0 + xTranslation, height, 0), 
        2); // Left wall
    drawer.DrawTexturedQuad(wall_texture, 
        Point(width + xTranslation, 0, 0), 
        Point(width + xTranslation, 0, depth), 
        Point(width + xTranslation, height, depth), 
        Point(width + xTranslation, height, 0), 
        2); // Right wall

    // Draw floor
    drawer.DrawTexturedQuad(floor_texture, 
        Point(0 + xTranslation, 0, 0), 
        Point(width + xTranslation, 0, 0), 
        Point(width + xTranslation, 0, depth), 
        Point(0 + xTranslation, 0, depth), 
        8);

    // Draw ceiling
    drawer.DrawTexturedQuad(wall_texture, 
        Point(0 + xTranslation, height, 0), 
        Point(width + xTranslation, height, 0), 
        Point(width + xTranslation, height, depth), 
        Point(0 + xTranslation, height, depth), 
        2);

    // Front face with the hole and double door design
    float doorWidth = 3.0f;       // Width of each hole
    float doorHeight = 6.0f;      // Height of each hole
    float holeSpacing = 2.0f;     // Space between the two holes
    float upperHeight = height - doorHeight; // Height of the upper section
    float totalHoleWidth = (2 * doorWidth) + holeSpacing; // Combined width of both holes and spacing
    float sideWallWidth = (width - totalHoleWidth) / 2.0f; // Width of the side walls

    // Left side of the front wall
    drawer.DrawTexturedQuad(
        wall_texture,
        Point(0 + xTranslation, 0, depth),
        Point(sideWallWidth + xTranslation, 0, depth),
        Point(sideWallWidth + xTranslation, height, depth),
        Point(0 + xTranslation, height, depth),
        3
    );

    // Right side of the front wall
    drawer.DrawTexturedQuad(
        wall_texture,
        Point(sideWallWidth + totalHoleWidth + xTranslation, 0, depth),
        Point(width + xTranslation, 0, depth),
        Point(width + xTranslation, height, depth),
        Point(sideWallWidth + totalHoleWidth + xTranslation, height, depth),
        3
    );

    // Draw the upper middle section of the front face
    drawer.DrawTexturedQuad(
        wall_texture,
        Point(sideWallWidth + xTranslation, doorHeight, depth),
        Point(sideWallWidth + totalHoleWidth + xTranslation, doorHeight, depth),
        Point(sideWallWidth + totalHoleWidth + xTranslation, height, depth),
        Point(sideWallWidth + xTranslation, height, depth),
        1
    );

    // Define dimensions for the title
    float titleWidth = 6.0f;      // Width of the title
    float titleHeight = 2.0f;     // Height of the title
    float titleDepthOffset = 0.3f; // Slight offset to place it in front of the front face
    float titleXStart = (width - titleWidth) / 2.0f; // Center the title horizontally
    float titleYStart = height - titleHeight - 18;       // Position the title near the top of the front face

    // Draw the title quad
    drawer.DrawTexturedQuad(
        title_texture,
        Point(titleXStart + xTranslation, titleYStart, depth + titleDepthOffset),                          // Bottom-left corner
        Point(titleXStart + titleWidth + xTranslation, titleYStart, depth + titleDepthOffset),             // Bottom-right corner
        Point(titleXStart + titleWidth + xTranslation, titleYStart + titleHeight, depth + titleDepthOffset), // Top-right corner
        Point(titleXStart + xTranslation, titleYStart + titleHeight, depth + titleDepthOffset),            // Top-left corner
        1
    );

// Draw the first table with laptops
glPushMatrix();
glTranslated(105.0f, -1.0f, 5.0f);
DrawTable(
    wood,      // Texture for table body
    wood,      // Texture for the playing surface
    wood,      // Texture for the legs
    Point(0.0f, 3.0f, 0.0f), // Starting position
    20.0f,             // Table width
    0.6f,              // Table height
    5.0f,              // Table depth
    0.5f,              // Leg width
    2.7f               // Leg height
);

// Place 3 laptops on the first table
float laptopSpacing = 8.0f; // Spacing between laptops
for (int i = 0; i < 2; ++i) {
    float laptopX = 6.0f + i * laptopSpacing;
    glPushMatrix();
    glTranslated(laptopX, 3.6f,5.0f); // Position for the laptop
    glRotated(180, 0.0f, 1.0f, 0.0f); // Rotate laptop 180 degrees around the Y-axis
    DrawLaptop(
        screen_body, screen, keys,
        Point(0.0f, 0.0f, 0.0f), // Laptop's local origin
        6.0f,        // Laptop base width
        4.0f,        // Laptop base depth
        0.4f,        // Laptop base height
        5.0f,        // Laptop screen width
        3.0f,        // Laptop screen height
        0.2f         // Laptop screen thickness
    );
    glPopMatrix();
}
glPopMatrix();

// Draw the second table with laptops
glPushMatrix();
glTranslated(125.0f, -1.0f, 5.0f);
DrawTable(
    wood,      // Texture for table body
    wood,      // Texture for the playing surface
    wood,      // Texture for the legs
    Point(0.0f, 3.0f, 0.0f), // Starting position
    20.0f,             // Table width
    0.6f,              // Table height
    5.0f,              // Table depth
    0.5f,              // Leg width
    2.7f               // Leg height
);

// Place 3 laptops on the second table
for (int i = 0; i < 2; ++i) {
    float laptopX = 6.0f + i * laptopSpacing;
    glPushMatrix();
    glTranslated(laptopX, 3.6f, 5.0f); // Position for the laptop
    glRotated(180, 0.0f, 1.0f, 0.0f); // Rotate laptop 180 degrees around the Y-axis
    DrawLaptop(
        screen_body, screen, keys,
        Point(0.0f, 0.0f, 0.0f), // Laptop's local origin
        6.0f,        // Laptop base width
        4.0f,        // Laptop base depth
        0.4f,        // Laptop base height
        5.0f,        // Laptop screen width
        3.0f,        // Laptop screen height
        0.2f         // Laptop screen thickness
    );
    glPopMatrix();
}
glPopMatrix();

// Draw the third table with laptops
glPushMatrix();
glTranslated(145.0f, -1.0f, 5.0f);
DrawTable(
    wood,      // Texture for table body
    wood,      // Texture for the playing surface
    wood,      // Texture for the legs
    Point(0.0f, 3.0f, 0.0f), // Starting position
    20.0f,             // Table width
    0.6f,              // Table height
    5.0f,              // Table depth
    0.5f,              // Leg width
    2.7f               // Leg height
);

// Place 3 laptops on the third table
for (int i = 0; i < 3; ++i) {
    float laptopX = 6.0f + i * laptopSpacing;
    glPushMatrix();
    glTranslated(laptopX, 3.6f, 5.0f); // Position for the laptop
    glRotated(180, 0.0f, 1.0f, 0.0f); // Rotate laptop 180 degrees around the Y-axis
    DrawLaptop(
        screen_body, screen, keys,
        Point(0.0f, 0.0f, 0.0f), // Laptop's local origin
        6.0f,        // Laptop base width
        4.0f,        // Laptop base depth
        0.4f,        // Laptop base height
        5.0f,        // Laptop screen width
        3.0f,        // Laptop screen height
        0.2f         // Laptop screen thickness
    );
    glPopMatrix();
}
glPopMatrix();

glPushMatrix();
glTranslated( 99.0f ,3.0f, 35.0f);
drawer.DrawTV(screen_body , fifa ,Point(1 , 2.1 , 6.5) , 0.1 , 7 , 9);

glPopMatrix();

glPushMatrix();
glTranslated( 99.0f ,3.0f, 20.0f);
drawer.DrawTV(screen_body , fifa ,Point(1 , 2.1 , 6.5) , 0.1 , 7 , 9);

glPopMatrix();


	glPopMatrix();
}


void Electric::DrawTable(GLuint tableTexture, GLuint surfaceTexture, GLuint legTexture, 
                       Point tablePos, float tableWidth, float tableHeight, float tableDepth, 
                       float legWidth, float legHeight) {
    PrimitiveDrawer drawer;

    // Draw the main body of the table
    drawer.DrawOpenTextureRectangularPrism(
        tableTexture,
        tablePos,
        tableWidth,
        tableHeight,
        tableDepth,
        1,
        "top"
    );

    // Draw the top surface with the unique surface texture
    Point surfaceStart = Point(tablePos.x, tablePos.y + tableHeight, tablePos.z);
    drawer.DrawTexturedQuad(
        surfaceTexture,
        surfaceStart,
        Point(surfaceStart.x + tableWidth, surfaceStart.y, surfaceStart.z),
        Point(surfaceStart.x + tableWidth, surfaceStart.y, surfaceStart.z + tableDepth),
        Point(surfaceStart.x, surfaceStart.y, surfaceStart.z + tableDepth),
        1
    );

    // Calculate leg positions relative to the table
    std::vector<Point> legPositions;

    // Front-left
    legPositions.push_back(Point(tablePos.x, tablePos.y - legHeight, tablePos.z));

    // Front-right
    legPositions.push_back(Point(tablePos.x + tableWidth - legWidth, tablePos.y - legHeight, tablePos.z));

    // Back-left
    legPositions.push_back(Point(tablePos.x, tablePos.y - legHeight, tablePos.z + tableDepth - legWidth));

    // Back-right
    legPositions.push_back(Point(tablePos.x + tableWidth - legWidth, tablePos.y - legHeight, tablePos.z + tableDepth - legWidth));

    // Draw legs
    for (int i = 0; i < 4; ++i) {
        drawer.DrawTextureRectangularPrism(
            legTexture,
            legPositions[i],
            legWidth,
            legHeight,
            legWidth,
            1
        );
    }
}


void Electric::DrawLaptop(GLuint baseTexture, GLuint screenTexture, GLuint keyboardTexture, 
                          Point laptopPos, float baseWidth, float baseDepth, float baseHeight, 
                          float screenWidth, float screenHeight, float screenThickness) {
    PrimitiveDrawer drawer;

    // Adjust screenWidth and screenHeight to match the keyboard size
    screenWidth = baseWidth; // Match screen width to base width
    screenHeight = baseDepth; // Match screen height to base depth

    // Base of the laptop (keyboard area)
    drawer.DrawTextureRectangularPrism(
        baseTexture,
        laptopPos,
        baseWidth,
        baseHeight,
        baseDepth,
        1
    );

    // Keyboard area on top of the base
    Point keyboardPos = Point(laptopPos.x, laptopPos.y + baseHeight, laptopPos.z + baseDepth * 0.1f);
    drawer.DrawTexturedQuad(
        keyboardTexture,
        keyboardPos,
        Point(keyboardPos.x + baseWidth, keyboardPos.y, keyboardPos.z),
        Point(keyboardPos.x + baseWidth, keyboardPos.y, keyboardPos.z + baseDepth * 0.8f),
        Point(keyboardPos.x, keyboardPos.y, keyboardPos.z + baseDepth * 0.8f),
        1
    );

    // Screen (hinge slightly above the back of the base)
    Point screenPos = Point(laptopPos.x, laptopPos.y + baseHeight, laptopPos.z + baseDepth);
    glPushMatrix();
    glTranslated(screenPos.x + screenWidth / 2.0f, screenPos.y, screenPos.z - screenThickness / 2.0f);
    glRotated(-60.0f, 1.0f, 0.0f, 0.0f); // Tilt the screen to an open position
    drawer.DrawTextureRectangularPrism(
        screenTexture,
        Point(-screenWidth / 2.0f, 0.0f, 0.0f),
        screenWidth,
        screenThickness,
        screenHeight,
        1
    );
    glPopMatrix();
}
