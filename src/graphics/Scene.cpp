#include "Scene.h"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

namespace scim
{

Scene::Scene()
{
	m_wmat.push_back(glm::mat4(1));
	m_lmat.push_back(glm::mat4(1));

	m_parents[0] = 0;

	m_lmat[0] = glm::translate(m_lmat[0], glm::vec3(2,2,2));
}
SceneNode Scene::CreateNode(U32 parentNode)
{
	m_wmat.push_back(glm::mat4(1));
	m_lmat.push_back(glm::mat4(1));

	m_parents[m_wmat.size()] = parentNode;

	SceneNode sn =
	{
		(U32)m_wmat.size() - 1,		// node index
		&m_wmat[m_wmat.size()],		// wmat pointer
		&m_lmat[m_lmat.size()],		// lmat pointer
		m_parents[m_wmat.size()]	// parent node
	};

	return sn;
}
const SceneNode Scene::GetNode(U32 nodeIndex)
{
	return SceneNode
	{
		nodeIndex,
		&m_wmat.data()[nodeIndex],
		&m_lmat.data()[nodeIndex],
		m_parents[nodeIndex]
	};
}

void Scene::UpdateNodes()
{
	U32* 				parents = m_parents;
	glm::mat4* 			wmat = m_wmat.data();
	glm::mat4* 			lmat = m_lmat.data();

	wmat[0] = lmat[0];
	for (size_t i = 1; i < m_lmat.size(); ++i)
	{
		const U32 parentNode = parents[i];
		wmat[i] = wmat[parentNode] * lmat[i];
	}
}

}
