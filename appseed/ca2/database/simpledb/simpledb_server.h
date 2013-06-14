#pragma once


namespace simpledb
{

   class CLASS_DECL_ca2 server :
      virtual public ::ca2::object
   {
   public:


      base *     m_pbase;


      server(sp(::ca2::application) papp);
      virtual ~server();

      
      virtual bool open(const char * pszDatabase);
      virtual bool close();


      virtual bool sql(const char * pszQuery, var & var);
      

   };


} // namespace simpledb


