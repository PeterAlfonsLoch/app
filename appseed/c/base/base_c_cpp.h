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
class bergedge;
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



namespace plane
{


   class session;
   class system;
   //class cube;


} // namespace plane



namespace file
{

   
   class file;
   class input_stream;
   class output_stream;


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



#include "base_lparam.h"
#include "base_muldiv64.h"

#include "base_auto_pointer.h"

#include "base_smart_pointer1.h"
#include "base_root.h"
#include "base_smart_pointer2.h"


#include "c/primitive/primitive_logic.h"



#include "c/math/math_static_numeric_info.h"
#include "c/math/math_numeric_info.h"
#include "c/math/math_number.h"


#include "c/datetime/datetime_duration.h"


#include "c/primitive/primitive_element.h"

#include "base_debug.h"



#include "c/exception/exception.h"




#include "base_template.h"

#include "c/comparison/comparison_md5.h"

#include "c/net/net.h"

#include "base_conv.h"



#include "base_core.h"
#include "base_common.h"

#include "c/primitive/primitive_request_interface.h"


#include "c/multithreading/multithreading_wait_result.h"
#include "c/multithreading/multithreading_waitable.h"



#include "c/primitive/primitive_object.h"


#include "c/collection/collection_decl.h"
#include "c/collection/collection_array_decl.h"
#include "c/collection/collection_raw_array_decl.h"
#include "c/collection/collection_lemon_array_decl.h"


#include "base_fixed_alloc.h"



#include "base_allocate.h"
#include "base_plex.h"
#include "base_plex_heap.h"


#include "c/primitive/primitive_id.h"


#include "c/str/str.h"


#include "c/datetime/datetime_time.h"


#include "c/file/file.h"


#include "c/geometry/geometry.h"


#include "c/comparison/comparison.h"


#include "c/collection/collection.h"


#include "c/file/file_plain_text.h"


#include "c/primitive/primitive_var2.h"


#include "c/primitive/primitive_id_space.h"


#ifdef WINDOWS

#include "c/windows/windows.h"

#endif

#include "base_thread.h"
#include "base_user_interaction.h"




CLASS_DECL_c vsstring get_system_error_message(uint32_t dwError);

#include "c/multithreading/multithreading.h"


#include "c/primitive/primitive_type.h"

#include "base_application.h"

#include "base_departament.h"
#include "base_departament_container.h"

#include "c/net/net_url_departament.h"

#include "c/primitive/primitive_interlocked_long.h"
#include "c/primitive/primitive_interlocked_long_pulse.h"
#include "c/primitive/primitive_factory.h"
#include "c/primitive/primitive_data.h"
#include "c/primitive/primitive_data_listener.h"
#include "c/primitive/primitive_data_container.h"
#include "c/primitive/primitive_edit.h"


#include "c/xml/xml.h"

#include "c/primitive/primitive_application_bias.h"
#include "c/exception/exception_engine.h"

#include "base_fixed_alloc_impl.h"
#include "base_plex_heap_impl.h"
#include "c/primitive/primitive_command_line.h"
#include "c/primitive/primitive_create_context.h"
#include "c/primitive/primitive_command.h"
#include "c/primitive/primitive_request_signal.h"








#include "c/primitive/primitive_command_thread.h"


#include "base_system.h"
#include "base_system_smart_pointer.h"
#include "base_system_object.h"
#include "base_system_id.h"
#include "base_system_factory.h"
#include "base_system_primitive_var.h"
#include "base_system_xml.h"


#include "c/primitive/primitive_memory_base.h"
#include "c/primitive/primitive_memory.h"
#include "c/primitive/primitive_shared_memory.h"
#include "c/primitive/primitive_virtual_memory.h"
#include "c/primitive/primitive_memory_container.h"


#include "c/str/str_international2.h"










#include "c/net/net.h"




#include "c/os/os_process.h"


#include "c/spa/spa_trace.h"
