#include "Mall.h"

Mall::Mall() {
    // Constructor logic, if needed
}

void Mall::drawMallFloor(Point start, float width, float depth, int floor_texture ) {

    PrimitiveDrawer drawer;

    drawer.DrawTexturedQuad(
        floor_texture,
        Point(start.x, start.y, start.z),
        Point(start.x + width, start.y, start.z),
        Point(start.x + width, start.y, start.z + depth),
        Point(start.x, start.y, start.z + depth),
        16
    );
}

void Mall::createMallLand(float floor_width, float floor_depth, int floor_texture, int street_texture) {
	glPushMatrix();
	glRotated(-90 , 0 , 1 , 0);
	glTranslated(-150.0f , -5.0f ,-200.0f);
    Point floorStart(-20.0f, 0.0f, -20.0f);  // Adjusted starting point
    drawMallFloor(floorStart, floor_width, floor_depth, floor_texture);

    PrimitiveDrawer drawer;

    // Street parameters
    float streetWidth = 10.0f; // Width of the street surrounding the floor
    float streetHeight = 0.1f; // Height of the street (slightly above the floor level)

    // Define the outer and inner boundaries of the street
    Point outerStart = Point(floorStart.x - streetWidth, floorStart.y, floorStart.z - streetWidth);
    Point outerEnd = Point(floorStart.x + floor_width + streetWidth, floorStart.y, floorStart.z + floor_depth + streetWidth);
    Point innerStart = Point(floorStart.x, floorStart.y, floorStart.z);
    Point innerEnd = Point(floorStart.x + floor_width, floorStart.y, floorStart.z + floor_depth);

    // Draw the street as four surrounding strips
    // Front strip
    drawer.DrawTexturedQuad(
        street_texture,
        Point(innerStart.x, streetHeight, innerEnd.z),
        Point(outerEnd.x, streetHeight, innerEnd.z),
        Point(outerEnd.x, streetHeight, outerEnd.z),
        Point(innerStart.x, streetHeight, outerEnd.z),
        1
    );

    // Back strip
    drawer.DrawTexturedQuad(
        street_texture,
        Point(outerStart.x, streetHeight, outerStart.z),
        Point(innerEnd.x, streetHeight, outerStart.z),
        Point(innerEnd.x, streetHeight, innerStart.z),
        Point(outerStart.x, streetHeight, innerStart.z),
        1
    );

    // Left strip
    drawer.DrawTexturedQuad(
        street_texture,
        Point(outerStart.x, streetHeight, innerStart.z),
        Point(innerStart.x, streetHeight, innerStart.z),
        Point(innerStart.x, streetHeight, innerEnd.z),
        Point(outerStart.x, streetHeight, innerEnd.z),
        1
    );

    // Right strip
    drawer.DrawTexturedQuad(
        street_texture,
        Point(innerEnd.x, streetHeight, innerStart.z),
        Point(outerEnd.x, streetHeight, innerStart.z),
        Point(outerEnd.x, streetHeight, innerEnd.z),
        Point(innerEnd.x, streetHeight, innerEnd.z),
        1
    );
	glPopMatrix();
}


void Mall::drawMall(GLuint wall_texture, GLuint floor_texture, GLuint ceiling_texture, GLuint title_texture) {
	glPushMatrix();
	glRotated(-90 , 0 , 1 , 0);
	glTranslated(-150.0f , -5.0f ,-200.0f);
    PrimitiveDrawer drawer;

    // Adjusted starting position for all walls
    float startX = -20.0f;
    float startZ = -20.0f;

    // Dimensions for the mall rectangular prism
    float width = 200.0f;
    float height = 75.0f;
    float depth = 200.0f;

    // Draw the ceiling
    drawer.DrawTexturedQuad(
        ceiling_texture,
        Point(startX, height, startZ),
        Point(startX + width, height, startZ),
        Point(startX + width, height, startZ + depth),
        Point(startX, height, startZ + depth),
        10
    );

    // Draw the back wall
    drawer.DrawTexturedQuad(
        wall_texture,
        Point(startX, 0.0f, startZ),
        Point(startX + width, 0.0f, startZ),
        Point(startX + width, height, startZ),
        Point(startX, height, startZ),
        10
    );

    // Define dimensions for the front face
    float doorWidth = 20.0f;        // Width of the door
    float doorHeight = 40.0f;       // Height of the door
    float holeSpacing = 10.0f;      // Space between the two doors
    float upperHeight = height - doorHeight; // Height of the upper section
    float totalHoleWidth = doorWidth + holeSpacing; // Combined width of the door and spacing
    float sideWallWidth = (width - totalHoleWidth) / 2.0f; // Width of the side walls

    // Left section of the front wall
    drawer.DrawTexturedQuad(
        wall_texture,
        Point(startX, 0.0f, startZ + depth),
        Point(startX + sideWallWidth, 0.0f, startZ + depth),
        Point(startX + sideWallWidth, height, startZ + depth),
        Point(startX, height, startZ + depth),
        10
    );

    // Right section of the front wall
    drawer.DrawTexturedQuad(
        wall_texture,
        Point(startX + sideWallWidth + totalHoleWidth, 0.0f, startZ + depth),
        Point(startX + width, 0.0f, startZ + depth),
        Point(startX + width, height, startZ + depth),
        Point(startX + sideWallWidth + totalHoleWidth, height, startZ + depth),
        10
    );

    // Upper middle section of the front wall
    drawer.DrawTexturedQuad(
        wall_texture,
        Point(startX + sideWallWidth, doorHeight, startZ + depth),
        Point(startX + sideWallWidth + totalHoleWidth, doorHeight, startZ + depth),
        Point(startX + sideWallWidth + totalHoleWidth, height, startZ + depth),
        Point(startX + sideWallWidth, height, startZ + depth),
        3
    );


    // Define dimensions for the title
    float titleWidth = 30.0f;      // Width of the title
    float titleHeight = 10.0f;     // Height of the title
    float titleDepthOffset = 0.5f; // Slight offset to place it in front of the front face
    float titleXStart = (width - titleWidth) / 2.0f; // Center the title horizontally
    float titleYStart = height - titleHeight - 5.0f; // Position the title near the top of the front face

    // Draw the title quad
    drawer.DrawTexturedQuad(
        title_texture,
        Point(startX + titleXStart, titleYStart, startZ + depth + titleDepthOffset),
        Point(startX + titleXStart + titleWidth, titleYStart, startZ + depth + titleDepthOffset),
        Point(startX + titleXStart + titleWidth, titleYStart + titleHeight, startZ + depth + titleDepthOffset),
        Point(startX + titleXStart, titleYStart + titleHeight, startZ + depth + titleDepthOffset),
        1
    );

    // Draw the left wall
    drawer.DrawTexturedQuad(
        wall_texture,
        Point(startX, 0.0f, startZ),
        Point(startX, 0.0f, startZ + depth),
        Point(startX, height, startZ + depth),
        Point(startX, height, startZ),
        10
    );

    // Draw the right wall
    drawer.DrawTexturedQuad(
        wall_texture,
        Point(startX + width, 0.0f, startZ),
        Point(startX + width, 0.0f, startZ + depth),
        Point(startX + width, height, startZ + depth),
        Point(startX + width, height, startZ),
        10
    );
	glPopMatrix();
}
