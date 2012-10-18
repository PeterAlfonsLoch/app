#pragma once


class html_document;


namespace html
{


   class data;


   class signal : 
      public gen::signal_object
   {
   public:


      ::html::data * m_pdata;
      gen::signal_object * m_psignal;
      ::user::interaction * m_pui;


      signal(gen::signal * psignal);


   };

} // namespace html