#pragma once


class string_array;


#include "str_ch.h"
#include "str_str.h"


#include "str_simple.h"
#include "str_interface.h"
#include "str_composite.h"
#include "str_format.h"
#include "str_string.h"

#include "str_stringtow.h"
#include "str_from_integer.h"


CLASS_DECL_AURA string get_md5(const void * data, ::count c);
CLASS_DECL_AURA string get_md5(const char * psz);
CLASS_DECL_AURA void zero_pad(string & str, count iPad);


#include "str_ch_class.h"
#include "str_international.h"
#include "str_str2.h"

#include "str_tokenizer.h"

#include "str_hex.h"

#include "str_istring.h"

#include "str_base64.h"

#include "str_parse.h"


