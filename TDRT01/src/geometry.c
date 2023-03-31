#include "../include/geometry.h"

Point3D createPoint(float x, float y, float z)
{
    return { x, y, z }
}

Vector3D createVector(float x, float y, float z)
{
    return { x, y, z }
}

Vector3D createVectorFromPoints(Point3D p1, Point3D p2)
{
    return { p1.x + p2.x, p1.y + p2.y, p1.z + p2.z }
}

Point3D pointPlusVector(Point3D p, Vector3D v)
{
    return { p.x + v.x, p.y + v.y, p.z + v.z }
}

Vector3D addVectors(Vector3D v1, Vector3D v2)
{
    return { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z }
}

Vector3D subVectors(Vector3D v1, Vector3D v2)
{
    return { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z }
}

Vector3D multVector(Vector3D v1, float a)
{
    return { a *v1.x, a *v1.y, a *v1.z }
}

Vector3D divVector(Vector3D v1, float a)
{
    return { v1.x / a, v1.y / a, v1.z / a }
}

float dot(Vector3D a, Vector3D b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z
}

float norm(Vector3D v)
{
    return sqrt(pow(v.x, 2), pow(v.y, 2), pow(v.z, 2))
}