#pragma once

#include <u_engine_includes.h>
#include <maths/maths.h>


#include <vector>
#include <iostream>


namespace u_engine{ namespace graphics {
	

		


	class Shader {
    private:

		const UE_char* m_Name;
		const UE_char* m_VertPath;
		const UE_char* m_FragPath;
		const UE_char* m_VertSrc;
		const UE_char* m_FragSrc;

	public:
		GLuint m_ShaderID;
		Shader(const UE_char* name, const UE_char* vertSrc, const UE_char* fragSrc);
		Shader(const UE_char* vertPath, const UE_char* fragPath);
		~Shader(); 


		UE_void setUniform1i(const GLchar* name, UE_int val);
		UE_void setUniform1iv(const GLchar* name, UE_int* val, UE_int count);
		UE_void setUniform1f(const GLchar* name, UE_float val);
		UE_void setUniform1fv(const GLchar* name, UE_float* val, UE_int count);
		UE_void setUniform2f(const GLchar* name, const maths::vec2& vector);
		UE_void setUniform3f(const GLchar* name, const maths::vec3& vector);
		UE_void setUniform4f(const GLchar* name, const maths::vec4& vector);	
		UE_void setUniformMat4(const GLchar* name, const maths::mat4& matrix);


		UE_void bind() const;
		UE_void unbind() const;

	private:
		GLuint load(const UE_char* vertSrc, const UE_char* fragSrc);
		GLint getUniformLocation(const GLchar* name);
	public:
		static Shader* FromFile(const UE_char* vertPath, const UE_char* fragPath);
		static Shader* FromSource(const UE_char* vertSrc, const UE_char* fragSrc);
		static Shader* FromSource(const UE_char* name, const UE_char* vertSrc, const UE_char* fragSrc);

	};



} }