#pragma once

#include "support.h"

#include "EventListener.h"

#include "SceneManager.h"
#include "FrameBuffer.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <unordered_map>
#include <optional>

class Renderer : public EventListener
{
private:
	enum _BuildinPPS
	{
		_PBR_COMP_PPS, _EDIT_VISUAL_PPS
	};

	enum _BuildinBuffLoc
	{
		_RASTER, _AO_ELS
	};

public:
	static GLint max_resolution_w;
	static GLint max_resolution_h;

public:
	GLuint r_frame_num = 0;
	GLuint r_frame_width = SCREEN_W;
	GLuint r_frame_height = SCREEN_H;

private:
	std::shared_ptr<FrameBuffer> r_render_result;
public:
	Renderer();
	void Init();

	~Renderer();
public:
	bool r_deferred_rendering = true;
	bool r_using_fxaa = true;
	bool r_using_ssr = true;

	float r_gamma = 1.0f;
	int r_ao_ksize = 16;
public:
	bool is_light_changed = false;

	std::shared_ptr<SceneResource> r_scene;

	LightArrayBuffer r_light_data;

public:

	std::string GetObjectName(int ID);
	int GetSelectID(GLuint x, GLuint y);

public:

	std::vector<FrameBuffer> r_buffer_list;
	void InitFrameBuffer();
	void BindFrameBuffer(int slot);
	void EndFrameBuffer(int slot);
	void FrameBufferResize(const ImVec2& size);
	GLuint GetFrameBufferTexture(int slot);

public:

	bool multi_select = false;
	void EventInit();
	void LMB_CLICK();
	void SHIFT();

public:

	void NewFrame();

	void Render(bool rend = true, bool buff = true);
	void RenderShadowMap(Light* light);

	void Reset();
	void FrameResize(GLuint _w, GLuint _h);

public:

	void UseScene(std::shared_ptr<SceneResource> _scene);

	void ActivateCamera(int cam_id);
	void ActivateEnvironment(int envir_id);

	std::shared_ptr<Camera> GetActiveCamera();
	std::shared_ptr<Environment> GetActiveEnvironment();
	std::shared_ptr<PostProcessing> GetPPS(int _tar);
};

