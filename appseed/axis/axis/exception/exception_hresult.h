#pragma once


class CLASS_DECL_AXIS hresult_exception : 
   virtual public ::exception::base
{
public:
   
   
   HRESULT     m_hresult;


   hresult_exception(sp(::base::application) papp, HRESULT hr);
   virtual ~hresult_exception();


   operator HRESULT () const
   {
      return m_hresult;
   }

};
