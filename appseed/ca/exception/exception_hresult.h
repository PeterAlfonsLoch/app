#pragma once


class CLASS_DECL_ca hresult_exception : 
   public base_exception
{
public:
   
   
   HRESULT     m_hresult;


   hresult_exception(HRESULT hr);
   virtual ~hresult_exception();


   operator HRESULT () const
   {
      return m_hresult;
   }

};
