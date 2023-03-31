#include <math.h>

typedef struct Vec3f
{
    float x, y, z;
} Point3D, Vector3D;

Point3D createPoint(float x, float y, float z);

Vector3D createVector(float x, float y, float z);

Vector3D createVectorFromPoints(Point3D p1, Point3D p2);

Point3D pointPlusVector(Point3D p, Vector3D v);

Vector3D addVectors(Vector3D v1, Vector3D v2);

Vector3D subVectors(Vector3D v1, Vector3D v2);

Vector3D multVector(Vector3D v1, float a);

Vector3D divVector(Vector3D v1, float a);

float dot(Vector3D a, Vector3D b);

float norm(Vector3D v);