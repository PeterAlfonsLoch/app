#pragma once


namespace simpledb
{


   class CLASS_DECL_AXIS file_set :
      virtual public ::file::set,
      virtual public ::database::client
   {
   public:


      file_set(::aura::application * papp);
      virtual ~file_set();


      virtual void refresh();

      bool add_search(const char * pszSearchDirectory, bool bRecursive);

      virtual void clear_search();

      DECL_GEN_SIGNAL(data_on_after_change);


   };


} // namespace simpledb




