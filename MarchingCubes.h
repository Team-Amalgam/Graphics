#pragma once
#include "Essentials.h"

typedef unsigned long DWORD;
typedef unsigned int UINT;
typedef glm::vec3 Vec3f;

struct TriMeshFace
{
    TriMeshFace() {}
    TriMeshFace(DWORD I0, DWORD I1, DWORD I2)
    {
        I[0] = I0;
        I[1] = I1;
        I[2] = I2;
    }

    DWORD I[3];
};
struct MeshVertex
{
    Vec3f Pos;           // position of the vertex in 3-space
    Vec3f Normal;        // vector normal to the surface passing through this vertex
    Vec3f Color;      // color of this vertex
    
    MeshVertex() {}
    explicit MeshVertex(const Vec3f& _Pos)
    {
        Pos = _Pos;
        Normal = Vec3f(0, 0, 0);
        Color = Vec3f(0xff, 0xff, 0xff);
    }
    MeshVertex(const Vec3f& _Pos, const Vec3f& _Normal, const Vec3f& _Color)
    {
        Pos = _Pos;
        Normal = _Normal;
        Color = _Color;
    }
    static void Interpolate(const MeshVertex& sv, const MeshVertex& ev, MeshVertex& out, float s)
    {
        int i;
        unsigned char* color1, * color2, * color;
        color = (unsigned char*)&out.Color;
        color1 = (unsigned char*)&sv.Color;
        color2 = (unsigned char*)&ev.Color;
        for (i = 0; i < 3; i++)
            color[i] = unsigned char(color1[i] + int(s * (color2[i] - color1[i])));    //interpolate each component of the color seperately

        //out.TexCoord.x = sv.TexCoord.x + s * (ev.TexCoord.x - sv.TexCoord.x);
        //out.TexCoord.y = sv.TexCoord.y + s * (ev.TexCoord.y - sv.TexCoord.y);    //interpolate the texture coordinates

        out.Normal = sv.Normal + s * (ev.Normal - sv.Normal);    //interpolate the normal vector
        float Len = glm::length(out.Normal);
        if (Len == 0.0f) 
            out.Normal = sv.Normal;                                    //renormalize the normal vector
        else out.Normal /= Len;

        out.Pos = sv.Pos + s * (ev.Pos - sv.Pos);    //interpolate the position
    }
};
struct GRIDCELL {
	Vec3f p[8];		//position of each corner of the grid in world space
	float val[8];	//value of the function at this grid corner
};

//given a grid cell, returns the set of triangles that approximates the region where val == 0.
/*
   Given a grid cell and an isolevel, calculate the triangular
   facets required to represent the isosurface through the cell.
   Return the number of triangular facets, the array "triangles"
   will be loaded up with the vertices at most 5 triangular facets.
	0 will be returned if the grid cell is either totally above
   of totally below the isolevel.
*/
int Polygonise(GRIDCELL& Grid, TriMeshFace* Triangles, int& NewVertexCount, Vec3f* Vertices);