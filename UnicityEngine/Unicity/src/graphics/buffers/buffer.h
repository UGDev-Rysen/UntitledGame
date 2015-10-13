#pragma once
#include <glew.h>
#include <u_engine_includes.h>
namespace u_engine { namespace graphics {

	class Buffer {


	private:
		GLuint				m_BufferID;
		GLuint				m_ComponentCount;
	public:
		Buffer(	GLfloat*	data,
				GLsizei		count,
				GLuint		componentCount);
		~Buffer();
		UE_void bind()		const;
		UE_void unbind()	const;
		inline GLuint getComponentCount() const { return m_ComponentCount; }

	};



} }