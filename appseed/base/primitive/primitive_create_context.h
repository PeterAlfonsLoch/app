#pragma once


#include "primitive_command.h"





class command_line;

class CLASS_DECL_c command_line_sp :
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




class CLASS_DECL_c create_context :
   virtual public command
{
public:


   bool                                   m_bMakeVisible;
   bool                                   m_bTransparentBackground;
   bool                                   m_bClientOnly;
   bool                                   m_bOuterPopupAlertLike;
   bool                                   m_bHold;
   sp(::user::base_interaction)           m_puiParent;
   sp(::user::base_interaction)           m_puiViewAlloc;
   sp(application_bias)                   m_spApplicationBias;
   command_line_sp                        m_spCommandLine;
   stack < sp(::root) >                   m_user; // used root but expect to store ::user::create_context
   sp(command_thread)                     m_pthreadParent;



   create_context(sp(base_application) papp);
   create_context(sp(command_thread) pthreadParent);
   create_context(sp(command_thread) pthreadParent, var varFile, bool bMakeVisible = true, sp(::user::base_interaction) puiParent = NULL);
   create_context(const create_context & createcontext);
   virtual ~create_context();


   create_context & operator = (const create_context & createcontext);

};





