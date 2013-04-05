#pragma once


class CLASS_DECL_ca hresult_exception : 
   virtual public base_exception
{
public:
   
   
   HRESULT     m_hresult;


   hresult_exception(::ca::applicationsp papp, HRESULT hr);
   virtual ~hresult_exception();


   operator HRESULT () const
   {
      return m_hresult;
   }

};
