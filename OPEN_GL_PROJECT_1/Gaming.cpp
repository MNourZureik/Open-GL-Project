#include <windows.h>    // Header File For Windows
#include <gl.h>         // Header File For The OpenGL32 Library
#include <glu.h>        // Header File For The GLu32 Library
#include "Gaming.h"
#include <vector>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void Gaming::createGamingRoom(float height, float width, float depth,
                              int wall_texture, int floor_texture, int door_texture, int title_texture, int table_texture ,int surface_texture , int leg_texture , int screen , int screen_body , int sopha) {
	glPushMatrix();
	glRotated(0 , 0 , 1 , 0);
	glTranslated(-70.0f , -4.0f ,-150.0f);
    PrimitiveDrawer drawer;
    float xTranslation = 100.0f;  // Translate on the x-axis by 100
    float zTranslation = 100.0f; // Translate on the z-axis by -100

    // Draw walls
    drawer.DrawTexturedQuad(wall_texture, 
        Point(0 + xTranslation, 0, depth + zTranslation), 
        Point(width + xTranslation, 0, depth + zTranslation), 
        Point(width + xTranslation, height, depth + zTranslation), 
        Point(0 + xTranslation, height, depth + zTranslation), 
        2); // Front wall (replacing back wall)
    drawer.DrawTexturedQuad(wall_texture, 
        Point(0 + xTranslation, 0, 0 + zTranslation), 
        Point(0 + xTranslation, 0, depth + zTranslation), 
        Point(0 + xTranslation, height, depth + zTranslation), 
        Point(0 + xTranslation, height, 0 + zTranslation), 
        2); // Left wall
    drawer.DrawTexturedQuad(wall_texture, 
        Point(width + xTranslation, 0, 0 + zTranslation), 
        Point(width + xTranslation, 0, depth + zTranslation), 
        Point(width + xTranslation, height, depth + zTranslation), 
        Point(width + xTranslation, height, 0 + zTranslation), 
        2); // Right wall

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
        2);

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
        3
    );

    // Right side of the back wall
    drawer.DrawTexturedQuad(
        wall_texture,
        Point(sideWallWidth + totalHoleWidth + xTranslation, 0, 0 + zTranslation),
        Point(width + xTranslation, 0, 0 + zTranslation),
        Point(width + xTranslation, height, 0 + zTranslation),
        Point(sideWallWidth + totalHoleWidth + xTranslation, height, 0 + zTranslation),
        3
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
    float titleYStart = height - titleHeight - 18;       // Position the title near the top of the back wall

    // Draw the title quad
    drawer.DrawTexturedQuad(
        title_texture,
        Point(titleXStart + xTranslation, titleYStart, titleDepthOffset + zTranslation),                          // Bottom-left corner
        Point(titleXStart + titleWidth + xTranslation, titleYStart, titleDepthOffset + zTranslation),             // Bottom-right corner
        Point(titleXStart + titleWidth + xTranslation, titleYStart + titleHeight, titleDepthOffset + zTranslation), // Top-right corner
        Point(titleXStart + xTranslation, titleYStart + titleHeight, titleDepthOffset + zTranslation),            // Top-left corner
        1
    );
	glPushMatrix();
	glTranslated(110.0f, 0.0f, 135.0f);
	DrawBilliardTable(
		table_texture,      // Texture for table body
		surface_texture,    // Texture for the playing surface
		leg_texture,        // Texture for the legs
    Point(0.0f, 3.0f, 0.0f), // Starting position
    17.0f,             // Table width
    0.6f,              // Table height
    7.0f,              // Table depth
    0.5f,              // Leg width
    2.7f               // Leg height
);
	glPopMatrix();

	glPushMatrix();
	glTranslated(110.0f, 0.0f, 120.0f);
	DrawBilliardTable(
		table_texture,      // Texture for table body
		surface_texture,    // Texture for the playing surface
		leg_texture,        // Texture for the legs
    Point(0.0f, 3.0f, 0.0f), // Starting position
    17.0f,             // Table width
    0.6f,              // Table height
    7.0f,              // Table depth
    0.5f,              // Leg width
    2.7f               // Leg height
);
	glPopMatrix();
	

	glPushMatrix();
	glTranslated(172.0f, 0.0f, 145.0f);
	glRotated(180 , 0 , 1 , 0);
	drawer.DrawTV(screen_body , screen ,Point(1 , 2.1 , 6.5) , 0.1 , 4 , 5);
	DrawTreasury(Point(0 , 0 ,0) , Point(2 , 2 , 8) , table_texture);
	glPopMatrix();

	glPushMatrix();
	glTranslated(172.0f, 0.0f, 130.0f);
	glRotated(180 , 0 , 1 , 0);
	drawer.DrawTV(screen_body , screen ,Point(1 , 2.1 , 6.5) , 0.1 , 4 , 5);
	DrawTreasury(Point(0 , 0 ,0) , Point(2 , 2 , 8) , table_texture);
	glPopMatrix();

	glPushMatrix();
	glTranslated(172.0f, 0.0f, 115.0f);
	glRotated(180 , 0 , 1 , 0);
	drawer.DrawTV(screen_body , screen ,Point(1 , 2.1 , 6.5) , 0.1 , 4 , 5);
	DrawTreasury(Point(0 , 0 ,0) , Point(2 , 2 , 8) , table_texture);
	glPopMatrix();

	glPushMatrix();
	glTranslated(150.0f, 0.0f, 155.0f);
	glRotated(90 , 0 , 1 , 0);
	DrawSofa(table_texture, sopha, sopha, 
              Point(10.0f, 0.0f, 10.0f), // Sofa position
              10.0f, // Width
              2.5f, // Depth
              3.0f, // Height
              0.6f, // Cushion height
              0.4f  // Arm width
);
	glPopMatrix();


	glPushMatrix();
	glTranslated(150.0f, 0.0f, 140.0f);
	glRotated(90 , 0 , 1 , 0);
	DrawSofa(table_texture, sopha, sopha, 
              Point(10.0f, 0.0f, 10.0f), // Sofa position
              10.0f, // Width
              2.5f, // Depth
              3.0f, // Height
              0.6f, // Cushion height
              0.4f  // Arm width
);
	glPopMatrix();

		glPushMatrix();
	glTranslated(150.0f, 0.0f, 125.0f);
	glRotated(90 , 0 , 1 , 0);
	DrawSofa(table_texture, sopha, sopha, 
              Point(10.0f, 0.0f, 10.0f), // Sofa position
              10.0f, // Width
              2.5f, // Depth
              3.0f, // Height
              0.6f, // Cushion height
              0.4f  // Arm width
);
	glPopMatrix();

	glPopMatrix();
}

void Gaming::DrawBilliardTable(GLuint tableTexture, GLuint surfaceTexture, GLuint legTexture, 
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


void Gaming::DrawTreasury(Point position , Point size , int wood){
	PrimitiveDrawer drawer;
	drawer.DrawOpenTextureRectangularPrism(wood , position , size.x , size.y , size.z , 1 , "right");
	drawer.DrawTextureTreasuryHandle(wood , Point(position.x + size.x , position.y , position.z) , size.z / 2 , size.y / 2 , false );
	drawer.DrawTextureTreasuryHandle(wood , Point(position.x + size.x , position.y + size.y/2 , position.z) , size.z / 2 , size.y / 2 , false);
	drawer.DrawTextureTreasuryHandle(wood , Point(position.x + size.x , position.y , position.z + size.z) , size.z / 2 , size.y / 2 , true);
	drawer.DrawTextureTreasuryHandle(wood , Point(position.x + size.x , position.y + size.y/2 , position.z + size.z) , size.z / 2 , size.y / 2 , true );
	
}

void Gaming::DrawSofa(GLuint baseTexture, GLuint cushionTexture, GLuint armTexture,
                      Point sofaPos, float sofaWidth, float sofaDepth, float sofaHeight,
                      float cushionHeight, float armWidth) {
    PrimitiveDrawer drawer;

    // Dimensions for sofa parts
    float baseHeight = sofaHeight * 0.2f;       // Base is 20% of the total height
    float cushionDepth = sofaDepth * 0.8f;     // Cushions are slightly smaller than the sofa depth
    float backCushionDepth = sofaDepth * 0.2f; // Back cushion depth
    float armHeight = sofaHeight * 0.8f;       // Armrest height
    float armCurveDepth = armWidth * 0.5f;     // Curve depth for the armrest

    // Draw the base
    glBindTexture(GL_TEXTURE_2D, baseTexture); // Bind base texture
    drawer.DrawTextureRectangularPrism(
        baseTexture,
        sofaPos,
        sofaWidth,
        baseHeight,
        sofaDepth,
        1
    );

    // Draw backrest (full width of the sofa)
    Point backRestPos = Point(sofaPos.x, sofaPos.y + baseHeight, sofaPos.z);
    glBindTexture(GL_TEXTURE_2D, cushionTexture); // Bind cushion texture
    drawer.DrawTextureRectangularPrism(
        cushionTexture,
        backRestPos,
        sofaWidth,
        sofaHeight - baseHeight,
        backCushionDepth,
        1
    );

    // Draw seat cushions (split into 3 sections)
    float seatCushionWidth = sofaWidth / 3.0f; // Divide the seat cushion into 3 sections
    for (int i = 0; i < 3; ++i) {
        Point seatCushionPos = Point(
            sofaPos.x + i * seatCushionWidth,
            sofaPos.y + baseHeight,
            sofaPos.z + backCushionDepth
        );
        glBindTexture(GL_TEXTURE_2D, cushionTexture); // Bind cushion texture
        drawer.DrawTextureRectangularPrism(
            cushionTexture,
            seatCushionPos,
            seatCushionWidth - 0.1f, // Add spacing between cushions
            cushionHeight,
            cushionDepth,
            1
        );
    }

    // Draw left armrest (with slight curvature)
    Point leftArmPos = Point(sofaPos.x, sofaPos.y + baseHeight, sofaPos.z);
    glBindTexture(GL_TEXTURE_2D, armTexture); // Bind armrest texture
    drawer.DrawTextureRectangularPrism(
        armTexture,
        leftArmPos,
        armWidth,
        armHeight,
        sofaDepth - armCurveDepth,
        1
    );

    // Draw curved top for left armrest
    DrawTexturedCylinder(
        armTexture,
        Point(sofaPos.x + armWidth / 2, sofaPos.y + baseHeight + armHeight, sofaPos.z + sofaDepth / 2),
        armWidth / 2,
        armCurveDepth,
        36
    );

    // Draw right armrest (with slight curvature)
    Point rightArmPos = Point(sofaPos.x + sofaWidth - armWidth, sofaPos.y + baseHeight, sofaPos.z);
    glBindTexture(GL_TEXTURE_2D, armTexture); // Bind armrest texture
    drawer.DrawTextureRectangularPrism(
        armTexture,
        rightArmPos,
        armWidth,
        armHeight,
        sofaDepth - armCurveDepth,
        1
    );

    // Draw curved top for right armrest
    DrawTexturedCylinder(
        armTexture,
        Point(sofaPos.x + sofaWidth - armWidth / 2, sofaPos.y + baseHeight + armHeight, sofaPos.z + sofaDepth / 2),
        armWidth / 2,
        armCurveDepth,
        36
    );

    // Draw decorative buttons on seat cushions
    for (int i = 0; i < 3; ++i) {
        Point seatButtonPos = Point(
            sofaPos.x + (i + 0.5f) * seatCushionWidth,
            sofaPos.y + baseHeight + cushionHeight / 2,
            sofaPos.z + backCushionDepth + cushionDepth / 2
        );
        glBindTexture(GL_TEXTURE_2D, cushionTexture); // Bind cushion texture for buttons
        DrawTexturedCylinder(
            cushionTexture,
            seatButtonPos,
            0.1f, // Button radius
            0.05f, // Button height
            20
        );
    }

    // Ensure textures are unbound after drawing
    glBindTexture(GL_TEXTURE_2D, 0);
}


void Gaming::DrawTexturedCylinder(GLuint texture, Point baseCenter, float radius, float height, int segments) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);

    float angleStep = static_cast<float>(2.0 * M_PI / segments); // Convert to float for consistency

    // Draw the side surface of the cylinder
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= segments; ++i) {
        float angle = static_cast<float>(i) * angleStep;
        float x = radius * cosf(angle);
        float z = radius * sinf(angle);

        float u = static_cast<float>(i) / segments;

        // Bottom vertex
        glTexCoord2f(u, 0.0f);
        glVertex3f(baseCenter.x + x, baseCenter.y, baseCenter.z + z);

        // Top vertex
        glTexCoord2f(u, 1.0f);
        glVertex3f(baseCenter.x + x, baseCenter.y + height, baseCenter.z + z);
    }
    glEnd();

    // Draw the bottom circle
    glBegin(GL_TRIANGLE_FAN);
    glTexCoord2f(0.5f, 0.5f); // Center of the bottom circle
    glVertex3f(baseCenter.x, baseCenter.y, baseCenter.z);
    for (int i = 0; i <= segments; ++i) {
        float angle = static_cast<float>(i) * angleStep;
        float x = radius * cosf(angle);
        float z = radius * sinf(angle);

        glTexCoord2f(0.5f + 0.5f * cosf(angle), 0.5f + 0.5f * sinf(angle));
        glVertex3f(baseCenter.x + x, baseCenter.y, baseCenter.z + z);
    }
    glEnd();

    // Draw the top circle
    glBegin(GL_TRIANGLE_FAN);
    glTexCoord2f(0.5f, 0.5f); // Center of the top circle
    glVertex3f(baseCenter.x, baseCenter.y + height, baseCenter.z);
    for (int i = 0; i <= segments; ++i) {
        float angle = static_cast<float>(i) * angleStep;
        float x = radius * cosf(angle);
        float z = radius * sinf(angle);

        glTexCoord2f(0.5f + 0.5f * cosf(angle), 0.5f + 0.5f * sinf(angle));
        glVertex3f(baseCenter.x + x, baseCenter.y + height, baseCenter.z + z);
    }
    glEnd();

    glDisable(GL_TEXTURE_2D);
}
