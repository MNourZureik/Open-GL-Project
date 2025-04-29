
#include <windows.h>
#include "Kitchen.h"
#include <gl.h>
#include <glu.h>
#include "PrimitiveDrawer.h"
#include "texture.h"		
#include "Textures.h"


Kitchen::Kitchen() {
    // Constructor logic (if any)
}

void Kitchen::createKitchenRoom(float height, float width, float depth , int kitchen_wall , int kitchen_floor , int fridge_side_texture , int fridge_front_texture , int washing_machine_side_texture, int washing_machine_front_texture , int microwave_front_texture , int shelf_texture , int oven_front_texture , int title_texture ) {
	glPushMatrix();
	glRotated(0 , 0 , 1 , 0);
	glTranslated(120.0f , -4.0f ,-150.0f);
    PrimitiveDrawer drawer;

    // Draw walls
    drawer.DrawTexturedQuad(kitchen_wall, Point(0, 0, 0), Point(width, 0, 0), Point(width, height, 0), Point(0, height, 0) , 2); // Back wall
    drawer.DrawTexturedQuad(kitchen_wall, Point(0, 0, 0), Point(0, 0, depth), Point(0, height, depth), Point(0, height, 0), 2); // Left wall
    drawer.DrawTexturedQuad(kitchen_wall, Point(width, 0, 0), Point(width, 0, depth), Point(width, height, depth), Point(width, height, 0), 2); // Right wall

    // Draw floor
	drawer.DrawTexturedQuad(kitchen_floor, Point(0, 0, 0), Point(width, 0, 0), Point(width, 0, depth), Point(0, 0, depth), 8);

	 // Draw ceiling
    drawer.DrawTexturedQuad(kitchen_wall, Point(0, height, 0), Point(width, height, 0), Point(width, height, depth), Point(0, height, depth), 2);
	
	// Define dimensions for the front face
float doorWidth = 3.0f;       // Width of each hole
float doorHeight = 6.0f;      // Height of each hole
float holeSpacing = 2.0f;     // Space between the two holes
float upperHeight = height - doorHeight; // Height of the upper section
float totalHoleWidth = (2 * doorWidth) + holeSpacing; // Combined width of both holes and spacing
float sideWallWidth = (width - totalHoleWidth) / 2.0f; // Width of the side walls

// Left side of the front wall
drawer.DrawTexturedQuad(
    kitchen_wall,
    Point(0, 0, depth),
    Point(sideWallWidth, 0, depth),
    Point(sideWallWidth, height, depth),
    Point(0, height, depth),
    3
);

// Right side of the front wall
drawer.DrawTexturedQuad(
    kitchen_wall,
    Point(sideWallWidth + totalHoleWidth, 0, depth),
    Point(width, 0, depth),
    Point(width, height, depth),
    Point(sideWallWidth + totalHoleWidth, height, depth),
    3
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
    Point(titleXStart, titleYStart, depth + titleDepthOffset),                          // Bottom-left corner
    Point(titleXStart + titleWidth, titleYStart, depth + titleDepthOffset),             // Bottom-right corner
    Point(titleXStart + titleWidth, titleYStart + titleHeight, depth + titleDepthOffset), // Top-right corner
    Point(titleXStart, titleYStart + titleHeight, depth + titleDepthOffset),            // Top-left corner
    1
);

drawer.DrawTexturedQuad(
    kitchen_wall,
    Point(sideWallWidth, doorHeight, depth),                        // Bottom-left corner
    Point(sideWallWidth + totalHoleWidth, doorHeight, depth),       // Bottom-right corner
	Point(sideWallWidth + totalHoleWidth, height, depth), // Top-right corner
    Point(sideWallWidth, height , depth), // Top-left corner
    1
);



    // Place multiple fridges in the kitchen
    Point fridgeStart(0.2f, 0.0f, depth * 0.2f); // Position the first fridge near the corner
    float fridgeWidth = 4;
    float fridgeHeight = 9;
    float fridgeDepth = 4;

    int numFridges = 8; // Total number of fridges to draw
    for (int i = 0; i < numFridges; ++i) {
        drawFridge(fridgeStart, fridgeWidth, fridgeHeight, fridgeDepth, fridge_side_texture, fridge_front_texture);
        fridgeStart.z += fridgeDepth + 0.5f; // Move the next fridge back with a small gap
    }

	// Place multiple washing machines in front of the back wall
	Point washingMachineStart(fridgeWidth + 0.5 , 0.0f,  fridgeDepth - 0.5f); // Start near the back wall
    float washingMachineWidth = 3.5f;
    float washingMachineHeight = 6;
    float washingMachineDepth = 3.5f;

    int numWashingMachines = 8; // Total number of washing machines to draw
    for (int i = 0; i < numWashingMachines; ++i) {
        drawWashingMachine(washingMachineStart, washingMachineWidth, washingMachineHeight, washingMachineDepth, washing_machine_side_texture, washing_machine_front_texture);
        washingMachineStart.x += washingMachineWidth + 0.5f; // Move the next washing machine to the right with a small gap
    }

// Place microwaves on top of shelves
Point shelfStart(fridgeWidth + 35, 0.0f, fridgeDepth - 0.5f); // Start position for the shelves
float shelfWidth = 3.4f;
float shelfHeight = 0.5f; // Thickness of the shelf
float shelfDepth = 3.5f;

Point microwaveStart = shelfStart;
microwaveStart.y += shelfHeight + 0.1f; // Add height to place microwave 0.2 units above the shelf
float microwaveWidth = 3.0f;
float microwaveHeight = 2.0f;
float microwaveDepth = 3.5f;

int numMicrowaves = 6; // Total number of microwaves and shelves to draw
for (int i = 0; i < numMicrowaves; ++i) {
    drawShelf(shelfStart, shelfWidth, shelfHeight, shelfDepth, shelf_texture); // Draw shelf
    drawMicrowave(microwaveStart, microwaveWidth, microwaveHeight, microwaveDepth, fridge_side_texture, microwave_front_texture); // Draw microwave
    shelfStart.x += shelfWidth + 0.6f; // Move the next shelf to the right with a small gap
    microwaveStart.x += shelfWidth + 0.7f; // Move the next microwave accordingly
}


// Place ovens along the z-axis like the fridge
Point ovenStart(microwaveStart.x + 5, microwaveStart.y - shelfHeight - 0.2f, microwaveStart.z); // Start position for the first oven
float ovenWidth = 6.0f;
float ovenHeight = 4.0f;
float ovenDepth = 4.0f;

int numOvens = 6; // Total number of ovens to draw
for (int i = 0; i < numOvens; ++i) {
    drawOven(ovenStart, ovenWidth, ovenHeight, ovenDepth, fridge_side_texture, oven_front_texture); // Draw oven
    ovenStart.z += ovenDepth + 0.5f; // Move the next oven back along the z-axis with a small gap
}

glPopMatrix();
}

	
void Kitchen::drawFridge(Point start, float width, float height, float depth, int side_texture, int front_texture) {
    PrimitiveDrawer drawer;

    // Draw the sides (5 faces with the same texture)
    // Left face
    drawer.DrawTexturedQuad(
        side_texture,
        Point(start.x, start.y, start.z),
        Point(start.x, start.y + height, start.z),
        Point(start.x, start.y + height, start.z + depth),
        Point(start.x, start.y, start.z + depth),
        1
    );

    // Right face (now the main face with the unique texture)
    drawer.DrawTexturedQuad(
        front_texture,
        Point(start.x + width, start.y, start.z + depth),
		Point(start.x + width, start.y, start.z),
        Point(start.x + width, start.y + height, start.z),
        Point(start.x + width, start.y + height, start.z + depth),
		1
    );

    // Top face
    drawer.DrawTexturedQuad(
        side_texture,
        Point(start.x, start.y + height, start.z),
        Point(start.x + width, start.y + height, start.z),
        Point(start.x + width, start.y + height, start.z + depth),
        Point(start.x, start.y + height, start.z + depth),
        1
    );

    // Bottom face
    drawer.DrawTexturedQuad(
        side_texture,
        Point(start.x, start.y, start.z),
        Point(start.x + width, start.y, start.z),
        Point(start.x + width, start.y, start.z + depth),
        Point(start.x, start.y, start.z + depth),
        1
    );

    // Back face
    drawer.DrawTexturedQuad(
        side_texture,
        Point(start.x, start.y, start.z + depth),
        Point(start.x + width, start.y, start.z + depth),
        Point(start.x + width, start.y + height, start.z + depth),
        Point(start.x, start.y + height, start.z + depth),
        1
    );

    // Front face (now a regular face with the same texture as sides)
    drawer.DrawTexturedQuad(
        side_texture,
        Point(start.x, start.y, start.z),
        Point(start.x + width, start.y, start.z),
        Point(start.x + width, start.y + height, start.z),
        Point(start.x, start.y + height, start.z),
        1
    );
}


void Kitchen::drawWashingMachine(Point start, float width, float height, float depth, int side_texture, int front_texture) {
    PrimitiveDrawer drawer;

    // Draw the sides (5 faces with the same texture)
    // Left face
    drawer.DrawTexturedQuad(
        side_texture,
        Point(start.x, start.y, start.z),
        Point(start.x, start.y + height, start.z),
        Point(start.x, start.y + height, start.z + depth),
        Point(start.x, start.y, start.z + depth),
        1
    );

    // Right face
    drawer.DrawTexturedQuad(
        side_texture,
        Point(start.x + width, start.y, start.z),
        Point(start.x + width, start.y + height, start.z),
        Point(start.x + width, start.y + height, start.z + depth),
        Point(start.x + width, start.y, start.z + depth),
        1
    );

    // Top face
    drawer.DrawTexturedQuad(
        side_texture,
        Point(start.x, start.y + height, start.z),
        Point(start.x + width, start.y + height, start.z),
        Point(start.x + width, start.y + height, start.z + depth),
        Point(start.x, start.y + height, start.z + depth),
        1
    );

    // Bottom face
    drawer.DrawTexturedQuad(
        side_texture,
        Point(start.x, start.y, start.z),
        Point(start.x + width, start.y, start.z),
        Point(start.x + width, start.y, start.z + depth),
        Point(start.x, start.y, start.z + depth),
        1
    );

    // Back face (unique texture)
    drawer.DrawTexturedQuad(
        front_texture,
        Point(start.x, start.y, start.z + depth),
        Point(start.x + width, start.y, start.z + depth),
        Point(start.x + width, start.y + height, start.z + depth),
        Point(start.x, start.y + height, start.z + depth),
        1
    );

    // Front face
    drawer.DrawTexturedQuad(
        side_texture,
        Point(start.x, start.y, start.z),
        Point(start.x + width, start.y, start.z),
        Point(start.x + width, start.y + height, start.z),
        Point(start.x, start.y + height, start.z),
        1
    );
}

void Kitchen::drawMicrowave(Point start, float width, float height, float depth, int side_texture, int front_texture) {
    PrimitiveDrawer drawer;

    // Draw the sides (5 faces with the same texture)
    // Left face
    drawer.DrawTexturedQuad(
        side_texture,
        Point(start.x, start.y, start.z),
        Point(start.x, start.y + height, start.z),
        Point(start.x, start.y + height, start.z + depth),
        Point(start.x, start.y, start.z + depth),
        1
    );

    // Right face
    drawer.DrawTexturedQuad(
        side_texture,
        Point(start.x + width, start.y, start.z),
        Point(start.x + width, start.y + height, start.z),
        Point(start.x + width, start.y + height, start.z + depth),
        Point(start.x + width, start.y, start.z + depth),
        1
    );

    // Top face
    drawer.DrawTexturedQuad(
        side_texture,
        Point(start.x, start.y + height, start.z),
        Point(start.x + width, start.y + height, start.z),
        Point(start.x + width, start.y + height, start.z + depth),
        Point(start.x, start.y + height, start.z + depth),
        1
    );

    // Bottom face
    drawer.DrawTexturedQuad(
        side_texture,
        Point(start.x, start.y, start.z),
        Point(start.x + width, start.y, start.z),
        Point(start.x + width, start.y, start.z + depth),
        Point(start.x, start.y, start.z + depth),
        1
    );

    // Back face (unique texture)
    drawer.DrawTexturedQuad(
        front_texture,
        Point(start.x, start.y, start.z + depth),
        Point(start.x + width, start.y, start.z + depth),
        Point(start.x + width, start.y + height, start.z + depth),
        Point(start.x, start.y + height, start.z + depth),
        1
    );

    // Front face
    drawer.DrawTexturedQuad(
        side_texture,
        Point(start.x, start.y, start.z),
        Point(start.x + width, start.y, start.z),
        Point(start.x + width, start.y + height, start.z),
        Point(start.x, start.y + height, start.z),
        1
    );
}


void Kitchen::drawShelf(Point start, float width, float height, float depth, int texture) {
    PrimitiveDrawer drawer;

    // Draw the top face (shelf surface)
    drawer.DrawTexturedQuad(
        texture,
        Point(start.x, start.y + height, start.z),
        Point(start.x + width, start.y + height, start.z),
        Point(start.x + width, start.y + height, start.z + depth),
        Point(start.x, start.y + height, start.z + depth),
        1
    );

    // Draw the bottom face
    drawer.DrawTexturedQuad(
        texture,
        Point(start.x, start.y, start.z),
        Point(start.x + width, start.y, start.z),
        Point(start.x + width, start.y, start.z + depth),
        Point(start.x, start.y, start.z + depth),
        1
    );

    // Draw the left face
    drawer.DrawTexturedQuad(
        texture,
        Point(start.x, start.y, start.z),
        Point(start.x, start.y + height, start.z),
        Point(start.x, start.y + height, start.z + depth),
        Point(start.x, start.y, start.z + depth),
        1
    );

    // Draw the right face
    drawer.DrawTexturedQuad(
        texture,
        Point(start.x + width, start.y, start.z),
        Point(start.x + width, start.y + height, start.z),
        Point(start.x + width, start.y + height, start.z + depth),
        Point(start.x + width, start.y, start.z + depth),
        1
    );

    // Draw the back face
    drawer.DrawTexturedQuad(
        texture,
        Point(start.x, start.y, start.z + depth),
        Point(start.x + width, start.y, start.z + depth),
        Point(start.x + width, start.y + height, start.z + depth),
        Point(start.x, start.y + height, start.z + depth),
        1
    );

    // Draw the front face
    drawer.DrawTexturedQuad(
        texture,
        Point(start.x, start.y, start.z),
        Point(start.x + width, start.y, start.z),
        Point(start.x + width, start.y + height, start.z),
        Point(start.x, start.y + height, start.z),
        1
    );
}

void Kitchen::drawOven(Point start, float width, float height, float depth, int side_texture, int left_texture) {
    PrimitiveDrawer drawer;

    // Left face (unique texture)
    drawer.DrawTexturedQuad(
        left_texture,
		Point(start.x, start.y, start.z + depth),
		Point(start.x, start.y, start.z),
		Point(start.x, start.y + height, start.z),
		Point(start.x, start.y + height, start.z + depth),

        1
    );

    // Right face
    drawer.DrawTexturedQuad(
        side_texture,
        Point(start.x + width, start.y, start.z),
        Point(start.x + width, start.y + height, start.z),
        Point(start.x + width, start.y + height, start.z + depth),
        Point(start.x + width, start.y, start.z + depth),
        1
    );

    // Top face
    drawer.DrawTexturedQuad(
        side_texture,
        Point(start.x, start.y + height, start.z),
        Point(start.x + width, start.y + height, start.z),
        Point(start.x + width, start.y + height, start.z + depth),
        Point(start.x, start.y + height, start.z + depth),
        1
    );

    // Bottom face
    drawer.DrawTexturedQuad(
        side_texture,
        Point(start.x, start.y, start.z),
        Point(start.x + width, start.y, start.z),
        Point(start.x + width, start.y, start.z + depth),
        Point(start.x, start.y, start.z + depth),
        1
    );

    // Back face
    drawer.DrawTexturedQuad(
        side_texture,
        Point(start.x, start.y, start.z + depth),
        Point(start.x + width, start.y, start.z + depth),
        Point(start.x + width, start.y + height, start.z + depth),
        Point(start.x, start.y + height, start.z + depth),
        1
    );

    // Front face
    drawer.DrawTexturedQuad(
        side_texture,
        Point(start.x, start.y, start.z),
        Point(start.x + width, start.y, start.z),
        Point(start.x + width, start.y + height, start.z),
        Point(start.x, start.y + height, start.z),
        1
    );
}


