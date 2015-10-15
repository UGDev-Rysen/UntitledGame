#pragma once

#include <graphics/renderable2d.h>
#include <utils/unicitydef.h>

namespace u_engine { namespace graphics {

	class Sprite : public Renderable2D
	{
	public:
		maths::vec3& position;
		maths::vec2& size;
	public:
		Sprite(Texture* texture);
		Sprite(UE_float x, UE_float y, Texture* texture);
		Sprite(UE_float x, UE_float y, UE_float width, UE_float height, UE_uint color);
		Sprite(UE_float x, UE_float y, UE_float width, UE_float height, maths::vec4 color);
		Sprite(UE_float x, UE_float y, UE_float width, UE_float height, Texture* texture);

		UE_void setUV(const std::vector<maths::vec2>& uv);
	};

} }