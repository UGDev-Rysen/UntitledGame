#pragma once

#include <graphics/texture.h>
#include <maths/maths.h>
#include <u_engine_includes.h>

namespace u_engine { namespace graphics {

	struct Mask {

		Texture* texture;
		maths::mat4 transform;

		Mask(Texture* texture, const maths::mat4& transform = maths::mat4::identity())
			: texture(texture), transform(transform) {

			this->transform = maths::mat4::scale(maths::vec3((UE_float)texture->getWidth() / (UE_float)texture->getHeight(), 1.0f, 1.0f));
		}
	};




} }