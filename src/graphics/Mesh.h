#ifndef MESH_H_
#define MESH_H_

#include <xmlParser.h>
#include <GL/glew.h>
#include <GL/glfw.h>

#include <vector>
#include <unordered_map>

namespace scim
{

struct MeshData
{
	MeshData(const std::vector<F32> &attribs, const std::vector<I32> &indicies, GLuint program);
	~MeshData();

	GLuint m_attribBuffer;
	GLuint m_indexBuffer;
	GLuint m_VAO;
	GLuint m_program;
	GLuint m_modelToCamUnf;

	std::vector<F32> m_attribArray;
};

class Mesh
{
public:
	MeshData* m_meshData;
public:
	Mesh(const XMLNode& compRootNode);
	~Mesh();

	void Render();

	const MeshData* GetMeshData() const { return m_meshData; }
};

}

#endif
