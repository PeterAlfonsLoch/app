#pragma once


namespace webserver
{


   namespace music
   {


      class CLASS_DECL_ca database_cache :
         virtual public dynamic_source::ptr
      {
      public:


         database_cache();

         // $onlycheck - it does only check, but does not update the last user update time
         bool can_bypass_user_update_verification_code_check(var userid);

         // $onlycheck - it does only check, but does not update the last user update time
         void set_bypass_user_update_verification_code_check(var userid);

         void defer_updatecycle1();

         void create_proc();

         var get_useragent_id_ex(var useragent);


         var getClassIdArray2();

         void pulse_access_stats_1();

         void registerSongClick(var topicid, var address, var http_referer, var lang = "unk", var style = "unk", var referer = "unk", var type = CLICK_KARAOKE);
         void tmp_song_insert(bool bVerbose);;
         void tmp_song_update_classida(bool bVerbose);
         void tmp_song_update_performerida(bool bVerbose);
         var gethostbyaddr_ex(var ip);
         bool access_stats_1_gethostbyaddr(var ip, string & strhostname, string &lastvisit, string &lastgethost);
         var access_stats_1_updatehost(var ip);
         void update_tmp_song_clickdistinct1_item(var song_click_id, var topicid, var langid, var styleid, bool bVerbose = false);
         void song_cache_initialize(bool bVerbose);
         var update_song_click_stats(bool bVerbose = false, bool bPartial = true);

         void karaoke_update_tmp_song_clickdistinct1(bool bVerbose = false);

         void karaoke_update_tmp_song_clickdistinct1_item(var song_click_id, var topicid, var langid, var styleid, bool bVerbose = false);

         void tmp_performer_update(bool bVerbose);

         void tmp_performer_item_update_classida(var performerid, var classida);

         void tmp_performer_item_update_chord_classida(var performerid, var classida);

         void karaoke_update_tmp_class( bool bVerbose);
         var karaoke_getCodeArray(var classid, var topic, bool bVerbose);

         var karaoke_getCodeArrayField(var classid, var topic, bool bVerbose);

         void tmp_class_update_classida_item(var topictype, var classid, var classida, bool bVerbose);

         void tmp_class_update_classida( bool bVerbose);

         void tmp_class_2_update_classida(bool bVerbose);



         void karaoke_update_tmp_song_lyricscount(bool bVerbose);
         void karaoke_update_tmp_song_chordcount(bool bVerbose);
         void karaoke_update_tmp_song_karaokecount(bool bVerbose);
         void karaoke_update_tmp_song_topictype_count(var tmp_song_field, var topictype, bool bVerbose);

         void update_lyrics(bool bVerbose = false);

         void full_song_update(bool bVerbose);
         void on_song_insertion(bool bVerbose);


         void on_song_insertion_1(bool bVerbose);


         void update_tmp_song_lang_style_rank(bool bVerbose= false);

         void tmp_topic_lang_style_update_top(var top_field, var lastdatetime, bool bVerbose= false);


         void tmp_topic_lang_style_update_top_item(var topicid, var langid, var styleid, var top_field, var lastdatetime, bool bVerbose= false);

         var get_min_datetime_hour_round_song_click();
         var get_max_datetime_hour_round_song_click();;

         var get_min_datetime_topic_click_compiled();
         var get_max_datetime_topic_click_compiled();

         void update_tmp_topic(bool bVerbose);





         void update_tmp_topic_click(bool bVerbose);

         var get_classida_text(var ida);

         var debug_delta(var time1, var time2);


      }; // cache class


   } // namespace music


} // namespace webserver


