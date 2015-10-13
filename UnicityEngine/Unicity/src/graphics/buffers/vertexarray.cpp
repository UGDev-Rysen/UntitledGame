#include <graphics/buffers/vertexarray.h>


namespace u_engine { namespace graphics {


	VertexArray::VertexArray() {
	GLCall(glGenVertexArrays(1, &m_ArrayID));

	}


	VertexArray::~VertexArray(){
		for (UE_int i = 0; i < m_Buffers.size(); i++) {
			delete m_Buffers[i];
			GLCall(glDeleteVertexArrays(1, &m_ArrayID));
		}
	}



	UE_void VertexArray::addBuffer(Buffer* buffer, 
								GLuint index){

		bind();
		buffer->bind();

		GLCall(glEnableVertexAttribArray(index));
		GLCall(glVertexAttribPointer(index, buffer->getComponentCount(),
								GL_FLOAT, GL_FALSE, 0, 0));

		buffer->unbind();
		unbind();

		m_Buffers.push_back(buffer);
	}

	UE_void VertexArray::bind() const {
		GLCall(glBindVertexArray(m_ArrayID));
	}


	UE_void VertexArray::unbind() const {
		GLCall(glBindVertexArray(0));
	}


} }