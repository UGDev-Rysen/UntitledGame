#pragma once

#include <u_engine_includes.h>

namespace u_engine { namespace graphics { namespace MeshFactory {

	/**
	*	TODO: Perhaps this should return some sort of Mesh object with modifiable data.
	*			As of now it just uploads data to the GPU and returns the handle.
	*/


	UE_uint CreateQuad(UE_float x, UE_float y, UE_float width, UE_float height);
	UE_uint CreateQuad(const maths::vec2& position, const maths::vec2& size);


} } }