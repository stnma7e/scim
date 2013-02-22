#include "RenderComponent.h"
#include "../../graphics/RenderFramework.h"

#include <iostream>

namespace scim
{

char RenderComponent::plusOne = 0;

RenderComponent::RenderComponent(GameObject* owner, const float vertDatafds[]) : GameComponent(owner, GameComponent::RENDER)
{
	glGenBuffers(1, &m_VBO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertData), vertData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	m_plusOne = plusOne++;
}

bool RenderComponent::Init()
{
	return 1;
}
void RenderComponent::Render()
{
	GLuint theProgram = RenderFramework::GetInstance().theProgram;
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	glUseProgram(theProgram);

	glUniform2f(RenderFramework::GetInstance().modelToCamUnf, 0.5f + m_plusOne, 0.5f + m_plusOne);

	size_t colorData = sizeof(vertData) / 2;
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
