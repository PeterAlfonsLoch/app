#pragma once


#include "nodeapp/operational_system/operational_system.h"


class string;
class istring;
class var;
class property;
class property_set;
class object;
class type;
class base_application;
class base_system;
class dump_context;
class string_interface;
class id_space;
class type;
class ptra;
class factory_item_base;
class fixed_alloc_no_sync;
class base_system;
class critical_section;
class allocatorsp;
class application_signal_details;
class var_array;
class pair_set_interface;
class str_str_interface;
class command_thread;
class thread;





namespace visual
{


   class icon;


} // namespace visual

namespace primitive
{

   class memory;

} // namespace primitive

namespace plane
{

   class application;
   class session;
   class system;
   //class cube;


} // namespace plane



namespace file
{

   
   class stream_buffer;
   class input_stream;
   class output_stream;
   class serializable;


} // namespace file


namespace user
{


   class base_interaction;
   class create_context;
   class view;


} // namespace user


#define SCAST_PTR(TYPE, ptarget, psource) TYPE * ptarget = dynamic_cast < TYPE * > (psource);
#define SCAST_REF(TYPE, rtarget, psource) TYPE & rtarget = *(dynamic_cast < TYPE * > (psource));


#define sp(TYPE) smart_pointer < TYPE >

#define CaSys(pca) (*pca->m_pcaapp->m_pcasystem)
#define Sys(papp) (*papp->m_pcasystem)
#define System (Sys(this->m_pcaapp))
#define threadSystem (Sys(get_thread_app()))
//#define Mathematics(papp) (Sys(papp).math())
//#define Math (Mathematics(this->m_pcaapp))

//#define Sess(papp) (*papp->m_psession)
//#define Session (Sess(this->m_pcaapp))

#undef App
#define App(pcaapp) (*pcaapp)
#define Application (App(m_pcaapp))

// return - result - if not ok
#ifndef RINOK
#define RINOK(x) { int32_t __result__ = (x); if (__result__ != 0) return __result__; }
#endif

// throw - exception - result exception - if not ok
#ifndef TINOK
#define TINOK(e, x) { int32_t __result__ = (x); if (__result__ != 0) throw new e(get_app(), __result__); }
#endif


#ifdef WINDOWS
#pragma warning(disable: 4251)  // using non-exported as public in exported
#pragma warning(disable: 4250)  // via dominance
#endif

CLASS_DECL_c base_application * get_thread_app();

#include "base_definition.h"

#include "base_lparam.h"
#include "base_muldiv64.h"

#include "base_auto_pointer.h"

#include "base_smart_pointer1.h"
#include "base_root.h"
#include "base_smart_pointer2.h"


namespace file
{
   

   typedef sp(stream_buffer) buffer_sp;


} // namespace file


#include "base/primitive/primitive_logic.h"



#include "base/math/math_static_numeric_info.h"
#include "base/math/math_numeric_info.h"
#include "base/math/math_number.h"


#include "base/datetime/datetime_duration.h"


#include "base/primitive/primitive_element.h"

#include "base_debug.h"







#include "base_template.h"

#include "base/comparison/comparison_md5.h"

#include "base/net/net.h"

#include "base_conv.h"



#include "base_core.h"

#include "base/primitive/primitive_request_interface.h"


#include "base/multithreading/multithreading_wait_result.h"
#include "base/multithreading/multithreading_waitable.h"



#include "base/primitive/primitive_object.h"


#include "base/collection/collection_decl.h"
#include "base/collection/collection_array_decl.h"
#include "base/collection/collection_raw_array_decl.h"
#include "base/collection/collection_lemon_array_decl.h"


#include "base_fixed_alloc.h"



#include "base_allocate.h"
#include "base_plex.h"
#include "base_plex_heap.h"


#include "base/primitive/primitive_id.h"


#include "base/str/str.h"
#include "base/exception/exception.h"
#include "base_common.h"


#include "base/datetime/datetime_time.h"




#include "base/file/file.h"




#include "base/geometry/geometry.h"


#include "base/comparison/comparison.h"


#include "base/collection/collection.h"


#include "base/file/file_string_buffer.h"


#include "base/primitive/primitive_var2.h"


#include "base/primitive/primitive_id_space.h"


#ifdef WINDOWS

#include "base/windows/windows.h"

#endif

#include "base_thread.h"
#include "base_user_interaction.h"




CLASS_DECL_c string get_system_error_message(uint32_t dwError);

#include "base/multithreading/multithreading.h"


#include "base/primitive/primitive_type.h"

#include "base_application.h"

#include "base_departament.h"
#include "base_departament_container.h"

#include "base/net/net_url_departament.h"

#include "base/primitive/primitive_interlocked_long.h"
#include "base/primitive/primitive_interlocked_long_pulse.h"
#include "base/primitive/primitive_factory.h"
#include "base/primitive/primitive_data.h"
#include "base/primitive/primitive_data_listener.h"
#include "base/primitive/primitive_data_container.h"
#include "base/primitive/primitive_edit.h"


#include "base/xml/xml.h"

#include "base/primitive/primitive_application_bias.h"
#include "base/exception/exception_engine.h"

#include "base_fixed_alloc_impl.h"
#include "base_plex_heap_impl.h"
#include "base/primitive/primitive_command_line.h"
#include "base/primitive/primitive_create_context.h"
#include "base/primitive/primitive_command.h"
#include "base/primitive/primitive_request_signal.h"








#include "base/primitive/primitive_command_thread.h"


#include "base_system.h"
#include "base_system_smart_pointer.h"
#include "base_system_object.h"
#include "base_system_id.h"
#include "base_system_factory.h"
#include "base_system_primitive_var.h"
#include "base_system_xml.h"


#include "base/primitive/primitive_memory_base.h"
#include "base/primitive/primitive_memory.h"
#include "base/primitive/primitive_shared_memory.h"
#include "base/primitive/primitive_virtual_memory.h"
#include "base/primitive/primitive_memory_container.h"

#include "base/file/file_memory_buffer.h"

#include "base/file/file_byte_stream_memory_buffer.h"


#include "base/str/str_international2.h"










#include "base/net/net.h"




#include "base/os/os_process.h"


#include "base/spa/spa_trace.h"


#include "base/multithreading/multithreading.inl"


#include "base/str/str.inl"

#include "base/base/base.inl"

#include "base/base/base_enum.h"


