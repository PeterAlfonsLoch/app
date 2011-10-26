#pragma once

namespace veiev
{

   class CLASS_DECL_CA2_VEIEV right_split_view : public ::userbase::split_view
   {
   public:


      simple_list_view *             m_plistview;
      view *                  m_pview;


      right_split_view(::ca::application * papp);
      void install_message_handling(::user::win::message::dispatch * pinterface);
      DECL_GEN_SIGNAL(_001OnCreate)
      DECL_GEN_SIGNAL(_001OnTimer)



      document * get_document();
   };

} // namespace veiev


