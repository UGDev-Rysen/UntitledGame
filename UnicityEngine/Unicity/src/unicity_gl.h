#pragma once

#include <glew.h>
#include <u_engine_defines.h>



#ifndef UNICITY_USE_NATIVE_WINDOW
#include <glfw3.h>
#endif

#include <utils/Log.h>


static UE_void log_gl_call(const UE_char* function, const UE_char* file, UE_int line) {

	GLenum error = glGetError();
	if (error != GL_NO_ERROR)  {

		UNICITY_ERROR("[OpenGL Error] (", error, "): ", function, " ", file, ":", line);
	}

#ifdef UNICITY_DEBUG
	#define GLCall(x) glGetError();\
			x;\
			log_gl_call(#x, __FILE__, __LINE__);
#else
	#define GLCall(x) x
#endif

}