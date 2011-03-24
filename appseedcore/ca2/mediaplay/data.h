#pragma once

#include "mus/MidiDocHelper.h"

class ::userbase::document;
class PlaylistDoc;
class CVmpLightSrvrItem;

namespace mediaplay
{

   class document;

   class CLASS_DECL_ca data :
      virtual public ikar::data_container,
      virtual public MidiDocHelper
   {
   public:


      enum EMode
      {
         ModeNone,
         ModeMidi,
         ModeWave,
      };

      enum e_type
      {
         TypeUnknown,
         TypeAiff,
         TypeCda,
         TypeMpeg,
         TypeTwinVQ,
         TypeWm,
         TypeWav,
         TypeZip,
         TypeRtp,
      };

      gen::memory_file                m_memfile;
      ex1::filesp                m_fileWave;
      EMode                      m_emode;
      e_type                     m_etype;
      string                     m_strPathName;
      bool                       m_bWrite;   
      bool                       m_bPlay;
      document *                 m_pdocument;
      ::mediaplay::karaoke       m_karaokeinterface;


   public:
      data(document * pdocument);
      virtual ~data();


      virtual ::radix::thread * HelperGetMidiPlayerCallbackThread();
      virtual BOOL on_new_document();
      virtual bool on_open_document(var varFile);
      virtual void delete_contents();
      BOOL OnOpenZipFile(const char * lpszPathName);
      bool is_writing();
      string GetAnimatedTitle();
      ex1::filesp & GetWaveFile();
      ::userbase::document * get_document();
      string get_path_name();
      EMode DetermineMode(e_type e_type);
      e_type get_type();

      e_type DetermineFileType(var varFile);
      void AttachPlaylist(PlaylistDoc * pdoc);
      EMode GetMode();
      afx_msg BOOL OpenFile(const char * bstrFilePath, BOOL bMakeVisible);

      virtual void on_http_request_response(gen::signal_object * pobj);

   };

} // namespace mediaplay
