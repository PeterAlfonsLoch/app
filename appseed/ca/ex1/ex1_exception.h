#pragma once


namespace ex1
{


   class CLASS_DECL_ca exception :
      public base_exception
   {
   public:


      exception(::ca::application * papp);
      exception(const exception & e);


      void operator delete(void * pbData);
      void operator delete(void * pbData, const char * lpszFileName, int32_t nLine);


   };


   typedef ::ca::smart_pointer < exception > exception_sp;


} // namespace ex1



