#pragma once
#include "support.h"

#include "GameObject.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shaders.h"

#include "Camera.h"

enum PointType {
	SQUARE_POINT, RHOMBUS_POINT, CIR_POINT
};

class DebugPoints : public GameObject
{

private:
	VertexArray dp_vertArry;
	VertexBuffer dp_vertBuffer;
	IndexBuffer dp_index;

	std::vector<float> VertData = {
	-1.0f, 1.0f, 0.0f,
	 1.0f, 1.0f, 0.0f,
	-1.0f,-1.0f, 0.0f,
	 1.0f,-1.0f, 0.0f
	};

public:
	PointType dp_type = SQUARE_POINT;
	bool is_proj = true;

	bool is_scaled;
	mutable Shaders dp_shader[2]; //no proj | using proj

	mutable float dp_scale = 1.0f;
	float dp_opacity = 1.0f;
	glm::vec3 dp_color = glm::vec3(1.0f, 1.0f, 1.0f);
	std::vector<float> dp_pos_list;

	DebugPoints();
	DebugPoints(const std::vector<float>& pos_list);
	~DebugPoints();

	void RenderDebugPoint(Camera* camera) const;

	void SetDebugPointsShader(PointType type, bool proj);
	void PushDebugPoint(const glm::vec3& point);
	void PushDebugPoints(const std::vector<glm::vec3>& points);

	void DeleteDebugPoints() const;
};
