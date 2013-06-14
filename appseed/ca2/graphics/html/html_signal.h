#pragma once


class html_document;


namespace html
{


   class data;


   class signal : 
      public ::ca2::signal_object
   {
   public:


      ::html::data * m_pdata;
      ::ca2::signal_object * m_psignal;
      sp(::user::interaction) m_pui;


      signal(::ca2::signal * psignal);


   };

} // namespace html