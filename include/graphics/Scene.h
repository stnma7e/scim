#ifndef SCENE_H_
#define SCENE_H_

#include "IMesh.h"

#include <glm/glm.hpp>
#include <vector>
#include <stdio.h>
#include <iostream>

namespace scim
{

struct SceneNode
{
	U32 			index;
	glm::mat4*		wmat;
	glm::mat4* 		lmat;
	U32 			parentNode;
	IMesh*			mesh;
};

class Scene
{
	std::vector<glm::mat4> 		m_wmat;	// world transform matrix list
	std::vector<glm::mat4> 		m_lmat;	// local transform matrix list
	std::vector<const IMesh*>	m_meshes;

	std::vector<U32> 			m_parents;
public:
	enum SceneConstant
	{
		ROOT_NODE = 0
	};

	static void PrintMatrix(const glm::mat4& matToPrint)
	{
		for (int j = 0; j < 4; ++j)
		{
			printf("row %d: ", j);
			for (int k = 0; k < 4; ++k)
			{
				std::cout << matToPrint[k][j] << ", ";	// row major order
			}
			printf("\n");
		}
		printf("\n");
	}

	Scene();
	void UpdateNodes();
	void RenderNodes();
	SceneNode CreateNode(U32 parentNode, IMesh* mesh);

	const SceneNode GetNode(U32 nodeIndex);
};

}

#endif
