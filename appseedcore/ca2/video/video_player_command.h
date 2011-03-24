#pragma once

#include "video_command.h"

namespace video
{

   class CLASS_DECL_ca player_command
   {
   protected:
      e_command      m_ecommand;
      ex1::file *    m_pfileOpen;
      base_array < CEvent *, CEvent * > m_evptra;
   public:
      bool       m_bResult;
      bool *     m_pbResult;
      void SetEvents();
      void AttachEvent(CEvent * pevent);
      player_command();
      player_command(const player_command & command);
      player_command & operator =(const player_command & command);
      void OpenFile(ex1::file * pfile);
      void Play();
      void Stop();
      void SetOpenFile(ex1::file * pfile);
      ex1::file * GetOpenFile() const;
      void SetCommand(e_command ecommand);
      e_command GetCommand() const;
   };

} // namespace video