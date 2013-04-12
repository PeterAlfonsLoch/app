#pragma once


class html_document;


namespace html
{


   class data;


   class signal : 
      public ::ca::signal_object
   {
   public:


      ::html::data * m_pdata;
      ::ca::signal_object * m_psignal;
      sp(::user::interaction) m_pui;


      signal(::ca::signal * psignal);


   };

} // namespace html