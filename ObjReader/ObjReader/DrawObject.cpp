#include <glut.h>
#include <freeglut.h>
#include "ObjHeader.h"
#include "VectorHeader.h"
#include <math.h>


void drawObjTRIANGLES(ObjFile* inObjFile, float positionX, float positionY, float positionZ, float pitch, float yaw, float roll)

{
	int faceNum = inObjFile->getFace3vCount();
	
	Vector* vector1 = new Vector();
	Vector* vector2 = new Vector();
	Vector* vector3 = new Vector();
	Vector* normal = new Vector();

	for (int i = 0; i < faceNum; i ++)
		{
		ObjFaces3v* my3v = inObjFile->getFace3v(i);
		ObjFaces3vNormal* myn = inObjFile->getFace3vNormal(i);
		ObjFaces3vTexture* myt = inObjFile->getFace3vTexture(i);

		int f1 = my3v->getFace3vValue1();
		int f2 = my3v->getFace3vValue2();
		int f3 = my3v->getFace3vValue3();
		int n = myn->getFace3vValue();
		int t1 = myt->getFace3vValue1();
		int t2 = myt->getFace3vValue2();
		int t3 = myt->getFace3vValue3();
		ObjVertex3f* myVertex = inObjFile->getVertexValues(f1 - 1);
		float vx1 = myVertex->getCoordinateX();
		float vy1 = myVertex->getCoordinateY();
		float vz1 = myVertex->getCoordinateZ();

		myVertex = inObjFile->getVertexValues(f2 -1);
		float vx2 = myVertex->getCoordinateX();
		float vy2 = myVertex->getCoordinateY();
		float vz2 = myVertex->getCoordinateZ();

		myVertex = inObjFile->getVertexValues(f3 - 1);
		float vx3 = myVertex->getCoordinateX();
		float vy3 = myVertex->getCoordinateY();
		float vz3 = myVertex->getCoordinateZ();
		
		ObjNormal3f* myNormal = inObjFile->getNormalValues(n - 1);
		float nx = myNormal->getCoordinateX();
		float ny = myNormal->getCoordinateY();
		float nz = myNormal->getCoordinateZ();
		
		ObjTexture2f* myTexture = inObjFile->getTextureValues(t1 - 1);
		float texX1 = myTexture->getCoordinateX();
		float texY1 = myTexture->getCoordinateY();
		
		myTexture = inObjFile->getTextureValues(t2 - 1);
		float texX2 = myTexture->getCoordinateX();
		float texY2 = myTexture->getCoordinateY();
		
		myTexture = inObjFile->getTextureValues(t3 - 1);
		float texX3 = myTexture->getCoordinateX();
		float texY3 = myTexture->getCoordinateY();

		vector1->setX(vx1);
		vector1->setY(vy1);
		vector1->setZ(vz1);
		normal->setX(nx);
		
		vector2->setX(vx2);
		vector2->setY(vy2);
		vector2->setZ(vz2);
		normal->setY(ny);

		vector3->setX(vx3);
		vector3->setY(vy3);
		vector3->setZ(vz3);
		normal->setZ(nz);

		if(pitch!=0)
		{
			vector1->rotateX(pitch);
			vector2->rotateX(pitch);
			vector3->rotateX(pitch);
			normal->rotateX(pitch);
		}
		if (yaw != 0)
		{
			vector1->rotateY(yaw);
			vector2->rotateY(yaw);
			vector3->rotateY(yaw);
			normal->rotateY(yaw);
		}
		if (roll != 0)
		{
			vector1->rotateZ(roll);
			vector2->rotateZ(roll);
			vector3->rotateZ(roll);
			normal->rotateZ(roll);
		}
		
		/*
		glBegin(GL_TRIANGLES);
			glNormal3f(nx*cos(pitch) - ny*sin(pitch), nx*sin(pitch) + ny*cos(pitch), nz);
			glVertex3f(-vy1*sin(pitch)  + vx1*cos(pitch) + positionX, vx1*sin(pitch) + vy1*cos(pitch) + positionY, vz1 + positionZ);
			glVertex3f(-vy2*sin(pitch)  + vx2*cos(pitch) + positionX, vx2*sin(pitch) + vy2*cos(pitch) + positionY, vz2 + positionZ);
			glVertex3f(-vy3*sin(pitch)  + vx3*cos(pitch) + positionX, vx3*sin(pitch) + vy3*cos(pitch) + positionY, vz3 + positionZ);
		glEnd();
		*/

		glBegin(GL_TRIANGLES);
			glNormal3f(normal->getX(), normal->getY(), normal-> getZ());
			glTexCoord2f(texX1, texY1);
			glVertex3f(vector1->getX() + positionX, vector1->getY() + positionY, vector1->getZ() + positionZ);
			glTexCoord2f(texX2, texY2);
			glVertex3f(vector2->getX() + positionX, vector2->getY() + positionY, vector2->getZ() + positionZ);
			glTexCoord2f(texX3, texY3);
			glVertex3f(vector3->getX() + positionX, vector3->getY() + positionY, vector3->getZ() + positionZ);
		glEnd();


	}
	
	delete vector1;
	delete vector2;
	delete vector3;
	delete normal;
	
}
