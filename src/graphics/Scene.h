#ifndef SCENE_H_
#define SCENE_H_

#include <glm/glm.hpp>
#include <vector>

namespace scim
{

struct SceneNode
{
	glm::mat4*		wmat;
	glm::mat4* 		lmat;
	U32 			parentNode;
};

class Scene
{
	std::vector<glm::mat4> 		m_wmat;	// world transform matrix list
	std::vector<glm::mat4> 		m_lmat;	// local transform matrix list

	U32 m_parents[65536];
public:
	enum SceneConstant
	{
		ROOT_NODE = 0
	};

	Scene();
	void UpdateNodes();
	void RenderNodes();
	SceneNode CreateNode(U32 parentNode);

	const SceneNode GetNode(U32 nodeIndex);
};

}

#endif
