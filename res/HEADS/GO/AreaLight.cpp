#include "AreaLight.h"
#include "support.h"
#include <numeric>

AreaLight::AreaLight()
{
	//o_type = GO_MESH;
	//o_name = read.name;

	std::vector<float> VertData = {
		0.0f, 0.0f,
		0.5f, 0.0f,
		0.5f, 0.5f,
		0.0f, 0.5f
	};

	std::vector<GLuint> indexArray = std::vector<GLuint>{0, 1, 2, 0, 2, 3};

	o_vertBuffer = VertexBuffer(VertData.data(), VertData.size() * sizeof(float));

	BufferLayout layout;
	layout.Push<float>(2); // 2D position

	o_vertArray.AddBuffer(o_vertBuffer, layout);

	o_index = IndexBuffer(indexArray.data(), indexArray.size() * sizeof(GLuint));

	SetPolygonShader();
}

AreaLight::~AreaLight()
{
	//DeleteObj();
}

void AreaLight::RenderPolygon(Camera* cam)
{
	o_vertArray.Bind();
	o_index.Bind();
	o_shader->UseShader();

	if (o_shader->is_shader_changed)
		o_shader->InitShader();

	if(is_Uniform_changed || o_shader->is_shader_changed)
		o_shader->SetValue("U_obj_trans", o_Transform);

	if (cam->is_invUniform_changed || o_shader->is_shader_changed)
		o_shader->SetValue("U_cam_trans", cam->o_InvTransform);

	if(cam->is_frustum_changed || o_shader->is_shader_changed)
		o_shader->SetValue("U_ProjectM", cam->cam_frustum);

	if(cam->is_Uniform_changed || cam->is_frustum_changed || o_shader->is_shader_changed)
		o_shader->SetValue("Scene_data", 8, cam->cam_floatData.data(), VEC1_ARRAY);

	o_shader->SetValue("is_selected", (int)is_selected);

	glDrawElements(GL_TRIANGLES, o_index.count(), GL_UNSIGNED_INT, nullptr);

	o_index.Unbind();
	o_shader->UnuseShader();
	o_vertArray.Unbind();
}

void AreaLight::SetPolygonShader()
{
	o_shader = RenderShader("Polygon");
	o_shader->UseShader();

	o_shader->InitShader = [&] {
		o_shader->UseShader();

		o_shader->SetValue("blen", 0.5f);
		o_shader->SetValue("RAND_color", id_color_rand);
		o_shader->SetValue("ID_color", id_color);

		o_shader->UnuseShader();
	};
}

//void Mesh::SetTex(std::string _path, TextureType _type)
//{
//    o_tex = Texture(_path, _type ,GL_REPEAT);
//}

//void Mesh::SetCenter()
//{
//    SetPos(-center);
//}

//void Mesh::DeleteObj()
//{
//    if(o_tex)o_tex->Unbind();
//    if(o_shader)o_shader->UnuseShader();
//    o_index.Unbind();
//    o_vertArry.Unbind();
//    o_vertBuffer.Unbind();

//    if(o_tex)o_tex->DelTexture();
//    if(o_shader)o_shader->DelShad();
//    o_index.DelIndBuff();
//    o_vertBuffer.DelVertBuff();
//    o_vertArry.DelVertArr();

//}
