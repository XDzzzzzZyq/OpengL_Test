#version 430 core

layout(location = 0) out vec4 COMBcolor;
layout(location = 5) out vec4 RANDcolor;
layout(location = 6) out vec4 IDcolor;
layout(location = 7) out vec4 MASKcolor;

in vec2 screen_uv;
uniform sampler2D hdr_texture;

uniform mat4 cam_rotM;
uniform float cam_fov;
uniform float cam_ratio;

uniform vec3 ID_color;
uniform vec3 RAND_color;

vec4 ray_dir;
vec2 reUV;
vec2 equirectangularUV;

const vec2 invAtan = vec2(0.1591, 0.3183);
vec2 genHdrUV(vec3 dir) {
	vec2 uv = vec2(atan(dir.z, dir.x), asin(dir.y));
	uv *= invAtan;
	uv += 0.5;
	return -uv + vec2(0.5, 1);
}

vec2 reMapUV(vec2 uv) {
	return uv * 2 - vec2(1.0f, 1.0f);
}

vec4 GetSelect(vec4 col, float act) {
	col[3] = 1.0f;
	col -= vec4((act + 1) / 256, 0, 0, 0);
	if (col[0] >= 0 || col[0] <= -0.005) {
		col = vec4(1, 1, 1, 1);
	}
	return col;
}

void main() {
	
	IDcolor = vec4(ID_color, 1.0f);
	RANDcolor = vec4(RAND_color, 1.0f);
	MASKcolor = vec4(0);

	reUV =  reMapUV(screen_uv);
	ray_dir = cam_rotM * vec4(vec3(-1, -1, 1) * normalize(vec3(reUV * tan(cam_fov / 2) * vec2(cam_ratio, 1), 1)), 1);

	COMBcolor = vec4(texture(hdr_texture, genHdrUV(normalize(vec3(ray_dir)))).rgb, 1.0f);
};