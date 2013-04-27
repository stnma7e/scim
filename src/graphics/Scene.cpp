#include "graphics/Scene.h"
#include "graphics/RenderFramework.h"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <sstream>

namespace scim
{

Scene::Scene()
{
	// root node identity index
	m_wmat.push_back(glm::mat4(1));
	m_lmat.push_back(glm::mat4(1));
	m_parents.push_back(0);
	m_meshes.push_back(NULL);
}
SceneNode Scene::CreateNode(U32 parentNode, IMesh* mesh)
{
	m_wmat.push_back(glm::mat4(1));
	m_lmat.push_back(glm::mat4(1));
	m_meshes.push_back(mesh);

	m_parents.push_back(parentNode);

	SceneNode sn =
	{
		(U32)m_wmat.size() - 1,		// node index
		&m_wmat[m_wmat.size()],		// wmat pointer
		&m_lmat[m_lmat.size()],		// lmat pointer
		m_parents[m_wmat.size()],	// parent node
		(IMesh*)mesh
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
		m_parents[nodeIndex],
		(IMesh*)m_meshes[nodeIndex]
	};
}

void Scene::UpdateNodes()
{
	U32* 				parents = &m_parents[0];
	glm::mat4* 			wmat = &m_wmat[0];
	glm::mat4* 			lmat = &m_lmat[0];

	wmat[0] = lmat[0];
	for (size_t i = 1; i < m_lmat.size(); ++i)
	{
		const U32 parentNode = parents[i];
		wmat[i] = wmat[parentNode] * lmat[i];
	}
}

void Scene::RenderNodes()
{
	for (size_t i = 1; i < m_meshes.size(); ++i)
	{
		m_meshes[i]->Render((*RenderFramework::GetCamToClipMatrix()) * m_wmat[i]);
	}
}

}
