#pragma once
#include <glew.h>
#include <u_engine_includes.h>
namespace u_engine { namespace graphics {



	class IndexBuffer {


	private:
		GLuint					m_BufferID;
		GLuint					m_Count;
	public:
		IndexBuffer(GLushort*	data,
			GLsizei				count);


		IndexBuffer(GLuint*		data,
			GLsizei				count);
		~IndexBuffer();
		UE_void bind()		const;
		UE_void unbind()	const;
		inline GLuint	getCount()	const { return m_Count; }

	};



} }