#pragma once


namespace ca2
{


   class CLASS_DECL_ca2 system :
      virtual public ::ca2::application
      #ifdef LINUX
      , virtual public ::exception::translator
      #endif
   {
   public:


      system();
      virtual ~system();

      virtual bool assert_failed_line(const char * lpszFileName, int32_t iLine);
      virtual bool on_assert_failed_line(const char * pszFileName, int32_t iLine);

      friend class application;

      virtual sp(element) clone(sp(element) pobj);
      virtual void discard_to_factory(sp(element) pca);


      static id_space                            s_idspace;

      static class id                            idEmpty;




      virtual void on_allocation_error(sp(::application) papp, sp(type) info);
      sp(element) alloc(sp(::application) papp, sp(type) info);
      sp(element) alloc(sp(::application) papp, const std_type_info & info);
      virtual sp(element) on_alloc(sp(::application) papp, sp(type) info);


      static inline class id id(const ::std_type_info & info);
      static inline class id id(const char * psz);
      static inline class id id(const string & str);
      static inline class id id(int64_t i);
      static inline class id_space & id();
      inline class id id(const var & var);
      inline class id id(const property & prop);

   };

   inline id system::id(const class var & var)
   {
      return ::id((const char *) (class var &) var);
   }

   inline id system::id(const property & prop)
   {
      return ::id((const string &) (property &) prop);
   }


   inline id system::id(const std_type_info & info)
   {
#ifdef WINDOWS
      return s_idspace(info.name());
#else
      return s_idspace(info.name());
#endif
   }

   inline id system::id(const char * psz)
   {
      return s_idspace(psz);
   }

   inline id system::id(const string & str)
   {
      return s_idspace(str);
   }

   inline id system::id(int64_t i)
   {
      return s_idspace(i);
   }

   inline id_space & system::id()
   {
      return s_idspace;
   }

} // namespace ca2



inline id::id(const char * psz)
{
   operator = (::ca2::system::id(psz));
}

#if defined(_LP64) || defined(_AMD64_)
inline id & id::operator = (int32_t i)
{
   return operator = (::ca2::system::id(::str::from(i)));
}
#endif

inline id & id::operator = (int_ptr i)
{
   return operator = (::ca2::system::id(::str::from(i)));
}
