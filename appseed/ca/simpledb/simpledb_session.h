#pragma once


namespace simpledb
{

   class server;

   class CLASS_DECL_ca session :
      virtual public ::ca::object
   {
   public:


      server *       m_pserver;

      session(::ca::applicationsp papp);
      virtual ~session();

      
      virtual bool open(const char * pszDatabase);
      virtual bool close();


      virtual bool query(const char * pszQuery, var & var);
      

   };


} // namespace simpledb


