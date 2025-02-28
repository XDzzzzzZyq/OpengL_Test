#pragma once

#ifdef _DEBUG

#include <GL/glew.h>
#include <iostream>
#include <string>

inline std::string glDebug_xdz() {
	const GLuint err = glGetError();
	switch (err)
	{
#define GL_ERR(err) case GL_##err: return #err
		GL_ERR(NO_ERROR);
		GL_ERR(INVALID_ENUM);
		GL_ERR(INVALID_VALUE);
		GL_ERR(INVALID_OPERATION);
		GL_ERR(INVALID_FRAMEBUFFER_OPERATION);
		GL_ERR(OUT_OF_MEMORY);
	default:
		return "UNKOWN_ERROR" + std::to_string(err);
	}
}

#define DEBUG(x) std::cout<<(x)<<"\n"
#define DEBUGS(x) std::cout<__func__<<" : "<<__LINE__<<" : "<<(x)<<"\n"
#define GLDEBUG std::cout<<__func__<<" : "<<__LINE__<<" : "<<glDebug_xdz()<<"\n"

#else

#define DEBUG(x)
#define DEBUGS(x)
#define GLDEBUG

#endif


#define SCREEN_W 1740
#define SCREEN_H 810
#define LOOP_N(x, n) for(int n = 0; n < (int)x; n++)
#define LOOP(x) LOOP_N(x, i)

#define OPTIONS(...) std::vector<std::string>{__VA_ARGS__}

/* --- internal helpers --- */
#define _VA_NARGS_GLUE(x, y) x y
#define _VA_NARGS_RETURN_COUNT(\
  _1_, _2_, _3_, _4_, _5_, _6_, _7_, _8_, _9_, _10_, _11_, _12_, _13_, _14_, _15_, _16_, \
  _17_, _18_, _19_, _20_, _21_, _22_, _23_, _24_, _25_, _26_, _27_, _28_, _29_, _30_, _31_, _32_, \
  _33_, _34_, _35_, _36_, _37_, _38_, _39_, _40_, _41_, _42_, _43_, _44_, _45_, _46_, _47_, _48_, \
  _49_, _50_, _51_, _52_, _53_, _54_, _55_, _56_, _57_, _58_, _59_, _60_, _61_, _62_, _63_, _64_, \
  count, ...) count
#define _VA_NARGS_EXPAND(args) _VA_NARGS_RETURN_COUNT args
#define _VA_NARGS_OVERLOAD_MACRO2(name, count) name##count
#define _VA_NARGS_OVERLOAD_MACRO1(name, count) _VA_NARGS_OVERLOAD_MACRO2(name, count)
#define _VA_NARGS_OVERLOAD_MACRO(name,  count) _VA_NARGS_OVERLOAD_MACRO1(name, count)
/* --- expose for re-use --- */
/* 64 args max */
#define VA_NARGS_COUNT(...) _VA_NARGS_EXPAND((__VA_ARGS__, \
  64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, \
  48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, \
  32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, \
  16, 15, 14, 13, 12, 11, 10,  9,  8,  7,  6,  5,  4,  3,  2, 1, 0))
#define VA_NARGS_CALL_OVERLOAD(name, ...) \
  _VA_NARGS_GLUE(_VA_NARGS_OVERLOAD_MACRO(name, VA_NARGS_COUNT(__VA_ARGS__)), (__VA_ARGS__))
/* ISIN#(v, ...): is the first arg equal any others? */
/* internal helpers. */
#define _VA_ISIN2(v, a) ((v) == (a))
#define _VA_ISIN3(v, a, b) \
  (_VA_ISIN2(v, a) || _VA_ISIN2(v, b))
#define _VA_ISIN4(v, a, b, c) \
  (_VA_ISIN3(v, a, b) || _VA_ISIN2(v, c))
#define _VA_ISIN5(v, a, b, c, d) \
  (_VA_ISIN4(v, a, b, c) || _VA_ISIN2(v, d))
#define _VA_ISIN6(v, a, b, c, d, e) \
  (_VA_ISIN5(v, a, b, c, d) || _VA_ISIN2(v, e))
#define _VA_ISIN7(v, a, b, c, d, e, f) \
  (_VA_ISIN6(v, a, b, c, d, e) || _VA_ISIN2(v, f))
#define _VA_ISIN8(v, a, b, c, d, e, f, g) \
  (_VA_ISIN7(v, a, b, c, d, e, f) || _VA_ISIN2(v, g))

/* reusable ISIN macro */
#define ISIN(...) VA_NARGS_CALL_OVERLOAD(_VA_ISIN, __VA_ARGS__)