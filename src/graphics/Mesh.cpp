#include "Mesh.h"
#include "../res/ResourceManager.h"
#include "RenderFramework.h"

#include <sstream>
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string.h>

#define ARRAY_COUNT( array ) (sizeof( array ) / (sizeof( array[0] ) * (sizeof( array ) != sizeof(void*) || sizeof( array[0] ) <= sizeof(void*))))

namespace scim
{

MeshData::MeshData(const std::vector<F32> &attribList, const std::vector<I32> &indexList, GLuint program) : m_program(program), m_attribArray(attribList)
{
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glGenBuffers(1, &m_attribBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_attribBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(attribList.data()), attribList.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &m_indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexList.data()), indexList.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glUseProgram(m_program);

    m_modelToCamUnf = glGetUniformLocation(m_program, "modelToCamMatx");
}
MeshData::~MeshData()
{
	glDeleteBuffers(1, &m_attribBuffer);
	glDeleteBuffers(1, &m_indexBuffer);
	glDeleteVertexArrays(1, &m_VAO);
}

Mesh::Mesh(const XMLNode& compRootNode)
{
	XMLNode attribNode = compRootNode.getChildNode("attrib");
	std::stringstream strAttribs(attribNode.getText());
	XMLNode indexNode = compRootNode.getChildNode("indicies");
	std::stringstream strIndicies(indexNode.getText());

	std::vector<F32> attribList = ResourceManager::GetInstance().GetListFromSpacedString<F32>(strAttribs.str());
	std::vector<I32> indexList  = ResourceManager::GetInstance().GetListFromSpacedString<I32>(strIndicies.str());

	GLuint vertShader = 0, fragShader = 0;
	for (I8 i = 0; i < 2; ++i)
	{
		XMLNode shaderNode = compRootNode.getChildNode("program").getChildNode("shader");
		if (strcmp(shaderNode.getAttribute("type"), "vertex") == 0)
		{
			GLuint vertShader = RenderFramework::GetInstance().LoadShader(GL_VERTEX_SHADER, shaderNode.getText());
		} else if (strcmp(shaderNode.getAttribute("type"), "fragment") == 0)
		{
			GLuint fragShader = RenderFramework::GetInstance().LoadShader(GL_FRAGMENT_SHADER, shaderNode.getText());
		} else
		{
			std::cout << "Error: invalid shader element type" << std::endl;
		}
	}

	GLuint program = glCreateProgram();
	RenderFramework::GetInstance().LinkProgram(program, vertShader, fragShader);


	m_meshData = new MeshData(attribList, indexList, program);
}
Mesh::~Mesh()
{
	delete m_meshData;
}

void Mesh::Render()
{
	glBindVertexArray(m_meshData->m_VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_meshData->m_indexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_meshData->m_attribBuffer);
	glUseProgram(m_meshData->m_program);

	glUniform2f(m_meshData->m_modelToCamUnf, 0.5f, 0.5f);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(m_meshData->m_attribArray.data()) / 2));

	glDrawArrays(GL_TRIANGLES, 0, ARRAY_COUNT(m_meshData->m_attribArray.data()));

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glUseProgram(0);
	glBindVertexArray(0);
}

}
