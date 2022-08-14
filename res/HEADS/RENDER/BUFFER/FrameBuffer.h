#pragma once
#include "Texture.h"
#include "RenderBuffer.h"
#include <cstdarg>
#include <optional>

enum FBType
{
	NONE_FB=-1, COMBINE_FB, ID_FB, RAND_FB, ALPHA_FB, NORMAL_FB, DIFF_FB, SPEC_FB, SHADOW_FB, DEPTH_FB = GL_COLOR_ATTACHMENT0 - GL_DEPTH_ATTACHMENT
};

struct FBPixel
{
	GLuint RGBA[4];
	int GetID() { return RGBA[0]; }
};

class FrameBuffer
{
private:
	GLuint fb_ID = 0, fb_attach = 0;
	float fb_w = SCREEN_W, fb_h = SCREEN_H;
public:
	Texture BufferTexture;
	Texture IDTexture;
	std::optional<RenderBuffer> renderBuffer;

	FBType fb_type = NONE_FB;
	mutable std::unordered_map<FBType, int> fb_type_list;      //  tex_type -> tex_index
	mutable std::vector<Texture> fb_tex_list;
	bool using_list = false;

	FrameBuffer();
	FrameBuffer(FBType type, GLuint attach=0);
	FrameBuffer(int count, ...);
	~FrameBuffer();

	void BindFrameBuffer() const;
	void UnbindFrameBuffer() const;

	void Resize(const ImVec2& size, bool all = false);
	void Resize(float w,float h, bool all = false);

	FBPixel ReadPix(GLuint x, GLuint y, FBType type);

	void BindFrameBufferTex() const;
	void BindFrameBufferTex(int count, ...) const;
	void UnbindFrameBufferTex() const;

	void Del() const;

	GLuint GetFrameBufferID() const { return fb_ID; }
	GLuint GetFBTextureID(FBType type) const { return fb_tex_list[fb_type_list[type]].GetTexID(); }
};

