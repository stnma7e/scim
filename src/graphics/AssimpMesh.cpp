#include "AssimpMesh.h"
#include "res/ResourceManager.h"

#include <iostream>
#include <stdio.h>
#include <GL/glfw.h>
#include <logging/logging.h>

namespace scim
{

AssimpMesh::AssimpMesh(const aiScene* pScene, GLuint shaderProgram)
{
    static const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);
	fprintf(stderr, "has textures: %s\n", pScene->HasTextures() ? "true" : "false");
	fprintf(stderr, "has texture coords: %s\n", pScene->mMeshes[0]->HasTextureCoords(0) ? "true" : "false");

    GLint linked;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linked);
    assert(linked == GL_TRUE);

	for (size_t i = 0; i < pScene->mNumMeshes; ++i)
	{
		const aiMesh* mesh = pScene->mMeshes[i];

		std::vector<glm::vec3> 	vertexList;
		std::vector<glm::vec3> 	normalList;
		std::vector<glm::vec2> 	uvList;
		std::vector<U32>		indexList;

		for (size_t i = 0; i < mesh->mNumVertices; ++i)
		{
			const aiVector3D* pPos = &(mesh->mVertices[i]);
			const aiVector3D* pNormal = &(mesh->mNormals[i]);
			const aiVector3D* pTexCoord = mesh->HasTextureCoords(0) ? &(mesh->mTextureCoords[0][i]) : &Zero3D;

			glm::vec3 vert(pPos->x, pPos->y, pPos->z);
			glm::vec3 norm(pNormal->x, pNormal->y, pNormal->z);
			glm::vec2 uv(pTexCoord->x, pTexCoord->y);

			vertexList.push_back(vert);
			normalList.push_back(norm);
			uvList.push_back(uv);
		}

		for (size_t i = 0; i < mesh->mNumFaces; ++i)
		{
			const aiFace& Face = mesh->mFaces[i];
			// assert(Face.mNumIndices == 3);
			indexList.push_back(Face.mIndices[0]);
			indexList.push_back(Face.mIndices[1]);
			indexList.push_back(Face.mIndices[2]);
		}

		std::vector<GLuint> textureIDs;
		for (size_t i = 0; i < pScene->mNumMaterials; ++i)
		{
        	const aiMaterial* pMaterial = pScene->mMaterials[i];

			if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0)
			{
				aiString Path;

				if (pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
				{
					std::cout << Path.data << std::endl;
					GLuint textureID;
					if (ResourceManager::LoadRGBATexture(Path.data, &textureID))
					{
						textureIDs.push_back(textureID);
					}

				}
			} else
			{
				logging::log::emit<logging::Error>() << "cannot init texture" << logging::log::endl;
			}
		}

		m_subMeshes.push_back(new MeshData(shaderProgram,
			vertexList,
			indexList,
			std::vector<glm::vec4>(), 	// empty colorList
			uvList,
			normalList,
			textureIDs
		));
	}
}

}
