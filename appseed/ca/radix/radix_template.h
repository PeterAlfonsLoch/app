#pragma once

#include "_flags.h"

template<>
inline UINT HashKey(::ca::type_info key)
{
	// default identity hash - works for most primitive values
	return HashKey(key.name());
}


