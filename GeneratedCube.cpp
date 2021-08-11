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
    //return -Pos.y + OkByeFunction(Pos); //+Kriti ko function
    return -Pos.y + (Fourier(Pos.x, Pos.z) + Fourier(Pos.z, Pos.z)) / 2; //Fourier terrain
    //return -Pos.y + (expf(Pos.x*10) + expf(Pos.z*10)) / 2;//Ramilo Function
}
float Fourier(float f1, float f2) {
    /*float a0 = 1.f,
        an = 5.f / (2 / 3.14),
        bn = 2.f / 3.14,
        sum = a0/2;*/
    float pi = 3.14159;
    float a0 = 2*sinhf(pi)/pi, an, bn,
        sum = a0/2;
    for (float i = 1; i < 60; i++) {
        an = 2 * cosf(i * pi) * sinhf(pi) / (pi * (1 + i * i));
        bn = -2 * i * cosf(i * pi) * sinhf(pi) / (pi * (1 + i * i));
        sum += an * cosf(i * 2 * 3.14 * f1) + bn * sinf(i * 2 * 3.14 * f1);
    }
    return sum;
}
double OkByeFunction(Vec3f Pos, int octaves, Vec3f offSet, int multiplier)
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