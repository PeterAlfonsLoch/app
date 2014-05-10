#pragma once


namespace core
{


   class CLASS_DECL_CORE history :
      virtual public ::object
   {
   public:


      history * m_phistory;


   protected:


      history();


   public:


      history(sp(::base::application) papp);
         
   
      virtual bool hist(const char *psz);

   };


} // namespace core


