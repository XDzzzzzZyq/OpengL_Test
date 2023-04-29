#version 330 core

layout(location = 0) out vec4 COMBcolor;
layout(location = 3) out vec4 ALBEDOcolor;
layout(location = 4) out vec4 MRSEcolor;
layout(location = 5) out vec4 RANDcolor;
layout(location = 6) out vec4 IDcolor;
layout(location = 7) out vec4 MASKcolor;

in vec3 L_color;

uniform float U_Opacity;
uniform vec3 ID_color;
uniform vec3 RAND_color;
uniform int is_selected;

void main() {

	//color = vec4(uv,0.0f,1.0f);
	COMBcolor = vec4(L_color, U_Opacity);
	ALBEDOcolor = vec4(L_color, 1);
	IDcolor = vec4(ID_color / 256, 1.0f);
	RANDcolor = vec4(RAND_color, 1.0f);
	MASKcolor = vec4(1, is_selected, 0, 1);
	MRSEcolor = vec4(0, 0, 0, 1);
};