/////////////////////////////////////////////////////////////////////////////////////////
//
//   All Pure and Aural ca2 and God and Gods and Goddssesses and devils's blessings
//
//   C++
//
//   C => in ca2 scope
//
//   Thank you God for C++!!
//

#pragma once

#pragma warning(disable: 4251)

#include "nodeapp/operational_system/operational_system.h"




namespace axis
{

   class application;
   class system;
   class copydesk;

   typedef smart_pointer < copydesk > copydesk_sp;



} // namespace axis


namespace database
{


   class server;


} // namespace database


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

   class session;
   class system;
   //class cube;


} // namespace plane

class cmd_ui;


namespace draw2d
{


   class graphics;


} // namespace draw2d


namespace file
{


   class stream_buffer;
   class input_stream;
   class output_stream;
   class serializable;


} // namespace file

class machine_event_data;
namespace html
{
   class html;
} // namespace html


namespace user
{

   class interaction_impl;
   class view_creator_data;
   class schema;
   class tree;
   class str_context;
   class schema_simple_impl;
   class impact;
   class window_draw;
   class str;

}


namespace message
{

   class mouse;

}

typedef sp(::user::interaction_impl) window_sp;

namespace user
{

   class interaction;
   class control_event;
   class create_context;
   class impact;
   class printer;
   class user;
   class document;
   class frame_window;

   class form_interface;
   class form_list;
   class form_callback;


} // namespace user


namespace simple_ui
{

   class label;
   class edit_box;
   class password;
   class tap;

}

namespace axis
{

   template < typename T >
   inline void del(T * & p)
   {
      if(p != NULL)
      {
         delete p;
         p = NULL;
      }
   }

} // namespace axis



class message_queue_listener;
class image_list;




namespace axis
{

#if defined METROWIN && defined(__cplusplus_winrt)

   interface class system_window
   {

      virtual Windows::Foundation::Rect get_window_rect() = 0;
      virtual Windows::Foundation::Point get_cursor_pos() = 0;



   };

   CLASS_DECL_AXIS bool get_window_rect(system_window ^ pwindow,RECTD * lprect);
   CLASS_DECL_AXIS bool get_window_rect(system_window ^ pwindow,LPRECT lprect);

#endif


   class session;

} // namespace axis


namespace data
{


   class item;


} // namespace data



namespace user
{

   class place_holder;
   class menu_base_item;

#if defined METROWIN && defined(__cplusplus_winrt)

   class CLASS_DECL_AXIS native_window_initialize
   {
   public:


      Platform::Agile<Windows::UI::Core::CoreWindow> window;
      ::axis::system_window ^ pwindow;


   };

#elif defined(APPLE_IOS)

   class CLASS_DECL_AXIS native_window_initialize
   {
   public:

      RECT   m_rect;

   };

#else

   class native_window_initialize;

#endif


   class control_event;
   class frame_window;
   class menu_base;





   CLASS_DECL_AXIS bool is_descendant(::user::interaction * puiParent,::user::interaction * puiChild);


} // namespace user





namespace str
{


   namespace international
   {


      class locale_schema;


   } // namespace international


} // namespace str




namespace draw2d
{


   class graphics;


} // namespace draw2d



class event;


class thread;




class thread;


typedef smart_pointer < thread > thread_sp;


class thread_impl;


typedef smart_pointer < thread_impl > thread_impl_sp;




#define SCAST_PTR(TYPE, ptarget, psource) TYPE * ptarget = dynamic_cast < TYPE * > (psource);
#define SCAST_REF(TYPE, rtarget, psource) TYPE & rtarget = *(dynamic_cast < TYPE * > (psource));

#undef CaSys
#define CaSys(pca) (*pca->m_pauraapp->m_paxissystem)
#undef Sys
#define Sys(pauraapp) (*pauraapp->m_paxissystem)
//#define System (Sys(this->m_pauraapp))
//#define threadSystem (Sys(get_thread_app()))

#undef Sess
#define Sess(pauraapp) (*pauraapp->m_paxissession)
//#define Session (Sess(m_pauraapp))
//#define Plat(pauraapp) (*pauraapp->m_pcoreplatform)
//#define Platform (Plat(m_pauraapp))


#undef App
#define App(pauraapp) (*pauraapp->m_paxisapp)
#define Application (App(m_pauraapp))



CLASS_DECL_AXIS bool axis_init();
CLASS_DECL_AXIS bool axis_term();

CLASS_DECL_AXIS bool __node_axis_pre_init();
CLASS_DECL_AXIS bool __node_axis_pos_init();

CLASS_DECL_AXIS bool __node_axis_pre_term();
CLASS_DECL_AXIS bool __node_axis_pos_term();



#if defined(LINUX)

#include "axis/os/ansios/ansios.h"
#include "axis/os/linux/linux_user_impl.h"

#elif defined(METROWIN)

#include "axis/os/metrowin/metrowin.h"
#include "axis/os/metrowin/metrowin_user_impl.h"

#elif defined(MACOS)

#include "axis/os/ansios/ansios.h"
#include "axis/os/macos/macos.h"
#include "axis/os/macos/macos_windowing.h"

#elif defined(ANDROID)

#include "axis/os/ansios/ansios.h"
#include "axis/os/android/android.h"

#elif defined(WINDOWS)

#include "axis/os/windows/windows.h"

#elif defined(APPLE_IOS)

#include "axis/os/ansios/ansios.h"
#include "axis/os/ios/ios.h"
#include "axis/os/ios/ios_windowing.h"

#elif defined(SOLARIS)

#include "axis/os/ansios/ansios.h"
#include "axis/os/solaris/solaris_user_impl.h"

#else


#error "not implemented!!"

#endif

#include "axis/primitive/datetime/datetime_value.h"

#include "axis/primitive/datetime/datetime_departament.h"

#include "axis/database/database/database.h"

#include "axis/axis/axis_static_start.h"

#include "axis/graphics/graphics.h"

#include "axis/axis/axis_platform_interface.h"

#include "axis/axis/axis_application.h"

#include "user/user/user_enum.h"

#include "user/user/user_key_enum.h"

#include "user/user/user_schema.h"

#include "axis/axis/axis_session.h"

#include "axis/axis/axis_system.h"

#include "axis/axis/axis_simple_app.h"

#include "axis/axis/axis.inl"




