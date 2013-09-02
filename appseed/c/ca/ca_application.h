#pragma once


class CLASS_DECL_c application :
   virtual public object
{
public:


   class system *                                  m_pcasystem;
   string                                          m_strAppName;


   application();
   virtual ~application();


   virtual sp(element) alloc(sp(type) info);
   virtual sp(element) alloc(const id & idType);


   int32_t simple_message_box(const char * pszMessage, UINT fuStyle);


   virtual bool load_string(string & str, id id);


};
