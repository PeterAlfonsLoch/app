#pragma once

namespace simpledb
{

   class table;
   class set;

   class CLASS_DECL_ca base : 
      public ::database::base
   {
   public:
      friend class set;

      base(::ca::application * papp);

      ::ex1::filesp m_spfileMeta;
      ::xml::node m_nodeMeta;
      ::collection::map < string, string, table *, table * > m_mapTable;

      virtual int connect();


      virtual class set * create_dataset();

   protected:

      table * get_table(const char * pszName);
      table * create_table(const char * pszName);


   };


} // namespace simpledb
