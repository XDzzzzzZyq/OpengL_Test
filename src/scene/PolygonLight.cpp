#include "PolygonLight.h"
#include <numeric>

PolygonLight::PolygonLight(const std::vector<float> &verts, const glm::vec3 &light_color, float light_power, bool use_shadow)
	: verts(verts), light_color{light_color}, light_power{light_power}, use_shadow{use_shadow}
{
	o_type = GO_POLYLIGHT;
	o_name = "Polygonal Light";

	std::vector<GLuint> indexArray = std::vector<GLuint>{0, 1, 2, 0, 2, 3};

	o_vertBuffer = VertexBuffer(this->verts);

	BufferLayout layout;
	layout.Push<float>(2); // 2D position

	o_vertArray.AddBuffer(o_vertBuffer, layout);

	o_index = IndexBuffer(indexArray.data(), indexArray.size() * sizeof(GLuint));

	SetPolygonShader();
}

void PolygonLight::RenderPolygon(Camera* cam)
{
	o_vertArray.Bind();
	o_index.Bind();
	o_shader.UseShader();

	if (o_shader.is_shader_changed)
		o_shader.InitShader();

	if(is_Uniform_changed || o_shader.is_shader_changed)
		o_shader.SetValue("U_obj_trans", o_Transform);

	if (cam->is_invUniform_changed || o_shader.is_shader_changed)
		o_shader.SetValue("U_cam_trans", cam->o_InvTransform);

	if(cam->is_frustum_changed || o_shader.is_shader_changed)
		o_shader.SetValue("U_ProjectM", cam->cam_frustum);

	if(cam->is_Uniform_changed || cam->is_frustum_changed || o_shader.is_shader_changed)
		o_shader.SetValue("Scene_data", 8, cam->cam_floatData.data(), VEC1_ARRAY);

	o_shader.SetValue("is_selected", (int)is_selected);

	glDrawElements(GL_TRIANGLES, o_index.Count(), GL_UNSIGNED_INT, nullptr);

	o_index.Unbind();
	o_shader.UnuseShader();
	o_vertArray.Unbind();
}

void PolygonLight::SetPolygonShader()
{
	o_shader = RenderShader("Polygon");
	o_shader.UseShader();

	o_shader.InitShader = [&] {
		o_shader.UseShader();

		o_shader.SetValue("light_color", light_color);
		o_shader.SetValue("blen", 0.5f);
		o_shader.SetValue("RAND_color", id_color_rand);
		o_shader.SetValue("ID_color", id_color);

		o_shader.UnuseShader();
	};
}
