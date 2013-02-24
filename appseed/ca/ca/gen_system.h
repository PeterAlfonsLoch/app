#pragma once


namespace gen
{

   class CLASS_DECL_ca system :
      virtual public ::ca::system,
      virtual public ::gen::object
   {
   public:


      static id_space                            s_idspace;

      static class id                            idEmpty;


      system();
      virtual ~system();

      virtual bool assert_failed_line(const char * lpszFileName, int32_t iLine);
      virtual bool on_assert_failed_line(const char * pszFileName, int32_t iLine);

      virtual void on_allocation_error(::ca::application * papp, ::ca::type_info & info);
      ::ca::ca * alloc(::ca::application * papp, ::ca::type_info & info);
      ::ca::ca * alloc(::ca::application * papp, const std_type_info & info);
      virtual ::ca::ca * on_alloc(::ca::application * papp, ::ca::type_info & info);
      virtual void on_delete(::ca::ca * pobject);


      static inline class id id(const ::std_type_info & info);
      static inline class id id(const char * psz);
      static inline class id id(const string & str);
      static inline class id id(int64_t i);
      static inline class id_space & id();
      inline class id id(const var & var);
      inline class id id(const gen::property & prop);

      friend class application;

   protected:


      virtual bool initialize();


   };

   inline id system::id(const class var & var)
   {
      return ::id((const char *) (class var &) var);
   }

   inline id system::id(const gen::property & prop)
   {
      return ::id((const string &) (gen::property &) prop);
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


} // namespace gen


