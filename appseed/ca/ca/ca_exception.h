#pragma once


namespace ca
{


   class CLASS_DECL_ca exception :
      virtual public ::gen::object
   {
   public:


      virtual ~exception();
      virtual void Delete();


   };


   void CLASS_DECL_ca rethrow(exception * pe);


} // namespace ca

