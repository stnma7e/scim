#ifndef MESH_H_
#define MESH_H_

#include <xmlParser.h>
#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>

#include <vector>
#include <unordered_map>

namespace scim
{

struct MeshData
{
	MeshData(const std::vector<F32> &vertexList, const std::vector<F32> &colorList, const std::vector<I32> &indexList, GLuint program);
	~MeshData();

	GLuint vertexBuffer;
	GLuint colorBuffer;
	GLuint indexBuffer;

	GLuint VAO;
	GLuint program;

	GLint mvpMatrixUnf;

	std::vector<F32> attribArray;
};

class Mesh
{
public:
	MeshData* m_meshData;
public:
	Mesh(const XMLNode& compRootNode);
	~Mesh();

	void Render(const glm::mat4& transformMatrix);

	const MeshData* GetMeshData() const { return m_meshData; }
};

}

#endif
