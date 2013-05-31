#include "graphics/MeshTools.h"
#include "graphics/AssimpMesh.h"
#include "res/ResourceManager.h"
#include "graphics/RenderFramework.h"
#include "graphics/XMLMesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <xmlParser.h>
#include <GL/glew.h>

#include <map>
#include <vector>
#include <iostream>

namespace scim
{

namespace MeshTools
{

namespace
{
	struct MeshConsData
	{
		const std::string meshName;
		GLuint program;
	};
	MeshConsData GetMeshData(const std::string& entityName)
	{
		static const MeshConsData voidData =
		{
			std::string(),
			0
		};

		std::string entityFileContents = ResourceManager::GetFileContents("entity/" + entityName + ".xml");
		XMLResults* res = NULL;
		XMLNode entityNode = XMLNode::parseString(entityFileContents.c_str(), "breed", res);
		if (res)
		{
			LOG_ERR("Invalid XML resource: %s", entityName.c_str());
			return voidData;
		}
		std::string meshName = entityNode.getChildNode("mesh").getAttribute("name");

		std::vector<GLuint> shaderList;
		for (I8 i = 0; i < 2; ++i)
		{
			XMLNode shaderNode = entityNode.getChildNode("program").getChildNode("shader", i);
			const char* shaderType = shaderNode.getAttribute("type");
			if (strcmp(shaderType, "vertex") == 0)
			{
				shaderList.push_back(RenderFramework::LoadShader(GL_VERTEX_SHADER, shaderNode.getText() + std::string(".vert")));
			} else if (strcmp(shaderType, "fragment") == 0)
			{
				shaderList.push_back(RenderFramework::LoadShader(GL_FRAGMENT_SHADER, shaderNode.getText() + std::string(".frag")));
			} else
			{
				std::cout << "Error: invalid shader element type" << std::endl;
			}
		}

		GLuint program = glCreateProgram();
		if (!RenderFramework::LinkProgram(program, shaderList))
		{
			return voidData;
		}

		MeshConsData mcd =
		{
			meshName,
			program
		};

		return mcd;
	}

	AssimpMesh* GetAssimpMesh(const MeshConsData mcd)
	{
		static std::map<const std::string, AssimpMesh*> meshMap;

		const std::string& meshName =  mcd.meshName;
		GLuint program = mcd.program;

		if (meshMap.find(meshName) != meshMap.end())
		{
			return meshMap.find(meshName)->second;
		}

		std::string fileContents = ResourceManager::GetFileContents("graphics/mesh/" + meshName);
		Assimp::Importer importer;

		const aiScene* scene = importer.ReadFileFromMemory(fileContents.c_str(),
			fileContents.size(),
			aiProcess_Triangulate |
				aiProcess_JoinIdenticalVertices |
				aiProcessPreset_TargetRealtime_Quality,
			""
		);

		if(!scene)
	 	{
			LOG_ERR("%s", importer.GetErrorString());
		}

		meshMap[meshName] = new AssimpMesh(scene, program);
		return meshMap.find(meshName)->second;
	}
	XMLMesh* GetXMLMesh(const MeshConsData mcd)
	{
		static std::map<const std::string, XMLMesh*> meshMap;

		const std::string& meshName =  mcd.meshName;
		GLuint program = mcd.program;

		if (meshMap.find(meshName) != meshMap.end())
		{
			return meshMap.find(meshName)->second;
		}

		std::string meshSource = ResourceManager::GetFileContents("graphics/mesh/" + meshName);
		XMLResults* res = NULL;
		XMLNode meshNode = XMLNode::parseString(meshSource.c_str(), "mesh", res);
		if (res)
		{
			LOG_ERR("invlaid mesh resource");
		}

		meshMap[meshName] = new XMLMesh(meshNode, program);
		return meshMap.find(meshName)->second;
	}
}

template <>
AssimpMesh* GetMesh<AssimpMesh>(const std::string& entityName)
{
	return GetAssimpMesh(GetMeshData(entityName));
}
template <>
XMLMesh* GetMesh<XMLMesh>(const std::string& entityName)
{
	return GetXMLMesh(GetMeshData(entityName));
}

}

}
