/*
 * Object Loader class implementation
 * @author Nathan McCulloch
 */


#include "ObjLoader.hpp"
#include <iostream>
#include <vector>
#include <stdio.h>
#include <string>
#include <cstring>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h> 

ObjLoader::ObjLoader() {

}

bool ObjLoader::loadOBJ(
	const char * path, 
	std::vector<glm::vec3> &out_vertices, 
	std::vector<glm::vec2> &out_uvs, 
	std::vector<glm::vec3> &out_normals
	) {
	std::cout << "Loading OBJ file " << path << "\n" << std::endl;


	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> temp_vertices; 
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;


	FILE * file = fopen(path, "r");
	if( file == NULL ){
		printf("Impossible to open the file.\n");
		getchar();
		return false;
	}

	while(1){

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

		// else : parse lineHeader
		
		if ( strcmp( lineHeader, "v" ) == 0 ){
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
			temp_vertices.push_back(vertex);
		}else if ( strcmp( lineHeader, "vt" ) == 0 ){
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y );
			uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
			temp_uvs.push_back(uv);
		}else if ( strcmp( lineHeader, "vn" ) == 0 ){
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
			temp_normals.push_back(normal);
		}else if ( strcmp( lineHeader, "f" ) == 0 ){
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
			if (matches != 9){
				printf("File can't be read by the simple parser\n");
				fclose(file);
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices    .push_back(uvIndex[0]);
			uvIndices    .push_back(uvIndex[1]);
			uvIndices    .push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}else{
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}

	}

	// For each vertex of each triangle
	for( unsigned int i=0; i<vertexIndices.size(); i++ ){

		// Get the indices of its attributes
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices[i];
		unsigned int normalIndex = normalIndices[i];
		
		// Get the attributes thanks to the index
		glm::vec3 vertex = temp_vertices[ vertexIndex-1 ];
		glm::vec2 uv = temp_uvs[ uvIndex-1 ];
		glm::vec3 normal = temp_normals[ normalIndex-1 ];
		
		// Put the attributes in buffers
		out_vertices.push_back(vertex);
		out_uvs     .push_back(uv);
		out_normals .push_back(normal);
	
	}
	fclose(file);
	return true;
}


bool ObjLoader::loadOBJMTL( const char * path, Group * outputMesh ) {
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(path, 0);

	if (!scene) {
		std::cout << importer.GetErrorString() << std::endl;
		return false;
	}

	if (scene->mNumMeshes > 0) {
		int meshIndex = 0;

		while (meshIndex < scene->mNumMeshes) {
			std::vector<unsigned short> indices;
			std::vector<glm::vec3> indexed_vertices;
			std::vector<glm::vec2> indexed_uvs;
			std::vector<glm::vec3> indexed_normals;

			aiMesh* mesh = scene->mMeshes[meshIndex];

			indexed_vertices.reserve(mesh->mNumVertices);
			for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
				aiVector3D pos = mesh->mVertices[i];
				indexed_vertices.push_back(glm::vec3(pos.x, pos.y, pos.z));
			}

			indexed_uvs.reserve(mesh->mNumVertices);
			for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
				if (mesh->mTextureCoords[0] != NULL) {
					aiVector3D UVW = mesh-> mTextureCoords[0][i];
					indexed_uvs.push_back(glm::vec2(UVW.x, UVW.y));
				}
			}

			indexed_normals.reserve(mesh->mNumVertices);
			for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
				aiVector3D n = mesh->mNormals[i];
				indexed_normals.push_back(glm::vec3(n.x, n.y, n.z));
			}

			indices.reserve(mesh->mNumFaces);
			for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
				indices.push_back(mesh->mFaces[i].mIndices[0]);
				indices.push_back(mesh->mFaces[i].mIndices[1]);
				indices.push_back(mesh->mFaces[i].mIndices[2]);
			}


			Mesh* geom = new Mesh();
			geom->setVertices(indexed_vertices);
			geom->setUVs(indexed_uvs);
			geom->setNormals(indexed_normals);
			geom->setIndices(indices);
			geom->setMaterialIndex(mesh->mMaterialIndex);

			outputMesh->addMesh(geom);
			meshIndex++;
		}
	}

	if (scene->mNumMaterials > 0) {
		Material* material;
		int materialIndex = 0;
		while (materialIndex < scene->mNumMaterials) {
			if (scene-> mMaterials[materialIndex] != NULL) {
				material = new Material();
				aiColor3D color (0.0f, 0.0f, 0.0f);
				aiString texPath;
				float opacity;
				scene->mMaterials[materialIndex]->Get(AI_MATKEY_COLOR_DIFFUSE, color);
				material->setDiffuseColour(glm::vec3(color[0], color[1], color[2]));

				scene->mMaterials[materialIndex]->Get(AI_MATKEY_COLOR_AMBIENT, color);
				material->setAmbientColour(glm::vec3(color[0], color[1], color[2]));

				scene->mMaterials[materialIndex]->Get(AI_MATKEY_COLOR_SPECULAR, color);
				material->setSpecularColour(glm::vec3(color[0], color[1], color[2]));

				scene->mMaterials[materialIndex]->Get(AI_MATKEY_OPACITY, opacity);
				material->setOpacity(opacity);

				if (scene->mMaterials[materialIndex]->GetTexture(aiTextureType_DIFFUSE, 0, &texPath, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
					material->setTextureName(texPath.data);
				}
				outputMesh->addMaterial(material);
			}
			materialIndex++;
		}
	}

	return true;
}