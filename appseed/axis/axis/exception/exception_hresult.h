#pragma once


class CLASS_DECL_AXIS hresult_exception : 
   virtual public ::exception::axis
{
public:
   
   
   HRESULT     m_hresult;


   hresult_exception(sp(::axis::application) papp, HRESULT hr);
   virtual ~hresult_exception();


   operator HRESULT () const
   {
      return m_hresult;
   }

};
