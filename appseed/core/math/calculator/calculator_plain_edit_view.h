#pragma once


namespace calculator
{


   class CLASS_DECL_CORE plain_edit_view:
      virtual public ::user::show < ::user::plain_edit >
   {
   public:


      class callback :
         virtual public object
      {
      public:

         virtual mutex * get_mutex() 
         {
            return m_pmutex; 
         }

         virtual void set_expression(const char * pszExp)
         {
         }

      };

      ::calculator::value        m_val;
      callback *                 m_pcallback;

      string                     m_strFormat;


      plain_edit_view(::aura::application * papp);
      virtual ~plain_edit_view();

      virtual void _001OnAfterChangeText(::action::context actioncontext);

      void on_update(::user::impact * pSender,LPARAM lHint,object* phint);

      bool keyboard_focus_is_focusable();

      virtual int64_t add_ref();

      virtual int64_t dec_ref();

      virtual var get_ex_value() override;

   };


} // namespace calculator




