#pragma once

#include "../utils/fileutils.h"
#include "../maths/maths.h"

#include <glew.h>
#include <vector>
#include <iostream>


namespace u_engine{ namespace graphics {
	
	class Shader {
    private:
		const char* m_VertPath;
		const char* m_FragPath;
		GLuint m_ShaderID;
	public:
		Shader(const char* vertPath, const char* fragPath);
		~Shader(); 


		void setUniform1i(const GLchar* name, int val);
		void setUniform1f(const GLchar* name, float val);
		void setUniform2f(const GLchar* name, const maths::vec2& vector);
		void setUniform3f(const GLchar* name, const maths::vec3& vector);
		void setUniform4f(const GLchar* name, const maths::vec4& vector);	
		void setUniformMat4(const GLchar* name, const maths::mat4& matrix);


		void enable() const;
		void disable() const;

	private:
		GLuint load();
		GLint getUniformLocation(const GLchar* name);

	};



} }