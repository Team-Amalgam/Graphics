#include "Essentials.h"
#include "Shape3D.h"
//#pragma once
//
//struct Mesh {
//	std::vector<Triangle> triangles;
//
//	bool LoadFromObjectFile(std::string FileName) {
//		std::ifstream f(FileName);
//		if (!f.is_open()) return false;
//		
//		//Vertices
//		std::vector<Vec3> vertices;
//
//		while (!f.eof()) {
//			char line[128];
//			f.getline(line, 128);
//
//			std::strstream s;
//			s << line;
//
//			char dataType;
//
//			//Getting vertices and making a pool
//			if (line[0] == 'v') {
//				Vec3 v;
//				s >> dataType >> v.x >> v.y >> v.z;
//				vertices.push_back(v);
//			}
//
//			//Getting triangles and making a pool
//			if (line[0] == 'f') {
//				int f[3];
//				s >> dataType >> f[0] >> f[1] >> f[2];
//				triangles.push_back({ vertices[f[0] - 1],vertices[f[1] - 1], vertices[f[2] - 1] });
//			}
//		}
//
//		return true;
//	}
//};
//struct Mat4x4 {
//	float m[4][4] = { 0 };
//	Vec3 MultiplyVector(Vec3& i) {
//		Vec3 o;
//		o.x = i.x * m[0][0] + i.y * m[1][0] + i.z * m[2][0] + i.width * m[3][0];
//		o.y = i.x * m[0][1] + i.y * m[1][1] + i.z * m[2][1] + i.width * m[3][1];
//		o.z = i.x * m[0][2] + i.y * m[1][2] + i.z * m[2][2] + i.width * m[3][2];
//		o.width = i.x * m[0][3] + i.y * m[1][3] + i.z * m[2][3] + i.width * m[3][3];
//		return o;
//	}
//	Mat4x4 MultiplyMatrix(Mat4x4& i) {
//		Mat4x4 mat;
//		for (int col = 0; col < 4; col++)
//			for (int row = 0; row < 4; row++)
//				for (int k = 0; k < 4; k++)
//					mat.m[row][col] += m[row][k] * i.m[k][col];
//		*this = mat;
//		return *this;
//	}
//	Mat4x4 MultiplyMatrix(Mat4x4& i1, Mat4x4& i2) {
//		Mat4x4 mat;
//		for (int col = 0; col < 4; col++)
//			for (int row = 0; row < 4; row++)
//				for (int k = 0; k < 4; k++)
//					mat.m[row][col] += i1.m[row][k] * i2.m[k][col];
//		*this = mat;
//		return *this;
//	}
//	static Mat4x4 MakeIdentity() {
//		Mat4x4 mat;
//		mat.m[0][0] = 1.0f;
//		mat.m[1][1] = 1.0f;
//		mat.m[2][2] = 1.0f;
//		mat.m[3][3] = 1.0f;
//		return mat;
//	}
//	static Mat4x4 MakeRotationZ(float rad) {
//		Mat4x4 mat;
//		mat.m[0][0] = cosf(rad);
//		mat.m[0][1] = sinf(rad);
//		mat.m[1][0] = -sinf(rad);
//		mat.m[1][1] = cosf(rad);
//		mat.m[2][2] = 1;
//		mat.m[3][3] = 1;
//		return mat;
//		/*
//		cos(theeta),	-sin(theeta),	0, 0,
//		sin(theeta),	cos(theeta),	0, 0,
//		0,				0,				1, 0,
//		0,				0,				0, 1
//		*/
//	}
//	static Mat4x4 MakeRotationY(float rad) {
//		Mat4x4 mat;
//		mat.m[0][0] = cosf(rad);
//		mat.m[0][2] = -sinf(rad);
//		mat.m[1][1] = 1;
//		mat.m[2][0] = sinf(rad);
//		mat.m[2][2] = cosf(rad);
//		mat.m[3][3] = 1;
//		return mat;
//		/*
//		cos(theeta),       0,       +sin(theeta),      0,
//		0,                 1,       0,                 0,
//		-sin(theeta),      0,       cos(theeta),       0,
//		0,                 0,       0,                 1
//		*/
//	}
//	static Mat4x4 MakeRotationX(float rad) {
//		Mat4x4 mat;
//		mat.m[0][0] = 1;
//		mat.m[1][1] = cosf(rad);
//		mat.m[1][2] = sinf(rad);
//		mat.m[2][1] = -sinf(rad);
//		mat.m[2][2] = cosf(rad);
//		mat.m[3][3] = 1;
//		return mat;
//		/*
//		1,              0,              0,              0,
//		0,              cos(theeta),    -sin(theeta),   0,
//		0,              sin(theeta),    cos(theeta),    0,
//		0,              0,              0,				1
//		*/
//	}	
//	static Mat4x4 MakeScale(float x, float y, float z ) {
//		Mat4x4 mat;
//		mat.m[0][0] = x;
//		mat.m[1][1] = y;
//		mat.m[2][2] = x;
//		mat.m[3][3] = 1;
//		return mat;
//		/*
//		{x,  0,   0,   0 },
//		{0,  x,   0,   0 },
//		{0,  0,   x,   0 },
//		{0,  0,   0,   1 }
//		*/
//	}
//	static Mat4x4 MakeScale(float s) {
//		return MakeScale(s,s,s);
//		/*
//		{s,  0,   0,   0 },
//		{0,  s,   0,   0 },
//		{0,  0,   s,   0 },
//		{0,  0,   0,   1 }
//		*/
//	}
//	static Mat4x4 MakeTranslate(Vec3 e) {
//		Mat4x4 mat;
//		mat.m[0][0] = 1;
//		mat.m[1][1] = 1;
//		mat.m[2][2] = 1;
//		mat.m[3][0] = e.x;
//		mat.m[3][1] = e.y;
//		mat.m[3][2] = e.z;
//		mat.m[3][3] = 1;
//		return mat;
//		/*
//		{1,  0,   0,   e.x },
//		{0,  1,   0,   e.y },
//		{0,  0,   1,   e.z },
//		{0,  0,   0,   1   }
//		*/
//	}
//	static Mat4x4 MakeTranslate(float x, float y, float z) {
//		return MakeTranslate({ x, y, z });
//		/*
//		{1,  0,   0,   x },
//		{0,  1,   0,   y },
//		{0,  0,   1,   z },
//		{0,  0,   0,   1   }
//		*/
//	}
//	static Mat4x4 MakeOrthographicProjection(bool x, bool y, bool z) {
//		Mat4x4 mat;
//		mat.m[0][0] = !x;
//		mat.m[1][1] = !y;
//		mat.m[2][2] = !z;
//		mat.m[3][3] = 1;
//		return mat;
//		/*
//		!x,   0,    0,   0,
//		0,    !y,   0,   0,
//		0,    0,    !z,  0,
//		0,    0,    0,   1
//		*/
//	}
//	static Mat4x4 MakeOrthographicProjection(float alpha, float theeta) {
//		if (alpha == 0 || alpha == 90 || alpha == 180 || alpha == 270 || alpha == 360) alpha++;
//
//		Mat4x4 mat;
//		theeta *= pi / 180;
//		alpha *= pi / 180;
//		float l1 = 1 / tan(alpha);
//		
//		mat.m[0][0] = 1;
//		mat.m[1][1] = 1;
//		mat.m[2][0] = l1 * cos(theeta);
//		mat.m[2][1] = l1 * sin(theeta);
//		mat.m[3][3] = 1;
//		return mat;
//		/*
//		{1, 0, l1 * cos(theeta), 0},
//		{0, 1, l1 * sin(theeta), 0},
//		{0, 0, 0,				 0},
//		{0, 0, 0,				 1}
//		*/
//	}
//	static Mat4x4 MakeProjection(float fNear = 0.1f, float fFar = 1000.0f, float fFovDegrees = 90.0f, float fAspectRatio = 0) {
//		if (fAspectRatio==0) fAspectRatio = (float)globalBuffer.height / (float)globalBuffer.width;
//		float fFovRad = 1.0f / tanf(fFovDegrees * 0.5f / 180.0f * pi);
//
//		Mat4x4 mat;
//		mat.m[0][0] = fAspectRatio * fFovRad;
//		mat.m[1][1] = fFovRad;
//		mat.m[2][2] = fFar / (fFar - fNear);
//		mat.m[3][2] = (-fFar * fNear) / (fFar - fNear);
//		mat.m[2][3] = 1.0f;
//		mat.m[3][3] = 0.0f;
//		return mat;
//	}
//};
//
//class Shape3D {
//	Mesh mesh;
//	Mat4x4 matProj;
//	Vec3 camera;
//	float fTheta;
//
//public:
//	Shape3D() {
//		//Default Cube
//		mesh.triangles = {
//			//South
//			{0.0f, 0.0f, 0.0f,	0.0f, 1.0f, 0.0f,	1.0f, 1.0f, 0.0f},
//			{0.0f, 0.0f, 0.0f,	1.0f, 1.0f, 0.0f,	1.0f, 0.0f, 0.0f},
//
//			//East
//			{1.0f, 0.0f, 0.0f,	1.0f, 1.0f, 0.0f,	1.0f, 1.0f, 1.0f},
//			{1.0f, 0.0f, 0.0f,	1.0f, 1.0f, 1.0f,	1.0f, 0.0f, 1.0f},
//
//			//North
//			{1.0f, 0.0f, 1.0f,	1.0f, 1.0f, 1.0f,	0.0f, 1.0f, 1.0f},
//			{1.0f, 0.0f, 1.0f,	0.0f, 1.0f, 1.0f,	0.0f, 0.0f, 1.0f},
//
//			//West
//			{0.0f, 0.0f, 1.0f,	0.0f, 1.0f, 1.0f,	0.0f, 1.0f, 0.0f},
//			{0.0f, 0.0f, 1.0f,	0.0f, 1.0f, 0.0f,	0.0f, 0.0f, 0.0f},
//
//			//Top
//			{0.0f, 1.0f, 0.0f,	0.0f, 1.0f, 1.0f,	1.0f, 1.0f, 1.0f},
//			{0.0f, 1.0f, 0.0f,	1.0f, 1.0f, 1.0f,	1.0f, 1.0f, 0.0f},
//
//			//Bottom
//			{1.0f, 0.0f, 1.0f,	0.0f, 0.0f, 1.0f,	0.0f, 0.0f, 0.0f},
//			{1.0f, 0.0f, 1.0f,	0.0f, 0.0f, 0.0f,	1.0f, 0.0f, 0.0f},
//
//		};
//
//		//Loading obj
//		//mesh.LoadFromObjectFile("../Assets/Church.obj");
//		//mesh.LoadFromObjectFile("../Assets/Cube.obj");
//
//		//Projection Matrix
//		matProj = Mat4x4::MakeProjection();
//		fTheta = 0;
//	}
//	void draw(float fElapsedTime = 0) {
//		camera = { 0.0f, 0.0f, 0.0f };
//
//		//Set Up Transformation Matrices
//		fTheta += fElapsedTime * 0.01f;
//
//		// Rotation Z
//		Mat4x4 matRotZ;
//		matRotZ = Mat4x4::MakeRotationZ(fTheta);
//		// Rotation X
//		Mat4x4  matRotX;
//		matRotX = Mat4x4::MakeRotationX(fTheta * 0.5f);
//		//Tranlation
//		Mat4x4 matTrans;
//		matTrans = Mat4x4::MakeTranslate(0.0f, 0.0f, 16.0f);
//		//World Transformations
//		Mat4x4 matWorld;
//		matWorld = Mat4x4::MakeIdentity();
//		matWorld.MultiplyMatrix(matRotZ, matRotX);
//		matWorld.MultiplyMatrix(matTrans);
//
//		Mesh toRaster;
//		//Draw Triangles
//		for (auto tri : mesh.triangles) {
//			Triangle triProjected, triTransformed;
//
//			//Apply Transformations
//			for (int i = 0; i < 3; i++)
//				triTransformed.vertex[].position[0]=matWorld.MultiplyVector(tri.vertex[].position[i]);
//
//			//Find Normal
//			Vec3 normal = triTransformed.normal();
//			Vec3 CameraRay = triTransformed.vertex[].position[0] - camera;
//
//			if(normal.dot(CameraRay) < 0.0f){
//				//Illumination
//				Vec3 lightDirection = { 0.0f, 0.0f, -1.0f };
//				lightDirection.normalize();
//
//				float light = normal.dot(lightDirection);
//
//				unsigned col = interPolate(-1.0f, 1.0f, light, (unsigned int)0, (unsigned int)0xff);
//				triTransformed.color
//					= col * 0x100 * 0x100 +
//					  col * 0x100 +
//					  col;
//
//				//Projection
//				for (int i = 0; i < 3; i++)
//					triProjected.vertex[].position[i]=matProj.MultiplyVector(triTransformed.vertex[].position[i]);
//
//				//Normalise Projected matrix
//				for (int i = 0; i < 3; i++)
//					triProjected.vertex[].position[i] = triProjected.vertex[].position[i] / triProjected.vertex[].position[i].width;
//
//				//Scale Triangles into view
//				Vec3 offSetView = { 1.0f, 1.0f, 0.0f };
//				triProjected += offSetView;
//				triProjected.multiply({ 0.5f * (float)globalBuffer.width, 0.5f * (float)globalBuffer.height, 1.0f });
//				triProjected.color = triTransformed.color;
//
//				//Store Triangles
//				toRaster.triangles.push_back(triProjected);				
//			}
//		}
//		
//		//Sort Triangles - Painter's Algorithm
//		std::sort(toRaster.triangles.begin(), toRaster.triangles.end(), [](Triangle& t1, Triangle& t2) {
//			float midZ1 = (t1.vertex[].position[0].z + t1.vertex[].position[1].z + t1.vertex[].position[2].z) / 3.0f;
//			float midZ2 = (t2.vertex[].position[0].z + t2.vertex[].position[1].z + t2.vertex[].position[2].z) / 3.0f;
//			return midZ1 > midZ2;
//		});
//
//		//Rasterize Triangle
//		for (auto& triProjected : toRaster.triangles) {
//			ColorTriangle(triProjected, triProjected.color);
//			//DrawTriangle(triProjected, 0);
//		}
//	}	
//
//};
//
std::vector<Vec3> LoadOBJ(std::istream& f)
{
	/*std::vector< Vec3 > verts;
	std::vector< Vec3 > positions(1, Vec3{ 0,0,0,0 });
	std::vector< Vec2 > texcoords(1, Vec2{ 0, 0, 0 });
	std::vector< Vec3 > pramissnormal(1, Vec3{ 0, 0, 0 });*/
	std::string lineStr;
	while (std::getline(f, lineStr))
	{
		std::istringstream lineSS(lineStr);
		std::string lineType;
		lineSS >> lineType;

		// vertex[].position
		if (lineType == "v")
		{
			float x = 0, y = 0, z = 0, w = 1;
			lineSS >> x >> y >> z >> w;
			positions.push_back(glm::vec4(x, y, z, w));
		}

		// texture
		if (lineType == "vt")
		{
			float u = 0, v = 0, w = 0;
			lineSS >> u >> v >> w;
			texcoords.push_back(glm::vec3(u, v, w));
		}

		// normal
		if (lineType == "vn")
		{
			float i = 0, j = 0, k = 0;
			lineSS >> i >> j >> k;
			normals.push_back(glm::normalize(glm::vec3(i, j, k)));
		}

		// polygon
		if (lineType == "f")
		{
			std::vector< VertRef > refs;
			std::string refStr;
			while (lineSS >> refStr)
			{
				std::istringstream ref(refStr);
				std::string vStr, vtStr, vnStr;
				std::getline(ref, vStr, '/');
				std::getline(ref, vtStr, '/');
				std::getline(ref, vnStr, '/');
				int v = atoi(vStr.c_str());
				int vt = atoi(vtStr.c_str());
				int vn = atoi(vnStr.c_str());
				v = (v >= 0 ? v : positions.size() + v);
				vt = (vt >= 0 ? vt : texcoords.size() + vt);
				vn = (vn >= 0 ? vn : normals.size() + vn);
				refs.push_back(VertRef(v, vt, vn));
			}

			// triangulate, assuming n>3-gons are convex and coplanar
			for (size_t i = 1; i + 1 < refs.size(); ++i)
			{
				const VertRef* p[3] = { &refs[0], &refs[i], &refs[i + 1] };

				// http://www.opengl.org/wiki/Calculating_a_Surface_Normal
				glm::vec3 U(positions[p[1]->v] - positions[p[0]->v]);
				glm::vec3 V(positions[p[2]->v] - positions[p[0]->v]);
				glm::vec3 faceNormal = glm::normalize(glm::cross(U, V));

				for (size_t j = 0; j < 3; ++j)
				{
					Vertex vert;
					vert.position = glm::vec3(positions[p[j]->v]);
					vert.texcoord = glm::vec2(texcoords[p[j]->vt]);
					vert.normal = (p[j]->vn != 0 ? pramissMornal[p[j]->vn] : faceNormal);
					verts.push_back(vert);
				}
			}
		}
	}

	struct Vertex
	{
		glm::vec3 position;
		glm::vec2 texcoord;
		glm::vec3 normal;
	};

	return verts;
}