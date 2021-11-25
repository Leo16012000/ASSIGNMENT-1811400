/*
* 	Bai tap lon Do Hoa May Tinh
*	So dinh tren hinh tron: 36
*	Ten: 	Dang Tuan Anh
* 	MSSV:	1811400
* 	Lop:	L01
*/

#include <math.h>
#include <iostream>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <cmath>

#define PI 3.14159265358979323846
#define COLORNUM 14
#define NUM 36

using namespace std;

// supportClass
#pragma region
class Point3
{
public:
	float x, y, z;
	void set(float dx, float dy, float dz)
	{
		x = dx;
		y = dy;
		z = dz;
	}
	void set(Point3& p)
	{
		x = p.x;
		y = p.y;
		z = p.z;
	}
	Point3() { x = y = z = 0; }
	Point3(float dx, float dy, float dz)
	{
		x = dx;
		y = dy;
		z = dz;
	}
};
class Color3
{
public:
	float r, g, b;
	void set(float red, float green, float blue)
	{
		r = red;
		g = green;
		b = blue;
	}
	void set(Color3& c)
	{
		r = c.r;
		g = c.g;
		b = c.b;
	}
	Color3() { r = g = b = 0; }
	Color3(float red, float green, float blue)
	{
		r = red;
		g = green;
		b = blue;
	}
};
class Point2
{
public:
	Point2() { x = y = 0.0f; } // constructor 1
	Point2(float xx, float yy)
	{
		x = xx;
		y = yy;
	} // constructor 2
	void set(float xx, float yy)
	{
		x = xx;
		y = yy;
	}
	float getX() { return x; }
	float getY() { return y; }
	void draw()
	{
		glBegin(GL_POINTS);
		glVertex2f((GLfloat)x, (GLfloat)y);
		glEnd();
	}

private:
	float x, y;
};
class IntRect
{
public:
	IntRect()
	{
		l = 0;
		r = 100;
		b = 0;
		t = 100;
	} // constructor
	IntRect(int left, int right, int bottom, int top)
	{
		l = left;
		r = right;
		b = bottom;
		t = top;
	}
	void set(int left, int right, int bottom, int top)
	{
		l = left;
		r = right;
		b = bottom;
		t = top;
	}
	void draw()
	{
		glRecti(l, b, r, t);
		glFlush();
	} // draw this rectangle using OpenGL
	int getWidth() { return (r - l); }
	int getHeight() { return (t - b); }

private:
	int l, r, b, t;
};

class RealRect
{
public:
	RealRect()
	{
		l = 0;
		r = 100;
		b = 0;
		t = 100;
	} // constructor
	RealRect(float left, float right, float bottom, float top)
	{
		l = left;
		r = right;
		b = bottom;
		t = top;
	}
	void set(float left, float right, float bottom, float top)
	{
		l = left;
		r = right;
		b = bottom;
		t = top;
	}
	float getWidth() { return (r - l); }
	float getHeight() { return (t - b); }
	void draw()
	{
		glRectf(l, b, r, t);
		glFlush();
	}; // draw this rectangle using OpenGL
private:
	float l, r, b, t;
};

class Vector3
{
public:
	float x, y, z;
	void set(float dx, float dy, float dz)
	{
		x = dx;
		y = dy;
		z = dz;
	}
	void set(Vector3& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
	}
	void flip()
	{
		x = -x;
		y = -y;
		z = -z;
	}
	void normalize();
	Vector3() { x = y = z = 0; }
	Vector3(float dx, float dy, float dz)
	{
		x = dx;
		y = dy;
		z = dz;
	}
	Vector3(Vector3& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
	}
	Vector3 cross(Vector3 b);
	float dot(Vector3 b);
};

Vector3 Vector3::cross(Vector3 b)
{
	Vector3 c(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
	return c;
}
float Vector3::dot(Vector3 b)
{
	return x * b.x + y * b.y + z * b.z;
}
void Vector3::normalize()
{
	float temp = sqrt(x * x + y * y + z * z);
	x = x / temp;
	y = y / temp;
	z = z / temp;
}
#pragma endregion

// Mesh
#pragma region
class VertexID
{
public:
	int vertIndex;
	int colorIndex;
};

class Face
{
public:
	int nVerts;
	VertexID* vert;

	Vector3 facenorm; // Chứa pháp tuyến của mặt.

	Face()
	{
		nVerts = 0;
		vert = NULL;
	}
	~Face()
	{
		if (vert != NULL)
		{
			delete[] vert;
			vert = NULL;
		}
		nVerts = 0;
	}
};

class Mesh
{
public:
	int numVerts;
	Point3* pt;

	int numFaces;
	Face* face;

	float slideX, slideY, slideZ;
	float rotateX, rotateY, rotateZ;
	float scaleX, scaleY, scaleZ;

public:
	Mesh()
	{
		numVerts = 0;
		pt = NULL;
		numFaces = 0;
		face = NULL;
		//
		slideX = 0;
		slideY = 0;
		slideZ = 0;
		rotateX = 0;
		rotateY = 0;
		rotateZ = 0;
		scaleX = 0;
		scaleY = 0;
		scaleZ = 0;
	}
	~Mesh()
	{
		if (pt != NULL)
		{
			delete[] pt;
		}
		if (face != NULL)
		{
			delete[] face;
		}
		numVerts = 0;
		numFaces = 0;
	}

	void DrawWireframe();
	void DrawColor();
	void SetColor(int colorIdx);
	//// Lab 2
	void CreateTetrahedron();
	void CreateCube(float	fSize);
	void CreateCuboid(float fSizeX, float fSizeY, float fSizeZ);
	void CreateCylinder(int N, float base1Height, float base1Radius);

	void BTCuboid(float fSizeX, float fSizeY, float fSizeZ);
	// Lab 5
	void CalculateFacesNorm();
	void Draw();
	void setupMaterial(float ambient[], float diffuse[], float specular[], float shiness);
};

float ColorArr[COLORNUM][3] = {
	{1.0, 0.0, 0.0}, //0
	{0.0, 1.0, 0.0}, //1
	{0.0, 0.0, 1.0}, //2
	{1.0, 1.0, 0.0}, //3
	{1.0, 0.0, 1.0}, //4
	{0.0, 1.0, 1.0}, //5
	{0.3, 0.3, 0.3}, //6
	{0.5, 0.5, 0.5}, //7
	{0.9, 0.9, 0.9}, //8
	{1.0, 0.5, 0.5}, //9
	{0.5, 1.0, 0.5}, //10
	{0.5, 0.5, 1.0}, //11
	{0.0, 0.0, 0.0}, //12
	{1.0, 1.0, 1.0} }; //13

void Mesh::DrawWireframe()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int iv = face[f].vert[v].vertIndex;

			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}

// To mau cho doi tuong (Lab 5)
void Mesh::Draw()
{
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int iv = face[f].vert[v].vertIndex;
			glNormal3f(face[f].facenorm.x, face[f].facenorm.y, face[f].facenorm.z);
			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}

void Mesh::DrawColor()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int iv = face[f].vert[v].vertIndex;
			int ic = face[f].vert[v].colorIndex;

			// Bật nên: mỗi mặt một màu
			// ic = f % COLORNUM;

			glColor3f(ColorArr[ic][0], ColorArr[ic][1], ColorArr[ic][2]);
			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}

void Mesh::SetColor(int colorIdx)
{
	for (int f = 0; f < numFaces; f++)
	{
		for (int v = 0; v < face[f].nVerts; v++)
		{
			face[f].vert[v].colorIndex = colorIdx;
		}
	}
}

// Tìm vector pháp tuyến theo phương pháp Newell
void Mesh::CalculateFacesNorm()
{
	for (int f = 0; f < numFaces; f++)
	{
		float mx = 0, my = 0, mz = 0;
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int iv = face[f].vert[v].vertIndex;
			int next = face[f].vert[(v + 1) % face[f].nVerts].vertIndex;
			mx += (pt[iv].y - pt[next].y) * (pt[iv].z + pt[next].z);
			my += (pt[iv].z - pt[next].z) * (pt[iv].x + pt[next].x);
			mz += (pt[iv].x - pt[next].x) * (pt[iv].y + pt[next].y);
		}
		face[f].facenorm.set(mx, my, mz);
		face[f].facenorm.normalize();
	}
}

// Thiet lap vat lieu cho doi tuong (Lab 5)
void Mesh::setupMaterial(float ambient[], float diffuse[], float specular[], float shiness)
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiness);
}

// Hinh lap phuong
void Mesh::CreateCube(float fSize)
{
	int i;

	numVerts = 8;
	pt = new Point3[numVerts];
	pt[0].set(-fSize, fSize, fSize);
	pt[1].set(fSize, fSize, fSize);
	pt[2].set(fSize, fSize, -fSize);
	pt[3].set(-fSize, fSize, -fSize);
	pt[4].set(-fSize, -fSize, fSize);
	pt[5].set(fSize, -fSize, fSize);
	pt[6].set(fSize, -fSize, -fSize);
	pt[7].set(-fSize, -fSize, -fSize);

	numFaces = 6;
	face = new Face[numFaces];

	//Left face
	face[0].nVerts = 4;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 1;
	face[0].vert[1].vertIndex = 5;
	face[0].vert[2].vertIndex = 6;
	face[0].vert[3].vertIndex = 2;
	for (i = 0; i < face[0].nVerts; i++)
		face[0].vert[i].colorIndex = 0;

	//Right face
	face[1].nVerts = 4;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;
	face[1].vert[1].vertIndex = 3;
	face[1].vert[2].vertIndex = 7;
	face[1].vert[3].vertIndex = 4;
	for (i = 0; i < face[1].nVerts; i++)
		face[1].vert[i].colorIndex = 1;

	//top face
	face[2].nVerts = 4;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 1;
	face[2].vert[2].vertIndex = 2;
	face[2].vert[3].vertIndex = 3;
	for (i = 0; i < face[2].nVerts; i++)
		face[2].vert[i].colorIndex = 2;

	//bottom face
	face[3].nVerts = 4;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 7;
	face[3].vert[1].vertIndex = 6;
	face[3].vert[2].vertIndex = 5;
	face[3].vert[3].vertIndex = 4;
	for (i = 0; i < face[3].nVerts; i++)
		face[3].vert[i].colorIndex = 3;

	//near face
	face[4].nVerts = 4;
	face[4].vert = new VertexID[face[4].nVerts];
	face[4].vert[0].vertIndex = 4;
	face[4].vert[1].vertIndex = 5;
	face[4].vert[2].vertIndex = 1;
	face[4].vert[3].vertIndex = 0;
	for (i = 0; i < face[4].nVerts; i++)
		face[4].vert[i].colorIndex = 4;

	//Far face
	face[5].nVerts = 4;
	face[5].vert = new VertexID[face[5].nVerts];
	face[5].vert[0].vertIndex = 3;
	face[5].vert[1].vertIndex = 2;
	face[5].vert[2].vertIndex = 6;
	face[5].vert[3].vertIndex = 7;
	for (i = 0; i < face[5].nVerts; i++)
		face[5].vert[i].colorIndex = 5;
}

// Hinh hop chu nhat
void Mesh::CreateCuboid(float fSizeX, float fSizeY, float fSizeZ)
{
	int i;
	numVerts = 8;
	pt = new Point3[numVerts];

	pt[0].set(-fSizeX / 2, -fSizeY / 2, -fSizeZ / 2);
	pt[1].set(fSizeX / 2, -fSizeY / 2, -fSizeZ / 2);
	pt[2].set(fSizeX / 2, fSizeY / 2, -fSizeZ / 2);
	pt[3].set(-fSizeX / 2, fSizeY / 2, -fSizeZ / 2);
	pt[4].set(-fSizeX / 2, -fSizeY / 2, fSizeZ / 2);
	pt[5].set(fSizeX / 2, -fSizeY / 2, fSizeZ / 2);
	pt[6].set(fSizeX / 2, fSizeY / 2, fSizeZ / 2);
	pt[7].set(-fSizeX / 2, fSizeY / 2, fSizeZ / 2);

	numFaces = 6;
	face = new Face[numFaces];

	face[0].nVerts = 4;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 0;
	face[0].vert[1].vertIndex = 4;
	face[0].vert[2].vertIndex = 7;
	face[0].vert[3].vertIndex = 3;
	for (i = 0; i < face[0].nVerts; i++)
		face[0].vert[i].colorIndex = 0;

	face[1].nVerts = 4;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 3;
	face[1].vert[1].vertIndex = 7;
	face[1].vert[2].vertIndex = 6;
	face[1].vert[3].vertIndex = 2;
	for (i = 0; i < face[1].nVerts; i++)
		face[1].vert[i].colorIndex = 1;

	face[2].nVerts = 4;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 1;
	face[2].vert[1].vertIndex = 2;
	face[2].vert[2].vertIndex = 6;
	face[2].vert[3].vertIndex = 5;
	for (i = 0; i < face[2].nVerts; i++)
		face[2].vert[i].colorIndex = 2;

	face[3].nVerts = 4;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 0;
	face[3].vert[1].vertIndex = 1;
	face[3].vert[2].vertIndex = 5;
	face[3].vert[3].vertIndex = 4;
	for (i = 0; i < face[3].nVerts; i++)
		face[3].vert[i].colorIndex = 3;

	face[4].nVerts = 4;
	face[4].vert = new VertexID[face[4].nVerts];
	face[4].vert[0].vertIndex = 6;
	face[4].vert[1].vertIndex = 7;
	face[4].vert[2].vertIndex = 4;
	face[4].vert[3].vertIndex = 5;
	for (i = 0; i < face[4].nVerts; i++)
		face[4].vert[i].colorIndex = 4;

	face[5].nVerts = 4;
	face[5].vert = new VertexID[face[5].nVerts];
	face[5].vert[0].vertIndex = 2;
	face[5].vert[1].vertIndex = 1;
	face[5].vert[2].vertIndex = 0;
	face[5].vert[3].vertIndex = 3;
	for (i = 0; i < face[5].nVerts; i++)
		face[5].vert[i].colorIndex = 5;
}

// Hinh tu dien
void Mesh::CreateTetrahedron()
{
	int i;
	numVerts = 4;
	pt = new Point3[numVerts];
	pt[0].set(0, 0, 0);
	pt[1].set(1, 0, 0);
	pt[2].set(0, 1, 0);
	pt[3].set(0, 0, 1);

	numFaces = 4;
	face = new Face[numFaces];

	face[0].nVerts = 3;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 1;
	face[0].vert[1].vertIndex = 2;
	face[0].vert[2].vertIndex = 3;
	for (i = 0; i < face[0].nVerts; i++)
		face[0].vert[i].colorIndex = 0;

	face[1].nVerts = 3;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;
	face[1].vert[1].vertIndex = 2;
	face[1].vert[2].vertIndex = 1;
	for (i = 0; i < face[1].nVerts; i++)
		face[1].vert[i].colorIndex = 1;

	face[2].nVerts = 3;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 3;
	face[2].vert[2].vertIndex = 2;
	for (i = 0; i < face[2].nVerts; i++)
		face[2].vert[i].colorIndex = 2;

	face[3].nVerts = 3;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 1;
	face[3].vert[1].vertIndex = 3;
	face[3].vert[2].vertIndex = 0;
	for (i = 0; i < face[3].nVerts; i++)
		face[3].vert[i].colorIndex = 3;
}

// Hinh hop chu nhat cat goc
void Mesh::BTCuboid(float fSizeX, float fSizeY, float fSizeZ)
{
	float fSizeT = fSizeY/4.0;
	int i;
	numVerts = 24;
	pt = new Point3[numVerts];

	pt[0].set(-fSizeX / 2, -fSizeY / 2, -fSizeZ / 2); //0
	pt[1].set(fSizeX / 2, -fSizeY / 2, -fSizeZ / 2); //1
	pt[2].set(fSizeX / 2, fSizeY / 2, -fSizeZ / 2); //2
	pt[3].set(-fSizeX / 2, fSizeY / 2, -fSizeZ / 2); //3
	pt[4].set(-fSizeX / 2, -fSizeY / 2, fSizeZ / 2); //4
	pt[5].set(fSizeX / 2, -fSizeY / 2, fSizeZ / 2); //5
	pt[6].set(fSizeX / 2, fSizeY / 2, fSizeZ / 2); //6
	pt[7].set(-fSizeX / 2, fSizeY / 2, fSizeZ / 2); //7

	pt[8].set(-fSizeX / 2, -fSizeY / 2, -fSizeZ / 2 + fSizeT); //0
	pt[9].set(-fSizeX / 2, -fSizeY / 2 + fSizeT, -fSizeZ / 2); //0
	pt[10].set(fSizeX / 2, -fSizeY / 2, -fSizeZ / 2 + fSizeT); //1
	pt[11].set(fSizeX / 2, -fSizeY / 2 + fSizeT, -fSizeZ / 2); //1

	pt[12].set(fSizeX / 2, fSizeY / 2 - fSizeT, -fSizeZ / 2); //2
	pt[13].set(fSizeX / 2, fSizeY / 2, -fSizeZ / 2 + fSizeT); //2
	pt[14].set(-fSizeX / 2, fSizeY / 2 - fSizeT, -fSizeZ / 2); //3
	pt[15].set(-fSizeX / 2, fSizeY / 2, -fSizeZ / 2 + fSizeT); //3

	pt[16].set(-fSizeX / 2, -fSizeY / 2 + fSizeT, fSizeZ / 2); //4
	pt[17].set(-fSizeX / 2, -fSizeY / 2, fSizeZ / 2 - fSizeT); //4
	pt[18].set(fSizeX / 2, -fSizeY / 2 + fSizeT, fSizeZ / 2); //5
	pt[19].set(fSizeX / 2, -fSizeY / 2, fSizeZ / 2 - fSizeT); //5

	pt[20].set(fSizeX / 2, fSizeY / 2, fSizeZ / 2 - fSizeT); //6
	pt[21].set(fSizeX / 2, fSizeY / 2 - fSizeT, fSizeZ / 2); //6
	pt[22].set(-fSizeX / 2, fSizeY / 2, fSizeZ / 2 - fSizeT); //7
	pt[23].set(-fSizeX / 2, fSizeY / 2 - fSizeT, fSizeZ / 2); //7
	numFaces = 10;
	face = new Face[numFaces];

	face[0].nVerts = 4;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 8;
	face[0].vert[1].vertIndex = 9;
	face[0].vert[2].vertIndex = 11;
	face[0].vert[3].vertIndex = 10;
	for (i = 0; i < face[0].nVerts; i++)
		face[0].vert[i].colorIndex = 0;

	face[1].nVerts = 4;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 12;
	face[1].vert[1].vertIndex = 13;
	face[1].vert[2].vertIndex = 15;
	face[1].vert[3].vertIndex = 14;
	for (i = 0; i < face[1].nVerts; i++)
		face[1].vert[i].colorIndex = 1;

	face[2].nVerts = 4;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 16;
	face[2].vert[1].vertIndex = 17;
	face[2].vert[2].vertIndex = 19;
	face[2].vert[3].vertIndex = 18;
	for (i = 0; i < face[2].nVerts; i++)
		face[2].vert[i].colorIndex = 2;

	face[3].nVerts = 4;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 20;
	face[3].vert[1].vertIndex = 21;
	face[3].vert[2].vertIndex = 23;
	face[3].vert[3].vertIndex = 22;
	for (i = 0; i < face[3].nVerts; i++)
		face[3].vert[i].colorIndex = 3;

	face[4].nVerts = 4;
	face[4].vert = new VertexID[face[4].nVerts];
	face[4].vert[0].vertIndex = 9;
	face[4].vert[1].vertIndex = 14;
	face[4].vert[2].vertIndex = 12;
	face[4].vert[3].vertIndex = 11;
	for (i = 0; i < face[4].nVerts; i++)
		face[4].vert[i].colorIndex = 3;

	face[5].nVerts = 4;
	face[5].vert = new VertexID[face[5].nVerts];
	face[5].vert[0].vertIndex = 8;
	face[5].vert[1].vertIndex = 17;
	face[5].vert[2].vertIndex = 19;
	face[5].vert[3].vertIndex = 10;
	for (i = 0; i < face[5].nVerts; i++)
		face[5].vert[i].colorIndex = 3;

	face[6].nVerts = 4;
	face[6].vert = new VertexID[face[6].nVerts];
	face[6].vert[0].vertIndex = 16;
	face[6].vert[1].vertIndex = 23;
	face[6].vert[2].vertIndex = 21;
	face[6].vert[3].vertIndex = 18;
	for (i = 0; i < face[6].nVerts; i++)
		face[6].vert[i].colorIndex = 3;

	face[7].nVerts = 4;
	face[7].vert = new VertexID[face[7].nVerts];
	face[7].vert[0].vertIndex = 22;
	face[7].vert[1].vertIndex = 15;
	face[7].vert[2].vertIndex = 13;
	face[7].vert[3].vertIndex = 20;
	for (i = 0; i < face[7].nVerts; i++)
		face[7].vert[i].colorIndex = 3;

	face[8].nVerts = 8;
	face[8].vert = new VertexID[face[8].nVerts];
	face[8].vert[0].vertIndex = 9;
	face[8].vert[1].vertIndex = 8;
	face[8].vert[2].vertIndex = 17;
	face[8].vert[3].vertIndex = 16;
	face[8].vert[4].vertIndex = 23;
	face[8].vert[5].vertIndex = 22;
	face[8].vert[6].vertIndex = 15;
	face[8].vert[7].vertIndex = 14;
	for (i = 0; i < face[4].nVerts; i++)
		face[4].vert[i].colorIndex = 3;

	face[9].nVerts = 8;
	face[9].vert = new VertexID[face[9].nVerts];
	face[9].vert[0].vertIndex = 11;
	face[9].vert[1].vertIndex = 10;
	face[9].vert[2].vertIndex = 19;
	face[9].vert[3].vertIndex = 18;
	face[9].vert[4].vertIndex = 21;
	face[9].vert[5].vertIndex = 20;
	face[9].vert[6].vertIndex = 13;
	face[9].vert[7].vertIndex = 12;
	for (i = 0; i < face[5].nVerts; i++)
		face[5].vert[i].colorIndex = 3;
}
void Mesh::CreateCylinder(int N, float base1Height, float base1Radius)
{
	/*
	* N: Số đỉnh trên hình tròn
	* base1Height: Chiều cao của hình trụ
	* base1Radius: bán kính của hình tròn
	*/
	int i;
	numVerts = 2 * N + 2;
	GLfloat angle = 2 * PI / N;
	pt = new Point3[numVerts];
	// Vong tron tren: [0, N - 1]
	for (i = 0; i < N; i++)
	{
		pt[i].set(base1Radius * sin((double)i * angle), base1Height / 2, -base1Radius * cos((double)i * angle));
	}
	// Vong tron duoi: [N, 2 * N - 1]
	for (i = 0; i < N; i++)
	{
		pt[i + N].set(base1Radius * sin((double)i * angle), -base1Height / 2, -base1Radius * cos((double)i * angle));
	}

	pt[2 * N].set(0, base1Height / 2, 0);
	pt[2 * N + 1].set(0, -base1Height / 2, 0);

	numFaces = 3 * N;
	face = new Face[numFaces];

	for (i = 0; i < numFaces; i++)
	{
		if (i < N - 1)
		{
			face[i].nVerts = 3;
			face[i].vert = new VertexID[face[i].nVerts];

			face[i].vert[0].vertIndex = i;
			face[i].vert[1].vertIndex = i + 1;
			face[i].vert[2].vertIndex = 2 * N;
		}
		else if (i == N - 1)
		{
			face[i].nVerts = 3;
			face[i].vert = new VertexID[face[i].nVerts];

			face[i].vert[0].vertIndex = i;
			face[i].vert[1].vertIndex = 0;
			face[i].vert[2].vertIndex = 2 * N;
		}
		else if (i < 2 * N - 1)
		{
			face[i].nVerts = 3;
			face[i].vert = new VertexID[face[i].nVerts];

			face[i].vert[0].vertIndex = i;
			face[i].vert[1].vertIndex = 2 * N + 1;
			face[i].vert[2].vertIndex = i + 1;
		}
		else if (i == 2 * N - 1)
		{
			face[i].nVerts = 3;
			face[i].vert = new VertexID[face[i].nVerts];

			face[i].vert[0].vertIndex = i;
			face[i].vert[1].vertIndex = 2 * N + 1;
			face[i].vert[2].vertIndex = N;
		}
		else if (i < 3 * N - 1)
		{
			face[i].nVerts = 4;
			face[i].vert = new VertexID[face[i].nVerts];

			face[i].vert[0].vertIndex = i - 2 * N + 1;
			face[i].vert[1].vertIndex = i - 2 * N;
			face[i].vert[2].vertIndex = i - N;
			face[i].vert[3].vertIndex = i - N + 1;
		}
		else
		{
			face[i].nVerts = 4;
			face[i].vert = new VertexID[face[i].nVerts];

			face[i].vert[0].vertIndex = 0;
			face[i].vert[1].vertIndex = N - 1;
			face[i].vert[2].vertIndex = 2 * N - 1;
			face[i].vert[3].vertIndex = N;
		}
		for (int j = 0; j < face[i].nVerts; j++)
			face[i].vert[j].colorIndex = i;
	}
}

// Tham so
#pragma region
// Truc tren
float trucX = 2;
float trucY = 0.2;
float trucZ = 0.2;

// Truc duoi
float base1Radius = 0.2;
float base1Height = 0.8;
//---------------------------------
// Tham so cua cua so
int screenWidth = 600;
int screenHeight = 600;

//float base2Radius = 0.6;
//float base2Height = 1.2;
//
//float cylinderRadius = 0.4;
//float cylinderHeight = 1.6;
//float cylinderRotateStep = 5;
//float cylinderTranslationStep = 0.05;
//float cylinderOffset = base2Height / 2;
//float	cylinderOffset = base2Height-cylinderHeight/2;



Mesh trucTren;
Mesh trucDuoi;

double angle = 0;

bool au = false;
bool bWireFrame = false;
bool bLight1 = true;
// bool b4View = false; // Ham chuyen trang thai giua 1 goc nhin va 4 goc nhin

// Tham so cho camera
float camera_angle;
float camera_height;
float camera_dis;
float camera_X, camera_Y, camera_Z;
float lookAt_X, lookAt_Y, lookAt_Z;

bool bCamera = true;

#pragma endregion

void mySpecialKeyboard(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		camera_height += 0.5;
		break;
	case GLUT_KEY_DOWN:
		camera_height -= 0.5;
		if (camera_height < 0)
			camera_height = 0;
		break;
	case GLUT_KEY_RIGHT:
		camera_angle += 5;
		break;
	case GLUT_KEY_LEFT:
		camera_angle -= 5;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

void myKeyboard(unsigned char key, int x, int y)
{
	float fRInc;
	float fAngle;
	switch (key)
	{
	case '1':
		break;
	case '2':
		break;
	case '3':
		break;
	case '4':
		break;
	case '5':
		break;
	case '6':
		break;
	case '7':
		break;
	case '8':
		break;
	case 'w':
	case 'W':
		bWireFrame = !bWireFrame;
		break;
	case 'a':
	case 'A':
		au = !au;
		break;
		/*case 'b':
		case 'B':
			b4View = !b4View;
			break;*/
	case 'd':
	case 'D':
		bLight1 = !bLight1;
		break;
	case '+':
		camera_dis += 0.5;
		break;
	case '-':
		camera_dis -= 0.5;
		break;
	}
	glutPostRedisplay();
}

// Ve vat the
#pragma region

void drawAxis()
{
	glColor3f(0, 0, 1);
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0); //x
	glVertex3f(4, 0, 0);

	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0); //y
	glVertex3f(0, 4, 0);

	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0); //z
	glVertex3f(0, 0, 4);
	glEnd();
}

void drawTrucTren()
{
	glPushMatrix();
	//glTranslated(0, cylinderHeight + base1Height + cylinderOffset + trucY / 2.0, 0);

	GLfloat diffuse[] = { 0.0, 1.0, 0.0, 1.0 };
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 40.0;
	trucTren.setupMaterial(ambient, diffuse, specular, shininess);

	if (bWireFrame)
	{
		trucTren.DrawWireframe();
	}
	else
	{
		trucTren.Draw();
	}

	glPopMatrix();
}
void drawTrucDuoi()
{
	glPushMatrix();

	//glTranslated(0, cylinderHeight + base1Height + cylinderOffset + trucY / 2.0, 0);
	glRotatef(90, 0, 0, 1);

	GLfloat diffuse[] = { 0.0, 1.0, 0.0, 1.0 };
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 40.0;
	trucDuoi.setupMaterial(ambient, diffuse, specular, shininess);


	if (bWireFrame)
	{
		trucDuoi.DrawWireframe();
	}
	else
	{
		trucDuoi.Draw();
	}

	glPopMatrix();
}
#pragma endregion

void drawAll()
{
	drawAxis();
	drawTrucTren();
	drawTrucDuoi();
}

void myDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	GLfloat light_position0[] = { 10.0, 10.0, 10.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position0);

	if (bLight1 == true)
	{
		glEnable(GL_LIGHT1);
		GLfloat diffuse1[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat specular1[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat ambient1[] = { 0.0, 0.0, 0.0, 1.0 };
		GLfloat position1[] = { -10.0, 10.0, -10.0, 0.0 };

		glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse1);
		glLightfv(GL_LIGHT1, GL_AMBIENT, ambient1);
		glLightfv(GL_LIGHT1, GL_SPECULAR, specular1);
		glLightfv(GL_LIGHT1, GL_POSITION, position1);
	}
	else
		glDisable(GL_LIGHT1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	camera_X = camera_dis * sinf(camera_angle * PI / 180);
	camera_Y = camera_height;
	camera_Z = camera_dis * cosf(camera_angle * PI / 180);


	if (camera_dis == 0)
	{
		gluLookAt(camera_X, camera_Y, camera_Z, lookAt_X, lookAt_Y, lookAt_Z, sinf(camera_angle * PI / 180), 0, cosf(camera_angle * PI / 180));
	}
	else
	{
		gluLookAt(camera_X, camera_Y, camera_Z, lookAt_X, lookAt_Y, lookAt_Z, 0, 1, 0);
	}

	glViewport(0, 0, screenWidth, screenHeight);

	// Clear the stencil buffers
	glClearStencil(0);
	// Clear depth
	glClearDepth(1.0f);
	// Draw
	drawAll();
	/* Don't update color or depth. */
	glDisable(GL_DEPTH_TEST);
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	/* Draw 1 into the stencil buffer. */
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	/* Re-enable update of color and depth. */
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glEnable(GL_DEPTH_TEST);
	/* Now, only render where stencil is set to 1. */
	glStencilFunc(GL_EQUAL, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
	//Draw the cube, reflected vertically, at all PIxels where the stencil
	//buffer is 1
	glPushMatrix();
	glScalef(1, -1, 1);
	drawAll();
	glPopMatrix();
	glDisable(GL_STENCIL_TEST);
	// Blend the floor onto the screen
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_BLEND);

	glFlush();
	glutSwapBuffers();
}


void myInit()
{
	camera_angle = -30;  // Góc quay camera xung quanh trục Oy
	camera_height = 5.5; // Chiều cao camera so với mặt phẳng xOz
	camera_dis = 6.5;	// Khoảng cách đến trục Oy

	lookAt_X = 0;
	lookAt_Y = 0;
	lookAt_Z = 0;

	float fHalfSize = 4;

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);


	const float ar = (float)screenWidth / (float)screenHeight;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-ar, ar, -1.0, 1.0, 1.5, 50.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);
	glDepthFunc(GL_LEQUAL);
	//glEnable(GL_COLOR_MATERIAL);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// Lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	GLfloat lmodel_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

	GLfloat light_ambient0[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light_diffuse0[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular0[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular0);
}

void create(int N)
{
	int M = 2 * (N - 1);
	// Truc tren hinh chu nhat cat goc
	trucTren.BTCuboid(trucX, trucY, trucZ);
	trucTren.SetColor(1);
	trucTren.CalculateFacesNorm();

	//Truc duoi tru
	trucDuoi.CreateCylinder(M, base1Height, base1Radius);
	trucDuoi.SetColor(1);
	trucDuoi.CalculateFacesNorm();

}

void print()
{
	cout << "1, 2: Rotate the base" << endl
		<< "3, 4: Rotate the cylinder" << endl
		<< "5, 6 : Cylinder up / down" << endl
		<< "7, 8 : Rotate the rotator" << endl
		<< "W, w : Switch between wireframeand solid mode" << endl
		<< "A, a : Turn on / off animation" << endl
		<< "D, d : Turn on / off the 2nd light source" << endl
		<< "+ : to increase camera distance." << endl
		<< "- : to decrease camera distance." << endl
		<< "up arrow : to increase camera height." << endl
		<< "down arrow : to decrease camera height." << endl
		<< "< -: to rotate camera clockwise." << endl
		<< "-> : to rotate camera counterclockwise." << endl;
}

int main(int argc, char* argv[])
{
	glutInit(&argc, (char**)argv);									//initialize the tool kit
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);		//set the display mode
	glutInitWindowSize(screenWidth, screenHeight);					//set window size
	glutInitWindowPosition(100, 100);								// set window position on screen
	glutCreateWindow("Assignment - Dang Tuan Anh (1811400)");	// open the screen window

	print();

	int N = NUM / 2 + 1;		// So dinh tren mot nua hinh tron
	create(N);

	myInit();

	glutKeyboardFunc(myKeyboard);
	glutSpecialFunc(mySpecialKeyboard);
	glutDisplayFunc(myDisplay);
	glutMainLoop();
	return 0;
}