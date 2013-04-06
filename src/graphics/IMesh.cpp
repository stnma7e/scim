#include "IMesh.h"
#include "RenderFramework.h"

#include <iostream>
#include <GL/glfw.h>

namespace scim
{

extern RenderFramework* g_renderFramework;

MeshData::MeshData(GLuint program,
	const std::vector<glm::vec3> &vertexList,
	const std::vector<U32> &indexList,
	const std::vector<glm::vec4> &colorList,
	const std::vector<glm::vec2> &texUVList,
	const std::vector<glm::vec3> &normalList
) : program(program)
{
	GLint linked;
	glGetProgramiv(program, GL_LINK_STATUS, &linked);
	assert((!vertexList.empty()) &&
	       (!indexList.empty())  &&
	       (linked == GL_TRUE)
	);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, (vertexList.size() * sizeof(glm::vec3)), &vertexList[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (indexList.size() * sizeof(U32)), &indexList[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	if (!colorList.empty())
	{
		glGenBuffers(1, &colorBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
		glBufferData(GL_ARRAY_BUFFER, (colorList.size() * sizeof(glm::vec4)), &colorList[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	// if (!texUVList.empty())
	// {
	// 	glGenBuffers(1, &indexBuffer);
	// 	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	// 	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (indexList.size() * sizeof(U32)), &indexList[0], GL_STATIC_DRAW);
	// 	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	// }

	mvpMatrixUnf = glGetUniformLocation(program, "mvp");

	bufferInfo.vertexSize = (U16)vertexList.size();
	bufferInfo.indexSize  =	(U16)indexList.size();
	bufferInfo.isColors   =	colorList.empty()  ? false : true;
	bufferInfo.isTextured =	texUVList.empty()  ? false : true;
	bufferInfo.isNormals  =	normalList.empty() ? false : true;
}
MeshData::~MeshData()
{
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &colorBuffer);
	glDeleteBuffers(1, &indexBuffer);
	glDeleteVertexArrays(1, &VAO);
}

IMesh::~IMesh()
{
	for (size_t i = 0; i < m_subMeshes.size(); ++i)
	{
		delete m_subMeshes[i];
	}
}
void IMesh::Render(const glm::mat4& modelToWorldMatrix)
{
	for (size_t i = 0; i < m_subMeshes.size(); ++i)
	{
		const MeshData* meshData = m_subMeshes[i];

		glBindVertexArray(meshData->VAO);
		glUseProgram(meshData->program);

		glm::mat4 transformMatrix = g_renderFramework->camToClipMatx * modelToWorldMatrix;
		glUniformMatrix4fv(meshData->mvpMatrixUnf, 1, GL_FALSE, &transformMatrix[0][0]);

		glBindBuffer(GL_ARRAY_BUFFER, meshData->vertexBuffer);
		glEnableVertexAttribArray(RenderFramework::VERTEX_POSITION);
		glVertexAttribPointer(RenderFramework::VERTEX_POSITION, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		if (meshData->bufferInfo.isColors)
		{
			glBindBuffer(GL_ARRAY_BUFFER, meshData->colorBuffer);
			glEnableVertexAttribArray(RenderFramework::VERTEX_COLOR);
			glVertexAttribPointer(RenderFramework::VERTEX_COLOR, 4, GL_FLOAT, GL_FALSE, 0, 0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshData->indexBuffer);
		glDrawElements(GL_TRIANGLES, meshData->bufferInfo.indexSize, GL_UNSIGNED_INT, 0);

		glDisableVertexAttribArray(RenderFramework::VERTEX_POSITION);
		glDisableVertexAttribArray(RenderFramework::VERTEX_COLOR);
		glUseProgram(0);
		glBindVertexArray(0);
	}
}

}
