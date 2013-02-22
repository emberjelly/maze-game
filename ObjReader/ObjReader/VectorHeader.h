#define _USE_MATH_DEFINES
#include <math.h>
class Vector
{
public:
	Vector()
	{
		m_vecX = 0;
		m_vecY = 0;
		m_vecZ = 0;
		m_rad = M_PI/180;
	}

	~Vector()
	{

	}
	
	void rotateX(float pitch)
	{
		float temp = m_vecY;
		m_vecY = m_vecY * cos(pitch * m_rad) - m_vecZ * sin(pitch * m_rad);
		m_vecZ = temp * sin(pitch * m_rad) + m_vecZ * cos(pitch * m_rad);
	}

	void rotateY (float yaw)
	{
		float temp = m_vecX;
		m_vecX = m_vecX * cos(yaw * m_rad) + m_vecZ * sin(yaw * m_rad);
		m_vecZ = -temp * sin(yaw * m_rad) + m_vecZ * cos(yaw * m_rad);
	}

	void rotateZ(float roll)
	{
		float temp = m_vecX;
		m_vecX = m_vecX * cos(roll * m_rad) - m_vecY * sin(roll * m_rad);
		m_vecY = temp * sin(roll * m_rad) + m_vecY * cos(roll * m_rad);
	}

	void rotateXYZ(float x, float y, float z, float pitch, float yaw, float roll)
	{

	}
	
	void setX(float x)
	{
		m_vecX = x;
	}
	void setY(float y)
	{
		m_vecY = y;
	}
	void setZ(float z)
	{
		m_vecZ = z;
	}
	float getX()
	{
		return m_vecX;
	}
	float getY()
	{
		return m_vecY;
	}
	float getZ()
	{
		return m_vecZ;
	}

private:
	float m_vecX;
	float m_vecY;
	float m_vecZ;
	float m_rad;
};
