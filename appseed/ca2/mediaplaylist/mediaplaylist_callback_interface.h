#pragma once


namespace mediaplaylist
{


   class document;
   class info;


   class CLASS_DECL_ca callback_interface : 
      virtual public ::radix::object
   {
   public:


      document *                    m_pplaylistdoc;



      callback_interface();
      virtual ~callback_interface();

      virtual void OnClosePlayer();

      virtual bool DoesImplementSongNumber();
      virtual int GetSongNumber(const wchar_t * lpcwsz);

      virtual void PlaylistOnBeforeOpen();

      virtual void PlaylistOnPlaybackEnd();

      void PlaylistPlay(int iOffset);
      virtual e_play PlaylistPlay(info * pinfo);

      virtual bool is_playing();
   };


} // namespace mediaplaylist



