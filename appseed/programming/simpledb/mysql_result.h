#pragma once


typedef struct st_mysql_res MYSQL_RES;
typedef char **MYSQL_ROW;		/* return data as array of strings */

#ifndef METROWIN


namespace mysql
{


   class database;


   class CLASS_DECL_CA2_DATA result :
      virtual public ::simpledb::result
   {
   public:


      MYSQL_RES *    m_pres;


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




