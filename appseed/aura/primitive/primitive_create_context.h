#pragma once







class command_line;

class CLASS_DECL_AURA command_line_sp :
   public smart_pointer < command_line >
{
public:


   command_line_sp();
   command_line_sp(allocatorsp allocer);


   using smart_pointer < command_line >::operator =;
   inline command_line_sp & operator = (command_line * p)
   {
      smart_pointer < command_line >::operator =(p);
      return *this;
   }

};


CLASS_DECL_AURA void set_user_create_context_delfn(void (*pfn) (void *));
CLASS_DECL_AURA void call_user_create_context_delfn(void * pvoid);


class CLASS_DECL_AURA user_create_context_delfn
{
public:

   inline void void_delete(void * pvoid)
   {

      call_user_create_context_delfn(pvoid);

   }

};


class CLASS_DECL_AURA create_context :
   virtual public ::primitive::command
{
public:


   bool                                                        m_bMakeVisible;
   bool                                                        m_bTransparentBackground;
   bool                                                        m_bClientOnly;
   bool                                                        m_bOuterPopupAlertLike;
   bool                                                        m_bHold;
   ::user::interaction *                                       m_puiParent;
   ::user::interaction *                                       m_puiAlloc;
   sp(application_bias)                                        m_spApplicationBias;
   command_line_sp                                             m_spCommandLine;
   stack < ::user::create_context >                            m_user; 
   sp(::command_thread)                                        m_pthreadParent;



   create_context(sp(::aura::application) papp);
   create_context(sp(::command_thread) pthreadParent);
   create_context(sp(::command_thread) pthreadParent, var varFile, bool bMakeVisible = true, ::user::interaction * puiParent = NULL);
   create_context(const create_context & createcontext);
   virtual ~create_context();


   create_context & operator = (const create_context & createcontext);

};





