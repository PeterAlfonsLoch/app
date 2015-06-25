#pragma once

//////////////////////////////////////////////////////////////////////////
//
// FILE: TextSpeaker.h
//
// Defines a simple C++ class to speak some text.
//
// by Giovanni Dicanio <gdicanio@mvps.org>
//
// 2010, December 28th
//
//////////////////////////////////////////////////////////////////////////


#include <sapi.h>        // SAPI (for windows::tts::speaker)


namespace windows
{


   namespace tts
   {


      //------------------------------------------------------------------------
      // Simple class to speak some text (using SAPI).
      //------------------------------------------------------------------------
      class speaker:
         virtual public ::tts::speaker
      {
      public:


         ::windows::comptr < ISpVoice >            m_pvoice;
         ::windows::comptr < ISpObjectToken >      m_ptoken;

         //--------------------------------------------------------------------
         // Initializes the text speaker.
         //--------------------------------------------------------------------
         speaker(::aura::application * papp);
         virtual ~speaker();

         virtual bool initialize();
         virtual bool finalize();

         //--------------------------------------------------------------------
         // Speaks some text.
         // (The input text must not be empty.)
         //--------------------------------------------------------------------
         virtual bool speak(const string & text) override;

         virtual bool is_speaking() override;

         virtual bool stop() override;


      };



   } // namespace tts

} // namespace windows




