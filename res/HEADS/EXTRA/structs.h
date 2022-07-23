#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"

#include "ImGui/imgui.h"

#include <iostream>
#include <unordered_map>
#include <ctime>
#include <vector>

#define SCREEN_W 750
#define SCREEN_H 750
#define LOOP(x) for(int i = 0; i < x; i++)


struct ShaderPair {
	std::string verShader;
	std::string fragShader;

};

struct Timer
{
	time_t start, end, tick, temp = 0;
	time_t __duration = 0;
	int fact = 1;
	Timer(int fact) :fact(fact) {
		start = clock();
	}
	Timer() {
		std::cout <<"[ Thread Start ]\n";
		fact = 1;
		start = clock();
	}

	void Tick() {
		/*std::cout << 000000 << "\n";*/
		tick = clock();
		__duration = tick - temp;
		temp = tick;
		std::cout /*<< "\r"*/ << "\_[ duration = " << __duration * fact << "ms ]\n";
	}

	~Timer() {
		end = clock();
		__duration = end - start;
		std::cout /*<< "\r"*/ << "[ Whole Time = " << __duration * fact << "ms ]\n";
	}
};

struct Reading
{
	std::vector<float> result[4];
	std::vector<float> vertex;
	std::vector<float> center = { 0,0,0 };
	int count[4] = { 0,0,0,0 };

	std::string name = "";
};

struct Face
{
	int pos, uv, norm, smo_norm;
	void copy(const Face& inp) {
		pos = inp.pos;
		uv = inp.uv;
		norm = inp.norm;
		smo_norm = inp.smo_norm;
	}
	void print() {
		std::cout << pos << " " << uv << " " << norm << "\n";
	}
};

template<int num>
struct AverageTime
{
	float* timelist = new float[num] {0.0f};
	int count = 0;
	float result = 0;
	void Add(const float& in) {
		if (count >= num)count = 0;
		result -= timelist[count];
		timelist[count] = in / num;
		result += in / num;
		count++;
	}
	~AverageTime() {
		delete timelist;
	}
};