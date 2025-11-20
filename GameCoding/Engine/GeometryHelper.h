#pragma once

#include "Geometry.h"
#include "VertexData.h"

class GeometryHelper
{
public:
	// 사각형, 큐브, 구형, 그리드, 실린더 등 기본 도형 생성 헬퍼 함수들
	static void CreateQuad(shared_ptr<Geometry<VertexColorData>> geometry, Color color);
};