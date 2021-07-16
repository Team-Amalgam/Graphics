#include "Headers/GeneratedCube.h"
#include <glm/gtc/noise.hpp>

float interPolate(float input1, float input2, float position, float val1, float val2) {
    if (input1 == input2) return val1;
    else return val1 + (position - input1) / (input2 - input1) * (val2 - val1);
}
Vec3f interPolateColors(float input1, float input2, float position, Vec3f Color1, Vec3f Color2) {
    float r = interPolate(input1, input2, position, Color1.x, Color2.x);
    float g = interPolate(input1, input2, position, Color1.y, Color2.y);
    float b = interPolate(input1, input2, position, Color1.z, Color2.z);
    return Vec3f(r, g, b);
}
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
float PlaneFunction(const Vec3f& Pos)
{    
    return -Pos.y + KritiKoFunction(Pos); //+Kriti ko function
    //return -Pos.y+ sinf(2*Pos.z+) * cosf(2*Pos.x); //Ramailo terrain
}
double KritiKoFunction(Vec3f Pos, int octaves, Vec3f offSet, int multiplier)
{
    //OUTPUTS
    double maxValue = 0;
    double total = 0;

    //variables
    double freq = 0.5f;
    double amp = 2;
    double persistence = 1;
    
        for (unsigned i = 0; i < octaves; ++i)
        {
            glm::vec3 p((Pos.x * freq + offSet.x) * multiplier, (Pos.y * freq + offSet.y) * multiplier, (Pos.z * freq + offSet.z) * multiplier);

            total += ((glm::simplex(p) + 1.0) / 2.0) * amp;
            maxValue += amp;
            amp *= persistence;
            freq *= 2;
        }
    return total / maxValue;
}