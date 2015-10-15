#include <graphics/sprite.h>

namespace u_engine { namespace graphics {

	Sprite::Sprite(Texture* texture)
		: Renderable2D(maths::vec3(0.0f, 0.0f, 0.0f), maths::vec2((UE_float)texture->getWidth(), (UE_float)texture->getHeight()), 0xffffffff), position(m_Position), size(m_Size)
	{
		m_Texture = texture;
	}

	Sprite::Sprite(UE_float x, UE_float y, Texture* texture)
		: Renderable2D(maths::vec3(x, y, 0.0f), maths::vec2((UE_float)texture->getWidth(), (UE_float)texture->getHeight()), 0xffffffff), position(m_Position), size(m_Size)
	{
		m_Texture = texture;
	}

	Sprite::Sprite(UE_float x, UE_float y, UE_float width, UE_float height, UE_uint color)
		: Renderable2D(maths::vec3(x, y, 0.0f), maths::vec2(width, height), color), position(m_Position), size(m_Size)
	{

	}

	Sprite::Sprite(UE_float x, UE_float y, UE_float width, UE_float height, maths::vec4 color)
		: Renderable2D(maths::vec3(x, y, 0.0f), maths::vec2(width, height), 0xffffffff), position(m_Position), size(m_Size)
	{
		setColor(color);
	}

	Sprite::Sprite(UE_float x, UE_float y, UE_float width, UE_float height, Texture* texture)
		: Renderable2D(maths::vec3(x, y, 0.0f), maths::vec2(width, height), 0xffffffff), position(m_Position), size(m_Size)
	{
		m_Texture = texture;
	}

	UE_void Sprite::setUV(const std::vector<maths::vec2>& uv)
	{
		m_UV = uv;
	}

} }