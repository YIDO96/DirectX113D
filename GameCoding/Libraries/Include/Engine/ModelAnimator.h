#pragma once
#include "Component.h"

class Model;

struct AnimTransform
{

	using TransformArrayType = array<Matrix, MAX_MODEL_TRANSFORMS>; // 250개의 관절 정보를 담아두기

	array<TransformArrayType, MAX_MODEL_KEYFRAMES> transforms;		// 2차 배열

};

class ModelAnimator : public Component
{
	using Super = Component;

public:
	ModelAnimator(shared_ptr<Shader> shader);
	~ModelAnimator();

	//virtual void Update() override;


	void SetModel(shared_ptr<Model> model);
	void SetPass(uint8 pass) { _pass = pass; }
	shared_ptr<Shader> GetShader() { return _shader; }
	void UpdateTweenData();
	void RenderInstancing(shared_ptr<class InstancingBuffer>& buffer);
	InstanceID GetInstanceID();
	TweenDesc& GetTweenDesc() { return _tweenDesc; }

private:
	void CreateTexture();
	void CreateAnimationTransform(uint32 index);

private:
	vector<AnimTransform> _animTransforms;
	ComPtr<ID3D11Texture2D> _texture;
	ComPtr<ID3D11ShaderResourceView> _srv;

private:
	//KeyframeDesc _keyframeDesc;
	TweenDesc _tweenDesc;

private:
	shared_ptr<Shader>	_shader;
	uint8				_pass = 0;
	shared_ptr<Model>	_model;
};

