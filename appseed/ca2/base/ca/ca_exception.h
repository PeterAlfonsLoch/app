#pragma once


namespace ca
{


   class CLASS_DECL_ca2 exception :
      virtual public ::ca::ca
   {
   public:


      virtual ~exception();
      virtual void Delete();


   };


   void CLASS_DECL_ca2 rethrow(exception * pe);


} // namespace ca

