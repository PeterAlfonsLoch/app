#pragma once


namespace ca2
{


   class CLASS_DECL_ca2 history :
      virtual public object
   {
   public:


      history * m_phistory;


   protected:


      history();


   public:


      history(sp(::application) papp);
         
   
      virtual bool hist(const char *psz);

   };


} // namespace ca2


