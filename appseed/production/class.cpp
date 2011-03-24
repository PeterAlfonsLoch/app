#include "StdAfx.h"


production_class::production_class(::ca::application * papp) :
   ca(papp),
   thread(papp),
   simple_thread(papp)
{
   m_bClean       = false;
   m_bBuild       = true;
   m_bFinished    = true;
   m_eversion     = version_stage;
   m_iRelease     = 0;

   {
      stringa & stra = m_straStageDirAcceptedFileExtensions;
      stra.add("exe");
      stra.add("dll");
      stra.add("manifest");
   }
   m_bLoop = false;
}

production_class::~production_class()
{
}

void production_class::start_loop(e_version eversion, int iLoopCount)
{
	m_bLoop = true;
   if(m_iRelease > 0)
   {
      add_status("There are pending releases!!");
      return;
   }
   m_iLoop = -1;
   m_iLoopCount = iLoopCount;
   m_iRelease = 0;
   m_timeStart = time::get_current_time();
   m_eversion = eversion;


   m_iStep = 1;
   Begin();
}

void production_class::start(e_version eversion)
{
	m_bLoop = false;
   if(m_iRelease > 0)
   {
      add_status("There are pending releases!!");
      return;
   }
   m_iRelease = 0;
   m_timeStart = time::get_current_time();
   m_eversion = eversion;


   m_iStep = 1;
   Begin();
}
 
void production_class::step()
{
   m_iStep++;
   Begin();
}

int production_class::run()
{
   restart:
   if(m_iStep == 1)
   {
      m_strSignTool = System.dir().ca2("app/thirdparty/binary/signtool.exe");
      m_strSpc = "C:\\cecyn1.at.hotmail.com\\ccvotagus\\cgcl\\2011-02-ca2.p12";

      m_iLoop++;
      if(m_iLoopCount > 0)
      {
         if(m_iLoop > m_iLoopCount)
         {
            Application.PostThreadMessage(WM_QUIT, 0, 0);
            return 0;
         }
      }

      m_strBase = Application.file().as_string(System.dir().ca2("app\\stage\\app\\matter\\stage_path.txt"));

   //   goto skipCompress;
   //goto skipBuild;
      if(!sync_source("app", NULL))
	      return 1;

      string strRevision;

      string strTime;
      class time time;
      time = m_timeStart;
      time.FormatGmt(strTime, "%Y-%m-%d %H-%M-%S");
      string strVerWin;
      time.FormatGmt(strVerWin, "%Y,%m%d,%H%M,%S");
      string strSvnVersionCmd;
      strSvnVersionCmd.Format("svnversion %s", System.dir().path(m_strBase, "app"));
      m_strBuild = strTime;
      m_strFormatBuild = strTime;
      m_strFormatBuild.replace(" ", "_");
      strRevision = System.process().get_output(strSvnVersionCmd);
      string strSVN = "SVN" + strRevision;
      strSVN.trim();
      if(m_strSubversionRevision == strSVN)
      {
         goto restart;
      }
      m_iLoop = -1;
      string strStartTime;
      m_timeStart.FormatGmt(strStartTime, "%Y-%m-%d %H-%M-%S");
      add_status("Build starting at " + strStartTime + " - build version!");
      {
         // good pratice to initialize authentication of ca2status.com with fontopus.com auth information
         string str;
         gen::property_set post;
         gen::property_set headers;
         gen::property_set params;
         
         Application.http().get("http://ca2.cc/status/");

         post["new_status"] = "<h5 style=\"margin-bottom:0px; color: #CCAA55;\">" + strStartTime + "</h5><span style=\"color: #885522; display: block; margin-bottom: 1.5em;\">Starting production of new <a href=\"http://ca2.cc/\">ca2</a> release.</span>";
         
         Application.http().get("http://ca2.cc/status/", str, post, headers, params);

      }
      add_status(unitext("by Grace of God and CGCL1984+kaarurosu日歩路主!!"));
      m_dwStartTick = ::GetTickCount();

      keeper < bool > keepFinishedFalse(&m_bFinished, false, true, true);
      string str;
      m_iBaseLen = m_strBase.get_length();
      if(m_strBase.Right(1) != "/" && m_strBase.Right(1) != "\\")
         m_iBaseLen++;

      gen::property_set post;
      gen::property_set headers;
      string strStatus;
      m_strTag = strTime + " " + strSVN;
      m_strTagPath = System.dir().path("C:\\ca2\\build\\stage", m_strTag +".txt");

      string strBuildH;
      strBuildH.Format("-c1-production -c2-producer -t12n-producing -mmmi- %s", m_strTag);
      strBuildH += " - ";
      strBuildH += Application.file().as_string(System.dir().path("C:/cecyn1.at.hotmail.com/app/stage", "build_machine_pp_comment.txt"));
      strBuildH += unitext("// CarlosGustavoCecynLundgren1984+kaarurosu日歩路主\r\n");
      strBuildH += "// <==! Thanks and dedicated to &lt; <\r\n";
      strBuildH += "// Thanks to and in honor of God > &gt; ==>\r\n";
      strBuildH += "// for ca2 and 5!!\r\n";
      strBuildH += "// you(*) and me(*) and God(***) make 5...\r\n";
      strBuildH += "#define THIS_PRODUCT_VERSION \"" + m_strTag + "\\0\"\r\n#define THIS_FILE_VERSION \""+ m_strTag +"\\0\"\r\n";
      strBuildH += "#define __THIS_PRODUCT_VERSION " + strVerWin + "\r\n#define __THIS_FILE_VERSION "+ strVerWin +"\r\n";
      strBuildH += "\r\n";
      strBuildH += "\r\n";
      strBuildH += "\r\n";
      strBuildH += "\r\n";
      strBuildH += "\r\n";
      
      

      
      m_strVrel = "C:\\ca2\\vrel\\stage\\" + m_strFormatBuild;

      m_strCCVotagus = "C:\\home\\ccvotagus\\ca2_spa\\stage\\" + m_strFormatBuild;
      m_strCCVrel = "C:\\home\\ccvotagus\\ca2_spa\\stage";
      m_strCCVrelNew = "C:\\home\\ccvotagus\\ca2_spa\\ccvrelnew\\stage\\" + m_strFormatBuild;

      DWORD dwExitCode;

      int i;
      if(m_bClean)
      {
         add_status("Cleaning ca2 fontopus ccvotagus ...");
         gen::process process;
         string strPath;
         strPath = System.dir().ca2("app\\stage\\app\\matter\\stage_clean.bat");
         if(!process.create_child_process(strPath, false))
         {
            DWORD dw = GetLastError();
            string str;
            str.Format("Error creating clean process: %d", dw);
            add_status(str);
            return 0;   
         }
         i = 1;
         while(!process.has_exited(&dwExitCode))
         {
            Sleep(5000);
            str.Format("%d Cleaning ca2 fontopus ccvotagus ...", i);
            add_status(str);
            i++;
         }
      }

      string strCgclcst = Application.file().as_string("C:/cecyn1.at.hotmail.com/ccvotagus/CarlosGustavoCecynLundgrenVidaDeCamiloSasukeTsumanuma.txt");
      string strDedicaverse = Application.file().as_string("C:/cecyn1.at.hotmail.com/ccvotagus/dedicaverse.txt");

      //System.dir().mk(System.dir().path(m_strBase, "time"));
      System.file().put_contents(System.dir().path(m_strBase, "app\\build.txt"), m_strBuild);
      System.file().put_contents_utf8(System.dir().path(m_strBase, "app\\seed\\this_version_info.h"), strBuildH);
      System.file().put_contents_utf8(System.dir().path(m_strBase, "app\\seed\\this_version_info.txt"), strBuildH + "\r\n\r\n" + strDedicaverse + "\r\n\r\n" + strCgclcst);

      if(!commit_for_new_build_and_new_release())
         return 2;


      m_strSubversionRevision = "SVN" + gen::str::itoa(atoi(strRevision) + 1);

      if(m_bBuild)
      {
         add_status("Building ca2 fontopus ccvotagus ...");
         gen::process process;
         string strPath;
         strPath = System.dir().ca2("app\\stage\\app\\matter\\stage_build.bat");
         if(!process.create_child_process(strPath, false))
         {
            DWORD dw = GetLastError();
            string str;
            str.Format("Error creating build process: %d", dw);
            add_status(str);
            return 0;   
         }
         i = 1;
         while(!process.has_exited(&dwExitCode))
         {
            Sleep(5000);
            str.Format("%d Building ca2 fontopus ccvotagus ...", i);
            add_status(str);
            i++;
         }
      }


      add_status("Cleaning site...");
      string strPath = System.dir().ca2("time\\stage\\app\\matter\\job.bat");

      //System.http().ms_download("http://spaignition.api.veriterse.net/clean", 
	   //   System.dir().votagus("time\\spaignition_update.txt"), NULL, post, headers, ca2::app(get_app()).user().get_user());
      add_status("Cleaning ccvotagus folder...");
      gen::process process;
      System.file().put_contents(strPath, "rmdir /s /q C:\\ca2\\vrel\\stage");
      if(!process.create_child_process(strPath, false))
      {
         DWORD dw = GetLastError();
         string str;
         str.Format("Error creating process: %d", dw);
         add_status(str);
         return 0;   
      }
      i = 1;
      while(!process.has_exited(&dwExitCode))
      {
         Sleep(500);
         str.Format("%d Cleaning ccvotagus folder ...", i);
         add_status(str);
         i++;
      }

      m_straFiles.remove_all();
      stringa straTitle;
      stringa straRelative;
      string strRemote;
      get_file_list(m_strBase, "stage/x86", strRemote, m_straFiles, straTitle, straRelative);
      get_file_list(m_strBase, "stage/x64", strRemote, m_straFiles, straTitle, straRelative);
      get_file_list(m_strBase, "app/stage/metastage", strRemote, m_straFiles, straTitle, straRelative);
      get_file_list(m_strBase, "app/appmatter", strRemote, m_straFiles, straTitle, straRelative);
      get_file_list(m_strBase, "app/appmatter", strRemote, m_straFiles, straTitle, straRelative, true);
      for(int i = 0; i < m_straFiles.get_size();)
      {
         if(m_straFiles[i].find("\\.svn\\") >= 0 || (m_straFiles[i].get_length() < 5 || m_straFiles[i].Right(5) == "\\.svn"))
         {
            m_straFiles.remove_at(i);
         }
         else
         {
            i++;
         }
      }
      TRACE("\n");
      for(int i = 0; i < m_straFiles.get_size(); i++)
      {
         const char * lpcsz = m_straFiles[i];
         TRACE("file(%05d)=%s\n", i, lpcsz);
      }
      m_pview->PostMessage(WM_USER, 2);
   }
   else if(m_iStep == 2)
   {
      compress();
      generate_appmatter_spa();
      release();
      if(!release_npca2("x86"))
      {
         return 1;
      }
/*      if(!release_npca2("x64"))
      {
         return 1;
      }*/
      if(!release_iexca2("x86"))
      {
         return 1;
      }
      /*if(!release_iexca2("x64"))
      {
         return 1;
      }*/
      System.dir().mk("C:\\home\\ccvotagus\\ca2_spa\\stage\\app\\");
      System.file().put_contents("C:\\home\\ccvotagus\\ca2_spa\\stage\\app\\build.txt", m_strBuild);
      System.file().put_contents(m_strCCVrelNew + "\\app\\build.txt", m_strBuild);
      System.dir().mk(System.dir().name(m_strTagPath));
      System.file().put_contents(m_strTagPath, m_strTag);

      add_status("dtf - fileset - file from directory app");
      System.file36().dtf(m_strCCVrelNew + "\\ca2_spa_app.fileset", m_strCCVrelNew + "\\app");
      add_status("dtf - fileset - file from directory stage");
      System.file36().dtf(m_strCCVrelNew + "\\ca2_spa_stage.fileset", m_strCCVrelNew + "\\stage");
      add_status("bz - bzip - compressing app");
      System.compress().bz(m_strCCVrelNew + "\\ca2_spa_app.fileset.bz", m_strCCVrelNew + "\\ca2_spa_app.fileset");
      add_status("bz - bzip - compressing stage");
      System.compress().bz(m_strCCVrelNew + "\\ca2_spa_stage.fileset.bz", m_strCCVrelNew + "\\ca2_spa_stage.fileset");
      
      class release * prelease = NULL;
      
/*      add_status("_001cgcl - releasing at United States, GoDaddy, cgcl...");
      class release * prelease = new class release(this);
      prelease->m_strRelease = "http://production.server1serves.ccvotagus.net/release_ca2_ccvotagus_spa?authnone=1&version_shift="
         + m_strVersionShift + "&format_build=" + m_strFormatBuild;
      prelease->Begin();
      
      
      add_status("_002cst - releasing at United States, GoDaddy, cst...");
      prelease = new class release(this);
      prelease->m_strRelease = "http://production.server2serves.ccvotagus.net/release_ca2_ccvotagus_spa?authnone=1&version_shift="
         + m_strVersionShift + "&format_build=" + m_strFormatBuild;
      prelease->Begin();*/


      add_status("ca2.se - freigeben auf Deutschland, Hessen, Frankfurt, ServerLoft...");
      prelease = new class release(this);
      prelease->m_strRelease = "http://production.server4serves.ccvotagus.net/release_ca2_ccvotagus_spa?secure=0&authnone=1&format_build=" + m_strFormatBuild;
      prelease->Begin();

      add_status("ca2.cl - lançando no Brasil, Rio Grande do Sul, Porto Alegre, RedeHost...");
      prelease = new class release(this);
      prelease->m_strRelease = "http://production.server5serves.ccvotagus.net/release_ca2_ccvotagus_spa?secure=0&authnone=1&format_build=" + m_strFormatBuild;
      prelease->Begin();

/*
      add_status("releasing in server1serves.ccvotagus.net - United States...");
      {
         CInternetSession session;
         CFtpConnection ftpconn(
            &session,
            "server1serves.ccvotagus.net",
            "ccvotagus",
            "ccvotagus514Lund");
         ftp_put_dir(ftpconn, "C:\\home\\ccvotagus", "ca2_spa/" + m_strVersionShiftFwd + "stage", 0);
         ftp_put_dir(ftpconn, "C:\\home\\ccvotagus", "ca2_spa/" + m_strVersionShiftFwd + "app", 0);
      }
      */

/*
      add_status("releasing in server2serves.ccvotagus.net - United States...");
      {
         CInternetSession session;
         CFtpConnection ftpconn(
            &session,
            "server2serves.ccvotagus.net",
            "ccvotagus",
            "ccvotagus514Lund");
         ftp_put_dir(ftpconn, "C:\\home\\ccvotagus", "ca2_spa/" + m_strVersionShiftFwd + "stage", 0);
         ftp_put_dir(ftpconn, "C:\\home\\ccvotagus", "ca2_spa/" + m_strVersionShiftFwd + "app", 0);
      }
*/

      /*
      add_status("releasing in server3serves.ccvotagus.net - United States...");
      {
         CInternetSession session;
         CFtpConnection ftpconn(
            &session,
            "server3serves.ccvotagus.net",
            "ccvotagus",
            "ccvotagus514Lund");
         ftp_put_dir(ftpconn, "C:\\home\\ccvotagus", "ca2_spa/" + m_strVersionShiftFwd + "stage", 0);
         ftp_put_dir(ftpconn, "C:\\home\\ccvotagus", "ca2_spa/" + m_strVersionShiftFwd + "app", 0);
      }
      */

      /*System.http().ms_get("http://veriwell.us/release_ca2_ccvotagus_spa?authnone=1");
      try
      {
         CFtpConnection ftpconn(
            &session,
            "veriwell.de",
            "ccvotagus",
            "ccvotagus514Lund");
          add_status("send app to Germany...");
          ftpconn.PutFile("C:\\home\\ccvotagus\\ca2_spa_app.fileset.gz", "ca2_spa_app.fileset.gz");
          add_status("send stage to Germany...");
          ftpconn.PutFile("C:\\home\\ccvotagus\\ca2_spa_stage.fileset.gz", "ca2_spa_stage.fileset.gz");
          
          
      }
      catch(...)
      {
      }
      add_status("releasing in Germany...");
      System.http().ms_get("http://veriwell.de/release_ca2_ccvotagus_spa?authnone=1");
      try
      {
         CFtpConnection ftpconn(
            &session,
            "veriwell.co.uk",
            "ccvotagus",
            "ccvotagus514Lund");
          add_status("send app to United Kingdom...");
          ftpconn.PutFile("C:\\home\\ccvotagus\\ca2_spa_app.fileset.gz", "ca2_spa_app.fileset.gz");
          add_status("send stage to United Kingdom...");
          ftpconn.PutFile("C:\\home\\ccvotagus\\ca2_spa_stage.fileset.gz", "ca2_spa_stage.fileset.gz");
          
          
      }
      catch(...)
      {
      }
      add_status("releasing in United Kingdom...");
      System.http().ms_get("http://veriwell.co.uk/release_ca2_ccvotagus_spa?authnone=1");
      try
      {
         CFtpConnection ftpconn(
            &session,
            "veriwell.jp",
            "ccvotagus",
            "ccvotagus514Lund");
          add_status("send app to Japan...");
          ftpconn.PutFile("C:\\home\\ccvotagus\\ca2_spa_app.fileset.gz", "ca2_spa_app.fileset.gz");
          add_status("send stage to Japan...");
          ftpconn.PutFile("C:\\home\\ccvotagus\\ca2_spa_stage.fileset.gz", "ca2_spa_stage.fileset.gz");
      }
      catch(...)
      {
      }
      add_status("releasing in Japan...");
      System.http().ms_get("http://xn--gckc2msch3hc.jp/release_ca2_ccvotagus_spa?authnone=1");
      try
      {
         CFtpConnection ftpconn(
            &session,
            "veriwell.com.br",
            "ccvotagus",
            "ccvotagus514Lund");
          add_status("send app to Brazil...");
          ftpconn.PutFile("C:\\home\\ccvotagus\\ca2_spa_app.fileset.gz", "ca2_spa_app.fileset.gz");
          add_status("send stage to Brazil...");
          ftpconn.PutFile("C:\\home\\ccvotagus\\ca2_spa_stage.fileset.gz", "ca2_spa_stage.fileset.gz");
      }
      catch(...)
      {
      }
      add_status("releasing in Brazil...");
      System.http().ms_get("http://veriwell.com.br/release_ca2_ccvotagus_spa?authnone=1");*/
      m_bFinished = true;
      m_timeEnd = time::get_current_time();
      m_dwEndTick = ::GetTickCount();
         DWORD dwMin = (m_dwEndTick - m_dwStartTick) / 1000 / 60;
         DWORD dwSeg = ((m_dwEndTick - m_dwStartTick) / 1000) % 60;
         string strTime;
      
      string strStartTime;
      m_timeStart.FormatGmt(strStartTime, "%Y-%m-%d %H-%M-%S");
      string strEndTime;
      m_timeEnd.FormatGmt(strEndTime, "%Y-%m-%d %H-%M-%S");
      add_status("Build started at " + strStartTime);
      add_status("Build ending at " + strEndTime);
      strTime.Format("Build took: %dm %ds", dwMin, dwSeg);
      add_status(strTime);
      m_strBuildTook = strTime;
      add_status(unitext("Finished!! Thanks to God, Thanks to CGCL1984+kaarurosu日歩路主!!"));
      add_status("");
      add_status("");
      add_status("");
      add_status("");
      add_status("");
	   if(m_bLoop)
	   {
		  m_iStep = 1;
		  goto restart;
	   }
   }

   return 0;
}
void production_class::compress(const char * lpcszRelative)
{
   string strStatus;
   strStatus.Format("compressing %s", System.file().name_(lpcszRelative));
   add_status(strStatus);
   string strSrcFile = System.dir().path(m_strVrel, lpcszRelative);
   if(gen::str::ends_ci(lpcszRelative, ".dll")
   || gen::str::ends_ci(lpcszRelative, ".exe")
   || gen::str::ends_ci(lpcszRelative, ".ocx")
   || gen::str::ends_ci(lpcszRelative, ".cab"))
   {

      string strStatus;
      strStatus.Format("signing %s", System.file().name_(lpcszRelative));
      add_status(strStatus);

      string strCmd = "\"" + m_strSignTool + "\" sign /f \"" + m_strSpc + "\" /p ca2514GrenLund \"" + strSrcFile + "\"";
      System.process().synch(strCmd);

      add_status("Signing code ...");
   }

   
   System.compress().bz(System.dir().path(m_strCCVotagus, lpcszRelative) + ".bz", strSrcFile);
   strStatus.Format("%s compressed", System.file().name_(lpcszRelative));
   add_status(strStatus);
}

int get_current_process_affinity_order()
{
   DWORD_PTR dwProcessAffinityMask;
   DWORD_PTR dwSystemAffinityMask;
   if(!GetProcessAffinityMask(::GetCurrentProcess(), &dwProcessAffinityMask, & dwSystemAffinityMask))
   {
      return 0;
   }
   int iCount = 0;
   DWORD_PTR dwMask = 1;
   for(int i = 0; i < sizeof(dwProcessAffinityMask) * 8; i++)
   {
      if((dwMask & dwProcessAffinityMask) != 0)
      {
         iCount++;
      }
      dwMask = dwMask << 1;
   }
   return iCount;
}

void production_class::compress()
{
   string strStatus;
   strStatus = "Compressing";
   add_status(strStatus);

   string strVrel;
   strVrel = "C:\\ca2\\vrel\\stage\\" + m_strFormatBuild;

   string strCCVotagus;
   strCCVotagus = "C:\\home\\ccvotagus\\ca2_spa\\stage\\" + m_strFormatBuild;

   string strRelative;
   string strBz;
   string strUn;
   int i = 0;
   CSingleLock sl(&m_mutexCompress, TRUE);
   for(;i < m_straFiles.get_size();i++)
   {
      string & strFile = m_straFiles[i];
      if(gen::str::ends_ci(strFile, ".zip"))
      {
      }
      else if(System.dir().is(strFile))
      {
         continue;
      }
      if(System.file().extension(strFile) == "pdb")
      {
         continue;
      }
      if(System.file().extension(strFile) == "ilk")
      {
         continue;
      }
      //strStatus.Format("compressing %s", strFile);
      //add_status(strStatus);
      m_straCompress.add(strFile.Mid(m_iBaseLen));
   }
   sl.Unlock();

   UINT uiProcessorCount = get_current_process_affinity_order();

   base_array < compress_thread * > threada;
   if(uiProcessorCount == 0)
   {
      while(compress_next())
      {
      }
   }
   else
   {
      sync_object_base ** psynca = new sync_object_base * [uiProcessorCount];
      for(UINT ui = 0; ui < uiProcessorCount; ui++)
      {
         compress_thread * pthread = new compress_thread(this);
         threada.add(pthread);
         psynca[ui] = &pthread->m_evFinished;
         pthread->m_bAutoDelete = FALSE;
         pthread->m_p->m_bAutoDelete = FALSE;
         pthread->Begin();
      }
      CMultiLock ml(psynca, uiProcessorCount);
      ml.Lock();
      add_status("finished multi-threaded compression task");
      Sleep(584);
   }
   /*while(threada.get_size() > 0)
   {
      try
      {
         delete threada.last_element();
      }
      catch(...)
      {
      }
      threada.remove_last();
   }*/
}

bool production_class::compress_next()
{
   CSingleLock sl(&m_mutexCompress, TRUE);
   if(m_straCompress.get_size() <= 0)
      return false;
   string strNext = m_straCompress[0];
   m_straCompress.remove_at(0);
   sl.Unlock();
   compress(strNext);
   return true;
}


      production_class::compress_thread::compress_thread(production_class * pproduction) :
ca(pproduction->get_app()),
   thread(pproduction->get_app())
      {
         m_evFinished.ResetEvent();
         m_pproduction = pproduction;
      }

int production_class::compress_thread::run()
{
   SetThreadPriority(THREAD_PRIORITY_HIGHEST);
   while(m_pproduction->compress_next())
   {
   }
   m_evFinished.SetEvent();
   return 0;
}

/*void production_class::compress()
{
   string strStatus;
   strStatus = "Compressing";
   add_status(strStatus);

   int i = 0;
   while(i < m_straCC.get_size())
   {
      string strUrl;
      string strVar;
      strVar.Empty();
      m_straCC.implode(strVar, ",", i, min(8, m_straCC.get_size() - i));
      strUrl = "http://spaignition.api.veriterse.net/compress?file=";
      strUrl += strVar;

      strStatus.Format("compress step: %d", i);
      add_status(strStatus);

   gen::property_set post;

   gen::property_set headers;
      System.http().ms_download(strUrl, 
	      System.dir().votagus("time\\spaignition_update.txt"), NULL, post, headers, System.user().get_user());
      i += 8;
   }
}*/


bool  production_class::sync_source(const char * psz, const char * pszRevision)
{
   string strStatus;
   strStatus.Format("Updating source: %s ...", psz);
   add_status(strStatus);

   string str;
   string strBase = m_strBase;
	STARTUPINFO si;
	PROCESS_INFORMATION pi; 
	memset(&si, 0, sizeof(si));
	memset(&pi, 0, sizeof(pi));
	si.cb = sizeof(si);
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_HIDE; 
   if(pszRevision != NULL && pszRevision[0] != '\0')
   {
      str.Format("svn update --revision %s %s", pszRevision, System.dir().path(strBase, psz));
   }
   else
   {
      str.Format("svn update %s", System.dir().path(strBase, psz));
   }
   if(!::CreateProcess(NULL, (LPTSTR) (const char *) str, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
   {
	   strStatus.Format("     Error: Check svn installation!!");
	   add_status(strStatus);
	   return false;
   }

   DWORD dwExitCode;
   int i = 1;
   while(true)
   {
      if(!GetExitCodeProcess(pi.hProcess, &dwExitCode))
         break;
      if(dwExitCode != STILL_ACTIVE)
         break;
      Sleep(2300);
      str.Format("%d Updating source: %s ...", i, psz);
      add_status(str);
      i++;
   }
	return true;
}

bool production_class::commit_for_new_build_and_new_release()
{
   string strStatus;
   strStatus = unitext("Commit for new Build and new Release!! signature CGCL1984+kaarurosu日歩路主!!");
   add_status(strStatus);

   string str;
   string strBase = m_strBase;
	STARTUPINFO si;
	PROCESS_INFORMATION pi; 
	memset(&si, 0, sizeof(si));
	memset(&pi, 0, sizeof(pi));
	si.cb = sizeof(si);
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_HIDE; 
   str.Format("svn commit --force-log --encoding utf-8 --file %s %s", 
   System.dir().path(m_strBase, "app\\seed\\this_version_info.txt"),
   System.dir().path(strBase, "app"));
   if(!::CreateProcess(NULL, (LPTSTR) (const char *) str, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
   {
	   strStatus.Format("     Error: Check svn installation!!");
	   add_status(strStatus);
	   return false;
   }

   DWORD dwExitCode;
   int i = 1;
   while(true)
   {
      if(!GetExitCodeProcess(pi.hProcess, &dwExitCode))
         break;
      if(dwExitCode != STILL_ACTIVE)
         break;
      Sleep(2300);
      str.Format("%d: Commit for new Build and new Release ...", i);
      add_status(str);
      i++;
   }
	return true;
}


bool production_class::get_file_list(const char * pszBase, const char * pszDir, string & strRemote, stringa & stra, stringa & straTitle, stringa & straRelative, bool bFileSet)
{
   string strBase(pszBase);
   string strRelease;
   string strDirParam(pszDir);
   string strLocal(strDirParam);
   strLocal.replace("/", "\\");
   if(strLocal.Right(1) != "\\") strLocal += "\\";
   strRemote = strDirParam;
   strRemote.replace("\\", "/");
   if(strRemote.Right(1) != "/") strRemote += "/";
   if(strRemote.Left(1) != "/") strRemote = "/" + strRemote;
   strRelease = System.dir().path(strBase, strLocal);
   if(bFileSet)
   {
      string strFile;
      string strTitle;
      string strRelative;
      gen::str::ends_eat(strRelease, "\\");
      gen::str::ends_eat(strRelease, "/");
      gen::str::ends_eat(strLocal, "\\");
      gen::str::ends_eat(strLocal, "/");
      strFile = strRelease + ".expand_fileset";
      strTitle = System.file().name_(strRelease) + ".expand_fileset";
      strRelative = strLocal + ".expand_fileset";
      strRelative.replace("/", "\\");

      stringa stra1;
      stringa stra2;
      System.dir().rls(strRelease, &stra1, NULL, &stra2);
      for(int i = 0; i < stra1.get_size();)
      {
         if(stra1[i].find("\\.svn\\") >= 0 || (stra1[i].get_length() < 5 || stra1[i].Right(5) == "\\.svn"))
         {
            stra1.remove_at(i);
            stra2.remove_at(i);
         }
         else
         {
            i++;
         }
      }
      System.file36().dtf(strFile, stra1, stra2);
      stra.add(strFile);
      straTitle.add(strTitle);
      straRelative.add(strRelative);
   }
   else
   {
      System.dir().rls(strRelease, &stra, &straTitle, &straRelative);
   }
   strRemote = strRemote + "/stage/" + m_strFormatBuild + "/";
   return true;
}



void production_class::release()
{
   m_strStatus = "generating index file and releasing...";
   add_status(m_strStatus);


   int iBaseLen = m_strBase.get_length();
   if(m_strBase.Right(1) != "/" && m_strBase.Right(1) != "\\")
      iBaseLen++;

   stringa straStageDir;
   
   straStageDir.add(System.dir().path(m_strBase, "stage/x86"));
   straStageDir.add(System.dir().path(m_strBase, "stage/x64"));

   string strRelative;
   string strBz;
   string strUn;
   string strRelease;
   string strReleaseNew;
   var varUnSize;
   string strMd5;
   var varBzSize;
   string strContents;
   int i = 0;
   for(;i < m_straFiles.get_size();i++)
   {
      string & strFile = m_straFiles[i];
      if(gen::str::ends_ci(strFile, ".zip"))
      {
      }
      else if(System.dir().is(strFile))
      {
         continue;
      }
      if(straStageDir.str_find_first_begins_ci(strFile) >= 0
      && !m_straStageDirAcceptedFileExtensions.contains(
      System.file().extension(strFile)))
      {
         continue;
      }
      //strStatus.Format("compressing %s", strFile);
      //add_status(strStatus);
      strRelative = strFile.Mid(iBaseLen);
      strBz = System.dir().path(m_strCCVotagus, strRelative) + ".bz";
      strUn = System.dir().path(m_strVrel, strRelative);
      strMd5 = System.file36().md5(strUn);
      varUnSize = System.file().length(strUn);
      varBzSize = System.file().length(strBz);
      strRelease = System.dir().path(m_strCCVrel, strRelative);
      strRelease += ".bz.";
      strRelease += strMd5;
      strReleaseNew = System.dir().path(m_strCCVrelNew, strRelative);
      strReleaseNew += ".bz.";
      strReleaseNew += strMd5;
      strContents += strRelative;
      strContents += ",";
      strContents += varUnSize.get_string();
      strContents += ",";
      strContents += strMd5;
      strContents += ",";
      strContents += varBzSize.get_string();
      strContents += "\n";
      if(!System.file().exists(strRelease))
      {
         System.file().copy(strRelease, strBz, false);
      }
      System.file().copy(strReleaseNew, strBz, false);
   }

   strRelative = "app\\stage\\metastage\\index-" + m_strFormatBuild + ".spa";
   string strIndex = System.dir().path(m_strVrel, strRelative);
   System.file().put_contents(
      strIndex,
      strContents);

   m_strIndexMd5 = System.file36().md5(strIndex);

   strBz = System.dir().path(m_strCCVotagus, strRelative) + ".bz"; 
   ::DeleteFileW(gen::international::utf8_to_unicode(strBz));
   compress(strRelative);

   string strRelativeMd5 = "app\\stage\\metastage\\index-" + m_strFormatBuild + ".md5";
   strMd5 =  System.dir().path(m_strVrel, strRelativeMd5);
   System.file().put_contents(strMd5 , m_strIndexMd5);

   //string strStage = System.dir().path("C:\\home\\ccvotagus\\ca2_spa\\" + m_strVersionShift, strRelative) + ".bz"; 
   //::DeleteFileW(gen::international::utf8_to_unicode(
     // strStage));
   //System.file().copy(strStage, strBz);
   strRelease = System.dir().path(m_strCCVrel, strRelative) + ".bz";
   //::DeleteFileW(gen::international::utf8_to_unicode(
     // strRelease));
   System.file().copy(strRelease, strBz);
   strRelease = System.dir().path(m_strCCVrel, strRelativeMd5);
   System.file().copy(strRelease, strMd5);
   strReleaseNew = System.dir().path(m_strCCVrelNew, strRelative) + ".bz";
   //::DeleteFileW(gen::international::utf8_to_unicode(
     // strRelease));
   System.file().copy(strReleaseNew, strBz);
   strReleaseNew = System.dir().path(m_strCCVrelNew, strRelativeMd5);
   System.file().copy(strReleaseNew, strMd5);
}

void production_class::generate_appmatter_spa()
{
   string strStatus;
   strStatus = "updating appmatter spa spfile->...";
   add_status(strStatus);

   stringa straFiles;

   System.dir().rls(
      System.dir().path(m_strVrel, "app\\appmatter"),
      &straFiles);
   int iVrelLen = m_strVrel.get_length();
   if(m_strVrel.Right(1) != "/" && m_strVrel.Right(1) != "\\")
      iVrelLen++;
   string strRelative;
   string strBz;
   string strUn;
   var varUnSize;
   string strMd5;
   var varBzSize;
   string strContents;
   int i = 0;
   for(;i < straFiles.get_size();i++)
   {
      string & strFile = straFiles[i];
      if(System.file().extension(strFile).CompareNoCase("zip") == 0)
      {
      }
      else if(System.dir().is(strFile))
      {
         continue;
      }
      else if(System.file().extension(strFile) == "pdb")
      {
         continue;
      }
      else if(System.file().extension(strFile) == "ilk")
      {
         continue;
      }
      //strStatus.Format("compressing %s", strFile);
      //add_status(strStatus);
      strRelative = strFile.Mid(iVrelLen);
      strContents += strRelative;
      strContents += "\n";
   }
   strRelative = "app\\stage\\metastage\\app_appmatter.expand_fileset.spa";
   System.file().put_contents(
      System.dir().path(m_strVrel, strRelative),
      strContents);
   ::DeleteFileW(gen::international::utf8_to_unicode(
      System.dir().path(m_strCCVotagus, strRelative) + ".bz"));
   compress(strRelative);
}

bool production_class::release_npca2(const char * pszPlatform)
{
   
   string strPlatform(pszPlatform);

   string strDir;
   strDir = System.dir().path(m_strBase, "time/npca2/" + strPlatform);


   string strNpca2Version;

   strNpca2Version.Format(
      "%d.%d.%d.%d.%d.%d",
      atoi(m_strFormatBuild.Mid(0, 4)),
      atoi(m_strFormatBuild.Mid(5, 2)),
      atoi(m_strFormatBuild.Mid(8, 2)),
      atoi(m_strFormatBuild.Mid(11, 2)),
      atoi(m_strFormatBuild.Mid(14, 2)),
      atoi(m_strFormatBuild.Mid(17, 2))
      );
   

   string strChromeManifest = Application.file().as_string(System.dir().ca2("app/stage/app/matter/npca2/chrome.manifest"));
   strChromeManifest.replace("%BUILD%", strNpca2Version);
   strChromeManifest.replace("%PLATFORM%", strPlatform);
   System.file().put_contents(System.dir().path(strDir, "npca2", "chrome.manifest"), strChromeManifest);

   string strIcon = System.dir().matter("ca2-5c-32.png");
   System.file().copy(System.dir().path(strDir, "npca2/skin/classic", "ca2-5c-32.png"), strIcon);

   string strInstall = Application.file().as_string(System.dir().ca2("app/stage/app/matter/npca2/install.rdf"));
   strInstall.replace("%BUILD%", strNpca2Version);
   strInstall.replace("%PLATFORM%", strPlatform);
   System.file().put_contents(System.dir().path(strDir, "npca2", "install.rdf"), strInstall);


   string strWindows = Application.file().as_string(System.dir().ca2("app/stage/app/matter/npca2/windows.rdf"));
   strWindows.replace("%BUILD%", strNpca2Version);
   strWindows.replace("%PLATFORM%", strPlatform);
   System.file().put_contents(System.dir().path(strDir, "windows.rdf"), strWindows);
   

   System.file().copy(System.dir().path(strDir, "npca2/components/windows/npca2.dll"), System.dir().path(m_strVrel, "stage/" + strPlatform + "/npca2.dll"));

   System.file().del(System.dir().path(strDir, "npca2.xpi"));

   DWORD dwExitCode;
   string str;
   gen::process process;
   string strPath;
   strPath = System.dir().ca2("app\\thirdparty\\binary\\7za.exe") + " a -tzip -r \"" + System.dir().path(strDir, "npca2.xpi") + "\" \"" + System.dir().path(strDir, "npca2/*") + "\"";
   if(!process.create_child_process(strPath, false))
   {
      DWORD dw = GetLastError();
      string str;
      str.Format("Error compressing npca2: %d", dw);
      add_status(str);
      return 0;   
   }
   int i;
   i = 1;
   while(!process.has_exited(&dwExitCode))
   {
      Sleep(5000);
      str.Format("%d Compressing npca2 ...", i);
      add_status(str);
      i++;
   }
   
   System.file().copy("C:\\netnode\\net\\netseed\\ds\\ca2\\front\\cc\\ca2\\_std\\_std\\xpi\\"+strPlatform+"\\npca2.xpi", System.dir().path(strDir, "npca2.xpi"));
   System.file().copy("C:\\netnode\\net\\netseed\\ds\\ca2\\front\\cc\\ca2\\_std\\_std\\rdf\\"+strPlatform+"\\windows.rdf", System.dir().path(strDir, "windows.rdf"));

   return true;
}


bool production_class::release_iexca2(const char * pszPlatform)
{
   
   string strPlatform(pszPlatform);

   System.file().copy("C:\\netnode\\net\\netseed\\ds\\ca2\\front\\cc\\ca2\\_std\\_std\\cab\\"+strPlatform+"\\iexca2.cab", System.dir().path(m_strBase, "time\\iexca2\\"+strPlatform+"\\iexca2.cab"));

   return true;

}


void production_class::add_status(const char * psz)
{
   CSingleLock sl(&m_mutexStatus, TRUE);
   m_straStatus.add(psz);
   m_pview->SendMessage(WM_USER, 1);
}

void production_class::change_status(const char * psz)
{
   CSingleLock sl(&m_mutexStatus, TRUE);
   if(m_straStatus.get_count() == 0)
   {
      m_straStatus.add(psz);
   }
   else
   {
      m_straStatus.last_element() = psz;
   }
   m_pview->SendMessage(WM_USER, 1);
}



production_class::release::release(production_class * pproduction) : 
   ::ca::ca(pproduction->get_app()),
   thread(pproduction->get_app())
{
   m_pproduction = pproduction;
   m_pproduction->m_iRelease++;
   m_pproduction->OnUpdateRelease();
}

bool production_class::release::initialize_instance()
{
   return true;
}
int production_class::release::run()
{
   Application.http().get(m_strRelease);
   m_pproduction->m_iRelease--;
   m_pproduction->OnUpdateRelease();
   return 0;
}


void production_class::OnUpdateRelease()
{
   if(m_iRelease == 0)
   {
      add_status("All releases have been commanded!!.!.!!.");
      gen::property_set post;
      gen::property_set headers;
      gen::property_set params;
      post["new_status"] = "<h2 style=\"margin-bottom:0px; color: #55CCAA;\">" + m_strBuild +"</h2><span style=\"color: #228855; display: block; margin-bottom: 1.5em;\">"+m_strBuildTook+"<br>New release of <a href=\"http://ca2.cc/\">ca2</a> applications labeled " + m_strBuild + " is ready for download through compatible gateways.<br>Check <a href=\"http://fontopus.com/\">fontopus.com</a> or <a href=\"http://bergedge.com/\">bergedge.com</a> for simple gateway implementations.</span>";
      string str;
      Application.http().get("http://ca2.cc/status/", str, post, headers, params);
   }
   else if(m_iRelease > 0)
   {
      string strStatus;
      strStatus.Format("There are %d releases in command list!!", m_iRelease);
      add_status(strStatus);
   }
}