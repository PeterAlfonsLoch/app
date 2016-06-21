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

      using ::file::set::add_search;
      virtual void add_search(const ::file::path & pathSearchFolder, bool bRecursive) override;

      virtual void clear_search();

      DECL_GEN_SIGNAL(data_on_after_change);


   };


} // namespace simpledb




