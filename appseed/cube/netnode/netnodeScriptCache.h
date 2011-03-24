#pragma once

class netnodeScript;

class netnodeScriptCache :
   virtual public ::radix::object
{
public:
   netnodeScriptCache(::ca::application * papp);
   ~netnodeScriptCache(void);

   netnodeScriptManager * m_pmanager;
   netnodeScriptInstance * create_instance(const char * lpcszName);

   void set_all_out_of_date();
protected:
   void cache(netnodeScript * pscript);
   
   netnodeScript * get(const char * lpcszName);
   critical_section  m_cs;
   CMapStringToPtr   m_map;
};
