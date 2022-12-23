#pragma once
#include "ShaderLib.h"
#include <functional>

enum ArrayType
{
	NULL_ARRAY, VEC1_ARRAY, VEC2_ARRAY, VEC3_ARRAY, VEC4_ARRAY, MAT4_ARRAY
};

class Shaders {

protected:
	GLuint program_id;
	mutable std::unordered_map<std::string, GLuint> _uniforms_cache;

public:
	inline GLuint getProgramID() const { return program_id; }
	virtual GLuint getShaderID(ShaderType type) const = 0;

public:
	std::function<void(void)> InitShader{};
	void ResetCache() { _uniforms_cache = {}; }

	void UseShader() const;
	void UnuseShader() const;
	void DelShad() const;

public:
	inline GLuint getVarID(const char* name) const;

	void SetValue(const std::string& name, const glm::mat4& projection);
	void SetValue(const std::string& name, const int& v0, const int& v1, const int& v2, const float& v3);
	void SetValue(const std::string& name, const int& v0, const int& v1, const int& v2);
	void SetValue(const std::string& name, const glm::vec3& vec3);
	void SetValue(const std::string& name, const glm::vec4& vec4);
	void SetValue(const std::string& name, const float& v0);
	void SetValue(const std::string& name, const int& v0);
	void SetValue(const std::string& name, const GLuint& v0);
	//void SetValue(const std::string& name, GLsizei count, const GLint* va0);
	void SetValue(const std::string& name, GLsizei count, const float* va0, ArrayType TYPE);
	void SetValue(const std::string& name, GLsizei count, const int* va0, ArrayType TYPE);
public:
	virtual void LocalDebug() const = 0;

};


class RenderShader : public Shaders, public ShaderLib
{
private:
	std::string vert_name, frag_name;
	ShaderPair rend_shaders;
	GLuint vs_id, fs_id;
public:
	RenderShader(const std::string& name, const std::string& name2 = "");
	RenderShader();
	~RenderShader();

	void ResetID(ShaderType type, GLuint id);
	void CreatShader(const std::string& verShader, const std::string& fragShader);
public:
	void ParseShaderStream(std::istream& _stream, ShaderType _type);
	void ParseShaderFile(const std::string& _name, ShaderType _type);
	void ParseShaderCode(const std::string& _code, ShaderType _type);
	GLuint CompileShader(ShaderType tar = NONE_SHADER) override;

public:
	inline GLuint getShaderID(ShaderType type) const override;
	void LocalDebug() const override;
};

class ComputeShader : public Shaders {

public:
	std::string comp_name;

	GLuint comp_id;

public:
	ComputeShader(const std::string& name);
	ComputeShader();
	~ComputeShader();

	void ResetID(GLuint _id) { comp_id = _id; }
	void CreateShader(const std::string& compShader);
	GLuint CompileShader();

public:
	inline GLuint getShaderID(ShaderType type) const override;
	void LocalDebug() const override;
};