#pragma once


namespace ex1
{


   class CLASS_DECL_ca exception :
      public base_exception
   {
   public:


      exception();
      exception(const exception & e);


      void PASCAL operator delete(void * pbData);
      void PASCAL operator delete(void * pbData, const char * lpszFileName, int nLine);


   };


   typedef ::ca::smart_pointer < exception > exception_sp;


} // namespace ex1



