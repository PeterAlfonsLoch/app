#pragma once


class CLASS_DECL_AXIS db_str_set :
   virtual public ::object
{
public:

   
   sp(::db_set)            m_pcore;
   

   db_str_set(db_server * pserver);
   virtual ~db_str_set();


   bool load(const string & strKey, string & strValue);
   bool save(const string & strKey, const string & strValue);

   bool remove(const string & strKey);


};




