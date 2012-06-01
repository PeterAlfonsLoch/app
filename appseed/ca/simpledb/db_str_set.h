#pragma once


class CLASS_DECL_ca db_str_set :
   public db_set
{
public:

   class CLASS_DECL_ca str_item
   {
   public:

      DWORD       m_dwTimeout;
      string        m_str;

   };


   ::collection::string_map < str_item > m_map;

   sockets::socket_handler    m_handler;
   sockets::http_session *    m_phttpsession;


   db_str_set(db_server * pserver);
   virtual ~db_str_set();


   bool load(const char * lpKey, string &strValue);
   bool save(const char * lpKey, const char * lpcsz);

   bool remove(const char * lpKey);


};


