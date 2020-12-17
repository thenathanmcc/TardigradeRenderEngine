/*
 * Group class definition. Used to hold Objects with multiple meshes
 * and materials
 * @author Nathan McCulloch
 */



#ifndef GROUP_HPP
#define GROUP_HPP

#include "Object.hpp"
#include "Texture.hpp"
#include "Mesh.hpp"
#include "Material.hpp"


class Group: public Object {
public:

	Group();

	~Group();

	void addMesh(Mesh* mesh);

	void addMaterial(Material* material);

	Mesh* getMesh(int index);

	Material* getMaterial(int index);

	int getNumMeshes();

	void setRenderMode(float renderMode);

	void init();

	void render(Camera* camera);

	void setupShaders();

private:
	std::vector<Mesh*> m_meshes;
	std::vector<Material*> m_materials;
};
#endif