#include "StdAfx.h"


update_thread::update_thread(::ca::application * papp) :
   ca(papp),
   thread(papp)
{
}

   bool update_thread::initialize_instance()
   {
      return true;
   }
   int update_thread::run()
   {
      string strDir = System.dir().ca2("");
      string strVersionShift;
      if(gen::str::ends(strDir, "\\stage\\"))
      {
         strVersionShift = "stage";
      }
      else
      {
         strVersionShift = "basis";
      }
      string strPath = System.dir().ca2("app\\build.txt");
      string strCurrent = Application.file().as_string(strPath);
      strCurrent.trim();
      strCurrent.replace(" ", "_");
      strCurrent.replace(":", "-");
      if(strCurrent.get_length() != 19) // heuristcally incorrect
         return 0;
      string strUrl = "http://server3serves.ccvotagus.net/" + strVersionShift + "/app/build.txt";
      string strCandidate = System.http().get(strUrl);
      strCandidate.trim();
      strCandidate.replace(" ", "_");
      strCandidate.replace(":", "-");
      if(strCandidate.get_length() != 19) // heuristcally incorrect
         return 0;
      if(isdigit(strCandidate[0])
      && isdigit(strCandidate[1])
      && isdigit(strCandidate[2])
      && isdigit(strCandidate[3])
      && isdigit(strCandidate[5])
      && isdigit(strCandidate[6])
      && isdigit(strCandidate[8])
      && isdigit(strCandidate[9])
      && isdigit(strCandidate[11])
      && isdigit(strCandidate[12])
      && isdigit(strCandidate[14])
      && isdigit(strCandidate[15])
      && isdigit(strCandidate[17])
      && isdigit(strCandidate[18]))
      {
         if(strCandidate > strCurrent)
         {
            defer_update(strVersionShift, strCandidate);
         }
      }
      return 0;
   }

   void update_thread::defer_update(const char * pszVersionShift, const char * pszBuild)
   {
      //if(Application.simple_message_box("update ca2 now?<br>you may experience some kind of lapse...", MB_YESNO) == IDYES)
      {
         update(pszVersionShift, pszBuild);
      }
   }

   void update_thread::update(const char * pszVersionShift, const char * pszBuild)
   {
      CSingleLock slUpdating(&m_pschedulethread->m_mutexUpdating, FALSE);
      if(!slUpdating.Lock(0))
         return;
      string strUrl = "http://server3serves.ccvotagus.net/" + string(pszVersionShift) +
         "/stage/ccvotagus/Release/_set_windesk_" + string(pszBuild) + ".spaboot";
      string strPath = System.dir().ca2("spaboot\\_set_windesk_" + string(pszBuild) + ".spaboot");
      if(System.file().exists(strPath))
      {
         if(!::DeleteFile(strPath))
            return;
      }
      System.dir().mk(System.dir().name(strPath));
      gen::property_set post;
      gen::property_set headers;
      gen::property_set set;
      System.http().download(strUrl, strPath, post, headers, set, NULL, &ApplicationUser);
      ::ShellExecute(NULL, "open", strPath, NULL, NULL, SW_SHOWNORMAL);
   }

