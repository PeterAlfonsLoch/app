#pragma once


namespace ca2
{


   class CLASS_DECL_ca2 exception :
      virtual public ::ca2::ca2
   {
   public:


      virtual ~exception();
      virtual void Delete();


   };


   void CLASS_DECL_ca2 rethrow(exception * pe);


} // namespace ca2

