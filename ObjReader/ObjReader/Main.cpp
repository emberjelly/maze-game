#include <stdio.h>
#include <windows.h>
#include <GL/gl.h>
#include <glut.h>
#include <freeglut.h>
#include "playerStats.h"
#include <time.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include "imageloader.h"

//#define GLUTGAMEMODE

int texNum = 4;
GLuint* loadTexture(Image** image) {
	GLuint* textureId = new GLuint[texNum];
	glGenTextures(texNum, textureId); //Make room for our texture
	
	for (int i = 0; i < texNum; i ++)
	{
		glBindTexture(GL_TEXTURE_2D, textureId[i]); //Tell OpenGL which texture to edit
		//Map the image to the texture
		glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
					 0,                            //0 for now
					 GL_RGB,                       //Format OpenGL uses for image
					 image[i]->width, image[i]->height,  //Width and height
					 0,                            //The border of the image
					 GL_RGB, //GL_RGB, because pixels are stored in RGB format
					 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
					                   //as unsigned numbers
					 image[i]->pixels);               //The actual pixel data
	}
	
	
	return textureId; //Returns the id of the texture
}

GLuint* _textureId; //The id of the texture

ObjDeclarations graphics;
playerDetails player;


void reshape(GLsizei width, GLsizei height);
void display();

Sphere* mySpheres;
SphereManager* mySphereManager;

RecPrismManager* fenceManager;
recPrism* fence;

RecPrismManager* mazeWallManager;
recPrism* mazeWall;

void update(int value);
bool keyStates[256];



void display() 
{
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode (GL_MODELVIEW);
	glClear(GL_DEPTH_BUFFER_BIT);
	glLoadIdentity ();

	static float deltaTime = 0;
	clock_t startFrame = clock();
	glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH)/2, glutGet(GLUT_WINDOW_HEIGHT)/2);


	movePlayer(deltaTime);

	gluLookAt (0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0);
	drawHud(&graphics);

	glRotatef(player.pitch, 1.0f, 0.0f, 0.0f);
	glRotatef(player.yaw, 0.0f, 1.0f, 0.0f);


	glPushMatrix();

	glTranslated(-player.playerX,player.playerY -player.playerHeight,-player.playerZ);
	
	drawScene(&graphics, deltaTime);

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glPopMatrix();
	
	clock_t endFrame = clock();
	//printf ("Time to load frame: %f\n", ((float)endFrame - float(startFrame)));
	player.playerSpeed = player.startFrameSpeed*((float)endFrame - float(startFrame))/1000;
	deltaTime = (float)endFrame - float(startFrame);
	glutSwapBuffers();
	glutPostRedisplay();
}


void initialize () 
{

   // select projection matrix
    glMatrixMode(GL_PROJECTION);												
 
	// set the viewport
    glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));									
 
	// set matrix mode
    glMatrixMode(GL_PROJECTION);												
 
	// reset projection matrix
    glLoadIdentity();															
    GLfloat aspect = (GLfloat) glutGet(GLUT_WINDOW_WIDTH)/glutGet(GLUT_WINDOW_HEIGHT);
 
	// set up a perspective projection matrix
	gluPerspective(45.0f, aspect, 1.0f, 500.0f);
 
	// specify which matrix is the current matrix
	glMatrixMode(GL_MODELVIEW);													
    glShadeModel( GL_SMOOTH );
 
	// specify the clear value for the depth buffer
	glClearDepth( 1.0f );														
    glEnable( GL_DEPTH_TEST );
    glDepthFunc( GL_LEQUAL );
 
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// specify implementation-specific hints
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );						
 
	GLfloat amb_light[] = { 0.4, 0.4, 0.4, 1.0 };
    GLfloat diffuse[] = { 0.6, 0.6, 0.6, 1 };
    GLfloat specular[] = { 0.7, 0.7, 0.3, 1 };
    glLightModelfv( GL_LIGHT_MODEL_AMBIENT, amb_light );
    glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuse );
    glLightfv( GL_LIGHT0, GL_SPECULAR, specular );
    glEnable( GL_LIGHT0 );
    glEnable( GL_COLOR_MATERIAL );
    glShadeModel( GL_SMOOTH );
    glLightModeli( GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE );
    glDepthFunc( GL_LEQUAL );
    glEnable( GL_DEPTH_TEST );
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0); 
	
	GLfloat density = 0.0;
	GLfloat fogColor[4] = {0, 0, 0, 0.1}; 
	glEnable (GL_FOG);

	glFogi (GL_FOG_MODE, GL_EXP);
	glFogfv (GL_FOG_COLOR, fogColor);
	glFogf (GL_FOG_DENSITY, density);
	glHint (GL_FOG_HINT, GL_NICEST);
	glFogf (GL_FOG_START, 10.0);
    glFogf (GL_FOG_END, 12.0);
	glClearColor(1.0, 1.0f, 1.0f, 1.0f);
	

	_textureId = new GLuint();
	Image** image = new Image*[texNum];
	image[0] = loadBMP("fpsgame\\textures\\wall.bmp");
	image[1] = loadBMP("fpsgame\\textures\\bloodywall.bmp");	
	image[2] = loadBMP("fpsgame\\textures\\bloodywall2.bmp");
	image[3] = loadBMP("fpsgame\\textures\\largedirt.bmp");

	_textureId = loadTexture(image);
	delete image;
}

int main(int argc, char **argv) 
{
	mySphereManager = new SphereManager();
	genMaze();
	

	fenceManager = new RecPrismManager();

	for (int i = 0; i < 256; i ++) keyStates[i] = false;

	// initialize and run program
	glutInit(&argc, argv);                                      // GLUT initialization
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );  // Display Mode

		GLint m_viewport[4];

		glGetIntegerv( GL_VIEWPORT, m_viewport);
#ifdef GLUTGAMEMODE
		glutGameModeString("1280x720:32");
	// enter full screen
	if (glutGameModeGet(GLUT_GAME_MODE_POSSIBLE))
		glutEnterGameMode();
	else {
		printf("The select mode is not available\n");
		exit(1);
	}
#endif // GLUTGAMEMODE
#ifndef GLUTGAMEMODE
		glutInitWindowSize(1024,768);				// set window size
		glutInitWindowPosition(800,0);
		glutCreateWindow("FPS GAME");	
#endif // !GLUTGAMEMODE


				// create Window
	glutDisplayFunc(display);						// register Display Function
	glutIdleFunc( display );						// register Idle Function
	glutKeyboardFunc(keyDown);
	glutKeyboardUpFunc(keyUp);
	glutSpecialFunc(specialKeyDown);
	glutSpecialUpFunc(specialKeyUp);
	glutPassiveMotionFunc(mouseMovement);
	glutSetCursor(GLUT_CURSOR_NONE); 
	glutMouseFunc(mouseFire);
	initialize();
	

	
	
	glutMainLoop();							// run GLUT mainloop
	return 0;
}


