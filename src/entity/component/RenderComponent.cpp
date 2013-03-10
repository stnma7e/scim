#include "RenderComponent.h"
#include "../../graphics/RenderFramework.h"
#include "../../graphics/Mesh.h"

#include <iostream>

namespace scim
{

I8 RenderComponent::plusOne = 0;
extern RenderFramework* g_renderFramework;

RenderComponent::RenderComponent(GameObject* owner, const XMLNode& compRoot) : GameComponent(owner, GameComponent::RENDER)
{
	glGenBuffers(1, &m_VBO);
	m_mesh =  new Mesh(compRoot);

	// std::cout << "mesh: " << sizeof(m_mesh->GetMeshData()->m_attribArray.data() * m_mesh->GetMeshData()->m_attribArray.data()) << ", vertData: " << sizeof(vertData) << std::endl;
	// std::cout << "F32: " << 288 * sizeof(float) << std::endl;

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	const std::vector<F32>& attribArray = m_mesh->GetMeshData()->m_attribArray;
	glBufferData(GL_ARRAY_BUFFER, sizeof(attribArray.data()) * attribArray.size(), attribArray.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	m_plusOne = plusOne++;
}

bool RenderComponent::Init()
{
	return true;
}
void RenderComponent::Render()
{
	GLuint theProgram = g_renderFramework->theProgram;
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	glUseProgram(theProgram);

	glUniform2f(g_renderFramework->modelToCamUnf, 0.5f + m_plusOne, 0.5f + m_plusOne);

	const std::vector<F32>& attribArray = m_mesh->GetMeshData()->m_attribArray;
	size_t colorData = (sizeof(attribArray.data()) * attribArray.size()) / 2;
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)colorData);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glUseProgram(0);
}

}
