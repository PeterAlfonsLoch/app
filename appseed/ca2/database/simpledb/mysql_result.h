#pragma once


#ifndef METROWIN


#include "mysql/mysql.h"


namespace mysql
{


   class database;


   class CLASS_DECL_ca2 result :
      virtual public ::ca2::object
   {
   public:


      database *     m_pdatabase;
      MYSQL_RES *    m_pres;
      int32_t        m_iFieldCount;


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




