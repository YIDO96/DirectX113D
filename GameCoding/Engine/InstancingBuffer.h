#pragma once

class VertexBuffer;

struct InstancingData
{
	Matrix world;
};

#define MAX_MESH_INSTANCE 500

class InstancingBuffer
{
public:
	InstancingBuffer();
	~InstancingBuffer();


public:
	// 인스턴싱 버퍼를 매 프레임마다 싹 비워주고 데이터를 다시 채워주고 그 데이터들의 대표를 쉐이더에 밀어는 식으로 작업
	void ClearData();
	void AddData(InstancingData& data);
	void PushData();

public:
	uint32 GetCount() { return static_cast<uint32>(_data.size()); }
	shared_ptr<VertexBuffer> GetBuffer() { return _instanceBuffer; }


private:
	void CreateBuffer(uint32 maxCount = MAX_MESH_INSTANCE);

private:
	//uint64						_instanceId = 0;
	shared_ptr<VertexBuffer>	_instanceBuffer;
	uint32						_maxCount = 0;
	vector<InstancingData>	_data;
};