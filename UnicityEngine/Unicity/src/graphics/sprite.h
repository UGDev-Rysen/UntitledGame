#pragma once
#include "renderable2D.h"


namespace u_engine { namespace graphics {


	class Sprite : public Renderable2D {
	private:

	public:

		Sprite(float x, float y, float width, float height, const maths::vec4& color);
	};


} }