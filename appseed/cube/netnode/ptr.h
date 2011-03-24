#pragma once


class CLASS_DECL_CA2_CUBE ptr : 
   virtual public netnodeScriptComposite
{
public:
   ptr();
   virtual ~ptr();
   bool m_bUnkeep;
};


template < class TYPE >
class CLASS_DECL_CA2_CUBE ptr_array : 
   virtual public ptr,
   virtual public base_array < TYPE * >
{
public:
};








