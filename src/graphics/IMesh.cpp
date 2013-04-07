#include "IMesh.h"
#include "RenderFramework.h"

#include <iostream>
#include <GL/glfw.h>

namespace scim
{

MeshData::MeshData(GLuint program,
	const std::vector<glm::vec3> &vertexList,
	const std::vector<U32> &indexList,
	const std::vector<glm::vec4> &colorList,
	const std::vector<glm::vec2> &texUVList,
	const std::vector<glm::vec3> &normalList,
	const std::vector<GLuint> &textureList
) : program(program), textureList(textureList)
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

	if (!texUVList.empty())
	{
		glGenBuffers(1, &textureBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
		glBufferData(GL_ARRAY_BUFFER, (texUVList.size() * sizeof(glm::vec2)), &texUVList[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	mvpMatrixUnf = glGetUniformLocation(program, "mvp");
	texUnitUnf = glGetUniformLocation(program, "texUnit");

	bufferInfo.vertexSize = (U16)vertexList.size();
	bufferInfo.indexSize  =	(U16)indexList.size();
	bufferInfo.isColored    =	colorList.empty()   ? false : true;
	bufferInfo.isTextured   =	textureList.empty() ? false : true;
	bufferInfo.hasNormals   =	normalList.empty()  ? false : true;
}
MeshData::~MeshData()
{
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &colorBuffer);
	glDeleteBuffers(1, &indexBuffer);
	for (GLuint tex: textureList)
		glDeleteTextures(1, &tex);
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

		glm::mat4 transformMatrix = (*RenderFramework::GetCamToClipMatrix()) * modelToWorldMatrix;
		glUniformMatrix4fv(meshData->mvpMatrixUnf, 1, GL_FALSE, &transformMatrix[0][0]);

		glBindBuffer(GL_ARRAY_BUFFER, meshData->vertexBuffer);
		glEnableVertexAttribArray(RenderFramework::VERTEX_POSITION);
		glVertexAttribPointer(RenderFramework::VERTEX_POSITION, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		if (meshData->bufferInfo.isColored)
		{
			glBindBuffer(GL_ARRAY_BUFFER, meshData->colorBuffer);
			glEnableVertexAttribArray(RenderFramework::VERTEX_COLOR);
			glVertexAttribPointer(RenderFramework::VERTEX_COLOR, 4, GL_FLOAT, GL_FALSE, 0, 0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
		if (meshData->bufferInfo.isTextured)
		{
			for (size_t i = 0; i < meshData->textureList.size(); ++i)
			{
				GLuint tex = meshData->textureList[i];
				glUniform1i(meshData->texUnitUnf, 0);
				glActiveTexture(GL_TEXTURE0 + i);
				glBindTexture(GL_TEXTURE_2D, tex);

				glBindBuffer(GL_ARRAY_BUFFER, meshData->textureBuffer);
				glEnableVertexAttribArray(RenderFramework::TEXTURE_UV);
				glVertexAttribPointer(RenderFramework::TEXTURE_UV, 2, GL_FLOAT, GL_FALSE, 0, 0);
				glBindBuffer(GL_ARRAY_BUFFER, 0);
			}
		}

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshData->indexBuffer);
		glDrawElements(GL_TRIANGLES, meshData->bufferInfo.indexSize, GL_UNSIGNED_INT, 0);

		glDisableVertexAttribArray(RenderFramework::VERTEX_POSITION);
		glDisableVertexAttribArray(RenderFramework::VERTEX_COLOR);
		glDisableVertexAttribArray(RenderFramework::TEXTURE_UV);
		glUseProgram(0);
		glBindVertexArray(0);
	}
}

}
