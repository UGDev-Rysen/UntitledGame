#include <graphics/MeshFactory.h>
#include <u_engine_includes.h>

#include <graphics/renderable2d.h>
#include <shaders/Shader.h>




namespace u_engine { namespace graphics { namespace MeshFactory {
	UE_uint CreateQuad(UE_float x, UE_float y, UE_float width, UE_float height)
	{
		UE_uint result;

		VertexData data[4];
		data[0].vertex = maths::vec3(x, y, 0);
		data[0].uv = maths::vec2(0, 1);

		data[1].vertex = maths::vec3(x, y + height, 0);
		data[1].uv = maths::vec2(0, 0);

		data[2].vertex = maths::vec3(x + width, y + height, 0);
		data[2].uv = maths::vec2(1, 0);

		data[3].vertex = maths::vec3(x + width, y, 0);
		data[3].uv = maths::vec2(1, 1);

#if UNICITY_VERTEX_ARRAYS
		UE_uint buffer;
		GLCall(glGenVertexArrays(1, &result));
		GLCall(glGenBuffers(1, &buffer));

		GLCall(glBindVertexArray(result));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, buffer));

		GLCall(glBufferData(GL_ARRAY_BUFFER, RENDERER_VERTEX_SIZE * 4, data, GL_STATIC_DRAW));

		GLCall(glEnableVertexAttribArray(SHADER_VERTEX_INDEX));
		GLCall(glEnableVertexAttribArray(SHADER_UV_INDEX));
		GLCall(glEnableVertexAttribArray(SHADER_MASK_UV_INDEX));
		GLCall(glEnableVertexAttribArray(SHADER_TID_INDEX));
		GLCall(glEnableVertexAttribArray(SHADER_MID_INDEX));
		GLCall(glEnableVertexAttribArray(SHADER_COLOR_INDEX));

		GLCall(glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)0));
		GLCall(glVertexAttribPointer(SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, uv))));
		GLCall(glVertexAttribPointer(SHADER_MASK_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, mask_uv))));
		GLCall(glVertexAttribPointer(SHADER_TID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, tid))));
		GLCall(glVertexAttribPointer(SHADER_MID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, mid))));
		GLCall(glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, color))));

		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
		GLCall(glBindVertexArray(0));
#else
#error Sparky non-vertex arrays are not yet implemented!
#endif
		return result;
	}

	UE_uint CreateQuad(const maths::vec2& position, const maths::vec2& size)
	{
		return CreateQuad(position.x, position.y, size.x, size.y);
	}

} } }