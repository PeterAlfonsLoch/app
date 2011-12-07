#pragma once


namespace webserver
{


   namespace music
   {


      class CLASS_DECL_ca song :
         public dynamic_source::object < song, dynamic_source::object_base >
      {
      public:

         /*var m_fileid;
         var m_id;
         person_ptr_array * m_pperformera; // performer object base_array
         var m_performers;
         var m_performerida;
         var m_performerids;
         var m_click;
         var m_type;
         var m_contenttype;
         var m_filename;
         var m_title;
         var m_chordcount;
         var m_lyricscount;
         var m_isfun;
         var m_accessdatetime;
         var m_accesslang;
         var m_accessstyle;
         var m_rank;
         var m_karaokecount; // karaoke file count
         var m_topic;
         var m_topictype;
         var m_lyricscomment;
         var m_insertiondatetime;
         var m_insertionuserid;
         var m_insertionsourceid;
         var m_insertercomment;
         var m_insertionsourcecomment;
         var m_chordcomment;
         var m_translation_language;
         var m_classida;
         var m_lyrics;
         var m_releaseyear;*/

         song();
         virtual ~song();

         var calc_file_type();

         var calc_content_type();

         //void calc_file_array();
      
         var get_content_type();
      
         var get_performera_html_link(var css_class);

         var get_performera_html_link1(var css_class);
      
         var get_performer_namea();

         var get_performer_ida();

         var get_performer_id_list();
      
         var get_performers1();
      
         var get_file_path();
      
         var get_gz_file_path();


      };


      typedef dynamic_source::ptr_array < song > song_ptr_array;


   } // namespace music


} // namespace webserver

