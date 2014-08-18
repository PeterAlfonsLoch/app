#pragma once


template < class TYPE, class AXIS_ARRAY = array < TYPE > >
class stack :
   virtual public AXIS_ARRAY
{
public:


   TYPE * operator ->()
   {
      return &AXIS_ARRAY::last_element();
   }

   const TYPE * operator ->() const
   {
      return &AXIS_ARRAY::last_element();
   }

   TYPE & top()
   {
      return AXIS_ARRAY::last_element();
   }

   const TYPE & top() const
   {
      return AXIS_ARRAY::last_element();
   }

};


template < class TYPE, class ARG_TYPE = const TYPE & >
class raw_stack :
   virtual public stack < TYPE, raw_array < TYPE, ARG_TYPE > >
{
public:


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




