#pragma once


namespace simpledb
{

   class CLASS_DECL_ca server :
      virtual public ::ca::object
   {
   public:


      base *     m_pbase;


      server(::ca::applicationsp papp);
      virtual ~server();

      
      virtual bool open(const char * pszDatabase);
      virtual bool close();


      virtual bool sql(const char * pszQuery, var & var);
      

   };


} // namespace simpledb


