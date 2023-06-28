#pragma once

#include "GL/glew.h"
#include "glm/glm.hpp"

#include "GameObject.h"
#include "MeshData.h"

#include "Texture.h"
#include "Shaders.h"
#include "Camera.h"

#include "support.h"

#include <optional>

#define SPRITE_SIZE 0.7f

enum SpriteType
{
	NONE_SPRITE, POINT_LIGHT_SPRITE, SUN_LIGHT_SPRITE, SPOT_LIGHT_SPRITE, CAM_SPRITE, ENVIRN_SPRITE, PARTIC_SPIRIT
};

class Sprite : public GameObject
{

private:
	static std::string fileroot;
public:

	std::optional<Texture> spr_tex;

public:
	float spr_opacity = 0.9f;

	SpriteType spr_type = SpriteType::NONE_SPRITE;
	mutable std::optional<RenderShader> spr_shader;

	Sprite();
	~Sprite();

	void RenderSprite(const glm::vec3& pos, const glm::vec3& col, Camera* cam);
	void RenderSprite(Camera* cam);

	void SetSpriteShader();
	std::string ParsePath() const;
	void SetTex();
	void* GetShaderStruct() override { return dynamic_cast<ShaderLib*>(&spr_shader.value()); };

	void DeleteSprite();
};
