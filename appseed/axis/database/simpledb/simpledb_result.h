#pragma once




namespace simpledb
{


   class database;


   class CLASS_DECL_AXIS result :
      virtual public ::object
   {
   public:


      database *     m_pdatabase;
//      MYSQL_RES *    m_pres;
      int32_t        m_iFieldCount;
      uint64_t       m_uiAffectedRows;


      result(database * pdatabase);
      virtual ~result();


//      MYSQL_ROW fetch_row();
  //    unsigned long * fetch_lengths();
      virtual int64_t num_rows();
      virtual int32_t num_fields();

      virtual bool free_result();


   };


} //   namespace simpledb


