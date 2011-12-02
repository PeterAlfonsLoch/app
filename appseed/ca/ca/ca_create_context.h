#pragma once


#include "gen/gen_command.h"


template < class TYPE, class BASE_ARRAY = base_array < TYPE > >
class stack :
   virtual public BASE_ARRAY
{
public:


   TYPE * operator ->()
   {
      return &last_element();
   }

   const TYPE * operator ->() const
   {
      return &last_element();
   }

};

template < class TYPE, class STACK = stack < TYPE > >
class stacker
{
public:

   STACK & m_stack;

   stacker(STACK & stack) :
      m_stack(stack)
   {
      m_stack.add_new();
   }

   ~stacker()
   {
      m_stack.pop();
   }

   TYPE * operator ->()
   {
      return &m_stack.last_element();
   }

   const TYPE * operator ->() const
   {
      return &m_stack.last_element();
   }

};



namespace gen
{

   class command_line;

   class CLASS_DECL_ca command_line_sp :
      virtual public ::ca::smart_pointer < command_line >
   {
   public:


      command_line_sp();
      command_line_sp(::ca::application * papp);


      using ::ca::smart_pointer < command_line >::operator =;
      inline command_line_sp & operator = (command_line * p)
      {
         ::ca::smart_pointer < command_line >::operator =(p);
         return *this;
      }

   };


} // namespace gen


namespace ca
{


   class CLASS_DECL_ca create_context : 
      virtual public ::gen::command
   {
   public:


      bool                                m_bMakeVisible;
      bool                                m_bTransparentBackground;
      bool                                m_bClientOnly;
      bool                                m_bOuterPopupAlertLike;
      bool                                m_bHold;
      ::user::interaction *               m_puiParent;
      ::view *                            m_pviewAlloc;
      application_bias_sp                 m_spApplicationBias;
      ::gen::command_line_sp              m_spCommandLine;
      stack < ::user::create_context >    m_user;
      gen::command_thread *               m_pthreadParent;



      create_context(::ca::application * papp);
      create_context(gen::command_thread * pthreadParent);
      create_context(gen::command_thread * pthreadParent, var varFile, bool bMakeVisible = true, ::user::interaction * puiParent = NULL);
      create_context(const create_context & createcontext);
      virtual ~create_context();


      create_context & operator = (const create_context & createcontext);

   };


   class CLASS_DECL_ca create_context_sp :
      virtual public smart_pointer < create_context >
   {
   public:


      create_context_sp();
      create_context_sp(::ca::application * papp);
      create_context_sp(gen::command_thread * pthreadParent);
      create_context_sp(gen::command_thread * pthreadParent, var varFile, bool bMakeVisible = true, ::user::interaction * puiParent = NULL);
      virtual ~create_context_sp();



   };


} // namespace ca


