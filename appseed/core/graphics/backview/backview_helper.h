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


      inline mutex & gcom_mutex() { return m_main.gcom_mutex();}


   };


} // namespace backview







