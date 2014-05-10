#pragma once

namespace simpledb
{

   class table;
   class set;

   class CLASS_DECL_CORE base : 
      public ::database::base
   {
   public:

      ::file::binary_buffer_sp                 m_spfileMeta;
      ::xml::document               m_xmldocumentMeta;
      string_map < table *, table * > m_mapTable;
      int32_t                           m_iErrorCode;


      base(sp(::base::application) papp);


      virtual int32_t connect();


      virtual class ::simpledb::set * create_dataset() const;

      table * get_table(const char * pszName);
      table * create_table(const char * pszName);


      // class ::database::base
      virtual class ::database::set * CreateDataset() const;
      virtual int32_t setErr(int32_t err_code);
      virtual long nextid(const char* sname);



   };


} // namespace simpledb
