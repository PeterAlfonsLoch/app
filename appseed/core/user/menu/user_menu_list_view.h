#pragma once


namespace user
{

   class CLASS_DECL_CORE menu_list_view : 
      virtual public menu_list_window
   {
   public:

      ::user::interaction   * m_puiNotify;


      menu_list_view(sp(::base::application) papp);
      virtual ~menu_list_view();

      void install_message_handling(::message::dispatch * pinterface);

      virtual void GuieProc(signal_details * pobj);

      virtual bool _001OnCmdMsg(::base::cmd_msg * pcmdmsg);

      bool LoadMenu(sp(::xml::node) pnode, sp(::user::interaction) puiNotify, UINT uiCallbackMessage);
         
   #ifdef DEBUG
      virtual void assert_valid() const;
   #ifndef _WIN32_WCE
      virtual void dump(dump_context & dumpcontext) const;
   #endif
   #endif

   };

} // namespace user