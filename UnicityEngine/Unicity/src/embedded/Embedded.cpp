#include <embedded/Embedded.h>

namespace u_engine { namespace internal {

	UE_byte DEFAULT_FONT_ARRAY[] = {
#include "files/SourceSansPro-Light.embed"
	};

	UE_byte* DEFAULT_FONT = DEFAULT_FONT_ARRAY;
	UE_uint DEFAULT_FONT_SIZE = sizeof(DEFAULT_FONT_ARRAY);

	
} }