#pragma once


namespace ca2
{


   class CLASS_DECL_ca2 history :
      virtual public ::ca2::object
   {
   public:


      history * m_phistory;


   protected:


      history();


   public:


      history(sp(::ca2::application) papp);
         
   
      virtual bool hist(const char *psz);

   };


} // namespace ca2


