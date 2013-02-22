#include <stdio.h>
#include "ObjHeader.h"

class playerDetails{
public:
	playerDetails()
	{
		walkSpeed = 8;
		runSpeed = 16;
		playerSpeed = walkSpeed;
		playerX = 9;
		playerZ = 9;
		playerY = 0;
		playerHeight = 6;
		speedChange = 5;
		pitch = 0;
		yaw = 0;
		playerAcceleration = 10;
		playerSpeedUp = 0;
		isJumping = false;
		isAlive = true;
		startFrameSpeed = playerSpeed;
		bulletX	= 0;
		bulletY	= 0;
		bulletZ	= 0;
		ground = 0;
		animStage = 0;
	}

	float playerSpeed;
	float playerX;
	float playerZ;
	float playerY;
	float playerHeight;
	float speedChange;
	float pitch;
	float yaw;
	float playerAcceleration;
	float playerSpeedUp;
	bool isJumping;
	bool isAlive;
	float startFrameSpeed;
	float walkSpeed;
	float runSpeed;
	float bulletX;
	float bulletY;
	float bulletZ;
	float ground;
	float animStage;
};
class Sphere{
public:
	Sphere()
	{
		sphereX = 0;
		sphereY = 0;
		sphereZ = 0;
		sphereR = 0;
		m_collision = false;
	}

	void setSphereValues(float x, float y, float z, float r)
	{
		sphereX = x;
		sphereY = y;
		sphereZ = z;
		sphereR = r;
	}

	float getX()
	{
		return sphereX;
	}
	float getY()
	{
		return sphereY;
	}
	float getZ()
	{
		return sphereZ;
	}
	float getR()
	{
		return sphereR;
	}

	void setX(float x)
	{
		sphereX = x;
	}
	void setY(float y)
	{
		sphereY = y;
	}
	void setZ(float z)
	{
		sphereZ = z;
	}
	void setR(float r)
	{
		sphereR = r;
	}

	void setCollisionStatus(bool c)
	{
		m_collision = c;
	}

	bool getCollisionStatus()
	{
		return m_collision;
	}

private:
	float sphereX;
	float sphereY;
	float sphereZ;
	float sphereR;
	bool m_collision;
};


class SphereManager{
public:
	SphereManager()
	{
		sphereCount = 0;
		m_ppSphere = NULL;
	}
	~ SphereManager()
	{
		if (m_ppSphere != NULL)
		{
			delete[] m_ppSphere;
			m_ppSphere = NULL;
		}
	}

	void addSphere(float x, float y, float z, float r)
	{
		sphereCount ++;
		Sphere ** temp = m_ppSphere;
		m_ppSphere = new Sphere*[sphereCount];

		for (int i = 0; i < sphereCount - 1; i ++)
		{
			m_ppSphere[i] = new Sphere();
			m_ppSphere[i] = temp[i];
		}
		m_ppSphere[sphereCount - 1] = new Sphere();
		m_ppSphere[sphereCount - 1]->setSphereValues(x, y, z, r);
		if (temp != NULL)
		{
			delete[] temp;
		}
	}

	void deleteSphere(int sphereNumber)
	{
		if (sphereCount > 0)
		{
			for (int i = sphereNumber; i < (sphereCount - 1); i ++)
			{
				m_ppSphere[i] = m_ppSphere[i+1];
			}
			sphereCount --;
		}
	}

	int getSphereNum()
	{
		return sphereCount;
	}

	Sphere* getSphere(int sphereNumber)
	{
		return m_ppSphere[sphereNumber];
	}

private:
	int sphereCount;
	Sphere** m_ppSphere;
};

class recPrism{
public:
	recPrism()
	{
		recX = 0;
		recY = 0;
		recZ = 0;
		recW = 0;
		recH = 0;
		recD = 0;
		textureNum = 0;
	}

	void setRecValues(float x, float y, float z, float w, float d, float h, int textureNumber)
	{
		recX = x;
		recY = y;
		recZ = z;
		recW = w;
		recH = h;
		recD = d;
		textureNum = textureNumber;
	}

	float getX()
	{
		return recX;
	}
	float getY()
	{
		return recY;
	}
	float getZ()
	{
		return recZ;
	}
	float getW()
	{
		return recW;
	}
	float getD()
	{
		return recD;
	}
	float getH()
	{
		return recH;
	}



	void setX(float x)
	{
		recX = x;
	}
	void setY(float y)
	{
		recY = y;
	}
	void setZ(float z)
	{
		recZ = z;
	}
	void setW(float w)
	{
		recW = w;
	}
	void setD(float d)
	{
		recD = d;
	}
	void setH(float h)
	{
		recH = h;
	}

	int getTexNum()
	{
		return textureNum;
	}
private:
	float recX;
	float recY;
	float recZ;
	float recW;
	float recH;
	float recD;
	int textureNum;
};


class RecPrismManager{
public:
	RecPrismManager()
	{
		recCount = 0;
		m_ppRecPrism = NULL;
	}
	~ RecPrismManager()
	{
		if (m_ppRecPrism != NULL)
		{
			delete[] m_ppRecPrism;
			m_ppRecPrism = NULL;
		}
	}

	void addRecPrism(float x, float y, float z, float w, float d, float h, int textureNumber)
	{
		recCount ++;
		recPrism ** temp = m_ppRecPrism;
		m_ppRecPrism = new recPrism*[recCount];

		for (int i = 0; i < recCount - 1; i ++)
		{
			m_ppRecPrism[i] = new recPrism();
			m_ppRecPrism[i] = temp[i];
		}
		m_ppRecPrism[recCount - 1] = new recPrism();
		m_ppRecPrism[recCount - 1]->setRecValues(x, y, z, w, d, h, textureNumber);
		if (temp != NULL)
		{
			delete[] temp;
		}
	}

	void deleteRecPrism(int recNumber)
	{
		if (recCount < recNumber)
		{
			printf ("There are not %d rectangular prisms in this manager\n", recNumber); 
		}
		else if (recCount > 0)
		{
			for (int i = recNumber; i < (recCount - 1); i ++)
			{
				m_ppRecPrism[i] = m_ppRecPrism[i+1];
			}
			recCount --;
		}
	}

	int getRecNum()
	{
		return recCount;
	}

	recPrism* getRecPrism(int recPrismNumber)
	{
		return m_ppRecPrism[recPrismNumber];
	}

private:
	int recCount;
	recPrism** m_ppRecPrism;
};



class ObjDeclarations{
public:
	ObjDeclarations()
	{
		//mp5 = loadObj("E:\\fpsgame\\mp5.obj");
		//sphere = loadObj("E:\\fpsgame\\sphere.obj");
		cube = loadObj("fpsgame\\cube.obj");
		oneUnitRadiusSphere = loadObj("fpsgame\\1unit_radius_sphere.obj");
		//fence = loadObj("E:\\fpsgame\\fence.obj");
		face = loadObj("fpsgame\\face.obj");
		unitCube = loadObj("fpsgame\\1unitcube.obj");
	}

	~ObjDeclarations()
	{
	}
	ObjFile* mp5;
	ObjFile* sphere;
	ObjFile* cube;
	ObjFile* oneUnitRadiusSphere;
	ObjFile* fence;
	ObjFile* face;
	ObjFile* unitCube;
};


//drawing scene
void drawHud(ObjDeclarations *hudGraphics);
void drawScene(ObjDeclarations *sceneGraphics, float frameTime);
struct ObjDeclarations;


// Input
void keyDown ( unsigned char key, int mousePositionX, int mousePositionY );
void mouseMovement(int x, int y);
void movePlayer(float deltaTime);
void keyUp ( unsigned char key, int mousePositionX, int mousePositionY );
void mouseFire(int button, int state , int x, int y);
void specialKeyUp ( int key, int mousePositionX, int mousePositionY );
void specialKeyDown (int key, int mousePositionX, int mousePositionY );
//collisions
bool sphereCollisions();
Sphere jumpCollision();

// Functions for collisions
bool sphereCollision (float c1x, float c1y, float c1z,float r1, float c2x, float c2y, float c2z, float r2);
bool pointToRectangularPrism(float px, float py, float pz, float rx, float ry, float rz, float rw, float rd, float rh);
bool vectorToSphere(float x1, float y1, float z1, float x2, float y2, float z2, float sphereX, float sphereY, float sphereZ, float sphereR);
void shootingCollisions(float x, float y, float z);
bool wallCollisions();



int genMaze(void);