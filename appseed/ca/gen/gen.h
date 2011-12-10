#pragma once


#include "ex1/ex1.h"


#include "gen_debug.h"

#include "gen_math_rng.h"
#include "gen_math.h"
#include "gen_geometry.h"

#include "muldiv32.h"

#define EX1ASSERT_VALID(pobj) ASSERT(pobj->Ex1IsObjValid())


#include "simple_thread.h"
#include "go_thread.h"



#include "radix/keep_ptr.h"
#include "radix/sensitive_ptr.h"
#include "gen_logic.h"



#include "gen_parse.h"



#include "radix/packset.h"
#include "radix/spreadset.h"



#include "collection/Base2DArray.h"
#include "collection/string_array.h"
#include "collection/stringa.h"
#include "collection/stringl.h"
#include "collection/string_sort_array.h"
#include "gen_string_tokenizer.h"
#include "gen_base_enum.h"
#include "gen_variable_strict_compare.h"
#include "primitive/var.h"
#include "gen_var.h"
#include "gen_var_array.h"

#include "gen_pointer_manager.h"

#include "radix/pipe.h"
#include "gen_process.h"

#include "primitive/memory.h"

#include "gen_savings.h"

#include "gen_command.h"
#include "gen_command_line.h"
#include "gen_command_thread.h"

#include "gen_base64.h"
#include "gen_system.h"


#include "gen_util1.h"


#include "gen_str.h"
#include "primitive/int_biunique.h"


#include "gen_memory_file.h"
#include "gen_byte_stream_memory_file.h"



template <class TYPE>
inline bool IsRefNull(const TYPE & ref)
{
   return &ref == NULL;
}

#define NULL_REF(class) (*((class *) NULL))


CLASS_DECL_ca ex1::byte_input_stream &  operator >>(ex1::byte_input_stream & istream, string & string);
CLASS_DECL_ca ex1::byte_output_stream &  operator <<(ex1::byte_output_stream & ostream, const string & string);

#ifdef WIN32
#include "radix/win_registry.h"
#include "gen_file_association.h"
#endif


#include "gen_signal_thread.h"

#include "gen_international_locale_style.h"

#include "gen_timer.h"

#include "gen_application.h"
