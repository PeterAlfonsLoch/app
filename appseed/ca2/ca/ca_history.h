#pragma once


namespace ca
{


   class CLASS_DECL_ca2 history :
      virtual public ::ca::object
   {
   public:


      history * m_phistory;


   protected:


      history();


   public:


      history(sp(::ca::application) papp);
         
   
      virtual bool hist(const char *psz);

   };


} // namespace ca


