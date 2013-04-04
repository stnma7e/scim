#include "Scene.h"
#include "math/Vec3.h"

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
	std::cout << "mat " << 0 << ": " << std::endl;
	for (int j = 0; j < 4; ++j)
	{
		printf("row %d: ", j);
		for (int k = 0; k < 4; ++k)
		{
			printf("%f, ", m_lmat[0][j][k]);
		}
		printf("\n");
	}
	printf("\n");
}
SceneNode Scene::CreateNode(U32 parentNode)
{
	m_wmat.push_back(glm::mat4(1));
	m_lmat.push_back(glm::mat4(1));

	m_parents[m_wmat.size()] = parentNode;

	SceneNode sn;
	sn.wmat 		= &m_wmat[m_wmat.size()];
	sn.lmat 		= &m_lmat[m_lmat.size()];
	sn.parentNode	= m_parents[m_wmat.size()];

	return sn;
}
const SceneNode Scene::GetNode(U32 nodeIndex)
{
	return SceneNode
	{
		&m_wmat.data()[nodeIndex],
		&m_lmat.data()[nodeIndex],
		m_parents[nodeIndex]
	};
}

void Scene::UpdateNodes()
{
	U32* 				parents = m_parents;
	glm::mat4* 			wmat = &m_wmat[0];
	glm::mat4* 			lmat = &m_lmat[0];

	wmat[0] = lmat[0];
	for (size_t i = 1; i < m_lmat.size(); ++i)
	{
		wmat[i] = wmat[parents[i]] * lmat[i];
	}
}

}
