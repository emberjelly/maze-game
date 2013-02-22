#include <stdio.h>
#include <string.h>

class ObjVertex3f
{
public:
	ObjVertex3f()
	{
		m_px = 0;
		m_py = 0;
		m_pz = 0;
	}
	~ObjVertex3f()
	{
	}
	float getCoordinateX()
	{
		return m_px;
	}
	float getCoordinateY()
	{
		return m_py;
	}
	float getCoordinateZ()
	{
		return m_pz;
	}

	void setCoordinateX (float xValue)
	{
		m_px = xValue;
	}

	void setCoordinateY (float yValue)
	{
		m_py = yValue;
	}

	void setCoordinateZ (float zValue)
	{
		m_pz = zValue;
	}

private:
	float m_px;
	float m_py;
	float m_pz;
};

class ObjTexture2f
{
public:
	ObjTexture2f()
	{
		m_px = 0;
		m_py = 0;
	}
	~ObjTexture2f()
	{
	}
	float getCoordinateX()
	{
		return m_px;
	}
	float getCoordinateY()
	{
		return m_py;
	}

	void setCoordinateX (float xValue)
	{
		m_px = xValue;
	}

	void setCoordinateY (float yValue)
	{
		m_py = yValue;
	}

private:
	float m_px;
	float m_py;
};

class ObjNormal3f
{
public:
	ObjNormal3f()
	{
		m_px = 0;
		m_py = 0;
		m_pz = 0;
	}
	~ObjNormal3f()
	{
	}

	float getCoordinateX()
	{
		return m_px;
	}
	float getCoordinateY()
	{
		return m_py;
	}
	float getCoordinateZ()
	{
		return m_pz;
	}

	void setCoordinateX (float xValue)
	{
		m_px = xValue;
	}

	void setCoordinateY (float yValue)
	{
		m_py = yValue;
	}

	void setCoordinateZ (float zValue)
	{
		m_pz = zValue;
	}

private:
	float m_px;
	float m_py;
	float m_pz;
};

class ObjFaces3v
{
public:
	ObjFaces3v()
	{
		m_pFace3v1 = 0;
		m_pFace3v2 = 0;
		m_pFace3v3 = 0;
	}
	~ObjFaces3v()
	{
	}

	void setFace3vValue (int v1, int v2, int v3)
	{
		m_pFace3v1 = v1;
		m_pFace3v2 = v2;
		m_pFace3v3 = v3;
	}
	
	int getFace3vValue1()
	{
		return m_pFace3v1;
	}
	int getFace3vValue2()
	{
		return m_pFace3v2;
	}
	int getFace3vValue3()
	{
		return m_pFace3v3;
	}

private:
	int m_pFace3v1;
	int m_pFace3v2;
	int m_pFace3v3;
};


class ObjFaces3vTexture
{
public:
	ObjFaces3vTexture()
	{
		m_pFace3v1Texture = 0;
		m_pFace3v2Texture = 0;
		m_pFace3v3Texture = 0;
	}
	~ObjFaces3vTexture()
	{
	}

	void setFace3vValue (int v1, int v2, int v3)
	{
		m_pFace3v1Texture = v1;
		m_pFace3v2Texture = v2;
		m_pFace3v3Texture = v3;
	}
	
	int getFace3vValue1()
	{
		return m_pFace3v1Texture;
	}
	int getFace3vValue2()
	{
		return m_pFace3v2Texture;
	}
	int getFace3vValue3()
	{
		return m_pFace3v3Texture;
	}

private:
	int m_pFace3v1Texture;
	int m_pFace3v2Texture;
	int m_pFace3v3Texture;
};


class ObjFaces3vNormal
{
public:
	ObjFaces3vNormal()
	{
		m_pNormalValue = 0;
	}
	~ObjFaces3vNormal()
	{
	}

	void set3vNormalValue (int n1)
	{
		m_pNormalValue = n1;
	}
	
	int getFace3vValue()
	{
		return m_pNormalValue;
	}

private:
	int m_pNormalValue;
};

class ObjFile
{
public:

	ObjFile()
	{
		m_ppObjFaces3v = NULL;
		m_ppVertex3f = NULL;
		m_ppNormal3f = NULL;
		m_ObjFaces3vCount = 0;
		m_vertex3fCount = 0;
		m_normal3fCount = 0;
		m_normalFace3vCount = 0;
		m_ppObjFaces3vNormal = NULL;
		m_ppObjFaces3vTexture = NULL;
		m_ppTexture2f = NULL;
		m_texture2fCount = 0;
		m_textureFace3vCount = 0;

	}
	~ObjFile()
	{
		if (m_ppObjFaces3v != NULL)
		{
			delete[] m_ppObjFaces3v;
			m_ppObjFaces3v = NULL;
		}
		if (m_ppVertex3f != NULL)
		{
			delete[] m_ppVertex3f;
			m_ppVertex3f = NULL;
		}
		if (m_ppNormal3f != NULL)
		{
			delete[] m_ppNormal3f;
			m_ppNormal3f = NULL;
		}
		if (m_ppObjFaces3vNormal != NULL)
		{
			delete[] m_ppObjFaces3vNormal;
			m_ppObjFaces3vNormal = NULL;
		}
		if (m_ppObjFaces3vTexture != NULL)
		{
			delete[] m_ppObjFaces3vTexture;
			m_ppObjFaces3vTexture = NULL;
		}
		if (m_ppTexture2f != NULL)
		{
			delete[] m_ppTexture2f;
			m_ppTexture2f = NULL;
		}
	}

	void addFace3v(int f1, int f2, int f3)
	{
		m_ObjFaces3vCount ++;
		ObjFaces3v** temp = m_ppObjFaces3v;
		m_ppObjFaces3v = new ObjFaces3v*[m_ObjFaces3vCount];
		
		for (int i = 0; i < (m_ObjFaces3vCount - 1); i ++)
		{
			m_ppObjFaces3v[i] = new ObjFaces3v();
			m_ppObjFaces3v[i] = temp[i];
		}

		m_ppObjFaces3v[m_ObjFaces3vCount - 1] = new ObjFaces3v();
		m_ppObjFaces3v[m_ObjFaces3vCount - 1]->setFace3vValue(f1, f2, f3);
		
		if (temp !=NULL)
		{
			delete[] temp;
		}
	}

	void addFace3vTexture(int t1, int t2, int t3)
	{
		m_textureFace3vCount ++;
		ObjFaces3vTexture** temp = m_ppObjFaces3vTexture;
		m_ppObjFaces3vTexture = new ObjFaces3vTexture*[m_ObjFaces3vCount];
		
		for (int i = 0; i < (m_textureFace3vCount - 1); i ++)
		{
			m_ppObjFaces3vTexture[i] = new ObjFaces3vTexture();
			m_ppObjFaces3vTexture[i] = temp[i];
		}

		m_ppObjFaces3vTexture[m_textureFace3vCount - 1] = new ObjFaces3vTexture();
		m_ppObjFaces3vTexture[m_textureFace3vCount - 1]->setFace3vValue(t1, t2, t3);
		
		if (temp !=NULL)
		{
			delete[] temp;
		}
	}
	
	void removeFace3v()
	{
	}
	

	void addFace3vNormal(int n1)
	{
		m_normalFace3vCount ++;
		ObjFaces3vNormal** temp = m_ppObjFaces3vNormal;
		m_ppObjFaces3vNormal = new ObjFaces3vNormal*[m_normalFace3vCount];
		
		for (int i = 0; i < (m_normalFace3vCount - 1); i ++)
		{
			m_ppObjFaces3vNormal[i] = new ObjFaces3vNormal();
			m_ppObjFaces3vNormal[i] = temp[i];
		}

		m_ppObjFaces3vNormal[m_normalFace3vCount - 1] = new ObjFaces3vNormal();
		m_ppObjFaces3vNormal[m_normalFace3vCount - 1]->set3vNormalValue(n1);
		
		if (temp !=NULL)
		{
			delete[] temp;
		}
	}

	ObjFaces3v* getFace3v(int num)
	{
		return m_ppObjFaces3v[num];
	}

	int getFace3vCount()
	{
		return m_ObjFaces3vCount;
	}

	
	ObjFaces3vNormal* getFace3vNormal(int num)
	{
		return m_ppObjFaces3vNormal[num];
	}

	int getFace3vNormalCount()
	{
		return m_normalFace3vCount;
	}

	ObjFaces3vTexture* getFace3vTexture(int num)
	{
		return m_ppObjFaces3vTexture[num];
	}

	int getFace3vTextureCount()
	{
		return m_textureFace3vCount;
	}


	void addVertex(float vX, float vY, float vZ)
	{
		m_vertex3fCount ++;
		ObjVertex3f** m_ppTemp = m_ppVertex3f;
		m_ppVertex3f = new ObjVertex3f*[m_vertex3fCount];
		for (int i = 0; i < (m_vertex3fCount - 1); i ++)
		{
			m_ppVertex3f[i] = new ObjVertex3f();
			*m_ppVertex3f[i] = *m_ppTemp[i];
		}

		m_ppVertex3f[m_vertex3fCount - 1] = new ObjVertex3f();
		m_ppVertex3f[m_vertex3fCount - 1]->setCoordinateX(vX);
		m_ppVertex3f[m_vertex3fCount - 1]->setCoordinateY(vY);
		m_ppVertex3f[m_vertex3fCount - 1]->setCoordinateZ(vZ);
		
		if (m_ppTemp !=NULL)
		{
			delete[] m_ppTemp;
		}
	}
	ObjVertex3f* getVertexValues (int vertexNum)
	{
		return m_ppVertex3f[vertexNum];
	}

void addNormal(float nX, float nY, float nZ)
	{
		m_normal3fCount ++;
		ObjNormal3f** m_ppTemp = m_ppNormal3f;
		m_ppNormal3f = new ObjNormal3f*[m_normal3fCount];
		for (int i = 0; i < (m_normal3fCount - 1); i ++)
		{
			m_ppNormal3f[i] = new ObjNormal3f();
			*m_ppNormal3f[i] = *m_ppTemp[i];
		}

		m_ppNormal3f[m_normal3fCount - 1] = new ObjNormal3f();
		m_ppNormal3f[m_normal3fCount - 1]->setCoordinateX(nX);
		m_ppNormal3f[m_normal3fCount - 1]->setCoordinateY(nY);
		m_ppNormal3f[m_normal3fCount - 1]->setCoordinateZ(nZ);
		
		if (m_ppTemp !=NULL)
		{
			delete[] m_ppTemp;
		}
	}
	
	ObjNormal3f* getNormalValues (int vertexNum)
	{
		return m_ppNormal3f[vertexNum];
	}

void addTexture(float tX, float tY)
	{
		m_texture2fCount ++;
		ObjTexture2f** m_ppTemp = m_ppTexture2f;
		m_ppTexture2f = new ObjTexture2f*[m_texture2fCount];
		for (int i = 0; i < (m_texture2fCount - 1); i ++)
		{
			m_ppTexture2f[i] = new ObjTexture2f();
			*m_ppTexture2f[i] = *m_ppTemp[i];
		}

		m_ppTexture2f[m_texture2fCount - 1] = new ObjTexture2f();
		m_ppTexture2f[m_texture2fCount - 1]->setCoordinateX(tX);
		m_ppTexture2f[m_texture2fCount - 1]->setCoordinateY(tY);
		
		if (m_ppTemp !=NULL)
		{
			delete[] m_ppTemp;
		}
	}
	
	ObjTexture2f* getTextureValues (int vertexNum)
	{
		return m_ppTexture2f[vertexNum];
	}


private:
ObjFaces3v** m_ppObjFaces3v;
ObjFaces3vNormal** m_ppObjFaces3vNormal;
ObjFaces3vTexture** m_ppObjFaces3vTexture;

ObjVertex3f** m_ppVertex3f;
ObjNormal3f** m_ppNormal3f;
ObjTexture2f** m_ppTexture2f;

int m_ObjFaces3vCount;
int m_vertex3fCount;
int m_normal3fCount;
int m_normalFace3vCount;
int m_textureFace3vCount;
int m_texture2fCount;
};

ObjFile* loadObj (char* objAddress);

// Functions required for drawing 3d models in glut


void drawObjTRIANGLES(ObjFile* inObjFile, float positionX, float positionY, float positionZ, float pitch, float yaw, float roll);

//Functions for textures in glut
#include <glut.h>
GLuint LoadTexture( const char * filename );




