#pragma once

namespace music
{
   class song;
}

namespace netnode
{

   class CLASS_DECL_CA2_CUBE music :
      public ptr
   {
   public:
      string m_strMainMode;
      var m_performer_glue1;
      var m_performer_lastglue1;
      var m_langid;
      var m_styleid;
   
      music();

      string karaoke_getFwdParamLang();
      string karaoke_getFwdParamStyle();

      ui_menu * get_top_left_menu();
      ui_menu * menu_getTopLeftMenu2();
      string karaoke_get_song_count();
      string karaoke_get_performer_count();
      string karaoke_get_class_count();
      ui_menu * menu_get_songs_menu(const char * pszTitle, const char * pszType,
         const char * pszCid = NULL, const char * pszAid = NULL, const char * pszTarget = NULL);
   
   
      ui_menu * karaoke_menu_get_top_left_menu2();
      ui_menu * karaoke_menu_get_song_menu(stringa & straSong);
      ui_menu * karaoke_menu_get_song_last_insertions_menu(const char * pszCid = NULL,
            const char * pszAid = NULL, const char * pszTarget = NULL);
      ui_menu * karaoke_menu_get_songs_menu(const char * pszTitle, const char * pszType, 
            const char * pszCid = NULL, const char * pszAid = NULL, const char * pszTarget = NULL);
      
      ui_menu * karaoke_menu_get_top_left_menu();


      string get_class_string(const char * pszClassId);

      string get_class_string_item(const char * pszClassId);

      void print_search_form_index_1();
      
      virtual string get_root_path(
              const char * pszRoot = NULL, 
            const char * pszDomain = NULL,
            const char * pszLocale = NULL,
            const char * pszStyle = NULL);
      
      virtual string get_root_medium_title(
              const char * pszRoot = NULL, 
            const char * pszDomain = NULL,
            const char * pszLocale = NULL,
            const char * pszStyle = NULL);

      virtual string get_root_short_title(
              const char * pszRoot = NULL, 
            const char * pszDomain = NULL,
            const char * pszLocale = NULL,
            const char * pszStyle = NULL);

      virtual string get_root_title(
              const char * pszRoot = NULL, 
            const char * pszDomain = NULL,
            const char * pszLocale = NULL,
            const char * pszStyle = NULL);

      var song_get_file_extension(var songid);
      var song_get_file_type(var songid);
      var song_get_file_name(var songid);
      var song_get_file_path(var songid);
      var song_resolve_file_name(var filename);
      var song_resolve_gz_file_name(var filename);
      var song_get_song_type_image1(var type);
      var song_get_song_extension_url(var extension);

      string performer_implode1(var performernamea);

      var veriwellkaraoke_getperformerinfo(var performerid);

      string music_performer_get_reg_exp(var code);

      string veriwell_getclassstring(var classid);
      string veriwell_getclassstring_item(var classid);
      string veriwell_getsongfileextension(var filename);
      string veriwell_map_song_file_extension_to_style(var type);
      var register_song_click(var songid, var address, var http_referer, var lang = 'unk', var style = 'unk', var referer = 'unk', var type = CLICK_KARAOKE);
      //void karaoke_update_tmp_song_clickdistinct1();
      //void karaoke_update_tmp_song_clickdistinct1_item(var songid);
      //void music_report_error(var error, bool bEmail = false);
      string song_get_content_type(var songid);
      void veriwellkaraoke_printperformerurlinfo(var urlinfo);

      
   

      string sparam_url_encode(var str); // single/simple parameter/argument url encoding

      string imgsrc(var id, var subtype = "");
      void register_get(gen::property_set & set);
      void register_post(gen::property_set & set);
      void register_request(gen::property_set & set);

      string js_langstr(var id, var value = gen::g_newconst);
      void js_tr_mdwn_parama(var tr_mdwn_parama);
      string karaoke_to_song_info_topictype(var topictype);
      string karaoke_nfy_count(var n);
      //var get_simage_path(var visual);
      //var karaoke_get_performer_list_2();
      //void karaoke_print_pick_artist(var rowa, var var_src, var var_dest, var return_link);
      void echo_mb_music_top_image_url();
      string mb_music_top_image_url();

      void printListClassInclude(var cid);
      void printListCategoryInclude(var category);
      void printListArtistInclude(var aid);
      void printListArtistSmallInclude(var aid);

      void print_lang_combo1(const char * pszLocale, const char * pszStyle);


      var file_get_kar_file_id(var filename);
      var file_get_kar_file_name(var id);
      var file_get_file(var filename, ::music::song ** ppsong);
      var file_get_file_by_kar_file_id(var karfileid, ::music::song ** ppsong);
      var file_test_file(var filename, ::music::song ** ppsong);

      var report_error(var error, bool bEmail);
   };
} // namespace netnode

