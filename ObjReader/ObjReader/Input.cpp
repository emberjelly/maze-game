#include <stdio.h>
#include "playerStats.h"
#include <math.h>
#include <glut.h>
#include <freeglut.h>
#define KEY_ESCAPE 27
#include "VectorHeader.h"

extern playerDetails player;
extern bool keyStates[256];

//extern ObjDeclarations graphics;

void movePlayer(float deltaTime)
{
	bool checkCollision = false;

	if (player.isJumping)
	{
		player.playerY -= player.playerSpeedUp*deltaTime/1000;
		player.playerSpeedUp -=  deltaTime*player.playerAcceleration/1000;
		checkCollision = sphereCollisions();
	}

	if (player.playerY > player.ground)
	{
		player.playerY = player.ground;
		player.isJumping = false;
	}


	if(keyStates['a'] == true) {
		float yRotRad = (float) (3.14/180*player.yaw);
		player.playerX -= -player.playerSpeed * cos(yRotRad);
		player.playerZ -= -player.playerSpeed * sin(yRotRad);
		checkCollision = sphereCollisions();
		if (!checkCollision)
			checkCollision = wallCollisions();
		if (checkCollision)
		{
			player.playerX += -player.playerSpeed * cos(yRotRad);
			player.playerZ += -player.playerSpeed * sin(yRotRad);
		}
	}
	if(keyStates['d'] == true) {
		float yRotRad = (float) (3.14/180*player.yaw);
		player.playerX -= player.playerSpeed * cos(yRotRad);
		player.playerZ -= player.playerSpeed * sin(yRotRad);
		checkCollision = sphereCollisions();
			if (!checkCollision)
		checkCollision = wallCollisions();
		if (checkCollision)
		{
			player.playerX += player.playerSpeed * cos(yRotRad);
			player.playerZ += player.playerSpeed * sin(yRotRad);
		}
	}
	if(keyStates['w'] == true) {
		float yRotRad = (float) (3.14/180*player.yaw);
		player.playerX -= player.playerSpeed * sin(yRotRad);
		player.playerZ -= -player.playerSpeed * cos(yRotRad);
		checkCollision = sphereCollisions();
		if (!checkCollision)
			checkCollision = wallCollisions();	
		if (checkCollision)
		{
			player.playerX += player.playerSpeed * sin(yRotRad);
			player.playerZ += -player.playerSpeed * cos(yRotRad);
		}
	}
	if(keyStates['s'] ==  true) { 
		float yRotRad = (float) (3.14/180*player.yaw);
		player.playerX -= -player.playerSpeed * sin(yRotRad);
		player.playerZ -= player.playerSpeed * cos(yRotRad);
		checkCollision = sphereCollisions();
		if (!checkCollision)
			checkCollision = wallCollisions();
		if (checkCollision)
		{
			player.playerX += -player.playerSpeed * sin(yRotRad);
			player.playerZ += player.playerSpeed * cos(yRotRad);
		}
	}
	if (keyStates[' '])
	{
		if (player.isJumping == false)
		player.playerSpeedUp = 7.2;
		player.isJumping = true;
	}
}

void keyDown ( unsigned char key, int mousePositionX, int mousePositionY )
{
	if (player.isAlive)
	{

	switch ( key ) 
		{
		case KEY_ESCAPE:
			exit ( 0 );   
			break;
		case 'w':
			keyStates['w'] = true;
			break;
		case 's':
			keyStates['s'] = true;
			break;
		case 'a':
			keyStates['a'] = true;
			break;
		case 'd':
			keyStates['d'] = true;
			break;
		case ' ':
			keyStates[' '] = true;
			break;
		case 'z':
			player.startFrameSpeed = player.runSpeed;
			break;
		default:
		break;
		}
	}
}

void keyUp ( unsigned char key, int mousePositionX, int mousePositionY )
{
	switch ( key ) 
	{
	case KEY_ESCAPE:
		exit ( 0 );   
		break;
	case 'w':
		keyStates['w'] = false;
		break;
	case 's':
		keyStates['s'] = false;
		break;
	case 'a':
		keyStates['a'] = false;
		break;
	case 'd':
		keyStates['d'] = false;
		break;
	case ' ':
		keyStates[' '] = false;
		break;
	case 'z':
		player.startFrameSpeed = player.walkSpeed;
		break;
	default:
	break;
	}
}
void specialKeyDown (int key, int mousePositionX, int mousePositionY )
{

}
void specialKeyUp (int key, int mousePositionX, int mousePositionY )
{
}

void mouseMovement(int x, int y)
{
	int width = glutGet(GLUT_WINDOW_WIDTH);
	int height = glutGet(GLUT_WINDOW_HEIGHT);
	
	player.pitch -= float(y - height/2);

	if (player.pitch <-90) player.pitch = -90;
	if (player.pitch >90) player.pitch = 90;


	player.yaw += float(x - width/2);
	if (player.yaw > 360)
	{
		player.yaw -= 360;
	}
	if (player.yaw < -360)
	{
		player.yaw += 360;
	}
}

void mouseFire(int button, int state , int x, int y)
{

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		Vector mouseVec;
		mouseVec.setX(0);
		mouseVec.setY(0);
		mouseVec.setZ(100);
	
		mouseVec.rotateX(player.pitch);
		mouseVec.rotateY(-player.yaw);
	
		player.bulletX = mouseVec.getX();
		player.bulletY = mouseVec.getY();
		player.bulletZ = mouseVec.getZ();
		
		shootingCollisions(mouseVec.getX(), mouseVec.getY(), mouseVec.getZ());
		//printf ("%f   %f   %f\n", mouseVec.getX(), mouseVec.getY(), mouseVec.getY());
	}
}
