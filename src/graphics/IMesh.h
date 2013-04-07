#ifndef IMESH_H_
#define IMESH_H_

#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>

#include <vector>

namespace scim
{

struct MeshData
{
	MeshData(GLuint program,
		const std::vector<glm::vec3> &vertexList,
		const std::vector<U32> &indexList,
		const std::vector<glm::vec4> &colorList,
		const std::vector<glm::vec2> &texUVList,
		const std::vector<glm::vec3> &normalList,
		const std::vector<GLuint> &textureList
	);
	~MeshData();

	GLuint vertexBuffer;
	GLuint colorBuffer;
	GLuint indexBuffer;
	GLuint textureBuffer;

	GLuint VAO;
	GLuint program;
	std::vector<GLuint> textureList;

	GLint mvpMatrixUnf;
	GLint texUnitUnf;

	struct
	{
		U16 vertexSize;
		U16 indexSize;
		bool isColored;
		bool isTextured;
		bool hasNormals;
	} bufferInfo;
};

class IMesh
{
protected:
	std::vector<MeshData*> m_subMeshes;
public:
	virtual ~IMesh();

	virtual void Render(const glm::mat4& modelToWorldMatrix);

	const std::vector<MeshData*>* GetMeshData() const { return &m_subMeshes; }
};

}

#endif
