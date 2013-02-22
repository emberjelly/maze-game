#include "playerStats.h"
extern SphereManager* mySphereManager;
extern Sphere* mySpheres;
extern recPrism* fence;
extern RecPrismManager* fenceManager;
extern RecPrismManager* mazeWallManager;
extern recPrism* mazeWall;

extern playerDetails player;

bool sphereCollisions()
{
	/*
	for (int i = 0; i < mySphereManager->getSphereNum(); i ++)
	{
		mySpheres = mySphereManager->getSphere(i);
		bool collision = false;
		
		collision = sphereCollision(player.playerX, 0, player.playerZ, 1.0f, mySpheres->getX() ,0, mySpheres->getZ(), mySpheres->getR());
		if (collision)
		{
			printf("hit");
			return true;
		}

	}*/
	return false;
}

bool wallCollisions()
{
	for (int i = 0; i < fenceManager->getRecNum(); i ++)
	{
		fence = fenceManager->getRecPrism(i);
		bool collision = false;
		
		collision = pointToRectangularPrism(player.playerX, -player.playerY*3.5, player.playerZ, fence->getX(), fence->getY(), fence->getZ(), fence->getW(), fence->getD(), fence->getH());
		if (collision)
		{
			printf("hit");
			return true;
		}
	}
	for (int i = 0; i < mazeWallManager->getRecNum(); i ++)
	{
		mazeWall = mazeWallManager->getRecPrism(i);
		bool collision = false;
		
		collision = pointToRectangularPrism(player.playerX + 1, 0, player.playerZ, mazeWall->getX(), 0, mazeWall->getZ(), mazeWall->getW(), mazeWall->getD(), mazeWall->getH());
		if (collision)
		{
			printf("hit");
			return true;
		}
		collision = pointToRectangularPrism(player.playerX - 1, 0, player.playerZ, mazeWall->getX(), 0, mazeWall->getZ(), mazeWall->getW(), mazeWall->getD(), mazeWall->getH());
		if (collision)
		{
			printf("hit");
			return true;
		}
		collision = pointToRectangularPrism(player.playerX, 0, player.playerZ + 1, mazeWall->getX(), 0, mazeWall->getZ(), mazeWall->getW(), mazeWall->getD(), mazeWall->getH());
		if (collision)
		{
			printf("hit");
			return true;
		}
		collision = pointToRectangularPrism(player.playerX, 0, player.playerZ - 1, mazeWall->getX(), 0, mazeWall->getZ(), mazeWall->getW(), mazeWall->getD(), mazeWall->getH());
		if (collision)
		{
			printf("hit");
			return true;
		}
	}

	return false;
}

Sphere jumpCollision()
{
	for (int i = 0; i < mySphereManager->getSphereNum(); i ++)
	{
		bool collision = false;
		mySpheres = mySphereManager->getSphere(i);
		mySpheres->setCollisionStatus(false);
		
		collision = sphereCollision(player.playerX, -player.playerY + 1, player.playerZ, 0.5, mySpheres->getX() , mySpheres->getY(), mySpheres->getZ(), mySpheres->getR());
		if (collision)
		{
			mySpheres->setCollisionStatus(true);
			printf("hit");
			return *mySpheres;
		}
		collision = sphereCollision(player.playerX, -player.playerY + 3, player.playerZ, 1.0, mySpheres->getX() , mySpheres->getY(), mySpheres->getZ(), mySpheres->getR());
		if (collision)
		{
			mySpheres->setCollisionStatus(true);
			printf("hit");
			return *mySpheres;
		}
	}
	return *mySpheres;
}

void shootingCollisions(float x, float y, float z)
{
	for (int i = 0; i < mySphereManager->getSphereNum(); i ++)
	{
		mySpheres = mySphereManager->getSphere(i);
		bool testHit = vectorToSphere(player.playerX, -player.playerY + player.playerHeight,  player.playerZ, x + player.playerX,  -y - player.playerY + player.playerHeight,  z + player.playerZ,  mySpheres->getX(), mySpheres->getY(), mySpheres->getZ(), mySpheres->getR());
		if (testHit)
		{
  			mySphereManager->deleteSphere(i);
			return;
		}
	}

}

