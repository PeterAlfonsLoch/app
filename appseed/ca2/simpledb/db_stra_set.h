#pragma once


#include "database/database_id.h"


class CLASS_DECL_ca2 db_stra_set :
   public ::database::client
{
public:


   int32_t         m_iMaximumCount;
   ::database::id     m_id;


   db_stra_set(db_server * pdatacentral, ::database::id & id);
   
   
   void get_data(stringa & stra);
   ::count set_data(stringa & stra);

};

