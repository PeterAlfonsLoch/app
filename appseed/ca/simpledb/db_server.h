#pragma once


class stringa;
class db_server;
class db_long_set;
class db_server;
class db_str_set;
class db_stra_set;
class DBFileSystemSizeSet;

class MidiInstrumentSet;

class stringa;
class CDWArray;


namespace sqlite
{
   class base;
}



class CLASS_DECL_ca db_server :
   virtual public ::database::server,
   virtual public ::ca::window_sp,
   virtual public gen::signalizable
{
public:


   ::sqlite::base *        m_pdb;
   ::sqlite::base *        m_pdatabaseImpl;
   ::critical_section      m_csImplDatabase;

   ::simpledb::base *      m_pbase;

   MidiInstrumentSet *     m_pmidiinstrumentset;
   db_stra_set *           m_pSongsDirsSet;
   db_long_set *           m_pLongsSet;
   db_str_set *            m_pStringSet;
   bool                    m_bWorking;
   bool                    m_bFullBuild;
   string                  m_strDatabase;
   DBFileSystemSizeSet *   m_pfilesystemsizeset;
   class ::im_post *       m_pimpost;
   class ::veiev_post *    m_pveievpost;
   
   mysql::database *       m_pmysqldbUser;
   string                  m_strUser;

   db_server(::ca::application * papp);
   virtual ~db_server();


   ::critical_section * GetImplCriticalSection();
   ::sqlite::base * GetImplDatabase();
   MidiInstrumentSet * GetMidiInstrumentSet();


   using database::server::data_server_load;
   virtual bool data_server_load(::database::id idSection, ::database::id id, ::database::id idIndex, ex1::writable & writable, ::database::update_hint * phint = NULL);

   using database::server::data_server_save;
   virtual bool data_server_save(::database::id idSection, ::database::id id, ::database::id idIndex, ex1::readable & readable, ::database::update_hint * phint = NULL);


   virtual bool data_pulse_change(::database::id idSection, ::database::id id, ::database::id idIndex, ::database::update_hint * puh);

   void close();

   bool load(const char * lpKey, string & str);
   bool load(const char * lpKey, ::ex1::writable & writer);

   bool save(const char * lpKey, const char * psz);
   bool save(const char * lpKey, ::ex1::readable & reader);


   static string calc_key(::database::id & idSection, ::database::id & id, ::database::id & idIndex);

   virtual bool initialize_user(mysql::database * pmysqldbUser, const char * pszUser);
   virtual bool initialize();
   virtual bool finalize();

   bool create_message_window();
   bool destroy_message_window();

   virtual class ::im_post & im_post();
   virtual class ::veiev_post & veiev_post();

   inline db_str_set * get_db_str_set();
   DECL_GEN_SIGNAL(_001OnTimer);

   void assert_valid() const;
   void dump(dump_context &) const;

};

