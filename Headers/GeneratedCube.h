#pragma once
#include "MarchingCubes.h"

float SphereFunction(const Vec3f&);
float RandomFunction(const Vec3f&);
float CrazyFunction(const Vec3f&);
float PlaneFunction(const Vec3f&);
double KritiKoFunction(Vec3f, int = 4, Vec3f = { 0,0,0 }, int = 1);
float interPolate(float input1, float input2, float position, float val1, float val2);
Vec3f interPolateColors(float input1, float input2, float position, Vec3f Color1, Vec3f Color2);

class GeneratedCube {
private:

    static const UINT FunctionCount = 4;
    float (*_functions[FunctionCount])(const Vec3f& Pos);
    UINT _functionIndex;

    UINT _XCount, _YCount, _ZCount;
    Vec3f _Start, _End, _Diff;
    float _CellSize;

    std::vector<Vec3f> _AllVertices;
    std::vector<TriMeshFace> _AllFaces;

    //Mesh
    UINT _VertexCount, _IndexCount;
    float* _Vertices;
    DWORD* _Indices;
    int compiledVertexSize = 9;

    //Temp Storage
    TriMeshFace _FaceStorage[10];
    Vec3f _VertexStorage[15];

    float (*_Function)(const Vec3f& Pos);
    float _Epsilon;

public:
    GeneratedCube() {
        _Vertices = 0;
        _Indices = 0;
        _VertexCount = 0;
        _IndexCount = 0;
        _Epsilon = 0.0003f;

        _functionIndex = 3;
        _functions[0] = SphereFunction;
        _functions[1] = RandomFunction;
        _functions[2] = CrazyFunction;
        _functions[3] = PlaneFunction;

        IsoApproximate(2.0f, 0.1f, _functions[_functionIndex]);
        //IsoApproximate(1.25f, 0.025f, _functions[_functionIndex]);
    }
    //Generate Surface
    void IsoApproximate(float BoxSize, float CellSize, float (*Function)(const Vec3f& Pos))
    {
        Vec3f End(BoxSize, BoxSize, BoxSize);
        IsoApproximate(-End, End, CellSize, Function);
    }
    void IsoApproximate(const Vec3f& Start, const Vec3f& End, float CellSize, float (*Function)(const Vec3f& Pos))
    {
        _Function = Function;
        _CellSize = CellSize;
        _Start = Start;
        _End = End;
        _Diff = _End - _Start;
        _XCount = int(_Diff.x / _CellSize);
        _YCount = int(_Diff.y / _CellSize);
        _ZCount = int(_Diff.z / _CellSize);

        float* TopGrid = new float[_XCount * _YCount];
        float* BottomGrid = new float[_XCount * _YCount];

        FillGrid(TopGrid, 0);
        for (UINT z = 1; z < _ZCount - 1; z++)
        {
            FillGrid(BottomGrid, z);
            PolygonizeGrids(TopGrid, BottomGrid, z);
            Swap(TopGrid, BottomGrid);
        }

        delete[] TopGrid;
        delete[] BottomGrid;

        MakeObject();
    }
    void MakeObject()//Sets up Indices and Vertices
    {
        const UINT noOfVertices = _AllVertices.size();
        AllocateMesh(noOfVertices, _AllFaces.size());

        MeshVertex* meshVertices = new MeshVertex[noOfVertices];
        for (UINT VertexIndex = 0; VertexIndex < _AllVertices.size(); VertexIndex++)
        {
            MeshVertex& CurVertex=meshVertices[VertexIndex];
            CurVertex.Pos = _AllVertices[VertexIndex];
            CalcGradient(CurVertex.Pos, CurVertex.Normal);            
        }
        for (UINT FaceIndex = 0; FaceIndex < _AllFaces.size(); FaceIndex++)
        {
            const TriMeshFace& CurFace = _AllFaces[FaceIndex];
            _Indices[FaceIndex * 3 + 0] = CurFace.I[0];
            _Indices[FaceIndex * 3 + 1] = CurFace.I[1];
            _Indices[FaceIndex * 3 + 2] = CurFace.I[2];
        }
        ColorbyThresHold(meshVertices);
        //ColorbyInterPolation(meshVertices);
        ConvertToVertices(meshVertices);
        delete[] meshVertices;
    }
    void ConvertToVertices(MeshVertex* meshVertices) {
        const UINT noOfVertices = _AllVertices.size();
        
		for (UINT VertexIndex = 0; VertexIndex < noOfVertices; VertexIndex++) {
			_Vertices[compiledVertexSize * VertexIndex + 0] = meshVertices[VertexIndex].Pos.x;
			_Vertices[compiledVertexSize * VertexIndex + 1] = meshVertices[VertexIndex].Pos.y;
			_Vertices[compiledVertexSize * VertexIndex + 2] = meshVertices[VertexIndex].Pos.z;
			_Vertices[compiledVertexSize * VertexIndex + 3] = meshVertices[VertexIndex].Normal.x;
			_Vertices[compiledVertexSize * VertexIndex + 4] = meshVertices[VertexIndex].Normal.y;
			_Vertices[compiledVertexSize * VertexIndex + 5] = meshVertices[VertexIndex].Normal.z;
            _Vertices[compiledVertexSize * VertexIndex + 6] = meshVertices[VertexIndex].Color.x;
            _Vertices[compiledVertexSize * VertexIndex + 7] = meshVertices[VertexIndex].Color.y;
            _Vertices[compiledVertexSize * VertexIndex + 8] = meshVertices[VertexIndex].Color.z;
        }
    }
    void ColorbyNormals(MeshVertex* meshVertices,
        float fr = 1.0f, float fg = 1.0f, float fb = 1.0f)
	{
		for (UINT VertexIndex = 0; VertexIndex < _AllVertices.size(); VertexIndex++) {

			float r = (meshVertices[VertexIndex].Normal.x / 2.0f + 0.5f) * fr;
			float g = (meshVertices[VertexIndex].Normal.y / 2.0f + 0.5f) * fg;
			float b = (meshVertices[VertexIndex].Normal.z / 2.0f + 0.5f) * fb;    //remap each normal's (x, y, z) to (r, g, b)
			meshVertices[VertexIndex].Color = Vec3f(r, g, b);
		}
	}
    void ColorbyInterPolation(MeshVertex* meshVertices,
        float fr = 1.0f, float fg = 1.0f, float fb = 1.0f)
    {
        for (UINT VertexIndex = 0; VertexIndex < _AllVertices.size(); VertexIndex++) {           
            Vec3f ColorA = Vec3f(0.0f * fr / 255, 150.0f * fg / 255, 198.0f * fb / 255); //from  0, 150, 199 //Lower Color
            Vec3f ColorB = Vec3f(233.0f * fr / 255, 196.0f * fg / 255, 106.0f * fb / 255); //to   233, 196, 106 //Upper Color
            meshVertices[VertexIndex].Color = interPolateColors(0.3f, 0.8f, meshVertices[VertexIndex].Pos.y, ColorA, ColorB);
        }
    }
    void ColorbyThresHold(MeshVertex* meshVertices,
        float fr = 1.0f, float fg = 1.0f, float fb = 1.0f)
    {
        for (UINT VertexIndex = 0; VertexIndex < _AllVertices.size(); VertexIndex++) {
            Vec3f ColorL1 = Vec3f(  3.0f * fr / 255,   4.0f * fg / 255,  94.0f * fb / 255); //from   3,   4,  94 //Lower Color1
            Vec3f ColorL2 = Vec3f(  0.0f * fr / 255, 150.0f * fg / 255, 198.0f * fb / 255); //from   0, 150, 199 //Lower Color2
            Vec3f ColorU1 = Vec3f(108.0f * fr / 255, 197.0f * fg / 255,  81.0f * fb / 255); //to   108, 197, 81 //Upper Color1
            Vec3f ColorU2 = Vec3f(233.0f * fr / 255, 196.0f * fg / 255, 106.0f * fb / 255); //to   233, 196, 106 //Upper Color2
            float lower = 0.2f, threshold = 0.4f, upper = 0.7f;
            //remap each normal's (x, y, z) to (r, g, b)
            if (meshVertices[VertexIndex].Pos.y < threshold) 
                meshVertices[VertexIndex].Color = interPolateColors(lower, threshold, meshVertices[VertexIndex].Pos.y, ColorL1, ColorL2);
            else 
                meshVertices[VertexIndex].Color = interPolateColors(threshold, upper, meshVertices[VertexIndex].Pos.y, ColorU1, ColorU2);
        }
    }
    template <class type> __forceinline void Swap(type& t1, type& t2)
    {
        type Temp = t1;
        t1 = t2;
        t2 = Temp;
    }
    //Mesh
    void FreeMesh()
    {
        _VertexCount = 0;
        _IndexCount = 0;
        if (_Vertices)
        {
            delete[] _Vertices;
            _Vertices = 0;
        }
        if (_Indices)
        {
            delete[] _Indices;
            _Indices = 0;
        }
    }
    void AllocateMesh(UINT NewVertexCount, UINT NewFaceCount)
    {
        FreeMesh();
        if (NewVertexCount == 0 || NewFaceCount == 0) return;
        _VertexCount = NewVertexCount;
        _IndexCount = NewFaceCount * 3;
        _Vertices = new float[_VertexCount*compiledVertexSize];
        _Indices = new DWORD[_IndexCount];
    }
    void CalcGradient(const Vec3f& Pos, Vec3f& Normal)
    {
        float value = _Function(Pos);
        Normal.x = (_Function(Vec3f(Pos.x + _Epsilon, Pos.y, Pos.z)) - value);
        Normal.y = (_Function(Vec3f(Pos.x, Pos.y + _Epsilon, Pos.z)) - value);
        Normal.z = (_Function(Vec3f(Pos.x, Pos.y, Pos.z + _Epsilon)) - value);
        Normal = glm::normalize(Normal);
    }
    void FillGrid(float* Grid, int z)
    {
        for (UINT x = 0; x < _XCount; x++)
        {
            for (UINT y = 0; y < _YCount; y++)
            {
                Vec3f Pos = Vec3f(_Start.x + _CellSize * x, _Start.y + _CellSize * y, _Start.z + _CellSize * (z + 1));
                Grid[x * _YCount + y] = _Function(Pos);
            }
        }
    }
    bool PushPolygons(GRIDCELL& g)
    {
        int NewVertexCount, IndexShift = _AllVertices.size();
        int NewFaceCount = Polygonise(g, _FaceStorage, NewVertexCount, _VertexStorage);
        if (NewFaceCount)
        {
            for (int FaceIndex = 0; FaceIndex < NewFaceCount; FaceIndex++)
            {
                _FaceStorage[FaceIndex].I[0] += IndexShift;
                _FaceStorage[FaceIndex].I[1] += IndexShift;
                _FaceStorage[FaceIndex].I[2] += IndexShift;
                _AllFaces.push_back(_FaceStorage[FaceIndex]);
            }
            for (int VertexIndex = 0; VertexIndex < NewVertexCount; VertexIndex++)
            {
                _AllVertices.push_back(_VertexStorage[VertexIndex]);
            }
            return true;
        }
        return false;
    }
    void PolygonizeGrids(float* TopVals, float* BottomVals, int z)
    {
        for (UINT x = 0; x < _XCount - 1; x++)
        {
            for (UINT y = 0; y < _YCount - 1; y++)
            {
                GRIDCELL g;
                g.p[0] = Vec3f(_Start.x + _CellSize * (x + 0), _Start.y + _CellSize * (y + 0), _Start.z + _CellSize * (z + 0));
                g.p[1] = Vec3f(_Start.x + _CellSize * (x + 1), _Start.y + _CellSize * (y + 0), _Start.z + _CellSize * (z + 0));
                g.p[2] = Vec3f(_Start.x + _CellSize * (x + 1), _Start.y + _CellSize * (y + 1), _Start.z + _CellSize * (z + 0));
                g.p[3] = Vec3f(_Start.x + _CellSize * (x + 0), _Start.y + _CellSize * (y + 1), _Start.z + _CellSize * (z + 0));

                g.val[0] = TopVals[x * _YCount + y];
                g.val[1] = TopVals[(x + 1) * _YCount + y];
                g.val[2] = TopVals[(x + 1) * _YCount + y + 1];
                g.val[3] = TopVals[x * _YCount + y + 1];

                g.p[4] = Vec3f(_Start.x + _CellSize * (x + 0), _Start.y + _CellSize * (y + 0), _Start.z + _CellSize * (z + 1));
                g.p[5] = Vec3f(_Start.x + _CellSize * (x + 1), _Start.y + _CellSize * (y + 0), _Start.z + _CellSize * (z + 1));
                g.p[6] = Vec3f(_Start.x + _CellSize * (x + 1), _Start.y + _CellSize * (y + 1), _Start.z + _CellSize * (z + 1));
                g.p[7] = Vec3f(_Start.x + _CellSize * (x + 0), _Start.y + _CellSize * (y + 1), _Start.z + _CellSize * (z + 1));

                g.val[4] = BottomVals[x * _YCount + y];
                g.val[5] = BottomVals[(x + 1) * _YCount + y];
                g.val[6] = BottomVals[(x + 1) * _YCount + y + 1];
                g.val[7] = BottomVals[x * _YCount + y + 1];

                bool Valid = true;
                for (UINT VertexIndex = 0; VertexIndex < 8 && Valid; VertexIndex++)
                {
                    if (g.val[VertexIndex] == FLT_MAX)
                    {
                        Valid = false;
                    }
                }
                if (Valid)
                {
                    PushPolygons(g);
                }
            }
        }
    }
    //Get Values
    float* getVertices(size_t* size=0) {
        if (size) *size = _VertexCount*compiledVertexSize;
        return _Vertices;
    }
    unsigned int* getIndices(size_t* size = 0) {
        if (size) *size = _IndexCount;
        return (unsigned int*)_Indices;
    }
};
