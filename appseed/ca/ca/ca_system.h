#pragma once


namespace ca
{


   class CLASS_DECL_ca system :
      virtual public ::ca::application
   {
   public:


      system();
      virtual ~system();

      virtual bool assert_failed_line(const char * lpszFileName, int32_t iLine);
      virtual bool on_assert_failed_line(const char * pszFileName, int32_t iLine);

      friend class application;

      virtual ::ca::ca * clone(::ca::ca * pobj);
      virtual void discard_to_factory(::ca::ca * pca);

      virtual bool initialize();


   };


} // namespace ca


