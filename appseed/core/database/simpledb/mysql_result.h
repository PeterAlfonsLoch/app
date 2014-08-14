#pragma once


typedef struct st_mysql_res MYSQL_RES;
typedef char **MYSQL_ROW;		/* return data as array of strings */

#ifndef METROWIN


namespace mysql
{


   class database;


   class CLASS_DECL_CORE result :
      virtual public ::object
   {
   public:


      database *     m_pdatabase;
      MYSQL_RES *    m_pres;
      int32_t        m_iFieldCount;
      uint64_t       m_uiAffectedRows;


      result(database * pdatabase, MYSQL_RES * pres);
      virtual ~result();


      MYSQL_ROW fetch_row();
      unsigned long * fetch_lengths();
      int64_t num_rows();
      int32_t num_fields();

      bool free_result();


   };


} //   namespace mysql


#endif




