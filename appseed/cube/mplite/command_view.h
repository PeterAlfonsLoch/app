#pragma once

namespace mplite
{

   class CLASS_DECL_CA2_CUBE command_view :
      public form_view
   {
   public:


      ::mplite::main_frame *     m_pmainframe;


      command_view(::ca::application * papp);
      virtual ~command_view();

      
   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

      bool BaseOnControlEvent(::user::control_event * pevent);

      void on_key(::user::win::message::key * pkey);

   };

} // namespace mplite