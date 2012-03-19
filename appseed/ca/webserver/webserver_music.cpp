#include "StdAfx.h"


namespace webserver
{

   namespace music
   {

   music::music()
   {
      if(gprop("param_lang") == "se")
      {
         m_performer_glue1 = ", ";
         m_performer_lastglue1 = " och ";
      }
      if(gprop("param_lang") == "pt-br" || gprop("param_lang") == "br")
      {
         m_performer_glue1 = ", ";
         m_performer_lastglue1 = " e ";
      }
      else if(gprop("param_lang") == "en" || gprop("param_lang") == "en-uk")
      {
         m_performer_glue1 = ", ";
         m_performer_lastglue1 = " and ";
      }
      else
      {
         m_performer_glue1 = ", ";
         m_performer_lastglue1 = ", ";
      }

      m_langid = musicdb().getLangId(gprop("param_locale"));
      m_styleid = musicdb().getStyleId(gprop("param_style"));

   }

   string music::get_root_path(
      const char * pszRoot,
      const char * pszDomain,
      const char * pszLocale,
      const char * pszStyle)
   {
      UNREFERENCED_PARAMETER(pszRoot);
      UNREFERENCED_PARAMETER(pszDomain);
      UNREFERENCED_PARAMETER(pszLocale);
      UNREFERENCED_PARAMETER(pszStyle);
      return "";
   }

   string music::get_root_medium_title(
      const char * pszRoot,
      const char * pszDomain,
      const char * pszLocale,
      const char * pszStyle)
   {
      UNREFERENCED_PARAMETER(pszRoot);
      UNREFERENCED_PARAMETER(pszDomain);
      UNREFERENCED_PARAMETER(pszLocale);
      UNREFERENCED_PARAMETER(pszStyle);
      return "";
   }

   string music::get_root_short_title(
      const char * pszRoot,
      const char * pszDomain,
      const char * pszLocale,
      const char * pszStyle)
   {
      UNREFERENCED_PARAMETER(pszRoot);
      UNREFERENCED_PARAMETER(pszDomain);
      UNREFERENCED_PARAMETER(pszLocale);
      UNREFERENCED_PARAMETER(pszStyle);
      return "";
   }

   string music::get_root_title(
      const char * pszRoot,
      const char * pszDomain,
      const char * pszLocale,
      const char * pszStyle)
   {
      UNREFERENCED_PARAMETER(pszRoot);
      UNREFERENCED_PARAMETER(pszDomain);
      UNREFERENCED_PARAMETER(pszLocale);
      UNREFERENCED_PARAMETER(pszStyle);
      return "";
   }

   ui_menu * music::get_top_left_menu()
   {
      //   ui_menu menu;
      return gprop("veriwell_top_left_menu").ca2 < ui_menu > ();
   }

   ui_menu * music::menu_getTopLeftMenu2()
   {
      //   ui_menu menu;
      return gprop("veriwell_top_left_menu").ca2 < ui_menu > ();
   }

   string music::karaoke_get_song_count()
   {
      if(m_strMainMode == "cifras")
      {
         return musicdb().query_item("SELECT COUNT(DISTINCT topic_song.song) FROM topic_song WHERE topic_song.topictype = 2");
      }
      else if(m_strMainMode == "letras")
      {
         return musicdb().query_item("SELECT COUNT(DISTINCT topic_song.song) FROM topic_song WHERE topic_song.topictype = 1 OR topic_song.topictype = 1001");
      }
      else
      {
         return musicdb().query_item("SELECT COUNT(song.id) FROM song;");
      }
   }

   string music::karaoke_get_performer_count()
   {
      if(m_strMainMode == "cifras")
      {
         return musicdb().query_item("SELECT COUNT(DISTINCT topic_person.person) FROM topic_person INNER JOIN topic_song ON topic_song.topic = topic_person.topic AND topic_song.topictype = topic_person.topictype INNER JOIN topic_song as ts2 ON ts2.song = topic_song.song WHERE ts2.topictype = 2");
      }
      else if(m_strMainMode == "letras")
      {
         return musicdb().query_item("SELECT COUNT(DISTINCT topic_person.person) FROM topic_person INNER JOIN topic_song ON topic_song.topic = topic_person.topic AND topic_song.topictype = topic_person.topictype INNER JOIN topic_song as ts2 ON ts2.song = topic_song.song WHERE ts2.topictype = 1 OR topic_song.topictype = 1001");
      }
      else
      {
         return musicdb().query_item("SELECT COUNT(DISTINCT song_performer.performerid) FROM song_performer;");
      }
   }

   string music::karaoke_get_class_count()
   {
      if(m_strMainMode == "cifras")
      {
         return musicdb().query_item("SELECT COUNT(DISTINCT topic_class.class) FROM topic_class INNER JOIN topic_song ON topic_song.topic = topic_class.topic AND topic_song.topictype = topic_class.topictype INNER JOIN topic_song as ts2 ON ts2.song = topic_song.song WHERE ts2.topictype = 2");
      }
      else if(m_strMainMode == "letras")
      {
         return musicdb().query_item("SELECT COUNT(DISTINCT topic_class.class) FROM topic_class INNER JOIN topic_song ON topic_song.topic = topic_class.topic AND topic_song.topictype = topic_class.topictype INNER JOIN topic_song as ts2 ON ts2.song = topic_song.song WHERE ts2.topictype = 1 OR topic_song.topictype = 1001");
      }
      else
      {
         return musicdb().query_item("SELECT COUNT(DISTINCT topic_class.class) FROM topic_class;");
      }
   }

   ui_menu * music::menu_get_songs_menu(const char * pszTitle, const char * pszType,
      const char * pszCid, const char * pszAid, const char * pszTarget)
   {
      //   ui_menu * pmenu = new ui_menu(this);
      if(gprop("param_root") == "karaoke")
      {
         return karaoke_menu_get_songs_menu(pszTitle, pszType, pszCid, pszAid, pszTarget);
      }
      else if(gprop("param_root") == "cifras")
      {
         //   return cifras_music.menu_get_songs_menu($title, $type, $cid, $aid, $target);
      }
      else if(gprop("param_root") == "letras")
      {
         //      return letras_music.menu_get_songs_menu($title, $type, $cid, $aid, $target);
      }

      return NULL;
   }



   ui_menu * music::karaoke_menu_get_top_left_menu()
   {
      return NULL;
   }

   ui_menu * music::karaoke_menu_get_song_last_insertions_menu(const char * pszCid,
      const char * pszAid, const char * pszTarget)
   {
      UNREFERENCED_PARAMETER(pszCid);
      UNREFERENCED_PARAMETER(pszAid);
      UNREFERENCED_PARAMETER(pszTarget);
      return NULL;
   }

   ui_menu * music::karaoke_menu_get_songs_menu(const char * pszTitle, const char * pszType,
      const char * pszCid, const char * pszAid, const char * pszTarget)
   {
      UNREFERENCED_PARAMETER(pszTitle);
      UNREFERENCED_PARAMETER(pszType);
      UNREFERENCED_PARAMETER(pszCid);
      UNREFERENCED_PARAMETER(pszAid);
      UNREFERENCED_PARAMETER(pszTarget);
      return NULL;
   }

   ui_menu * music::karaoke_menu_get_song_menu(stringa & straSong)
   {
      UNREFERENCED_PARAMETER(straSong);
      return NULL;
   }

   ui_menu * music::karaoke_menu_get_top_left_menu2()
   {
      return NULL;
   }


   void music::print_search_form_index_1()
   {
      string path = sys_get_include_path("ds", "partial", "search_form_index_1");
      include(path);
   }


   string music::get_class_string(const char * pszClassId)
   {
      stringa stra;
      stra.add_tokens(pszClassId, ",", false);
      for(int i = 0; i < stra.get_count(); i++)
      {
         stra[i] = get_class_string_item(stra[i]);
      }
      return stra.implode(", ");
   }

   string music::get_class_string_item(const char * pszClassId)
   {
      return musicdb().veriwell_get_class_string_item(pszClassId);
   }

   var music::song_get_file_extension(var songid)
   {
      var filename = song_get_file_name(songid);
      if(!filename)
         return false;
      return System.file().extension(filename);
   }

   var music::song_get_file_type(var songid)
   {
      var var = song_get_file_extension(songid);
      if(!var)
         return false;
      string str = var;
      str.make_lower();
      if(str == "mid")
         return "Midi";
      else if(str == "kar")
         return "SoftKaraoke";
      else if(str == "st3")
         return "StarKorea3";
      else if(str == "mk1")
         return "Microke1";
      return ::var(::var::e_type::type_null);
   }

   var music::song_get_file_name(var songid)
   {
      string sql = "SELECT song_file.filename FROM song WHERE song.id = " + songid;;
      return musicdb().query_item(sql);
   }

   var music::song_get_file_path(var songid)
   {
      var filename = song_get_file_name(songid);
      if(!filename)
         return false;
      return song_resolve_file_name(filename);
   }

   var music::song_resolve_file_name(var varFilename)
   {
      //global $g_karaoke_basepath;
      string basepath = gprop("g_karaoke_basepath");
      string filename = varFilename;

      dprint("karaoke_basepath=" + basepath);

      strsize pos = filename.find("_-_");
      dprint(filename);
      dprint("pos="+gen::str::itoa(pos));

      string prefix;
      string prefix1;
      string prefix2;
      string path;
      if(pos > 0 && natural(pos) < (strlen(filename) - 3))
      {
         prefix = filename;
         prefix.replace(" ", "");
         prefix1 = prefix.Mid(0, 1);
         prefix2 = prefix.Mid(0, pos);
         prefix1.make_lower();
         prefix2.make_lower();
         path = basepath + prefix1 + "/" + prefix2 + "/" + filename;
         dprint(path);
         if(Application.file().exists(path))
            return path;
      }

      strsize len;
      pos = filename.find("_");
      if(pos < 0)
         len = min(strlen(filename), 3);
      else
         len = pos;


      prefix = filename.Mid(0, len);
      prefix.make_lower();
      prefix = gen::str::pad(prefix, 3, "_", gen::str::pad_right);
      path = basepath + prefix[0] + "/" + prefix[1] + "/" + prefix[2] + "/" + filename;
      dprint(path);
      if(Application.file().exists(path))
         return path;

      path = basepath + filename;
      if(Application.file().exists(path))
         return path;

      return false;
   }

   var music::song_resolve_gz_file_name(var varFilename)
   {
      //global $g_karaoke_basepath;
      string basepath = gprop("g_karaoke_basepath");
      string filename = varFilename;

      strsize pos = filename.find("_-_");
      //   print(" $filename");
      //print(" "pos=$pos"");

      string prefix1;
      string prefix2;
      string path;
      if(pos > 0 && pos < (filename.get_length() - 3))
      {
         prefix1 = filename.Mid(0, 1);
         prefix2 = filename.Mid(0, pos);
         prefix1.make_lower();
         prefix2.make_lower();
         path = basepath + prefix1 + "/" + prefix2 + "/" + filename;
         dprint("candidate="+path);
         if(Application.file().exists(path))
            return path;
      }

      strsize len;
      pos = filename.find("_");
      if(pos < 0)
         len = min(filename.get_length(), 3);
      else
         len = pos;


      string prefix;
      prefix = filename.Mid(0, len);
      prefix.make_lower();
      prefix = gen::str::pad(prefix, 3, "_", gen::str::pad_right);
      path = basepath+prefix[0]+"/"+prefix[1]+"/"+prefix[2]+"/"+filename;
      dprint("candidate=" + path);

      if(Application.file().exists(path))
         return path;

      path = basepath + filename;
      if(Application.file().exists(path))
         return path;


      return false;
   }

   string music::performer_implode1(var performernamea)
   {
      ::count count = performernamea.array_get_count();
      string ret;
      if(count == 0)
         ret = "";
      else if(count == 1)
         ret = performernamea.at(0);
      else if(count == 2)
         ret = performernamea.at(0) + m_performer_lastglue1 + performernamea.at(1);
      else
         ret = performernamea.stra().implode(m_performer_glue1, (index) 0, count - 1) + m_performer_lastglue1 + performernamea.stra().last_element();
      return ret;
   }



   var music::veriwellkaraoke_getperformerinfo(var performerid)
   {
      string sql = "SELECT performer.name FROM performer WHERE performer.id = "+performerid;
      var item = musicdb().query_item(sql);
      if(!item)
         return false;
      gen::property_set performerinfo(get_app());
      performerinfo["name"] = item;
      sql = "SELECT performer_url.url, performer_url.title FROM performer_url WHERE performer_url.performerid = "+performerid;
      var rowa = musicdb().query_rows(sql);
      var_array urlinfo;
      for(int i = 0; i < rowa.array_get_count(); i++)
      {
         var row = rowa.at(i);
         gen::property_set urlinfoitem(get_app());
         urlinfoitem["url"] = row[0];
         urlinfoitem["title"] = row[1];
         if(urlinfoitem["title"].is_empty())
         {
            urlinfoitem["title"] = urlinfoitem['url'];
         }
         urlinfo.add((var)urlinfoitem);
      }
      performerinfo["urlinfo"] = urlinfo;
      return performerinfo;
   }

   string music::music_performer_get_reg_exp(var varCode)
   {
      string code(varCode);
      if(code == "*")
      {
         return ".*";
      }
      else if(code == "0")
      {
         return "^[0-9]";
      }
      else if(code == "?")
      {
         return "^[^[:alpha:]]";
      }
      else
      {
         if(gen::str::begins_eat(code, "kp-"))
         {
            return "kp-^" + code;
         }
         else
         {
            return "^" + code;
         }
      }
   }

   string music::veriwell_getclassstring(var classid)
   {
      stringa classida;
      classida.explode(",", classid);
      stringa reta;
      for(int i = 0; i < classida.get_count(); i++)
      {
         reta.add(veriwell_getclassstring_item(classida[i]));
      }
      return reta.implode(", ");
   }

   string music::veriwell_getclassstring_item(var classid)
   {
      return musicdb().veriwell_getclassstring_item(classid);
   }

   string music::veriwell_getsongfileextension(var filename)
   {
      strsize len = strlen(filename);
      string type;
      if(len >= 4)
      {
         type = filename.get_string().Mid(len - 4, 4);
         if(type == ".kar")
         {
            type = ".kar";
         }
         else if(type == ".mid")
         {
            type = ".mid";
         }
         else if(type == ".st3")
         {
            type = ".st3";
         }
         else if(type == ".mk1")
         {
            type = ".mk1";
         }
         else
         {
            type = "----";
         }
      }
      else
      {
         type = "----";
      }
      return type;
   }

   string music::veriwell_map_song_file_extension_to_style(var type)
   {
      string style;
      if(type == ".kar")
      {
         style = "ikar";
      }
      else if(type == ".mid")
      {
         style = "imid";
      }
      else if(type == ".st3")
      {
         style = "ist3";
      }
      else if(type == ".mk1")
      {
         style = "imk1";
      }
      else
      {
         style = "iunkaudio";
      }
      return style;
   }


   var music::register_song_click(var songid, var address, var http_referer, var lang, var style, var referer, var type)
   {
      return musicdb().register_song_click(songid, address, http_referer, lang, style, referer, type);
   }

/*   function karaoke_update_tmp_song_clickdistinct1()
   {
      global $musicdb;
      return $musicdb->karaoke_update_tmp_song_clickdistinct1();
   }

   function karaoke_update_tmp_song_clickdistinct1_item($songid)
   {
      global $musicdb;
      $sql = "SELECT songid, COUNT(DISTINCT FLOOR(UNIX_TIMESTAMP(`datetime`) / 120), `address`) FROM song LEFT OUTER JOIN song_click ON song.id = song_click.songid WHERE song.id = '$songid' GROUP BY songid";
      $result = $musicdb->write_query($sql);
      if(($row = mysql_fetch_row($result)) != NULL)
      {
         $songid      = $row[0];
         $songclick   = $row[1];
         $sql = "UPDATE tmp_song SET clickdistinct1 = '$songclick' WHERE songid = '$songid'";
         $musicdb->write_query($sql);
      }
   }


   */

   var music::report_error(var error, bool bEmail)
   {
      //global $param_locale;
      //global $param_style;
      //global $musicdb;
      string referer = inattr("HTTP_REFERER");
      string ruri = inattr("HTTP_HOST") + inattr("REQUEST_URI");
      string sql = "INSERT INTO error(`insertiondatetime`, `message`) VALUES(NOW(), '"+error+")";
      dprint(sql);
      musicdb().query(sql);
      if(bEmail)
      {
         email email(get_app());

         string body;
         body = "";
         body += "Automatic Message from music_reportError Function object.\n";
         body += "\n";
         body += "base locale: "+gprop("g_base_param_locale")+", base style: "+gprop("g_base_param_style")+"\n";
         body += "locale: "+gprop("param_locale")+", style: "+gprop("param_style")+"\n";
         body += "referer: "+referer+"\n";
         body += "uri: "+ruri+"\n";
         body += "error:\n";
         body += error + ";\n";
         body += "\n";
         body += "END - :-)\n";
         email.m_strBody = body;
         email.m_strSubject = "[deepInternal] user - User Song Exception Report";
         email.m_addressSender = "veriwell@veriwell.net";
         email.m_addressRecipient = "interno@veriwell.net";
         System.email().utf8_mail(email);
         email.m_addressRecipient = "internal@veriwell.net";
         System.email().utf8_mail(email);
      }
      return true;
   }


   string music::song_get_content_type(var songid)
   {
      string type = song_get_file_type(songid);
      if(type == "Midi")
         return "audio/midi";
      else if(type == "SoftKaraoke")
         return "audio/midi";
      else if(type == "StarKorea3")
         return "application/x-st3";
      else if(type == "Microke1")
         return "application/x-mk1";
      return ::var(::var::e_type::type_null);
   }



   void music::veriwellkaraoke_printperformerurlinfo(var urlinfo)
   {
      for(int i = 0; i < urlinfo.get_count(); i++)
      {
         gen::property_set & urlinfoitem = urlinfo.at(i).propset();
         var link = urlinfoitem["url"];
         var text = urlinfoitem["title"];
         if(!text.is_set() || text == "")
         {
            text = link;
         }
         print(" <a class = 'performerurlinfo' href='"+ link+ "' target='_blank'>\n");
         print(text);
         print(" </a>\n");
      }
   }





   string music::sparam_url_encode(var var) // single/simple parameter/argument url encoding
   {
      string str;
      str = urlencode(var);
      str.replace(".", "%2E");
      return str;
   }

   string music::imgsrc(var id, var subtype)
   {
      string str = gprop("karaokeimgsrca")[(const char *) id];
      str.replace("%", subtype);
      return gprop("prefiximage") + str;
   }

   void music::register_get(gen::property_set & a)
   {
      for(int i = 0; i < a.m_propertya.get_count(); i++)
      {
         gprop("param_" + a.m_propertya[i].name()) = a.m_propertya[i].get_value();
      }
   }

   void music::register_post(gen::property_set & a)
   {
      for(int i = 0; i < a.m_propertya.get_count(); i++)
      {
         gprop("param_" + a.m_propertya[i].name()) = a.m_propertya[i].get_value();
      }
   }

   void music::register_request(gen::property_set & a)
   {
      for(int i = 0; i < a.m_propertya.get_count(); i++)
      {
         gprop("param_" + a.m_propertya[i].name()) = a.m_propertya[i].get_value();
      }
   }

   string music::js_langstr(var id, var value)
   {
      return "\"" + langstr(id) + "\"";
   }

   void music::js_tr_mdwn_parama(var tr_mdwn_parama)
   {

      if(!gprop("tr_mdwn_parama_endtable").is_set())
         gprop("tr_mdwn_parama_endtable") = 0;
      else
         gprop("tr_mdwn_parama_endtable")++;

      print("<script>\n");
      print("<!--\n");
      for(int i = 0; i < tr_mdwn_parama.propset().m_propertya.get_count(); i++)
      {
         print("gtra[" + tr_mdwn_parama.propset().m_propertya[i].name() + "]= \""+
            tr_mdwn_parama.propset().m_propertya[i].get_value().get_string()+"\";\n");
      }
      print(" //-->\n");
      print(" </script>");
   }

   string music::karaoke_to_song_info_topictype(var topictype)
   {
      if(topictype == 0)
      {
         return "karaoke";
      }
      else if(topictype == 1 || topictype == 1001)
      {
         return "lyrics";
      }
      else if(topictype == 2)
      {
         return "chords";
      }
      else
      {
         return "unknown";
      }
   }

   string music::karaoke_nfy_count(var n)
   {
      if(n == 0)
         return "0";
      else if(n == 1)
         return "1";
      else if(n > 1)
         return "n";
      return "";
   }

/*
   function get_simage_path($visual)
   {
      global $g_langdir_modifier;
      global $param_style;

      $accept = array();


      $accept['performerico16.gif']             = "p1n";
      $accept['songico16.gif']                   = "s1n";
      $accept['list.download.btn.normal.gif']    = "sd1n";
      $accept['list.download.btn.hover.gif']    = "sd1h";
      $accept['list.download.btn.press.gif']    = "sd1p";
      $accept['list.play.btn.normal.gif']       = "sp1n";
      $accept['list.play.btn.hover.gif']          = "sp1h";
      $accept['list.play.btn.press.gif']          = "sp1p";

      // LYRICS Lyrics lyrics
      $accept['list.lyrics.btn.normal.gif']       = "sl1n";
      $accept['list.lyrics.btn.hover.gif']       = "sl1h";
      $accept['list.lyrics.btn.disable.gif']    = "sl1d";
      $accept['list.lyrics.btn.press.gif']       = "sl1p";

      // CHORD Chord chord
      $accept['list.chord.btn.normal.gif']       = "sc1n";
      $accept['list.chord.btn.press.gif']       = "sc1p";
      $accept['list.chord.btn.disable.gif']       = "sc1d";
      $accept['list.chord.btn.hover.gif']       = "sc1h";

      // INFO Info info
      $accept['list.info.btn.normal.gif']       = "si1n";
      $accept['list.info.btn.hover.gif']          = "si1h";

      // FUN Fun fun
      $accept['list.fun.btn.normal.png']          = "f1n";
      $accept['list.fun.btn.press.png']          = "f1p";
      $accept['list.fun.btn.unpress.png']       = "f1u";
      $accept['list.fun.btn.hover.png']          = "f1h";

      $accept['icon.16.report.exception.normal.png']       = "se1n";
      $accept['icon.16.report.exception.hover.png']       = "se1h";

      $accept['veriwell.topbar.png']             = "topbar1";
      $accept['title.png']                      = "title1";
      $accept['sing.veriwell.logo.png']          = "logo1";
      $accept['sing.veriwell.slogo.png']          = "slogo1";
      $accept['listheader1.png']                   = "listhd1";

      $accept['sorry404.png']                      = "sorry404";

      $accept['ext.kar.png']                      = "ext_kar";
      $accept['ext.mid.png']                      = "ext_mid";
      $accept['ext.st3.png']                      = "ext_st3";
      $accept['ext.mk1.png']                      = "ext_mk1";

      $accept['net/logo.png']                      = "net/logo";

      $title = array_search($visual, $accept);
      if(!isset($visual) || $title === FALSE)
         return FALSE;
      $base_url = "http://image.veriwell.net/";
      $path = util_file_realpath("image/karaoke/{$g_langdir_modifier}{$title}");
      if(!is_empty($path))
      {
         return $base_url."image/karaoke/{$g_langdir_modifier}{$title}";
      }
      $path = util_file_realpath("image/karaoke/{$param_style}/{$title}");
      if(!is_empty($path))
      {
         return $base_url."image/karaoke/{$param_style}/{$title}";
      }
      $path = util_file_realpath("image/karaoke/{$title}");
      if(!is_empty($path))
      {
         return $base_url."image/karaoke/{$title}";
      }
      $path = util_file_realpath("image/{$g_langdir_modifier}{$title}");
      if(!is_empty($path))
      {
         return $base_url."image/{$g_langdir_modifier}{$title}";
      }
      $path = util_file_realpath("image/$title");
      if(!is_empty($path))
      {
         return $base_url."image/$title";
      }
      return FALSE;
   }
*/
/*
   function karaoke_get_performer_list_2()
   {
      global $musicdb;
      $sql = "SELECT DISTINCT person.id, IFNULL(person.latin_name, person.name), IFNULL(person.latin_name, person.name) FROM person INNER JOIN person_role ON person_role.person = person.id AND person_role.role = 2 ORDER BY IFNULL(person.latin_name, person.name)";
      $rowa =   $musicdb->query_rows($sql);
      $count = count($rowa);
      $last_first_letter = '';
      $last_second_letter = '';
      $second_letter_count = 0;
      for($i = 0; $i < $count; $i++)
      {
         $name = $rowa[$i][2];
         if($last_first_letter != substr($name, 0, 1))
         {
            $last_first_letter = substr($name, 0, 1);
            $last_second_letter = substr($name, 1, 1);
            $second_letter_count = 1;
            $rowa[$i][] = substr($name, 0, 1);
            $rowa[$i][] = substr($name, 0, 2);
         }
         else if($last_second_letter != substr($name, 1, 1))
         {
            $last_second_letter = substr($name, 1, 1);
            $second_letter_count = 1;
         }
         else
         {
            $second_letter_count++;
         }
         if($second_letter_count == 5)
         {
            $rowa[$i - $second_letter_count + 1][] = '';
            $rowa[$i - $second_letter_count + 1][] = substr($name, 0, 2);
         }
      }

      return $rowa;
   }

   function karaoke_print_pick_artist($rowa, $var_src, $var_dest, $return_link)
   {
      ?>

         <table border="0" style="font-size: 9pt;">
         <tbody><tr>
         <td width="13%">                             </td>
         <td width="13%">                             </td>
         <td width="13%">                             </td>
         <td width="13%">                             </td>
         <td width="13%">                             </td>
         <td width="13%">                             </td>
         <td width="13%">                             </td>
         </tr><tr>
         <td valign="top">

         <?php

         $count = count($rowa);
      $part_count = ceil($count / 7.0);
      $count1 = $part_count;
      $count2 = $part_count * 2;
      $count3 = $part_count * 3;
      $count4 = $part_count * 4;
      $count5 = $part_count * 5;
      $count6 = $part_count * 6;

      $i= 0;
      foreach($rowa as $row)
      {
         $w = count($row);
         if($i == $count1 || $i == $count2 || $i == $count3 || $i == $count4 || $i == $count5 || $i == $count6)
         {
            print(" "</td>"");
            print(" "<td valign=\"top\">"");
         }
         $aida2 = $GLOBALS[$var_src];
         $aida2[] = $row[0];
         $GLOBALS[$var_dest] = implode(",", $aida2);
         if($w > 3)
         {
            if(!is_empty($row[3]))
            {
               print(" "<h2 style=\"margin-bottom: 0px;\">"");
                  print(" $row[3]");
               print(" "</h2>"");
               $prev_head = true;
            }
            else
            {
               $prev_head = false;
            }
            if($w > 4)
            {
               if($prev_head)
               {
                  print(" "<h3 style=\"margin-bottom: 0px; margin-top: 0px;\">"");
               }
               else
               {
                  print(" "<h3 style=\"margin-bottom: 0px;\">"");
               }
               print(" $row[4]");
               print(" "</h3>"");
            }
         }
         print(" eval("return $return_link;")");
         print(" $row[1]");
         print(" "</a>"");
         print(" "<br>"");
         $i++;
      }
      ?>
         </td></tr></tbody>
         </table>
         <?php
   }
*/
void music::echo_mb_music_top_image_url()
   {
      print(mb_music_top_image_url());
   }

string music::mb_music_top_image_url()
{
   if(gprop("param_root") == "karaoke")
   {
      if(gprop("param_style") == "mb")
      {
         return "/krftimg?mb=cantar.";
      }
      else if(gprop("param_style") == "mbpara")
      {
         return "/krftimg?mb=cante.";
      }
   }
   else if(gprop("param_root") == "letras")
   {
      if(gprop("param_style") == "mb")
      {
         return "/krftimg?mb=curtir.letras.";
      }
      else if(gprop("param_style") == "mbpara")
      {
         return "/krftimg?mb=curta.letras.";
      }
   }
   else if(gprop("param_root") == "cifras")
   {
      if(gprop("param_style") == "mb")
      {
         return "/krftimg?mb=tocar.musica.";
      }
      else if(gprop("param_style") == "mbpara")
      {
         return "/krftimg?mb=toque.musica.";
      }
   }
   return "";
}

string music::karaoke_getFwdParamLang()
   {

      return gprop("forward_param_lang");
   }

string music::karaoke_getFwdParamStyle()
   {
      return gprop("forward_param_style");
   }


   var music::song_get_song_type_image1(var type)
   {
      if(type == "SoftKaraoke")
      {
         return song_get_song_extension_url("kar");
      }
      else if(type == "Midi")
      {
         return song_get_song_extension_url("mid");
      }
      else if(type == "StarKorea3")
      {
         return song_get_song_extension_url("st3");
      }
      else if(type == "Microke1")
      {
         return song_get_song_extension_url("mk1");
      }
      else
      {
         return "";
      }
   }

   var music::song_get_song_extension_url(var extension)
   {
      return simage("ext_" + extension);
   }



   void music::printListClassInclude(var cid)
   {
      dprint("cid on music::printListClassInclude=$cid");
      stringa cida;
      cida.explode(",", cid);
      if(cida.contains("30321"))
      {
         printListCategoryInclude("mpb");
      }
   }
   void music::printListCategoryInclude(var category)
   {
      if(category.get_string().has_char())
      {
         string path = sys_get_include_path("ds", "partial", category);
         include(path);
      }
   }

   void music::printListArtistInclude(var aid)
   {
      dprint("aid on music::printListArtistInclude=$aid");
      stringa aida;
      aida.explode(",", aid);
      for(int i = 0; i < aida.get_count(); i++)
      {
         string strInclude = "";
         int aid = atoi(aida[i]);
         if(aid == 7)
         {
            strInclude = "djavan";
         }

         if(strInclude.has_char())
         {
            var path = sys_get_include_path("ds", "partial", strInclude);
            if(path.get_string().has_char())
            {
               include(path);
               continue;
            }
         }
         var path = sys_get_include_path("ds", "partial/artist", gen::str::itoa(aid));
         if(path.get_string().has_char())
         {
            include(path);
            continue;
         }
         path = sys_get_include_path("ds", "partial/artist", "_std");
         if(path.get_string().has_char())
         {
            include(path);
            continue;
         }
      }

   }

   void music::printListArtistSmallInclude(var aid)
   {
      dprint("aid on music::printListArtistSmallInclude=$aid");
      stringa aida;
      aida.explode(",", aid);
      for(int i = 0; i < aida.get_count(); i++)
      {
         string strInclude = "";
         string aid = aida[i];
         var path = sys_get_include_path("ds", "partial/artist_small", aid);
         if(path.get_string().has_char())
         {
            include(path);
            continue;
         }
         path = sys_get_include_path("ds", "partial/artist_small", "_std");
         if(path.get_string().has_char())
         {
            include(path);
            continue;
         }
      }

   }

   void music::print_lang_combo1(const char * pszLocale, const char * pszStyle)
   {
      UNREFERENCED_PARAMETER(pszLocale);
      UNREFERENCED_PARAMETER(pszStyle);
   }

   var music::file_get_kar_file_id(var filename)
   {
      string sql = "SELECT id FROM karfile WHERE filename = '"+filename+"'";
      return musicdb().query_item(sql);
   }

   var music::file_get_kar_file_name(var id)
   {
      string sql = "SELECT filename FROM karfile WHERE id = '"+id+"'";
      return musicdb().query_item(sql);
   }
   var music::file_get_file(var filename, ::webserver::music::song ** ppsong)
   {
      var karfileid = file_get_kar_file_id(filename);
      return file_get_file_by_kar_file_id(karfileid, ppsong);
   }

   var music::file_get_file_by_kar_file_id(var karfileid, ::webserver::music::song ** ppsong)
   {
      dprint("karfileid=" + karfileid);
      ::webserver::music::song * psong = musicdb().get_kar_file_song(karfileid);
      if(ppsong != NULL)
      {
         *ppsong = psong;
      }
      if(psong == NULL)
      {
         print("Sorry! This song does not exist. mailto:camilo@veriwell.net");
         return false;
      }

      var filename       = psong->m_propertyset["filename"];
      //var filepath       = psong->get_file_path();
      var contenttype    = psong->get_content_type();

      var filepath      = psong->get_gz_file_path();

      if(Application.file().exists(filepath))
      {
         dprint("filepath=" + filepath);
         dprint("contenttype=" + contenttype);
         return filepath;
      }
      else
      {
         return false;
      }
   }
   var music::file_test_file(var filename, ::webserver::music::song ** ppsong)
   {
      var filepath = file_get_file(filename, ppsong);
      if(strlen(filepath) > 0)
      {
         return true;
      }
      return false;
   }

   } // namespace music

} // namespace webserver

