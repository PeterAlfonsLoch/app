//#include "framework.h"

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


//#include <sapi.h>               // SAPI

// Declare local identifiers:

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Media::SpeechSynthesis;


namespace metrowin
{


   namespace tts
   {


      //------------------------------------------------------------------------
      // Simple class to speak some text (using SAPI).
      //------------------------------------------------------------------------

      speaker::speaker(::aura::application * papp):
         object(papp),
         ::tts::speaker(papp)
      {
      }


      speaker::~speaker()
      {

      }

      //--------------------------------------------------------------------
      // Initializes the text speaker.
      //--------------------------------------------------------------------
      bool speaker::initialize(string strLang)
      {

         finalize(strLang);

         //
         // Create text to speech engine
         //
         Windows::Media::SpeechSynthesis::SpeechSynthesizer ^ psynth = ref new Windows::Media::SpeechSynthesis::SpeechSynthesizer();
         if (psynth == nullptr)
         {

            return false;

         }

         m_synth[strLang] =  psynth;

         if(strLang.is_empty())
         {

            strLang = "en";

         }
         // get all of the installed voices
         IVectorView<VoiceInformation ^> ^voices = Windows::Media::SpeechSynthesis::SpeechSynthesizer::AllVoices;

         for (unsigned int index = 0; index < voices->Size; index++)
         {
            // create a combo box item, and copy the voice data into that
            VoiceInformation ^voice = voices->GetAt(index);
            string strL = voice->Language;
            if (::str::begins_ci(strL, strLang))
            {
               try
               {
                  psynth->Voice = voice;
                  return true;
               }
               catch(...)
               {

               }
               
            }

         }


         return false;

      }
      bool speaker::initialize_translator(string strLang)
      {

         return false;
      
      }

      bool speaker::finalize(string strLang)
      {

         if(m_synth[strLang] != nullptr)
         {

//            m_synth[strLang]->();

         }

         m_synth[strLang] = nullptr;



         return true;
      }
      bool speaker::finalize_translator(string strLang)
      {

         return false;

      }


      //--------------------------------------------------------------------
      // Speaks some text.
      // (The input text must not be empty.)
      //--------------------------------------------------------------------
      bool speaker::speak(const string & text)
      {

         return speak("",text);

      }


      //--------------------------------------------------------------------
      // Speaks some text.
      // (The input text must not be empty.)
      //--------------------------------------------------------------------
      bool speaker::speak(const string & strLang, const string & text, bool bSync)
      {
         
         //
         // Input text must not be empty
         //
         if(text.is_empty())
         {

            // nothing to speak?!?!
            return false;

         }

         bool bTts = false;

         //if((!m_tts.Lookup(strLang, bTts) || bTts) && m_voice[strLang].is_set() || (!is_speaking(strLang) && get_tick_count() - m_time[strLang] > 30 * 1000))
         if (!m_tts.Lookup(strLang, bTts))
         {

            if (initialize(strLang))
            {
               
               m_tts[strLang] = true;

            }
            else
            {

               m_tts[strLang] = false;

               if (!initialize_translator(strLang))
               {

                  return false;

               }

            }

         }


         wstring wstr(text);

         if(bSync)
         { 

            ::wait_then(GetSpeechStreamTask(strLang, wstr), [=](SpeechSynthesisStream ^speechStream)
            {

               sp(::memory_file) memfile;

               memfile = canew(::memory_file(get_app()));

               memory_size_t s = (memory_size_t)speechStream->Size;

               Windows::Storage::Streams::Buffer ^ buffer = ref new Windows::Storage::Streams::Buffer(s);

               if (buffer == nullptr)
                  return;

               ::wait(speechStream->ReadAsync(buffer, s, ::Windows::Storage::Streams::InputStreamOptions::ReadAhead));

               string strContentType = speechStream->ContentType;

               memfile->get_primitive_memory()->set_os_buffer(buffer);

               memfile->seek_to_begin();

               Application.play_audio(memfile, true);

            });

         }
         else
         {

            ::fork_then(get_app(), GetSpeechStreamTask(strLang, wstr), [=](SpeechSynthesisStream ^speechStream)
            {

               sp(::memory_file) memfile;

               memfile = canew(::memory_file(get_app()));

               memory_size_t s = (memory_size_t)speechStream->Size;

               Windows::Storage::Streams::Buffer ^ buffer = ref new Windows::Storage::Streams::Buffer(s);

               if (buffer == nullptr)
                  return;

               ::wait(speechStream->ReadAsync(buffer, s, ::Windows::Storage::Streams::InputStreamOptions::ReadAhead));
 
               string strContentType = speechStream->ContentType;

               memfile->get_primitive_memory()->set_os_buffer(buffer);

               memfile->seek_to_begin();

               Application.play_audio(memfile, true);

            });

         }

         return true;

      }


      bool speaker::is_speaking(string strLang)
      {
         return false;
         //if(m_synth[strLang].is_null())
         //{

         //   return false;

         //}

         //SPVOICESTATUS status ={};

         //HRESULT hr = m_voice[strLang]->GetStatus(&status,NULL);

         //if(FAILED(hr))
         //{

         //   return false;

         //}

         //return (status.dwRunningState & SPRS_IS_SPEAKING) != FALSE;

      }


      bool speaker::stop(string strLang)
      {

         if (m_tts[strLang])
         {
            
            finalize(strLang);

         }
         else
         {

            finalize_translator(strLang);

         }

         return true;

      }

      //actual creation of the stream using the new voice synthesis stream
      IAsyncOperation < SpeechSynthesisStream^ > ^ speaker::GetSpeechStreamTask(string strLang, string text)
      {
         return m_synth[strLang]->SynthesizeTextToStreamAsync(text);
      }
   } // namespace tts


} // namespace metrowin










