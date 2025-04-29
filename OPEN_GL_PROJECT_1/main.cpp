
#include <windows.h>		// Header File For Windows
#include <gl.h>			// Header File For The OpenGL32 Library
#include <glu.h>			// Header File For The GLu32 Library
#include <glaux.h>		// Header File For The Glaux Library
#include <cmath>
#include "texture.h"
#include "camera.h"
#include <fstream>
#include "PrimitiveDrawer.h"
#include <string.h>
#include "Model_3DS.h"
#include "Kitchen.h"
#include "Electric.h"
#include "Gaming.h"
#include "Library.h"
#include "Mall.h"
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif



HDC			hDC = NULL;		// Private GDI Device Context
HGLRC		hRC = NULL;		// Permanent Rendering Cntext
HWND		hWnd = NULL;		// Holds Our Window Handle
HINSTANCE	hInstance;		// Holds The Instance Of The Application

bool	keys[256];			// Array Used For The Keyboard Routine
bool	active = TRUE;		// Window Active Flag Set To TRUE By Default
bool	fullscreen = FALSE;	// Fullscreen Flag Set To Fullscreen Mode By Default

LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration For WndProc

GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		// Resize And Initialize The GL Window
{
	if (height == 0)										// Prevent A Divide By Zero By
	{
		height = 1;										// Making Height Equal One
	}

	glViewport(0, 0, width, height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 10000.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}

PrimitiveDrawer drawer;
Kitchen kitchen;
Electric ele;
Gaming game;
Library lib;
Mall mall;

// skybox
int SKYFRONT, SKYBACK, SKYLEFT, SKYRIGHT, SKYUP, SKYDOWN;

void Draw_Skybox(float x, float y, float z, float width, float height, float length)
{
	// Center the Skybox around the given x,y,z position
	x = x - width / 2;
	y = y - height / 2;
	z = z - length / 2;
	glEnable(GL_TEXTURE_2D);

	// Draw Front side
	glBindTexture(GL_TEXTURE_2D, SKYFRONT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z + length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z + length);
	glEnd();

	// Draw Back side
	glBindTexture(GL_TEXTURE_2D, SKYBACK);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);
	glEnd();

	// Draw Left side
	glBindTexture(GL_TEXTURE_2D, SKYLEFT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z + length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z + length);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z);
	glEnd();

	// Draw Right side
	glBindTexture(GL_TEXTURE_2D, SKYRIGHT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y, z + length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z);
	glEnd();

	// Draw Up side
	glBindTexture(GL_TEXTURE_2D, SKYUP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y + height, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y + height, z + length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z);
	glEnd();

	// Draw Down side
	glBindTexture(GL_TEXTURE_2D, SKYDOWN);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z + length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y, z);
	glEnd();

	glColor3f(1, 1, 1);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
} 
GLuint wallTexture , floorTexture , carpet , wood , frame , picture1 , picture2 , picture3 , window , curtains , screen , screen_body,
	leather,wood2 , door , chandelier , books ,syria_flag , kitchen_wall, kitchen_floor,fridge_front , fridge_side ,title_kitchen,washing_machine ,
	white ,microwave ,oven_front , ele_wall ,ele_floor , ele_title , game_wall ,game_floor ,game_title  , lib_wall ,lib_floor ,lib_title ,mall_wall 
	, bill_surface , sopha ,street,keyboard , fifa; 



void DrawRoom1(float height, float width, float depth) {
    PrimitiveDrawer drawer;
    // Floor
    drawer.DrawTexturedQuad(wood2,
							Point(width, 0, depth),
                            Point(0, 0, depth),
                            Point(0, 0, 0),
                            Point(width, 0, 0),
                            1);
	// carpet
	drawer.DrawTexturedQuad(carpet,
                            Point(2, 0.1, 3),
                            Point(width * 0.8, 0.1, 3),
                            Point(width * 0.8, 0.1, depth * 0.8),
                            Point(2, 0.1, depth * 0.8) , 1);
    // Ceiling
    drawer.DrawTexturedQuad(wallTexture,
                            Point(0, height, 0),
                            Point(width, height, 0),
                            Point(width, height, depth),
                            Point(0, height, depth) , 1);
    // Back wall
    drawer.DrawTexturedQuad(wallTexture,
                            Point(0, 0, 0),
                            Point(width, 0, 0),
                            Point(width, height, 0),
                            Point(0, height, 0) , 1);
    // Left wall
	drawer.DrawTexturedQuad(wallTexture,
                            Point(0, 0, 0),
                            Point(0, 0, depth),
                            Point(0, height, depth),
                            Point(0, height, 0), 1);
    // Right wall
    drawer.DrawTexturedQuad(wallTexture,
                            Point(width, 0, 0),
                            Point(width, 0, depth),
                            Point(width, height, depth),
                            Point(width, height, 0) , 1);

	
	drawer.DrawPictureFrame(frame , picture1 , Point(1.5 , 2 , 0.1) , 0.5 , 0.9 , 0.05);
	drawer.DrawPictureFrame(frame , picture2 , Point(2.3 , 2.8 , 0.1) , 0.5 , 0.9 , 0.05);
	glPushMatrix();
	glRotated(90 , 0 , 1 , 0);
	drawer.DrawPictureFrame(frame , picture3 , Point(-3.8 , 2.8 , 0) , 0.9 , 0.5 , 0.05);
	glPopMatrix();
	drawer.DrawWindowWithCurtains(window , curtains , Point(3.2 , 1.8 , 0.1) , 2 , 2 , 0.8);
	drawer.DrawPictureFrame(frame , picture1 , Point(5.4 , 2.8 , 0.1) , 0.5 , 0.9 , 0.05);
	
	
	drawer.DrawDoor(door , Point(6.5 , 0 , 0) , 2.3 , 4 , 0.01);
	glPushMatrix();
	glRotated(-90 , 0 , 1 , 0);
	drawer.DrawDoor(door , Point(7 , 0 , -10) , 2.3 , 4 , 0.01);
	glPopMatrix();
	drawer.DrawChandelier(chandelier , chandelier , chandelier, Point(5 , 3 , 5) , 1 , 2 , 0.5 , 10);
	glPushMatrix();
	glRotated(-90 , 0 , 1 , 0);
	drawer.DrawLibrary(wood , books , wood, Point(1 , 0 , -10) , 2.3 , 4.5 , 1 , 5);
	glPopMatrix();

}


Model_3DS *tank;
Model_3DS *tree;
Model_3DS *chair;
Model_3DS *table;
GLTexture BARK,Leaf,chair_tex,table_tex;

int InitGL(GLvoid)										// All Setup For OpenGL Goes Here
{
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

	// Load all my textures here: 
	glEnable(GL_TEXTURE_2D);
	// skybox
	SKYFRONT = LoadTexture("images/front.bmp", 255);
	SKYBACK = LoadTexture("images/back.bmp", 255);
	SKYLEFT = LoadTexture("images/left.bmp", 255);
	SKYRIGHT = LoadTexture("images/right.bmp", 255);
	SKYUP = LoadTexture("images/up.bmp", 255);
	SKYDOWN = LoadTexture("images/down.bmp", 255);
	kitchen_wall = LoadTexture("images/kitchen_wall.bmp", 255);
	kitchen_floor = LoadTexture("images/kitchen_floor.bmp", 255);
	fridge_front = LoadTexture("images/fridge_front.bmp" , 255);
	fridge_side = LoadTexture("images/fridge_side.bmp" , 255);
	washing_machine = LoadTexture("images/washing_machine.bmp" , 255);
	white = LoadTexture("images/white.bmp" , 255);
	microwave = LoadTexture("images/microwave_front.bmp" , 255);
	wood = LoadTexture("images/wood.bmp" , 255);
	oven_front = LoadTexture("images/oven_front.bmp" , 255);
	title_kitchen = LoadTexture("images/title_kitchen.bmp" , 255);
	ele_wall = LoadTexture("images/ele_wall.bmp" , 255);
	ele_floor = LoadTexture("images/ele_floor.bmp" , 255);
	ele_title = LoadTexture("images/ele_title.bmp" , 255);
	game_wall = LoadTexture("images/game_wall.bmp" , 255);
	game_floor = LoadTexture("images/game_floor.bmp" , 255);
	game_title = LoadTexture("images/game_title.bmp" , 255);
	lib_wall = LoadTexture("images/lib_wall.bmp" , 255);
	lib_floor = LoadTexture("images/lib_floor.bmp" , 255);
	lib_title = LoadTexture("images/lib_title.bmp" , 255);
	mall_wall = LoadTexture("images/mall_wall.bmp" , 255);
	books = LoadTexture("images/books.bmp" , 255);
	wood = LoadTexture("images/wood.bmp" , 255);
	wood2 = LoadTexture("images/wood2.bmp" , 255);
	bill_surface = LoadTexture("images/bill_surface.bmp" , 255);
	screen = LoadTexture("images/screen.bmp" , 255);
	screen_body = LoadTexture("images/tv_body.bmp" , 255);
	sopha =  LoadTexture("images/sopha.bmp" , 255);
	street = LoadTexture("images/street.bmp" , 255);
	keyboard = LoadTexture("images/keyboard.bmp" , 255);
	fifa = LoadTexture("images/fifa.bmp" , 255);
	glDisable(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	tree = new Model_3DS();
	tree->Load("images/Tree1.3DS");
	Leaf.LoadBMP("images/bat.bmp");
	BARK.LoadBMP("images/bark_loo.bmp");
	chair_tex.LoadBMP("images/leather.bmp");

	chair = new Model_3DS();
	chair->Load("images/chair.3DS");

	chair->Materials[0].tex=BARK;
	chair->Materials[1].tex=chair_tex;
	chair->Materials[2].tex=chair_tex;
	chair->Materials[3].tex=chair_tex;
	chair->Materials[4].tex=BARK;
	chair->Materials[5].tex=chair_tex;
	chair->Materials[6].tex=chair_tex;
	chair->Materials[7].tex=chair_tex;
	chair->Materials[8].tex=BARK;
	chair->Materials[9].tex=chair_tex;
	chair->Materials[10].tex=chair_tex;
	chair->Materials[11].tex=BARK;

	tree->Materials[0].tex=BARK;
	tree->Materials[1].tex=Leaf;
	tree->Materials[2].tex=Leaf;
	tree->Materials[3].tex=Leaf;
	tree->Materials[4].tex=Leaf;

	
	tree->pos.x=1;
	tree->pos.y=0;
	tree->pos.z=1;
	tree->scale=0.2;

	chair->pos.x=5;
	chair->pos.y=0;
	chair->pos.z=5;
	chair->scale=0.5;
	chair->rot.y=-55;


	return TRUE;
}
	// Create the mall floor
float mallWidth = 200.0f;
float mallDepth = 250.0f;

// Camera variables
double movX = 0.0, movY = 0.0, movZ = 5.0; // Camera position
double lX = 0.0, lY = 0.0, lZ = 0.0;       // Look-at position (center point)
double yaw = -90.0f, pitch = 0.0f;         // Yaw (horizontal rotation) and Pitch (vertical rotation)
double speed = 0.1;                       // Movement speed
double sensitivity = 0.2;                 // Rotation sensitivity

void UpdateLookAt() {
    // Calculate direction vector using yaw and pitch
    double frontX = cos(yaw * M_PI / 180.0) * cos(pitch * M_PI / 180.0);
    double frontY = sin(pitch * M_PI / 180.0);
    double frontZ = sin(yaw * M_PI / 180.0) * cos(pitch * M_PI / 180.0);

    // Normalize the direction vector and update the LookAt point
    double length = sqrt(frontX * frontX + frontY * frontY + frontZ * frontZ);
    lX = movX + frontX / length;
    lY = movY + frontY / length;
    lZ = movZ + frontZ / length;
}

void Camera() {
    // Apply the LookAt matrix
    gluLookAt(movX, movY, movZ, lX, lY, lZ, 0, 1, 0);

    // Handle forward and backward movement
    if (keys['W'] || keys['w']) {
        movX += cos(yaw * M_PI / 180.0) * speed;
        movZ += sin(yaw * M_PI / 180.0) * speed;
    }
    if (keys['S'] || keys['s']) {
        movX -= cos(yaw * M_PI / 180.0) * speed;
        movZ -= sin(yaw * M_PI / 180.0) * speed;
    }

    // Handle left and right strafing movement
    if (keys['A'] || keys['a']) {
        movX += sin(yaw * M_PI / 180.0) * speed;
        movZ -= cos(yaw * M_PI / 180.0) * speed;
    }
    if (keys['D'] || keys['d']) {
        movX -= sin(yaw * M_PI / 180.0) * speed;
        movZ += cos(yaw * M_PI / 180.0) * speed;
    }

    // Handle camera rotation (steering)
    if (keys[VK_RIGHT]) {
        yaw += sensitivity; // Look left
    }
    if (keys[VK_LEFT]) {
        yaw -= sensitivity; // Look right
    }
    if (keys[VK_UP]) {
        pitch += sensitivity; // Look up
        if (pitch > 89.0f) pitch = 89.0f; // Constrain pitch
    }
    if (keys[VK_DOWN]) {
        pitch -= sensitivity; // Look down
        if (pitch < -89.0f) pitch = -89.0f; // Constrain pitch
    }

    // Update LookAt based on yaw and pitch
    UpdateLookAt();
}

void drawTrees(){
	glPushMatrix();
	glRotated(-90 , 0 , 1 , 0);
	glTranslated(0.0f , -5.0f ,0.0f);
		
	tree->pos.x=-90;
	tree->pos.y=0;
	tree->pos.z=-10;
	tree->scale=2;
	tree->Draw();

	tree->pos.x=-45;
	tree->pos.y=0;
	tree->pos.z=-10;
	tree->scale=2;
	tree->Draw();
	glPopMatrix();
}

int DrawGLScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslated(0.0f , 0.0f ,-15.0f);
	Camera();

	mall.createMallLand(mallWidth, mallDepth, kitchen_floor  , street);
	mall.drawMall(mall_wall , kitchen_floor , mall_wall , mall_wall );

	kitchen.createKitchenRoom(29.0f , 75.0f , 50.0f , kitchen_wall , ele_floor , fridge_side , fridge_front , white, washing_machine , microwave , wood , oven_front , title_kitchen );

	ele.createElectricRoom(29.0f , 75.0f , 50.0f ,ele_wall , ele_floor , door ,ele_title , wood2 , screen , screen_body , keyboard , fifa);

	lib.createLibraryRoom(29.0f , 75.0f , 50.0f ,lib_wall , lib_floor , door ,lib_title , wood , wood2 , books);

	game.createGamingRoom(29.0f , 75.0f , 50.0f ,game_wall , game_floor , door ,game_title, wood , bill_surface , wood , screen , screen_body , sopha);

	drawTrees();
	//DrawRoom1(50 , 50 , 50);
	Draw_Skybox(0, 0, 0, 1000, 1000, 1000);
	 
	
	return TRUE;
}

GLvoid KillGLWindow(GLvoid)								// Properly Kill The Window
{
	if (fullscreen)										// Are We In Fullscreen Mode?
	{
		ChangeDisplaySettings(NULL, 0);					// If So Switch Back To The Desktop
		ShowCursor(TRUE);								// Show Mouse Pointer
	}

	if (hRC)											// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL, NULL))					// Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(NULL, "Release Of DC And RC Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))						// Are We Able To Delete The RC?
		{
			MessageBox(NULL, "Release Rendering Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}
		hRC = NULL;										// Set RC To NULL
	}

	if (hDC && !ReleaseDC(hWnd, hDC))					// Are We Able To Release The DC
	{
		MessageBox(NULL, "Release Device Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hDC = NULL;										// Set DC To NULL
	}

	if (hWnd && !DestroyWindow(hWnd))					// Are We Able To Destroy The Window?
	{
		MessageBox(NULL, "Could Not Release hWnd.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hWnd = NULL;										// Set hWnd To NULL
	}

	if (!UnregisterClass("OpenGL", hInstance))			// Are We Able To Unregister Class
	{
		MessageBox(NULL, "Could Not Unregister Class.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hInstance = NULL;									// Set hInstance To NULL
	}
}

/*	This Code Creates Our OpenGL Window.  Parameters Are:					*
*	title			- Title To Appear At The Top Of The Window				*
*	width			- Width Of The GL Window Or Fullscreen Mode				*
*	height			- Height Of The GL Window Or Fullscreen Mode			*
*	bits			- Number Of Bits To Use For Color (8/16/24/32)			*
*	fullscreenflag	- Use Fullscreen Mode (TRUE) Or Windowed Mode (FALSE)	*/

BOOL CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag)
{
	GLuint		PixelFormat;			// Holds The Results After Searching For A Match
	WNDCLASS	wc;						// Windows Class Structure
	DWORD		dwExStyle;				// Window Extended Style
	DWORD		dwStyle;				// Window Style
	RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left = (long)0;			// Set Left Value To 0
	WindowRect.right = (long)width;		// Set Right Value To Requested Width
	WindowRect.top = (long)0;				// Set Top Value To 0
	WindowRect.bottom = (long)height;		// Set Bottom Value To Requested Height

	fullscreen = fullscreenflag;			// Set The Global Fullscreen Flag

	hInstance = GetModuleHandle(NULL);				// Grab An Instance For Our Window
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc = (WNDPROC)WndProc;					// WndProc Handles Messages
	wc.cbClsExtra = 0;									// No Extra Window Data
	wc.cbWndExtra = 0;									// No Extra Window Data
	wc.hInstance = hInstance;							// Set The Instance
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground = NULL;									// No Background Required For GL
	wc.lpszMenuName = NULL;									// We Don't Want A Menu
	wc.lpszClassName = "OpenGL";								// Set The Class Name

	if (!RegisterClass(&wc))									// Attempt To Register The Window Class
	{
		MessageBox(NULL, "Failed To Register The Window Class.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;											// Return FALSE
	}

	if (fullscreen)												// Attempt Fullscreen Mode?
	{
		DEVMODE dmScreenSettings;								// Device Mode
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);		// Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth = width;				// Selected Screen Width
		dmScreenSettings.dmPelsHeight = height;				// Selected Screen Height
		dmScreenSettings.dmBitsPerPel = bits;					// Selected Bits Per Pixel
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			// If The Mode Fails, Offer Two Options.  Quit Or Use Windowed Mode.
			if (MessageBox(NULL, "The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?", "GL template", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
			{
				fullscreen = FALSE;		// Windowed Mode Selected.  Fullscreen = FALSE
			}
			else
			{
				// Pop Up A Message Box Letting User Know The Program Is Closing.
				MessageBox(NULL, "Program Will Now Close.", "ERROR", MB_OK | MB_ICONSTOP);
				return FALSE;									// Return FALSE
			}
		}
	}

	if (fullscreen)												// Are We Still In Fullscreen Mode?
	{
		dwExStyle = WS_EX_APPWINDOW;								// Window Extended Style
		dwStyle = WS_POPUP;										// Windows Style
		ShowCursor(FALSE);										// Hide Mouse Pointer
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
		dwStyle = WS_OVERLAPPEDWINDOW;							// Windows Style
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

	// Create The Window
	if (!(hWnd = CreateWindowEx(dwExStyle,							// Extended Style For The Window
		"OpenGL",							// Class Name
		title,								// Window Title
		dwStyle |							// Defined Window Style
		WS_CLIPSIBLINGS |					// Required Window Style
		WS_CLIPCHILDREN,					// Required Window Style
		0, 0,								// Window Position
		WindowRect.right - WindowRect.left,	// Calculate Window Width
		WindowRect.bottom - WindowRect.top,	// Calculate Window Height
		NULL,								// No Parent Window
		NULL,								// No Menu
		hInstance,							// Instance
		NULL)))								// Dont Pass Anything To WM_CREATE
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Window Creation Error.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	static	PIXELFORMATDESCRIPTOR pfd =				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		bits,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// 16Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};

	if (!(hDC = GetDC(hWnd)))							// Did We Get A Device Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Create A GL Device Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Find A Suitable PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!SetPixelFormat(hDC, PixelFormat, &pfd))		// Are We Able To Set The Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Set The PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(hRC = wglCreateContext(hDC)))				// Are We Able To Get A Rendering Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Create A GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!wglMakeCurrent(hDC, hRC))					// Try To Activate The Rendering Context
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Activate The GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	ShowWindow(hWnd, SW_SHOW);						// Show The Window
	SetForegroundWindow(hWnd);						// Slightly Higher Priority
	SetFocus(hWnd);									// Sets Keyboard Focus To The Window
	ReSizeGLScene(width, height);					// Set Up Our Perspective GL Screen

	if (!InitGL())									// Initialize Our Newly Created GL Window
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Initialization Failed.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	return TRUE;									// Success
}

LRESULT CALLBACK WndProc(HWND	hWnd,			// Handle For This Window
	UINT	uMsg,			// Message For This Window
	WPARAM	wParam,			// Additional Message Information
	LPARAM	lParam)			// Additional Message Information
{
	switch (uMsg)									// Check For Windows Messages
	{
	case WM_ACTIVATE:							// Watch For Window Activate Message
	{
													if (!HIWORD(wParam))					// Check Minimization State
													{
														active = TRUE;						// Program Is Active
													}
													else
													{
														active = FALSE;						// Program Is No Longer Active
													}

													return 0;								// Return To The Message Loop
	}

	case WM_SYSCOMMAND:							// Intercept System Commands
	{
													switch (wParam)							// Check System Calls
													{
													case SC_SCREENSAVE:					// Screensaver Trying To Start?
													case SC_MONITORPOWER:				// Monitor Trying To Enter Powersave?
														return 0;							// Prevent From Happening
													}
													break;									// Exit
	}

	case WM_CLOSE:								// Did We Receive A Close Message?
	{
													PostQuitMessage(0);						// Send A Quit Message
													return 0;								// Jump Back
	}

	case WM_KEYDOWN:							// Is A Key Being Held Down?
	{
													keys[wParam] = TRUE;					// If So, Mark It As TRUE
													return 0;								// Jump Back
	}

	case WM_KEYUP:								// Has A Key Been Released?
	{
													keys[wParam] = FALSE;					// If So, Mark It As FALSE
													return 0;								// Jump Back
	}

	case WM_SIZE:								// Resize The OpenGL Window
	{
													ReSizeGLScene(LOWORD(lParam), HIWORD(lParam));  // LoWord=Width, HiWord=Height
													return 0;								// Jump Back
	}
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE	hInstance,			// Instance
	HINSTANCE	hPrevInstance,		// Previous Instance
	LPSTR		lpCmdLine,			// Command Line Parameters
	int			nCmdShow)			// Window Show State
{
	MSG		msg;									// Windows Message Structure
	BOOL	done = FALSE;								// Bool Variable To Exit Loop

	// Ask The User Which Screen Mode They Prefer
	//if (MessageBox(NULL,"Would You Like To Run In Fullscreen Mode?", "Start FullScreen?",MB_YESNO|MB_ICONQUESTION)==IDNO)
	{
		fullscreen = FALSE;							// Windowed Mode
	}

	// Create Our OpenGL Window
	if (!CreateGLWindow("Example", 640, 480, 16, fullscreen))
	{
		return 0;									// Quit If Window Was Not Created
	}

	while (!done)									// Loop That Runs While done=FALSE
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))	// Is There A Message Waiting?
		{
			if (msg.message == WM_QUIT)				// Have We Received A Quit Message?
			{
				done = TRUE;							// If So done=TRUE
			}
			else									// If Not, Deal With Window Messages
			{
				TranslateMessage(&msg);				// Translate The Message
				DispatchMessage(&msg);				// Dispatch The Message
			}
		}
		else										// If There Are No Messages
		{
			// Draw The Scene.  Watch For ESC Key And Quit Messages From DrawGLScene()
			if (active)								// Program Active?
			{
				if (keys[VK_ESCAPE])				// Was ESC Pressed?
				{
					done = TRUE;						// ESC Signalled A Quit
				}
				else								// Not Time To Quit, Update Screen
				{
					DrawGLScene();					// Draw The Scene
					SwapBuffers(hDC);				// Swap Buffers (Double Buffering)
				}
			}

			if (keys[VK_F1])						// Is F1 Being Pressed?
			{
				keys[VK_F1] = FALSE;					// If So Make Key FALSE
				KillGLWindow();						// Kill Our Current Window
				fullscreen = !fullscreen;				// Toggle Fullscreen / Windowed Mode
				// Recreate Our OpenGL Window
				if (!CreateGLWindow("OpenGL template", 640, 480, 16, fullscreen))
				{
					return 0;						// Quit If Window Was Not Created
				}
			}
		}
	}

	// Shutdown
	KillGLWindow();									// Kill The Window
	return (msg.wParam);							// Exit The Program
}

