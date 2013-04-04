#include "Mesh.h"
#include "res/ResourceManager.h"
#include "RenderFramework.h"

#include <sstream>
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <vector>

#define ARRAY_COUNT( array ) (sizeof( array ) / (sizeof( array[0] ) * (sizeof( array ) != sizeof(void*) || sizeof( array[0] ) <= sizeof(void*))))

namespace scim
{

extern RenderFramework* g_renderFramework;

MeshData::MeshData(const std::vector<F32> &vertexList, const std::vector<F32> &colorList, const std::vector<U32> &indexList, GLuint program) :
	program(program)
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, (vertexList.size() * sizeof(F32)), &vertexList[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, (colorList.size() * sizeof(F32)), &colorList[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (indexList.size() * sizeof(U32)), &indexList[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	mvpMatrixUnf = glGetUniformLocation(program, "mvp");

	bufferSizes =
	{
		(U16)vertexList.size(),
		(U16)indexList.size()
	};
}
MeshData::~MeshData()
{
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &colorBuffer);
	glDeleteBuffers(1, &indexBuffer);
	glDeleteVertexArrays(1, &VAO);
}

Mesh::Mesh(const XMLNode& compRootNode)
{
	XMLNode vertexNode = compRootNode.getChildNode("vertex");
	std::stringstream strVertex(vertexNode.getText());

	XMLNode colorNode = compRootNode.getChildNode("color");
	std::stringstream strColors(colorNode.getText());

	XMLNode indexNode = compRootNode.getChildNode("index");
	std::stringstream strIndicies(indexNode.getText());


	std::vector<F32> vertexList = ResourceManager::GetListFromSpacedString<F32>(strVertex.str());
	std::vector<F32> colorList  = ResourceManager::GetListFromSpacedString<F32>(strColors.str());
	std::vector<U32> indexList  = ResourceManager::GetListFromSpacedString<U32>(strIndicies.str());

	std::vector<GLuint> shaderList;
	for (I8 i = 0; i < 2; ++i)
	{
		XMLNode shaderNode = compRootNode.getChildNode("program").getChildNode("shader", i);
		const char* shaderType = shaderNode.getAttribute("type");
		if (strcmp(shaderType, "vertex") == 0)
		{
			shaderList.push_back(g_renderFramework->LoadShader(GL_VERTEX_SHADER, shaderNode.getText()));
		} else if (strcmp(shaderType, "fragment") == 0)
		{
			shaderList.push_back(g_renderFramework->LoadShader(GL_FRAGMENT_SHADER, shaderNode.getText()));
		} else
		{
			std::cout << "Error: invalid shader element type" << std::endl;
		}
	}

	GLuint program = glCreateProgram();
	g_renderFramework->LinkProgram(program, shaderList);


	m_meshData = new MeshData(vertexList, colorList, indexList, program);
}
Mesh::~Mesh()
{
	delete m_meshData;
}

void Mesh::Render(const glm::mat4& modelToWorldMatrix)
{
	glBindVertexArray(m_meshData->VAO);
	glUseProgram(m_meshData->program);

	glm::mat4 transformMatrix = modelToWorldMatrix;
	glUniformMatrix4fv(m_meshData->mvpMatrixUnf, 1, GL_FALSE, &transformMatrix[0][0]);

	glBindBuffer(GL_ARRAY_BUFFER, m_meshData->vertexBuffer);
	glEnableVertexAttribArray(RenderFramework::VERTEX_POSITION);
	glVertexAttribPointer(RenderFramework::VERTEX_POSITION, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_meshData->colorBuffer);
	glEnableVertexAttribArray(RenderFramework::VERTEX_COLOR);
	glVertexAttribPointer(RenderFramework::VERTEX_COLOR, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_meshData->indexBuffer);
	glDrawElements(GL_TRIANGLES, m_meshData->bufferSizes.index, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(RenderFramework::VERTEX_POSITION);
	glDisableVertexAttribArray(RenderFramework::VERTEX_COLOR);
	glUseProgram(0);
	glBindVertexArray(0);
}

}
