#pragma once


namespace webserver
{


/*   namespace music
   {


      class song;
      class performer;
      class song_ptr_array;
      class song_source;
      class person_info;
      class person;
      class category;


   } // namespace netnode*/


   //class music_database_cache;


   class CLASS_DECL_ca fontopus_database :
      virtual public webserver::database,
      virtual public dynamic_source::ptr
   {
   public:


      int m_iLastServer;
      gen::property_set m_cache_person_only_name;
      gen::property_set m_cache_person;
      music::database_cache * m_pmusicdatabasecache;


      fontopus_database(::ca::application * papp);
      virtual ~fontopus_database();


      virtual bool initialize(int iServer);
      virtual bool initialize();
      bool get_session(const char * pszId, gen::property_set & set);
      bool set_session(const char * pszId, gen::property_set & set);
      void set_fun_session(const char * pszUserId, const char * pszSessId);
      string get_fun_session(const char * pszUserId);
      string fun_str_encrypt(const char * pszUserId, const char * psz);
      string fun_str_decrypt(const char * pszUserId, const char * psz);
      string fun_user_get_key1(const char * pszUserId);

      bool secure_email_available(const char * pszEmail);

      string veriwell_get_class_string_item(const char * pszClassId);

      string get_lang_string(var id, var languageid);

      int m_getstring_languageid;
      string m_strMainMode;



      var insertLang(var lang);
      var insertStyle(var style);

      var forceGetLangId(var lang);
      var forceGetStyleId(var style);

      var getLangId(var lang);
      var getStyleId(var style);

      int calc_topic_type(var topic);

      string get_string(var id, var langid = -1111111);


      bool is_valid_pass_v1(const char * psz);

      string secure_defer_register_login_email(
         const char * pszFirstName,
         const char * pszLastName,
         const char * pszLogin,
         const char * pszEmail,
         const char * pszRawPass,
         const char * pszInitialGroup,
         const char * pszRuri);

      bool secure_defer_register_a_b(const char * pszA, const char * pszB);
      bool secure_make_available_a(const char * pszA, int iLevel = 30);

      var _fun_get_dataclass(const char * pszId);
      void _fun_set_user_data(const char * pszUser, const char * pszKey, var var);
      bool _fun_get_user_data(const char * pszUser, const char * pszKey, var & var);

      virtual mysql::result * query(const char * pszSql);
      virtual var query_item(const char * pszSql, var varDefault = gen::g_newconst);
      virtual var query_items(const char * pszSql);
      virtual var query_row(const char * pszSql);
      virtual var query_rows(const char * pszSql);



      ::webserver::music::song_ptr_array * get_songs(
         var req_params,
         var query,
         var song,
         var lyrics,
         var querystyle_arg,
         var order,
         int limitstart,
         int limitcount,
         int & lastpage,
         int & totalcount,
         var cid,
         var aid,
         var topic,
         var funuid = gen::g_newconst,
         var params = gen::g_newconst,
         var flaga = gen::g_newconst);


      music::song_ptr_array * get_song_files(var id);
      music::song * get_song(var id);
      music::song * get_kar_file_song(var karfileid);
      music::song * get_song_kar_file(var songid, var index);
      music::song * get_lyrics_song(var topic, var topictype);
      music::song * get_song_lyrics(var songid, var index);
      music::song * get_chord_song(var chordid);
      music::song * get_song_chord(var songid, var index);
      music::song * get_topic_song(var topic, var topictype);

      ::webserver::music::song_source * get_song_source(var sourceid);


      music::person_info * getSongTopicTypeRolePersonInfo(var songid, var topictype, var role);
      music::person_info * getPersonInfo(var topicid, var topictype, var role);
      music::person_info * getPersonInfoEx(var topicid, var topictype, var role, var flaga = gen::g_newconst);
      music::person_info * getPersonInfoExFromA(var a, var flaga = gen::g_newconst);


      int get_lang_id(const char * pszLang);
      int get_style_id(const char * pszLang);

      string veriwell_getclassstring_item(var classid);
      var perpertop_getYears();
      var perpertop_getMonths(var year);
      var perpertop_getWeeks(var year, var month);

      var register_song_click(var songid, var address, var http_referer, var lang = "unk", var style = "unk", var referer = "unk", var type = CLICK_KARAOKE);
      var get_useragent_id_ex(var useragent);

      music::person * get_person(var personid, var flaga = gen::g_newconst);
      var get_song_classes_for_performers(var song);
      music::category * get_class_for_performers(int level, string order, string classa);
      var get_classes_for_performers(int level,  string order, string parentclass, int topictype = 0);



      var get_performers(var classid,  var namequerycode, var order, var topic, var query);
      var get_performers_by_class(var classid, var namequerycode, var order, var topic, var query);

      music::database_cache & cache();


      bool is_karfile_licensed(__int64 iKarFileId);

   };

   CLASS_DECL_ca string ida_to_condition(string list);


   CLASS_DECL_ca var cgcl_ltgt_to_array(string str);



} // namespace webserver
