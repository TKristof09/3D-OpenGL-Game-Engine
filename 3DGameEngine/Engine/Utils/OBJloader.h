#ifndef OBJLOADER_H
#define OBJLOADER_H

#include "3DMath\3DMath.h"
#include <vector>
#include <string>

struct OBJIndex
{
	int vertexIndex;
	int uvIndex;
	int normalIndex;

	bool operator<(const OBJIndex& r) const { return vertexIndex < r.vertexIndex; }
};

class IndexedModel
{
public:
	std::vector<math::Vector3> positions;
	std::vector<math::Vector2> texCoords;
	std::vector<math::Vector3> normals;
	std::vector<unsigned int> indices;

	void CalcNormals();
};

class OBJModel
{
public:
	std::vector<OBJIndex> OBJIndices;
	std::vector<math::Vector3> vertices;
	std::vector<math::Vector2> uvs;
	std::vector<math::Vector3> normals;
	bool hasUVs;
	bool hasNormals;

	OBJModel(const std::string& fileName);

	IndexedModel ToIndexedModel();
private:
	unsigned int FindLastVertexIndex(const std::vector<OBJIndex*>& indexLookup, const OBJIndex* currentIndex,
	                                 const IndexedModel& result);
	void CreateOBJFace(const std::string& line);

	math::Vector2 ParseOBJVec2(const std::string& line);
	math::Vector3 ParseOBJVec3(const std::string& line);
	OBJIndex ParseOBJIndex(const std::string& token, bool* hasUVs, bool* hasNormals);
};

#endif // OBJ_LOADER_H_INCLUDED
