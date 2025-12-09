#pragma once
class RawBuffer
{
public:
	RawBuffer(void* inputData, uint32 inputByte, uint32 outputByte);
	~RawBuffer();

public:
	// 모든 Create함수를 호출해주는 함수
	void CreateBuffer();

	// CPU쪽에서 데이터 가져오는 함수
	void CopyToInput(void* data);
	// 결과값을 가져오는 함수
	void CopyFromOutput(void* data);

public:
	ComPtr<ID3D11ShaderResourceView> GetSRV() { return _srv; }
	ComPtr<ID3D11UnorderedAccessView> GetUAV() { return _uav; }


	// 버퍼와 view를 만들어주는 함수
private:
	void CreateInput();
	void CreateSRV();
	void CreateOutput();
	void CreateUAV();
	void CreateResult();


private:
	// GPU에 넘겨주는 버퍼
	ComPtr<ID3D11Buffer> _input;
	// input을 묘사하는 View
	ComPtr<ID3D11ShaderResourceView> _srv;
	// 결과값을 받아주는 버퍼
	ComPtr<ID3D11Buffer> _output;
	// output을 묘사하는 View
	ComPtr<ID3D11UnorderedAccessView> _uav;

	// 최종 결과를 취합하기 위한 버퍼
	ComPtr<ID3D11Buffer> _result;


private:
	// * 어떤 데이터가 들어올지 예측하지 못하기 때문에 void형 포인트로 받아주기
	// * _inputData = CPU 메모리에 있는 정보들
	void* _inputData; 

	uint32 _inputByte = 0; // inputByte의 총 개수
	uint32 _outputByte = 0; // 출력해야 되는 데이터의 크기
};