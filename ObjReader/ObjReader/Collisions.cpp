#include <math.h>
#include <stdio.h>

bool sphereCollision (float c1x, float c1y, float c1z,float r1, float c2x, float c2y, float c2z, float r2)
{
	float distance = sqrt((c2x-c1x)*(c2x - c1x) + (c2y-c1y)*(c2y - c1y) + (c2z-c1z)*(c2z - c1z));
	float sumRadius = r1 + r2; 

	if (distance <= sumRadius)
	{
		return true;
	}else{
		return false;
	}
}

bool pointToRectangularPrism(float px, float py, float pz, float rx, float ry, float rz, float rw, float rd, float rh)
{
	if (px >= rx && px <= (rx + rw) && py >= ry && py <= (ry + rh) && pz >= rz && pz <= (rz + rd))
	{
		return true;
	}
	return false;
}

bool vectorToSphere(float x1, float y1, float z1, float x2, float y2, float z2, float sphereX, float sphereY, float sphereZ, float sphereR)
{
	float a = sqrt((sphereX-x1)*(sphereX - x1) + (sphereY-y1)*(sphereY - y1) + (sphereZ-z1)*(sphereZ - z1));
	float b = sqrt((sphereX-x2)*(sphereX - x2) + (sphereY-y2)*(sphereY - y2) + (sphereZ-z2)*(sphereZ - z2));
	float c = sqrt((x2-x1)*(x2 - x1) + (y2-y1)*(y2 - y1) + (z2-z1)*(z2 - z1));
	float p = (a + b + c)/2;
	float distance = 2*sqrt(p * (p - a) * (p - b) * (p - c))/c;
	printf("%f\n", distance);
	if (distance <= sphereR)
	{

		return true;
	}

	return false;
}
