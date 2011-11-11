#pragma once


#include "user/user_document_interface.h"
#include "imedia/imedia.h"


namespace mediaplaylist
{

   class view;
   class document;

   class CLASS_DECL_ca info
   {
   public:

      info();
      virtual ~info();

      document *                             m_pdocument;
      string                                 m_strFilePath;
      int                                    m_iCurrentSong;
      e_hint                                 m_ehint;
      bool                                   m_bMakeVisible;
      imedia::position                       m_position;
      bool                                   m_bUser;

   };


   class CLASS_DECL_ca document :
      public ::userbase::document,
      public user::document_interface,
      public imediamanager::playlist_interface
   {
   public:

      enum EAddSong
      {
         AddSongOnly,
         AddSongAndPlay,
         AddSongAndPlayIfNotPlaying,
      };

      xml::node                        m_xmlnode;
      gen::property_set                m_setFile;
      xml::node *                      m_pnodePlaylist;
      xml::node *                      m_pnodeCurrent;
      int_array                        m_iaQueue;
      int                              m_iCurrentSong;
      ph(callback_interface)           m_xpcallback;

      // pre calculated values
      int                              m_iCurrentPlaylistSongCount;
      stringa                          m_straQueue;

      static const                     LPARAM LHINT_FRAMEDOWN;
      static const                     LPARAM LHINT_FRAMEUP;


      document(::ca::application * papp);
      virtual ~document();



      void set_current_playlist(const char * pszPath);
      string get_current_playlist_path();
      string get_default_playlist_path();


      virtual void ensure_playlist();



      void PopViews();


      virtual void restart(bool bUser);

      virtual void populate_queue(int iSong);

      //bool PeekSongPath(string & strPath, int iOffset, bool bLoop);

      virtual void on_final_release();
      virtual bool on_open_document(var varFile);
      virtual void on_close_document();
      virtual BOOL on_new_document();
      virtual BOOL save_modified();

      void SetCallback(callback_interface * pcallback);
      ::userbase::view * GetFirstAttachableView();
      bool IsDefaultPath();
      bool IsDefaultPath(const char * lpcsz);

      void OnRemoveSong(::userbase::view * pview = NULL);
      bool IsDefaultPlaylist();
      void DoDefaultPlaylistSave();
      void OnChangeSongs(::userbase::view * pview = NULL);
      void OnAddSong();
      int get_song_count();
      int get_current_song();

      bool get_song_at(string & str, int iSong);
      bool pick_a_song(int & iSong, string & str);

      bool play(info * pinfo);

      bool RemoveSong(int iSong, ::userbase::view * pview = NULL);
      bool get_songs(stringa & stra);
      bool get_song_current_queue(stringa & stra);
      virtual void update_title();


      VMSRESULT AddSong(stringa & stra, bool bDoPlay, bool bMakeVisible);
      VMSRESULT AddSong(LPINT lpiaSongs, int iSongCount, bool bDoPlay, bool bMakeVisible);

      bool AddSong(var varFile, EAddSong eaddsong, bool bMakeVisible, bool bUpdateAllViews);
      VMSRESULT AddSong(int iSongCode, bool bDoPlay, bool bMakeVisible, bool bUpdateAllViews);


      bool has_next_song();

#ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
#endif

      void OnPlay();

      virtual void write(ex1::byte_output_stream & ostream);
      virtual void read(ex1::byte_input_stream & istream);


      int get_current_playlist_song_count();
      int get_current_queue_song_count();



      //gen::property_set                m_setFile;
      //stringa                          m_wstraSong;
      //int_array                        m_iaQueue;
      //int                              m_iCurrentSong;
      //bool                             m_bLoop;
      //bool                             m_bShuffle;
      void set_flag(const char * psz, bool bFlag);
      bool get_flag(const char * psz, bool bDefault);
      void set_int(const char * psz, int iValue);
      int get_int(const char * psz, int iDefault);
      void set_string(const char * psz, const char * pszValue);
      string get_string(const char * psz, const char * pszValue);


      bool is_recursive();
      bool is_loop();
      bool is_shuffle();


   };



} // namespace mediaplaylist

