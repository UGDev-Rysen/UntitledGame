#include <shaders/shader.h>


namespace u_engine{ namespace graphics {

	Shader::Shader(const UE_char* name, const UE_char* vertSrc, const UE_char* fragSrc)
		: m_Name(name), m_VertSrc(vertSrc), m_FragSrc(fragSrc)
	{
		m_ShaderID = load(m_VertSrc, m_FragSrc);
	}

	Shader::Shader(const UE_char* vertPath, const UE_char* fragPath)
		: m_Name(vertPath), m_VertPath(vertPath), m_FragPath(fragPath)
	{
		UE_string vertSourceString = read_file(m_VertPath);
		UE_string fragSourceString = read_file(m_FragPath);

		m_VertSrc = vertSourceString.c_str();
		m_FragSrc = fragSourceString.c_str();
		m_ShaderID = load(m_VertSrc, m_FragSrc);
	}

	Shader* Shader::FromFile(const UE_char* vertPath, const UE_char* fragPath)
	{
		return new Shader(vertPath, fragPath);
	}

	Shader* Shader::FromSource(const UE_char* vertSrc, const UE_char* fragSrc)
	{
		return new Shader(vertSrc, vertSrc, fragSrc);
	}

	Shader* Shader::FromSource(const UE_char* name, const UE_char* vertSrc, const UE_char* fragSrc)
	{
		return new Shader(name, vertSrc, fragSrc);
	}

	Shader::~Shader() {
		glDeleteProgram(m_ShaderID);
	}

	GLuint Shader::load(const UE_char* vertSrc, const UE_char* fragSrc) {
		GLuint program = glCreateProgram();
		GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

		glShaderSource(vertex, 1, &vertSrc, NULL);

		
		glCompileShader(vertex);



		GLint result;
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE) {
			GLint length;
			glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
			std::vector<UE_char> error(length);
			glGetShaderInfoLog(vertex, length, &length, &error[0]);
			UNICITY_ERROR("Failed to compile vertex shader!");
			
			UNICITY_ERROR(&error[0]);
			UNICITY_ASSERT(false, "Failed to compile vertex shader!");

			glDeleteShader(vertex);
			return 0;
		}


		glShaderSource(fragment, 1, &fragSrc, NULL);
		glCompileShader(fragment);



		glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE) {
			GLint length;
			glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
			std::vector<UE_char> error(length);
			glGetShaderInfoLog(fragment, length, &length, &error[0]);
			UNICITY_ERROR("Failed to compile fragment shader!");

			UNICITY_ERROR(&error[0]);
			UNICITY_ASSERT(false, "Failed to compile fragment shader!");
			glDeleteShader(fragment);
			return 0;
		}

		glAttachShader(program, vertex);
		glAttachShader(program, fragment);


		glLinkProgram(program);
		glValidateProgram(program);

		glDeleteShader(vertex);
		glDeleteShader(fragment);

		return program;
	}

	GLint Shader::getUniformLocation(const GLchar* name) {

		GLint result = glGetUniformLocation(m_ShaderID, name);
		if (result == -1) {
			UNICITY_ERROR(m_Name, " : could not find uniform ", name, " in shader!");
		}
		return result;
		
	}

	UE_void Shader::setUniform1i(const GLchar* name, UE_int val){
		glUniform1i(getUniformLocation(name), val);
	}	

	UE_void Shader::setUniform1iv(const GLchar* name, UE_int* value, UE_int count) {
		glUniform1iv(getUniformLocation(name), count, value);
		}

	UE_void Shader::setUniform1f(const GLchar* name, UE_float val) {
		glUniform1f(getUniformLocation(name), val);
	}

	UE_void Shader::setUniform1fv(const GLchar* name, UE_float* value, UE_int count) {
		glUniform1fv(getUniformLocation(name), count, value);
	}

	UE_void Shader::setUniform2f(const GLchar* name, const maths::vec2& vector) {
		glUniform2f(getUniformLocation(name), vector.x, vector.y);
	}	

	UE_void Shader::setUniform3f(const GLchar* name, const maths::vec3& vector) {
		glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z);
	}	 

	UE_void Shader::setUniform4f(const GLchar* name, const maths::vec4& vector) {
		glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
	}	 

	UE_void Shader::setUniformMat4(const GLchar* name, const maths::mat4& matrix) {
		glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, matrix.elements);

	}


	UE_void Shader::bind() const {
		glUseProgram(m_ShaderID);
	}
	UE_void Shader::unbind() const {
		glUseProgram(0);
	}











} }