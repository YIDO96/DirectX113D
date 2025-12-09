#pragma once
#include "Component.h"
class Terrain : public Component
{
public:
	Terrain();
	~Terrain();

	void Create(int32 sizeX, int32 sizeZ, shared_ptr<Material> material);

	bool Pick(int32 screenX, int32 screenY, Vec3& pickPos, float& distance);

	int32 GetSizeX() { return _sizeX; }
	int32 GetSizeZ() { return _sizeZ; }

private:
	shared_ptr<Mesh> _mesh;
	int32 _sizeX = 0;
	int32 _sizeZ = 0;
};