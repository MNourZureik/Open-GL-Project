
#include <windows.h>		// Header File For Windows
#include <gl.h>			// Header File For The OpenGL32 Library
#include <glu.h>			// Header File For The GLu32 Library
#include <glaux.h>		// Header File For The Glaux Library
#include <cmath>
#define M_PI 3.14159265358979323846 // Define M_PI if not defined
#include "Point.h"
#include "PrimitiveDrawer.h"
#include <string>
#include <iostream>
using namespace std;

PrimitiveDrawer::PrimitiveDrawer(){}

// Draw a point at the given position.
void PrimitiveDrawer::DrawPoint(Point point) {
    glBegin(GL_POINTS);
	glVertex3f(point.x,point.y,point.z);
    glEnd();
  }

 // Draw a line between the given two positions.
void PrimitiveDrawer::DrawLine(Point start, Point end) {
    glBegin(GL_LINES);
    glVertex3f(start.x, start.y, start.z);
    glVertex3f(end.x, end.y, end.z);
    glEnd();
  }

 // Draw a triangle with the given three vertices.
void PrimitiveDrawer::DrawTriangle(Point v1, Point v2, Point v3) {
    glBegin(GL_TRIANGLES);
    glVertex3f(v1.x, v1.y, v1.z);
    glVertex3f(v2.x, v2.y, v2.z);
    glVertex3f(v3.x, v3.y, v3.z);
    glEnd();
  }

// Draw a quadrilateral with the given four vertices.
  void PrimitiveDrawer::DrawQuad(Point v1, Point v2, Point v3, Point v4) {
    glBegin(GL_QUADS);
    glVertex3f(v1.x, v1.y, v1.z);
    glVertex3f(v2.x, v2.y, v2.z);
    glVertex3f(v3.x, v3.y, v3.z);
    glVertex3f(v4.x, v4.y, v4.z);
    glEnd();
  }

  void PrimitiveDrawer::DrawTexturedQuad(GLuint texture,Point v1, Point v2, Point v3, Point v4 , int repeat=1.0f) {
    glBindTexture(GL_TEXTURE_2D, texture);
    glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(v1.x, v1.y, v1.z);
	glTexCoord2f(repeat, 0.0f); glVertex3f(v2.x, v2.y, v2.z);
    glTexCoord2f(repeat, repeat); glVertex3f(v3.x, v3.y, v3.z);
    glTexCoord2f(0.0f, repeat); glVertex3f(v4.x, v4.y, v4.z);
    glEnd();
}

void PrimitiveDrawer::DrawRectangularPrism(Point start, float width, float height, float depth) {
    // Calculate the 8 vertices of the rectangular prism
    Point v1 = start; // Bottom-front-left
    Point v2 = Point(start.x + width, start.y, start.z); // Bottom-front-right
    Point v3 = Point(start.x + width, start.y, start.z + depth); // Bottom-back-right
    Point v4 = Point(start.x, start.y, start.z + depth); // Bottom-back-left

    Point v5 = Point(start.x, start.y + height, start.z); // Top-front-left
    Point v6 = Point(start.x + width, start.y + height, start.z); // Top-front-right
    Point v7 = Point(start.x + width, start.y + height, start.z + depth); // Top-back-right
    Point v8 = Point(start.x, start.y + height, start.z + depth); // Top-back-left

    // Draw the 6 faces of the rectangular prism using quads

    // Bottom face
    DrawQuad(v1, v2, v3, v4);

    // Top face
    DrawQuad(v5, v6, v7, v8);

    // Front face
    DrawQuad(v1, v2, v6, v5);

    // Back face
    DrawQuad(v4, v3, v7, v8);

    // Left face
    DrawQuad(v1, v4, v8, v5);

    // Right face
    DrawQuad(v2, v3, v7, v6);
}


void PrimitiveDrawer::DrawTextureRectangularPrism(GLuint texture ,Point start , float width , float height , float depth , int repeat){
	 // Calculate the 8 vertices of the rectangular prism
    Point v1 = start; // Bottom-front-left
    Point v2 = Point(start.x + width, start.y, start.z); // Bottom-front-right
    Point v3 = Point(start.x + width, start.y, start.z + depth); // Bottom-back-right
    Point v4 = Point(start.x, start.y, start.z + depth); // Bottom-back-left

    Point v5 = Point(start.x, start.y + height, start.z); // Top-front-left
    Point v6 = Point(start.x + width, start.y + height, start.z); // Top-front-right
    Point v7 = Point(start.x + width, start.y + height, start.z + depth); // Top-back-right
    Point v8 = Point(start.x, start.y + height, start.z + depth); // Top-back-left

    // Draw the 6 faces of the rectangular prism using quads

    // Bottom face
	DrawTexturedQuad( texture, v1, v2, v3, v4 , repeat);

    // Top face
    DrawTexturedQuad(texture,v5, v6, v7, v8, repeat);

    // Front face
    DrawTexturedQuad(texture,v1, v2, v6, v5, repeat);

    // Back face
    DrawTexturedQuad(texture,v4, v3, v7, v8, repeat);

    // Left face
    DrawTexturedQuad(texture,v1, v4, v8, v5, repeat);

    // Right face
    DrawTexturedQuad(texture,v2, v3, v7, v6, repeat);
}

void PrimitiveDrawer::DrawOpenRectangularPrism(Point start, float width, float height, float depth, string destination) {
    bool up = false, right = false, down = false, left = false, forward = false, backward = false;

    // Set booleans based on the destination string
    if (destination == "up") {
        up = true;
    } else if (destination == "right") {
        right = true;
    } else if (destination == "down") {
        down = true;
    } else if (destination == "left") {
        left = true;
    } else if (destination == "forward") {
        forward = true;
    } else if (destination == "backward") {
        backward = true;
    }

    // Calculate the 8 vertices of the rectangular prism
    Point v1 = start; // Bottom-front-left
    Point v2 = Point(start.x + width, start.y, start.z); // Bottom-front-right
    Point v3 = Point(start.x + width, start.y, start.z + depth); // Bottom-back-right
    Point v4 = Point(start.x, start.y, start.z + depth); // Bottom-back-left

    Point v5 = Point(start.x, start.y + height, start.z); // Top-front-left
    Point v6 = Point(start.x + width, start.y + height, start.z); // Top-front-right
    Point v7 = Point(start.x + width, start.y + height, start.z + depth); // Top-back-right
    Point v8 = Point(start.x, start.y + height, start.z + depth); // Top-back-left

    // Draw faces conditionally based on the booleans
    if (!down) {
        // Bottom face
        DrawQuad(v1, v2, v3, v4);
    }

    if (!up) {
        // Top face
        DrawQuad(v5, v6, v7, v8);
    }

    if (!forward) {
        // Front face
        DrawQuad(v1, v2, v6, v5);
    }

    if (!backward) {
        // Back face
        DrawQuad(v4, v3, v7, v8);
    }

    if (!left) {
        // Left face
        DrawQuad(v1, v4, v8, v5);
    }

    if (!right) {
        // Right face
        DrawQuad(v2, v3, v7, v6);
    }
}


void PrimitiveDrawer::DrawOpenTextureRectangularPrism(GLuint texture, Point start, float width, float height, float depth, int repeat, std::string destination) {
    bool up = false, right = false, down = false, left = false, forward = false, backward = false;

    // Set booleans based on the destination string
    if (destination == "up") {
        up = true;
    } else if (destination == "right") {
        right = true;
    } else if (destination == "down") {
        down = true;
    } else if (destination == "left") {
        left = true;
    } else if (destination == "forward") {
        forward = true;
    } else if (destination == "backward") {
        backward = true;
    }

    // Calculate the 8 vertices of the rectangular prism
    Point v1 = start; // Bottom-front-left
    Point v2 = Point(start.x + width, start.y, start.z); // Bottom-front-right
    Point v3 = Point(start.x + width, start.y, start.z + depth); // Bottom-back-right
    Point v4 = Point(start.x, start.y, start.z + depth); // Bottom-back-left

    Point v5 = Point(start.x, start.y + height, start.z); // Top-front-left
    Point v6 = Point(start.x + width, start.y + height, start.z); // Top-front-right
    Point v7 = Point(start.x + width, start.y + height, start.z + depth); // Top-back-right
    Point v8 = Point(start.x, start.y + height, start.z + depth); // Top-back-left

    // Draw faces conditionally based on the booleans
    if (!down) {
        // Bottom face
        DrawTexturedQuad(texture, v1, v2, v3, v4, repeat);
    }

    if (!up) {
        // Top face
        DrawTexturedQuad(texture, v5, v6, v7, v8, repeat);
    }

    if (!forward) {
        // Front face
        DrawTexturedQuad(texture, v1, v2, v6, v5, repeat);
    }

    if (!backward) {
        // Back face
        DrawTexturedQuad(texture, v4, v3, v7, v8, repeat);
    }

    if (!left) {
        // Left face
        DrawTexturedQuad(texture, v1, v4, v8, v5, repeat);
    }

    if (!right) {
        // Right face
        DrawTexturedQuad(texture, v2, v3, v7, v6, repeat);
    }
}

void PrimitiveDrawer::DrawTextureTreasuryHandle(GLuint texture, Point start, float width, float height, bool isPos) {
    // Define handle shape as a textured rectangular strip
	glPushMatrix();
    // Calculate points for the handle (a thin rectangle in 3D space)
    Point v4 = start; // Bottom-left
    Point v3 = Point(start.x, start.y, isPos ? start.z - width:start.z + width); // Bottom-right
    Point v2 = Point(start.x , start.y + height, isPos ? start.z - width:start.z + width); // Top-right
    Point v1 = Point(start.x, start.y + height, start.z); // Top-left

    // Draw the textured handle as a quad
    DrawTexturedQuad(texture, v1, v2, v3, v4, 1);

    // Draw a circle in the middle of the quad manually
    float centerX = (v1.x + v3.x) / 2.0f;
    float centerY = (v1.y + v3.y) / 2.0f;
    float centerZ = (v1.z + v3.z) / 2.0f;
    float radius = min(width, height) / 10.0f;
    int segments = 32;

    glBegin(GL_TRIANGLE_FAN);
	glColor3f(0 , 0 , 255);	
    glVertex3f(centerX, centerY, centerZ); // Center of the circle

    for (int i = 0; i <= segments; i++) {
        float angle = 2.0f * M_PI * i / segments;

        float y = centerY + radius * cos(angle);
        float z = centerZ + radius * sin(angle);
        glVertex3f(centerX + 0.01, y, z);
    }

    glEnd();
	glColor3f(255 , 255 , 255);
	glPopMatrix();
}


void PrimitiveDrawer::DrawCircle(Point center, float radius, int segments) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(center.x, center.y, center.z); // Center of the circle

    for (int i = 0; i <= segments; i++) {
        float angle = 2.0f * M_PI * i / segments; // Calculate angle
        float x = center.x;
        float y = center.y + radius * cos(angle);
        float z = center.z + radius * sin(angle);
        glVertex3f(x, y, z);
    }

    glEnd();
}

void PrimitiveDrawer::DrawCircleTexture(GLuint texture, Point center, float radius, int segments) {
    glBindTexture(GL_TEXTURE_2D, texture);
    glBegin(GL_TRIANGLE_FAN);

    glTexCoord2f(0.5f, 0.5f); // Texture center
    glVertex3f(center.x, center.y, center.z); // Circle center

    for (int i = 0; i <= segments; i++) {
        float angle = 2.0f * M_PI * i / segments; // Calculate angle
        float y = center.y + radius * cos(angle);
        float z = center.z + radius * sin(angle);

        float u = 0.5f + 0.5f * cos(angle); // Texture coordinate u
        float v = 0.5f + 0.5f * sin(angle); // Texture coordinate v

        glTexCoord2f(u, v);
        glVertex3f(center.x, y, z);
    }

    glEnd();
}

    // Draw a picture frame with texture inside
    void PrimitiveDrawer::DrawPictureFrame(GLuint frameTexture, GLuint pictureTexture, Point startPos, float width, float height, float frameThickness) {
        // Outer frame (front face)
        float outerLeft = startPos.x;
        float outerRight = startPos.x + width;
        float outerBottom = startPos.y;
        float outerTop = startPos.y + height;

        // Inner frame (hole for the picture)
        float innerLeft = outerLeft + frameThickness;
        float innerRight = outerRight - frameThickness;
        float innerBottom = outerBottom + frameThickness;
        float innerTop = outerTop - frameThickness;

        // Draw the top frame part
        DrawTexturedQuad(frameTexture,
                         Point(outerLeft, outerTop, startPos.z),
                         Point(outerRight, outerTop, startPos.z),
                         Point(outerRight, innerTop, startPos.z),
                         Point(outerLeft, innerTop, startPos.z));

        // Draw the bottom frame part
        DrawTexturedQuad(frameTexture,
                         Point(outerLeft, innerBottom, startPos.z),
                         Point(outerRight, innerBottom, startPos.z),
                         Point(outerRight, outerBottom, startPos.z),
                         Point(outerLeft, outerBottom, startPos.z));

        // Draw the left frame part
        DrawTexturedQuad(frameTexture,
                         Point(outerLeft, innerTop, startPos.z),
                         Point(innerLeft, innerTop, startPos.z),
                         Point(innerLeft, innerBottom, startPos.z),
                         Point(outerLeft, innerBottom, startPos.z));

        // Draw the right frame part
        DrawTexturedQuad(frameTexture,
                         Point(innerRight, innerTop, startPos.z),
                         Point(outerRight, innerTop, startPos.z),
                         Point(outerRight, innerBottom, startPos.z),
                         Point(innerRight, innerBottom, startPos.z));

        // Draw the picture inside the frame
        DrawTexturedQuad(pictureTexture,
						 Point(innerRight, innerBottom, startPos.z + 0.01f),
                         Point(innerLeft, innerBottom, startPos.z + 0.01f),
                         Point(innerLeft, innerTop, startPos.z + 0.01f),
                         Point(innerRight, innerTop, startPos.z + 0.01f)
                      );
    }

	// Draw a window with curtains
    void PrimitiveDrawer::DrawWindowWithCurtains(GLuint windowTexture, GLuint curtainTexture, Point startPos, float width, float height, float frameThickness) {
        // Outer frame of the window
        float outerLeft = startPos.x;
        float outerRight = startPos.x + width;
        float outerBottom = startPos.y;
        float outerTop = startPos.y + height;

        // Inner frame for the windowpane
        float innerLeft = outerLeft + frameThickness;
        float innerRight = outerRight - frameThickness;
        float innerBottom = outerBottom + frameThickness;
        float innerTop = outerTop - frameThickness;

        // Draw the window frame
        DrawTexturedQuad(windowTexture,
                         Point(outerLeft, outerTop, startPos.z),
                         Point(outerRight, outerTop, startPos.z),
                         Point(outerRight, outerBottom, startPos.z),
                         Point(outerLeft, outerBottom, startPos.z));


        // Draw the left curtain
        DrawTexturedQuad(curtainTexture,
                         Point(outerLeft, outerTop, startPos.z + 0.02f),
                         Point(innerLeft, outerTop, startPos.z + 0.02f),
                         Point(innerLeft, outerBottom, startPos.z + 0.02f),
                         Point(outerLeft, outerBottom, startPos.z + 0.02f));

        // Draw the right curtain
        DrawTexturedQuad(curtainTexture,
                         Point(innerRight, outerTop, startPos.z + 0.02f),
                         Point(outerRight, outerTop, startPos.z + 0.02f),
                         Point(outerRight, outerBottom, startPos.z + 0.02f),
                         Point(innerRight, outerBottom, startPos.z + 0.02f));
    }

	void PrimitiveDrawer::DrawTV(GLuint screenTexture, GLuint bodyTexture, Point startPos, float width, float height, float depth) {
    // TV front screen (rotated 180 degrees)
    DrawTexturedQuad(screenTexture,
                     Point(startPos.x, startPos.y + height, startPos.z),
                     Point(startPos.x + width, startPos.y + height, startPos.z),
                     Point(startPos.x + width, startPos.y, startPos.z),
                     Point(startPos.x, startPos.y, startPos.z),
                     true); // Pass a flag or set texture coordinates for rotation

    // TV back panel
    DrawTexturedQuad(bodyTexture,
                     Point(startPos.x, startPos.y + height, startPos.z - depth),
                     Point(startPos.x + width, startPos.y + height, startPos.z - depth),
                     Point(startPos.x + width, startPos.y, startPos.z - depth),
                     Point(startPos.x, startPos.y, startPos.z - depth));

    // TV left side
    DrawTexturedQuad(bodyTexture,
                     Point(startPos.x, startPos.y + height, startPos.z - depth),
                     Point(startPos.x, startPos.y + height, startPos.z),
                     Point(startPos.x, startPos.y, startPos.z),
                     Point(startPos.x, startPos.y, startPos.z - depth));

    // TV right side
    DrawTexturedQuad(bodyTexture,
                    Point(startPos.x + width, startPos.y, startPos.z),
                     Point(startPos.x + width, startPos.y, startPos.z - depth),
					  
					Point(startPos.x + width, startPos.y + height, startPos.z - depth),
                     Point(startPos.x + width, startPos.y + height, startPos.z)
                     );

    // TV top
    DrawTexturedQuad(bodyTexture,
                     Point(startPos.x, startPos.y + height, startPos.z - depth),
                     Point(startPos.x + width, startPos.y + height, startPos.z - depth),
                     Point(startPos.x + width, startPos.y + height, startPos.z),
                     Point(startPos.x, startPos.y + height, startPos.z));

    // TV bottom
    DrawTexturedQuad(bodyTexture,
                     Point(startPos.x, startPos.y, startPos.z - depth),
                     Point(startPos.x + width, startPos.y, startPos.z - depth),
                     Point(startPos.x + width, startPos.y, startPos.z),
                     Point(startPos.x, startPos.y, startPos.z));
}


	 // Draw a Pot Only
    void PrimitiveDrawer::DrawPot(GLuint potTexture, Point startPos, float potRadius, float potHeight) {
        int segments = 32; // Number of segments to approximate a circle

        // Draw the pot (cylinder)
        glBindTexture(GL_TEXTURE_2D, potTexture);
        glBegin(GL_QUAD_STRIP);
        for (int i = 0; i <= segments; ++i) {
            float angle = 2.0f * 3.1415926f * i / segments;
            float x = potRadius * cos(angle);
            float z = potRadius * sin(angle);

            glTexCoord2f((float)i / segments, 0.0f); glVertex3f(startPos.x + x, startPos.y, startPos.z + z);
            glTexCoord2f((float)i / segments, 1.0f); glVertex3f(startPos.x + x, startPos.y + potHeight, startPos.z + z);
        }
        glEnd();

        // Draw the bottom of the pot
        glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(0.5f, 0.5f); glVertex3f(startPos.x, startPos.y, startPos.z);
        for (int i = 0; i <= segments; ++i) {
            float angle = 2.0f * 3.1415926f * i / segments;
            float x = potRadius * cos(angle);
            float z = potRadius * sin(angle);
            glTexCoord2f(0.5f + 0.5f * cos(angle), 0.5f + 0.5f * sin(angle)); glVertex3f(startPos.x + x, startPos.y, startPos.z + z);
        }
        glEnd();
    }


	    // Draw a Door
    void PrimitiveDrawer::DrawDoor(GLuint doorTexture, Point startPos, float width, float height, float depth) {
        // Front face of the door
        DrawTexturedQuad(doorTexture,
                         Point(startPos.x, startPos.y + height, startPos.z),
                         Point(startPos.x + width, startPos.y + height, startPos.z),
                         Point(startPos.x + width, startPos.y, startPos.z),
                         Point(startPos.x, startPos.y, startPos.z));

        // Back face of the door
        DrawTexturedQuad(doorTexture,
                         Point(startPos.x, startPos.y + height, startPos.z - depth),
                         Point(startPos.x + width, startPos.y + height, startPos.z - depth),
                         Point(startPos.x + width, startPos.y, startPos.z - depth),
                         Point(startPos.x, startPos.y, startPos.z - depth));

        // Left side of the door
        DrawTexturedQuad(doorTexture,
                         Point(startPos.x, startPos.y + height, startPos.z - depth),
                         Point(startPos.x, startPos.y + height, startPos.z),
                         Point(startPos.x, startPos.y, startPos.z),
                         Point(startPos.x, startPos.y, startPos.z - depth));

        // Right side of the door
        DrawTexturedQuad(doorTexture,
                         Point(startPos.x + width, startPos.y + height, startPos.z - depth),
                         Point(startPos.x + width, startPos.y + height, startPos.z),
                         Point(startPos.x + width, startPos.y, startPos.z),
                         Point(startPos.x + width, startPos.y, startPos.z - depth));

        // Top of the door
        DrawTexturedQuad(doorTexture,
                         Point(startPos.x, startPos.y + height, startPos.z - depth),
                         Point(startPos.x + width, startPos.y + height, startPos.z - depth),
                         Point(startPos.x + width, startPos.y + height, startPos.z),
                         Point(startPos.x, startPos.y + height, startPos.z));

        // Bottom of the door
        DrawTexturedQuad(doorTexture,
                         Point(startPos.x, startPos.y, startPos.z - depth),
                         Point(startPos.x + width, startPos.y, startPos.z - depth),
                         Point(startPos.x + width, startPos.y, startPos.z),
                         Point(startPos.x, startPos.y, startPos.z));
    }

	  // Draw a Chandelier
    void PrimitiveDrawer::DrawChandelier(GLuint baseTexture, GLuint chainTexture, GLuint bulbTexture, Point startPos, float baseRadius, float baseHeight, float hangingLength, int numChains) {
        int segments = 64; // Higher resolution for smoother circles

        // Draw the circular base of the chandelier
        glBindTexture(GL_TEXTURE_2D, baseTexture);
        glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(0.5f, 0.5f); glVertex3f(startPos.x, startPos.y + baseHeight, startPos.z);
        for (int i = 0; i <= segments; ++i) {
            float angle = 2.0f * 3.1415926f * i / segments;
            float x = baseRadius * cos(angle);
            float z = baseRadius * sin(angle);
            glTexCoord2f(0.5f + 0.5f * cos(angle), 0.5f + 0.5f * sin(angle));
            glVertex3f(startPos.x + x, startPos.y + baseHeight, startPos.z + z);
        }
        glEnd();

        // Draw supporting chains and light bulbs
        for (int i = 0; i < numChains; ++i) {
            float angle = 2.0f * 3.1415926f * i / numChains;
            float x = baseRadius * cos(angle);
            float z = baseRadius * sin(angle);

            // Draw chains
            glBindTexture(GL_TEXTURE_2D, chainTexture);
            glBegin(GL_LINES);
            glVertex3f(startPos.x + x, startPos.y + baseHeight, startPos.z + z);
            glVertex3f(startPos.x + x, startPos.y + baseHeight - hangingLength, startPos.z + z);
            glEnd();

            // Draw light bulbs
            float bulbRadius = 0.2f;
            glBindTexture(GL_TEXTURE_2D, bulbTexture);
            int bulbSegments = 16;
            glBegin(GL_TRIANGLE_STRIP);
            for (int j = 0; j <= bulbSegments; ++j) {
                for (int k = 0; k <= bulbSegments; ++k) {
                    float theta = 2.0f * 3.1415926f * j / bulbSegments;
                    float phi = 3.1415926f * k / bulbSegments;

                    float x1 = bulbRadius * sin(phi) * cos(theta);
                    float y1 = bulbRadius * cos(phi);
                    float z1 = bulbRadius * sin(phi) * sin(theta);

                    glTexCoord2f((float)j / bulbSegments, (float)k / bulbSegments);
                    glVertex3f(startPos.x + x + x1, startPos.y + baseHeight - hangingLength + y1, startPos.z + z + z1);
                }
            }
            glEnd();

            // Add light source at the bulb's position
            GLfloat lightPos[] = {startPos.x + x, startPos.y + baseHeight - hangingLength, startPos.z + z, 1.0f};
            GLfloat lightDiffuse[] = {1.0f, 1.0f, 0.8f, 1.0f}; // Warm light
            GLfloat lightSpecular[] = {1.0f, 1.0f, 0.8f, 1.0f};
            GLfloat lightAmbient[] = {0.2f, 0.2f, 0.1f, 1.0f};

            glEnable(GL_LIGHTING);
            glEnable(GL_LIGHT0 + i); // Use different light sources per chain
            glLightfv(GL_LIGHT0 + i, GL_POSITION, lightPos);
            glLightfv(GL_LIGHT0 + i, GL_DIFFUSE, lightDiffuse);
            glLightfv(GL_LIGHT0 + i, GL_SPECULAR, lightSpecular);
            glLightfv(GL_LIGHT0 + i, GL_AMBIENT, lightAmbient);
        }

        // Draw extra decorative rings
        int numRings = 3;
        for (int r = 1; r <= numRings; ++r) {
            float ringRadius = baseRadius * (1.0f + 0.2f * r);
            float ringHeight = baseHeight - (0.2f * r);
            glBindTexture(GL_TEXTURE_2D, baseTexture);
            glBegin(GL_LINE_LOOP);
            for (int i = 0; i <= segments; ++i) {
                float angle = 2.0f * 3.1415926f * i / segments;
                float x = ringRadius * cos(angle);
                float z = ringRadius * sin(angle);
                glTexCoord2f(0.5f + 0.5f * cos(angle), 0.5f + 0.5f * sin(angle));
                glVertex3f(startPos.x + x, startPos.y + ringHeight, startPos.z + z);
            }
            glEnd();
        }

        // Add global ambient lighting effect for the chandelier
        GLfloat globalAmbient[] = {0.3f, 0.3f, 0.3f, 1.0f};
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);
    }

	//Draw a simplified Library with 3D shelves and an outer box
    void PrimitiveDrawer::DrawLibrary(GLuint shelfTexture, GLuint bookTexture, GLuint outerBoxTexture, Point startPos, float width, float height, float depth, int numShelves) {
        float shelfHeight = height / numShelves;

        // Draw the outer box as a rectangular prism around the shelves and books
        DrawOpenTextureRectangularPrism(
            outerBoxTexture,
            Point(startPos.x - 0.1f, startPos.y - 0.1f, startPos.z - 0.1f), // Slightly larger than the shelves
            width + 0.2f, // Add some padding to the width
            height + 0.2f, // Add some padding to the height
            depth + 0.2f, // Add some padding to the depth
            1,
        "backward");

        for (int i = 0; i < numShelves; ++i) {
            // Draw shelf as a rectangular prism
            DrawTextureRectangularPrism(
                shelfTexture,
                Point(startPos.x, startPos.y + i * shelfHeight, startPos.z),
                width,
                shelfHeight * 0.1f, // Thickness of the shelf
                depth,
                1
            );

            // Draw books as a single quad above each shelf
            DrawTexturedQuad(
                bookTexture,
				Point(startPos.x, startPos.y + i * shelfHeight + shelfHeight * 0.1f, startPos.z + depth * 0.1f + depth - 0.1),
                Point(startPos.x + width, startPos.y + i * shelfHeight + shelfHeight * 0.1f, startPos.z + depth * 0.1f + depth - 0.1),
                Point(startPos.x + width, startPos.y + (i + 1) * shelfHeight - shelfHeight * 0.1f, startPos.z + depth * 0.1f + depth - 0.1),
                Point(startPos.x, startPos.y + (i + 1) * shelfHeight - shelfHeight * 0.1f, startPos.z + depth * 0.1f + depth - 0.1),
                1
            );
        }
    }