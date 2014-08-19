#pragma once


namespace database
{

   
   class client;
   class server;

   
   class CLASS_DECL_BASE update_hint  :
      virtual public ::object
   {
   public:


      enum e_update
      {
         update_internal,
         update_user
            
      };
      

      flags < e_update > m_flagsupdate;
      comparable_array < client *, client * > m_selfa;


      update_hint();
      virtual ~update_hint();


      flags < e_update > & GetUpdateFlags();

      void add_self(client * lpvoid);
      bool has_self(client * lpvoid);


   };

   
} // namespace database





