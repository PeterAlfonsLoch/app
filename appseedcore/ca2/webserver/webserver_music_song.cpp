#include "StdAfx.h"


namespace webserver
{


   namespace music
   {


      song::song()
      {
         m_propertyset["pperformera"].vara(); // instantiate variable array
      }

      song::~song()
      {
      }

      var song::calc_file_type()
      {
         var strExtension = System.file().extension(m_propertyset["filename"]).make_lower();
         if(strExtension == "mid")
            return "Midi";
         else if(strExtension == "kar")
            return "SoftKaraoke";
         else if(strExtension == "st3")
            return "StarKorea3";
         else if(strExtension == "mk1")
            return "Microke1";
         else if(strExtension == "mp3")
            return "Mpeg3";
         else
            return "";
      }

      var song::calc_content_type()
      {
         var strType = calc_file_type();
         if(strType == "Midi")
            return "audio/midi";
         else if(strType == "SoftKaraoke")
            return "audio/midi";
         else if(strType == "StarKorea3")
            return "application/x-st3";
         else if(strType == "Microke1")
            return "application/x-mk1";
         else if(strType == "Mpeg")
            return "audio/mpeg";
         else
            return "application/x-download";

      }

      /*   void song::calc_file_array()
      {
      m_filea = musicdb().get_song_files(m_id);
      }
      */

      var song::get_content_type()
      {
         return calc_content_type();
      }

      var song::get_performera_html_link(var css_class)
      {
         var_array performerlinka;
         for(int i = 0; i < m_propertyset["pperformera"].array_get_count(); i++)
         {
            performerlinka.add(m_propertyset["pperformera"].at(i).ca2 < ::webserver::music::person > ()->get_html_link(css_class));
         }
         return performerlinka;
      }

      var song::get_performera_html_link1(var css_class)
      {
         return music().performer_implode1(get_performera_html_link(css_class));
      }

      var song::get_performer_namea()
      {
         stringa performernamea;
         for(int i = 0; i < m_propertyset["pperformera"].array_get_count(); i++)
         {
            performernamea.add((const char *) m_propertyset["pperformera"].at(i).ca2 < ::webserver::music::person > ()->m_propertyset["name"]);
         }
         return performernamea;
      }

      var song::get_performer_ida()
      {
         stringa performerida;
         for(int i = 0; i < m_propertyset["pperformera"].array_get_count(); i++)
         {
            performerida.add((const char *) m_propertyset["pperformera"].at(i).ca2 < ::webserver::music::person > ()->m_propertyset["id"]);
         }
         return performerida;
      }

      var song::get_performer_id_list()
      {
         return implode(",", get_performer_ida());
      }

      var song::get_performers1()
      {
         return music().performer_implode1(get_performer_namea());
      }

      var song::get_file_path()
      {
         return music().song_resolve_file_name(m_propertyset["filename"]);
      }

      var song::get_gz_file_path()
      {
         var path = music().song_resolve_gz_file_name(m_propertyset["filename"]);
         if(path.has_char())
            return path;
         string strSql;
         strSql.Format("SELECT filename, nessie, `key`, `size`, mimetype, extension FROM karfile WHERE id = %I64d", (__int64) m_propertyset["topic"]);
         var row = musicdb().query_row(strSql);
         if(!row.is_empty())
         {
            path = low_fs_file_path(row.at(1), row.at(2), row.at(3), row.at(4), row.at(5));
            if(System.file().exists(path))
               return path;
         }

         return false;

      }


   } // namespace netnode



} // namespace webserver


