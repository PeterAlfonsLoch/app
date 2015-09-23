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


inline HRESULT SpGetCategoryFromId(const WCHAR * pszCategoryId,ISpObjectTokenCategory ** ppCategory,BOOL fCreateIfNotExist = FALSE)
{
   HRESULT hr;

   ::windows::comptr < ISpObjectTokenCategory > pcategory;
   hr = pcategory.CoCreateInstance(CLSID_SpObjectTokenCategory);

   if(SUCCEEDED(hr))
   {
      hr = pcategory->SetId(pszCategoryId,fCreateIfNotExist);
   }

   if(SUCCEEDED(hr))
   {
      *ppCategory = pcategory.detach();
   }

   return hr;
}

inline HRESULT SpGetTokenFromId(const WCHAR * pszTokenId,ISpObjectToken ** ppToken,BOOL fCreateIfNotExist = FALSE)
{
   HRESULT hr;

   ::windows::comptr < ISpObjectToken > ptoken;
   hr = ptoken.CoCreateInstance(CLSID_SpObjectToken);

   if(SUCCEEDED(hr))
   {
      hr = ptoken->SetId(NULL,pszTokenId,fCreateIfNotExist);
   }

   if(SUCCEEDED(hr))
   {
      *ppToken = ptoken.detach();
   }


   return hr;

}

inline HRESULT SpGetDefaultTokenFromCategoryId(
   const WCHAR * pszCategoryId,
   ISpObjectToken ** ppToken,
   BOOL fCreateCategoryIfNotExist = TRUE)
{
   HRESULT hr;

   ::windows::comptr<ISpObjectTokenCategory> pcategory;
   hr = SpGetCategoryFromId(pszCategoryId,&pcategory,fCreateCategoryIfNotExist);

   if(SUCCEEDED(hr))
   {
      WCHAR * pszTokenId;
      hr = pcategory->GetDefaultTokenId(&pszTokenId);
      if(SUCCEEDED(hr))
      {
         hr = SpGetTokenFromId(pszTokenId,ppToken);
         ::CoTaskMemFree(pszTokenId);
      }
   }

   return hr;
}


namespace windows
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

         finalize();

      }

      //--------------------------------------------------------------------
      // Initializes the text speaker.
      //--------------------------------------------------------------------
      bool speaker::initialize()
      {

         finalize();

         //
         // Create text to speech engine
         //
         HRESULT hr = m_pvoice.CoCreateInstance(CLSID_SpVoice);
         if(FAILED(hr))
         {

            return false;

         }


         //
         // Get token corresponding to default voice 
         //
         hr = SpGetDefaultTokenFromCategoryId(SPCAT_VOICES,&m_ptoken,FALSE);

         if(FAILED(hr))
         {

            return false;

         }


         //
         // Set default voice
         //
         hr = m_pvoice->SetVoice(m_ptoken);

         if(FAILED(hr))
         {

            return false;

         }

         return true;

      }


      bool speaker::finalize()
      {

         if(m_pvoice.is_set())
         {

            m_pvoice->Pause();

         }

         m_ptoken.Release();

         m_pvoice.Release();



         return true;
      }

      //--------------------------------------------------------------------
      // Speaks some text.
      // (The input text must not be empty.)
      //--------------------------------------------------------------------
      bool speaker::speak(const string & text)
      {
         //
         // Input text must not be empty
         //
         if(text.is_empty())
         {
            // nothing to speak?!?!
            return false;
         }

         if(!initialize())
         {

            return false;

         }

         wstring wstr(text);
         //
         // Speak input text
         //
         ULONG streamNumber;
         HRESULT hr = m_pvoice->Speak(
            wstr,
            SPF_IS_NOT_XML | SPF_ASYNC | SPF_PURGEBEFORESPEAK,
            &streamNumber);
         if(FAILED(hr))
         {
            return false;
         }
         return true;
      }

      bool speaker::is_speaking()
      {

         if(m_pvoice.is_null())
         {

            return false;

         }

         SPVOICESTATUS status ={};

         HRESULT hr = m_pvoice->GetStatus(&status,NULL);

         if(FAILED(hr))
         {

            return false;

         }

         return (status.dwRunningState & SPRS_IS_SPEAKING) != FALSE;

      }


      bool speaker::stop()
      {

         finalize();

         return true;

      }


   } // namespace tts


} // namespace windows










