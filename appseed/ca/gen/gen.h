#pragma once


#include "ca/ex1/ex1.h"


#include "gen_debug.h"

#include "math/math_math.h"

#include "gen_math_rng.h"
#include "gen_math.h"
#include "gen_geometry.h"

#include "gen_equals.h"

#include "gen_iterator.h"
#include "gen_insert_iterator.h"
#include "gen_back_insert_iterator.h"
#include "gen_std_pair.h"


#include "gen_equals.h"
#include "gen_compare.h"

#include "gen_c_number.h"




#include "gen_muldiv32.h"

#define EX1ASSERT_VALID(pobj) ASSERT(pobj->Ex1IsObjValid())


#include "gen_simple_thread.h"
#include "gen_go_thread.h"



#include "gen_scoped_ptr.h"
#include "gen_logic.h"



#include "gen_parse.h"


#include "gen_template.h"


#include "ca/collection/Base2DArray.h"
#include "ca/collection/string_array.h"
#include "ca/collection/stringa.h"
#include "ca/collection/stringl.h"
#include "ca/collection/string_sort_array.h"

#include "gen_string_tokenizer.h"


#include "gen_base_enum.h"
#include "gen/gen_base_enum.h"
#include "gen_holder.h"
#include "gen_raw_pointer.h"
#include "gen_full_pointer.h"
#include "gen_time.h"
#include "ca/ex1/ex1_byte_serializable.h"
#include "collection/stringa.h"
#include "gen_var.h"
#include "gen_var_array.h"

#include "gen_pointer_manager.h"

#include "ca/radix/radix_pipe.h"
#include "gen_process.h"

#include "ca/primitive/memory.h"

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


#include "gen_microtimer.h"

template <class TYPE>
inline bool IsRefNull(const TYPE & ref)
{
   return &ref == NULL;
}

#define NULL_REF(class) (*((class *) NULL))


CLASS_DECL_ca ex1::byte_input_stream &  operator >>(ex1::byte_input_stream & istream, string & string);
CLASS_DECL_ca ex1::byte_output_stream &  operator <<(ex1::byte_output_stream & ostream, const string & string);

#ifdef WIN32
#include "gen_file_association.h"
#endif


#include "gen_signal_thread.h"

#include "gen_international_locale_schema.h"

#include "gen_timer.h"

#include "gen_application.h"

#include "gen_istring.h"


