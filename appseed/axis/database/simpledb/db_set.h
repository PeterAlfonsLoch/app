#pragma once

class db_server;

class CLASS_DECL_AXIS db_set :
   virtual public ::database::client
{
public:


   sp(sqlite::set)      m_pdataset;
   string               m_strTable;


   db_set(db_server * pserver, const char * pszTable);
   virtual ~db_set();


   db_server *            db();

};


class CLASS_DECL_AXIS simpledb_set :
   virtual public ::database::client
{
public:

   sp(simpledb::set)    m_pdataset;
   string               m_strTable;


   simpledb_set(db_server * pserver, const char * pszTable);
   virtual ~simpledb_set();

   db_server *            db();


};
