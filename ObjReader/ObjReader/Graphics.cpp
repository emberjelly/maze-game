#include "playerStats.h"
#define _USE_MATH_DEFINES
#include <math.h>

extern SphereManager* mySphereManager;
extern Sphere* mySpheres;
extern recPrism* fence;
extern RecPrismManager* fenceManager;
extern playerDetails player;
extern RecPrismManager* mazeWallManager;
extern recPrism* mazeWall;
extern int size;
extern GLuint* _textureId;
//NOTE ONE UNIT CORRESPONDS EXACTLY TO ONE BLENDER UNIT

void drawHud(ObjDeclarations *hudGraphics)
{
	/*
	glColor3f(1, 0, 0);
	
	glLineWidth(2.0f); 
	glBegin(GL_LINES);
	
	glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(-0.55f, -0.55f, 0.0f);
		glVertex3f(0.0f, 0.0f, 1.5f);
	glEnd();

	glBegin(GL_TRIANGLES);

		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(0.0f, 1.0f*0.01f, 1.5f);
		glVertex3f(0.866f*0.01f, -0.5f*0.01f, 1.5f);
		glVertex3f(-0.866f*0.01f, -0.5f*0.01f, 1.5f);
	glEnd();
	*/		

	/*
	glColor3f (1,1,1);
	drawObjTRIANGLES(hudGraphics->mp5, -0.6, -0.8, 1.5, 0, 0, 0);
	*/
	}

void drawScene(ObjDeclarations *sceneGraphics, float frameTime)
{
	static int animStage = 0;
	static	GLfloat density = 0.0;

		for (int i = 0; i < mySphereManager->getSphereNum(); i ++)
		{
			mySpheres = mySphereManager->getSphere(i);
			drawObjTRIANGLES(sceneGraphics->oneUnitRadiusSphere, mySpheres->getX(), mySpheres->getY(), mySpheres->getZ(), 0, 0, 0);
		}
		glColor3f(0.3, 0.3, 0.4);
		glEnable(GL_TEXTURE_2D);

		for (int i = 0; i < mazeWallManager->getRecNum(); i ++)
		{
			mazeWall = mazeWallManager->getRecPrism(i);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glBindTexture(GL_TEXTURE_2D, _textureId[mazeWall->getTexNum()]);
			drawObjTRIANGLES(sceneGraphics->cube, mazeWall->getX(), mazeWall->getY(), mazeWall->getZ(), 0, 0, 0);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glBindTexture(GL_TEXTURE_2D, _textureId[0]);
			

			drawObjTRIANGLES(sceneGraphics->cube, mazeWall->getX(), mazeWall->getY() + 6, mazeWall->getZ(), 0, 0, 0);
		}
		
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glBindTexture(GL_TEXTURE_2D, _textureId[0]);		

		
		glBegin(GL_QUADS);
			glNormal3d(0, -1, 0);
			glTexCoord2f(0, 0);			
			glVertex3f(0, 12.01, 0);
			glTexCoord2f(2*size, 0);
			glVertex3d(0, 12.01,  (2*size+1)*6);
			glTexCoord2f(2*size, 2*size);
			glVertex3d((2*size+1)*6, 12.01, (2*size+1)*6);
			glTexCoord2f(0, 2*size);
			glVertex3d((2*size+1)*6, 12.01, 0);
		glEnd();
		

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, _textureId[3]);
		
		glBegin(GL_QUADS);
			glNormal3d(0, 1, 0);
			glTexCoord2f(0, 0);
			glVertex3d(0, 0, 0);
			glTexCoord2f(1, 0);
			glVertex3d(0, 0,  (2*size+1)*6);
			glTexCoord2f(1, 1);
			glVertex3d((2*size+1)*6, 0, (2*size+1)*6);
			glTexCoord2f(0, 1);
			glVertex3d((2*size+1)*6, 0, 0);
		glEnd();

		glDisable(GL_TEXTURE_2D);
		float fps = 1000/frameTime;
		//printf("%f\n", fps);
		animStage ++;
		
		if (animStage%100 == 0 & density < 1)
		{
			if (density < 0.2)
			{
				density += 100*0.2/(3*fps*60);
				glFogf (GL_FOG_DENSITY, density);
			}else{
				player.isAlive = false;
				printf("%f\n", density);
				density += (100*0.8)/(10*fps);
				glFogf (GL_FOG_DENSITY, density);
			}
		}
}
