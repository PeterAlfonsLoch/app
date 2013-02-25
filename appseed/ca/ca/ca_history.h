#pragma once


namespace ca
{


   class CLASS_DECL_ca history :
      virtual public ::ca::object
   {
   public:


      history * m_phistory;


   protected:


      history();


   public:


      history(::ca::application * papp);
         
   
      virtual bool hist(const char *psz);

   };


} // namespace ca


