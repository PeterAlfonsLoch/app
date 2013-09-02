#pragma once


#include "nodeapp/operational_system/operational_system.h"


class string;
class istring;
class var;
class property;
class property_set;
class object;
class type;
class application;
class system;
class dump_context;
class string_interface;
class id_space;
class type;
class ptra;
class factory_item_base;
class fixed_alloc_no_sync;
class bergedge;
class system;
class critical_section;
class allocatorsp;
class application;
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


} // namespace file


namespace user
{


   class interaction;
   class create_context;
   class view;


} // namespace user


#define SCAST_PTR(TYPE, ptarget, psource) TYPE * ptarget = dynamic_cast < TYPE * > (psource);
#define SCAST_REF(TYPE, rtarget, psource) TYPE & rtarget = *(dynamic_cast < TYPE * > (psource));


#define sp(TYPE) smart_pointer < TYPE >

#define CaSys(pca) (*pca->m_pcaapp->m_pcasystem)
#define Sys(papp) (*papp->m_pcasystem)
#define System (Sys(this->m_pcaapp))
#define Mathematics(papp) (Sys(papp).math())
#define Math (Mathematics(this->m_pcaapp))

//#define Sess(papp) (*papp->m_psession)
//#define Session (Sess(this->m_pcaapp))

#undef App
#define App(pcaapp) (*pcaapp)
#define Application (App(m_pcaapp))



#ifdef WINDOWS
#pragma warning(disable: 4251)  // using non-exported as public in exported
#pragma warning(disable: 4250)  // via dominance
#endif



#include "base_lparam.h"


#include "base_smart_pointer1.h"
#include "base_base.h"
#include "base_smart_pointer2.h"


#include "c/primitive/primitive_logic.h"





#include "c/str/str1.h"


#include "c/datetime/datetime_duration.h"



#include "c/primitive/primitive_element.h"
#include "c/ca2/ca2_debug.h"



#include "c/exception/exception.h"




#include "ca/ca_template.h"
#include "ca/ca_memory.h"
#include "ca/ca_md5.h"
#include "ca/ca_file.h"
#include "ca/ca_net.h"
#include "ca/ca_time.h"
#include "ca/ca_natural.h"
#include "ca/ca_conv.h"



#include "c/ca2/ca2_core.h"
#include "c/ca2/ca2_common.h"

#include "c/primitive/primitive_request_interface.h"


#include "c/multithreading/multithreading_wait_result.h"
#include "c/multithreading/multithreading_waitable.h"



#include "c/primitive/primitive_object.h"


#include "c/collection/collection_decl.h"
#include "c/collection/collection_array_decl.h"


#include "c_fixed_alloc.h"



#include "c/ca2/ca2_allocate.h"
#include "c/ca2/ca2_plex.h"
#include "c/ca2/ca2_plex_heap.h"


#include "c/primitive/primitive_id.h"


#include "c/str/str.h"


#include "c_istring.h"


#include "c/datetime/datetime_time.h"


#include "c/file/file.h"


#include "c/geometry/geometry.h"


#include "c/comparison/comparison.h"


#include "c/collection/collection.h"


#include "c/file/file_plain_text.h"


#include "c/primitive/primitive_var2.h"


#include "c/primitive/primitive_id_space.h"


#ifdef WINDOWS

#include "c/windows/c_os.h"

#endif


#include "c/ca/ca_user.h"




CLASS_DECL_c vsstring get_system_error_message(uint32_t dwError);
#ifndef METROWIN
CLASS_DECL_c int_bool PrintModules(vsstring & strImage, uint32_t processID, const char * pszDll );
CLASS_DECL_c void dll_processes(uint_array & dwa, stringa & straProcesses, const char * pszDll);
#endif

#include "c/multithreading/multithreading.h"


#include "c/primitive/primitive_type.h"

#include "c/ca/ca_application.h"

#include "c/ca/ca_departament.h"
#include "c/ca/ca_departament_container.h"

#include "c/ca/ca_url_departament.h"

#include "c/primitive/primitive_interlocked_long.h"
#include "c/primitive/primitive_interlocked_long_pulse.h"
#include "c/primitive/primitive_factory.h"
#include "c/primitive/primitive_data.h"
#include "c/primitive/primitive_data_listener.h"
#include "c/primitive/primitive_data_container.h"
#include "c/primitive/primitive_edit.h"


#include "c/xml/xml.h"

#include "c/ca/ca_application_bias.h"
#include "c/exception/exception_engine.h"

#include "c_fixed_alloc_impl.h"
#include "c/ca2/ca2_plex_heap_impl.h"
#include "c/primitive/primitive_command_line.h"
#include "c/primitive/primitive_create_context.h"
#include "c/primitive/primitive_command.h"








#include "c/primitive/primitive_command_thread.h"


#include "c/ca/ca_system.h"


#include "c/primitive/primitive_memory_base.h"
#include "c/primitive/primitive_memory.h"
#include "c/primitive/primitive_shared_memory.h"
#include "c/primitive/primitive_virtual_memory.h"
#include "c/primitive/primitive_memory_container.h"


#include "c/str/str_international2.h"










#include "c/net/net.h"




#include "c/os/os_process.h"


#include "c/spa/spa_trace.h"
