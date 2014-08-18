#pragma once


namespace database
{

   class client;


   class CLASS_DECL_AXIS key
   {
   public:


      client *          m_pclient; // client may intefere in default key calculation
      id                m_idSection;
      id                m_idKey;
      id                m_idIndex;



      key();
      key(const key & key);
      key(client * pclient, id idSection, id idKey, id idIndex);


      key & operator = (const key & key);


   };


} // namespace database






