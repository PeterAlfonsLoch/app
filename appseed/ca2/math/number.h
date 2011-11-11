#pragma once


namespace math
{

class binary_operation;

class number : 
   virtual public value
{
public:
   number();
   virtual ~number();


   binary_operation * m_pbinop;

};


} // namespace math