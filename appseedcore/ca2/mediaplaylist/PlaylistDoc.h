#pragma once

#include "user/user_document_interface.h"
#include "imedia/imedia.h"

class CPlaylistView;
class PlaylistDoc;

class CLASS_DECL_ca playlist_info
{
public:

   playlist_info();
   virtual ~playlist_info();

   PlaylistDoc *                          m_pdoc;
   string                                 m_strFilePath;
   int                                    m_iCurrentSong;
   mediaplaylist::ESetCurrentSongHint     m_ehint;
   bool                                   m_bMakeVisible;
   imedia::position                       m_position;
   bool                                   m_bUser;

};


class CLASS_DECL_ca PlaylistDoc :
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


   gen::property_set                m_setFile;
   stringa                          m_wstraSong;
   int_array                        m_iaQueue;
   int                              m_iCurrentSong;
   bool                             m_bLoop;
   bool                             m_bShuffle;
   ph(PlaylistCallbackInterface)    m_xpcallback;

   static const LPARAM LHINT_FRAMEDOWN;
   static const LPARAM LHINT_FRAMEUP;


   PlaylistDoc(::ca::application * papp);



    

   void PopViews();


   virtual void restart(bool bUser);

   virtual void populate_queue(int iSong);
    
   //bool PeekSongPath(string & strPath, int iOffset, bool bLoop);

   virtual void on_final_release();
   virtual bool on_open_document(var varFile);
   virtual void on_close_document();
   virtual BOOL on_new_document();
   virtual BOOL save_modified();

   void SetCallback(PlaylistCallbackInterface * pcallback);
   ::userbase::view * GetFirstAttachableView();
   bool IsDefaultPath();
   bool IsDefaultPath(const char * lpcsz);
   
   void OnRemoveSong(::userbase::view * pview = NULL);
   bool IsDefaultPlaylist();
   void DoDefaultPlaylistSave();
   void OnChangeSongs(::userbase::view * pview = NULL);
   void OnAddSong();
   int GetSongCount();
   int GetCurrentSong();
   
   bool get_song_at(string & str, int iSong);
   bool pick_a_song(int & iSong, string & str);

   bool play(playlist_info * pinfo);

   bool RemoveSong(int iSong, ::userbase::view * pview = NULL);
   bool get_songs(stringa & stra);
   bool get_song_current_queue(stringa & stra);
   virtual void update_title();
   
   
   VMSRESULT AddSong(stringa & stra, bool bDoPlay, bool bMakeVisible);
   VMSRESULT AddSong(LPINT lpiaSongs, int iSongCount, bool bDoPlay, bool bMakeVisible);
   
   bool AddSong(var varFile, EAddSong eaddsong, bool bMakeVisible, bool bUpdateAllViews);
   VMSRESULT AddSong(int iSongCode, bool bDoPlay, bool bMakeVisible, bool bUpdateAllViews);


   bool has_next_song();
   
   virtual ~PlaylistDoc();
#ifdef _DEBUG
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif

   afx_msg void OnPlay();

   virtual void write(ex1::output_stream & ostream);
   virtual void read(ex1::input_stream & istream);

};
