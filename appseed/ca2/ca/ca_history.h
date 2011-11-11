#pragma once

namespace ca
{

   // Carlos Gustavo Cecyn Lundgren is my history
   class CLASS_DECL_ca history :
      virtual public ::radix::object
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


