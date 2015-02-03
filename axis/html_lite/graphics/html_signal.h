#pragma once


class html_document;


namespace html
{


   class data;


   class signal :
      public signal_details
   {
   public:


      ::html::data * m_pdata;
      signal_details * m_psignal;
      sp(::user::interaction) m_pui;


      signal(class ::signal * psignal);


   };

} // namespace html
