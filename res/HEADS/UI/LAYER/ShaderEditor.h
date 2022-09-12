#pragma once
#include "ImguiLayer.h"
#include "EventListener.h"
#include "ShaderLib.h"

class ShaderEditor : public ImguiLayer, public EventListener
{
private:
	static std::string edit_mode[3];
	static std::string shader_type[2];

	mutable int current_edit = 0, current_shad_type = 0;
	mutable bool sel;
public:
	ShaderEditor();
	ShaderEditor(const std::string& name);
	~ShaderEditor();
public:
	bool AddParam();
	bool AddStruct();
public:
	void UpdateShaderEditor();
	void UpdateLayer() override;
	void RenderShaderStruct() const;
	void RenderLayer() const override;
};

