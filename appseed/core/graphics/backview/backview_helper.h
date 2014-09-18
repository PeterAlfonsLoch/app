#pragma once


namespace backview
{


   class CLASS_DECL_CORE Helper :
      virtual public ::object
   {
   public:


      Main & m_main;


      Helper(Main & main);


      Main & HelperGetMain();


      inline mutex & user_mutex() { return m_main.user_mutex();}


   };


} // namespace backview







