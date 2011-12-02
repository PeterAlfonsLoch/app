#pragma once


#include "ca/database/database_id.h"


class CLASS_DECL_ca db_stra_set :
   public ::database::client
{
public:


   int         m_iMaximumCount;
   ::database::id     m_id;


   db_stra_set(db_server * pdatacentral, ::database::id & id);
   
   
   void get_data(stringa & stra);
   int set_data(stringa & stra);

};

