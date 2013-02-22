#include "ObjHeader.h"
#include <fstream>
#include <string>


ObjFile* loadObj (char* objAddress)
{
	ObjFile* loadObjFile = new ObjFile();
	ObjFaces3v* faces3vAddress;
	FILE* newObjFile = new FILE();
	newObjFile = fopen(objAddress, "rt");

	float x; float y; float z;
	int f1; int f2; int f3;
	int n1; int n2; int n3;
	int t1; int t2; int t3;
	int numberOfV = 0;
	int numberOfN = 0;
	int numberOfT = 0;
	int faceNum = 0;
	int normalNum = 0;
	int nextChar;
	
	if (!newObjFile)
	{
		printf("File does not exist");
	}else{
		do
		{
			nextChar = fgetc(newObjFile);
			if (nextChar == 'f')
			{
				nextChar = fgetc(newObjFile);
				if (nextChar == ' ')
				{
					fscanf(newObjFile, "%d", &f1);
					nextChar = fgetc(newObjFile);
					fscanf(newObjFile, "%d", &t1);
					nextChar = fgetc(newObjFile);
					fscanf(newObjFile, "%d", &n1);
					nextChar = fgetc(newObjFile);
					fscanf(newObjFile, "%d", &f2);
					nextChar = fgetc(newObjFile);
					fscanf(newObjFile, "%d", &t2);
					nextChar = fgetc(newObjFile);
					fscanf(newObjFile, "%d", &n2);
					nextChar = fgetc(newObjFile);
					fscanf(newObjFile, "%d", &f3);
					nextChar = fgetc(newObjFile);
					fscanf(newObjFile, "%d", &t3);
					nextChar = fgetc(newObjFile);
					fscanf(newObjFile, "%d", &n3);
			
					loadObjFile->addFace3v(f1, f2, f3);
					loadObjFile->addFace3vTexture(t1, t2, t3);
					loadObjFile->addFace3vNormal(n1);
					faceNum ++;
					printf("Face %d: %d %d %d\n", faceNum, f1, f2, f3);
					//printf("Normals: %d\n", n1);
				}
			}
		}while(nextChar != EOF);
		rewind(newObjFile);
		do
		{
			nextChar = fgetc(newObjFile);
			if (nextChar == 'v')
			{
				nextChar = fgetc(newObjFile);
				if (nextChar == ' ')
				{
					fscanf(newObjFile, "%f", &x);
					fscanf(newObjFile, "%f", &y);
					fscanf(newObjFile, "%f", &z);
					numberOfV ++;
					loadObjFile->addVertex(x, y, z);
				}
			
				if (nextChar == 'n')
				{
					nextChar = fgetc(newObjFile);
					if (nextChar == ' ')
					{
						fscanf(newObjFile, "%f", &x);
						fscanf(newObjFile, "%f", &y);
						fscanf(newObjFile, "%f", &z);
						//printf ("%f %f %f\n", x, y, z);
						numberOfN ++;
						loadObjFile->addNormal(x, y, z);
					}
				}
				if (nextChar == 't')
				{
					nextChar = fgetc(newObjFile);
					if (nextChar == ' ')
					{
						fscanf(newObjFile, "%f", &x);
						fscanf(newObjFile, "%f", &y);
						//printf ("%f %f %f\n", x, y, z);
						numberOfT ++;
						loadObjFile->addTexture(x, y);
					}
				}
			}
		}while(nextChar != EOF);
	}
	fclose(newObjFile);
	return loadObjFile;
}

