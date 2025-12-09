#pragma once
#include "IExecute.h"

class TextureBufferDemo : public IExecute
{

public:
	void Init() override;
	void Update() override;
	void Render() override;



private:
	shared_ptr<Shader> _shader;


private:
	// 가공이 끝난 이미지 파일의 View를 리턴하는 함수
	ComPtr<ID3D11ShaderResourceView> MakeComputeShaderTexture();
};

