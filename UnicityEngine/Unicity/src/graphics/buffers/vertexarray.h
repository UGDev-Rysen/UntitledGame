#pragma once

#include <glew.h>
#include <vector>
#include <u_engine_includes.h>
#include <graphics/buffers/buffer.h>

namespace u_engine { namespace graphics {

	class VertexArray {
	private:

		GLuint					m_ArrayID;
		std::vector<Buffer*>	m_Buffers;

	public:
		 VertexArray();
		~VertexArray();

		UE_void addBuffer(	Buffer*		buffer, 
						GLuint		index);
		UE_void bind() const;
		UE_void unbind() const;

	};


} }