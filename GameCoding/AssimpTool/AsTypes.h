#pragma once

using VertexType = VertexTextureNormalTangentBlendData;

struct asBone
{
	string name;
	int32 index = -1;
	int32 parent = -1;
	Matrix transform;
};

struct asMesh
{
	string name;
	aiMesh* mesh;	//async에서 로드한 메쉬
	vector<VertexType> vertices;
	vector<uint32> indices;

	int32 boneIndex;
	string materialName;
};

struct asMaterial
{
	string name;
	Color ambient;
	Color diffuse;
	Color specular;
	Color emissive;

	string diffuseFile;
	string specularFile;
	string normalFile;
};


// Animation

struct asBlendWeight
{
	void Set(uint32 index, uint32 boneIndex, float weight)
	{
		float i = (float)boneIndex;
		float w = weight;

		switch (index)
		{
		case 0: indices.x = i; weights.x = w; break;
		case 1: indices.y = i; weights.y = w; break;
		case 2: indices.z = i; weights.z = w; break;
		case 3: indices.w = i; weights.w = w; break;
		}
	}

	Vec4 indices = Vec4(0, 0, 0, 0);
	Vec4 weights = Vec4(0, 0, 0, 0);
};

// 정점마다 -> (뼈번호, 가중치)
struct asBoneWeights
{
	void AddWeights(uint32 boneIndex, float weight)
	{
		if (weight <= 0.0f)
			return;

		auto findit = std::find_if(boneWeights.begin(), boneWeights.end(),
			[weight](const Pair& p) {return weight > p.second; });

		boneWeights.insert(findit, Pair(boneIndex, weight));
	}

	asBlendWeight GetBlendWeights()
	{
		asBlendWeight blendWeights;

		for (uint32 i = 0; i < boneWeights.size(); i++)
		{
			if (i >= 4)
				break;

			blendWeights.Set(i, boneWeights[i].first, boneWeights[i].second);
		}

		return blendWeights;
	}

	// (1, 0.3) (2, 0.2) -> 두개의 합인 0.5이 최종 가중치가 되는데 합이 1이 되어야하기에 2를 곱해준다.
	void Normalize()
	{
		if (boneWeights.size() >= 4)
			boneWeights.resize(4);

		float totalWeight = 0.f;
		for (const auto& item : boneWeights)
			totalWeight += item.second;

		// 가중치의 합을 1로 만들어주는
		for (auto& item : boneWeights)
			item.second /= totalWeight;
	}

	using Pair = pair<int32, float>;
	vector<Pair> boneWeights;
};

// Animation Cilp
struct asKeyframeData
{
	float time;
	Vec3 scale;
	Quaternion rotation;
	Vec3 translation;
};

struct asKeyframe
{
	string boneName;
	vector<asKeyframeData> transforms;
};

struct asAnimation
{
	string name;
	uint32 frameCount;		// 
	float frameRate;		// = 30; 이면, 30분의 1초마다 애니메이션이 다음 프레임으로 넘어가는
	float duration;			// 지속 시간
	vector<shared_ptr<asKeyframe>> keyframes;
};

// 원본을 담아둘 Cache
struct asAnimationNode
{
	aiString name;
	vector<asKeyframeData> keyframe;
};