#include "GeneratedCube.h"
float SphereFunction(const Vec3f& Pos)
{
    return Pos.x * Pos.x + Pos.y * Pos.y + Pos.z * Pos.z - 1.0f;
}

float RandomFunction(const Vec3f& Pos)
{
    Vec3f P = Pos * 10.0f;
    return sinf(glm::length(P)) * P.x + sinf(glm::length(P)) * P.y;
}

float CrazyFunction(const Vec3f& Pos)
{
    Vec3f P = Pos * 3.0f;
    return sinf(P.x * P.y + P.x * P.z + P.y * P.z) + sinf(P.x * P.y) + sinf(P.y * P.z) + sinf(P.x * P.z) - 1.0f;
}