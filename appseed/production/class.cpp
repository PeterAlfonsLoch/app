#include "StdAfx.h"
#include <openssl/crypto.h>
#include <openssl/pem.h>
#include <openssl/err.h>

production_class::production_class(::ca::application * papp) :
   ca(papp),
   thread(papp),
   simple_thread(papp)
{
   m_bClean       = false;
   m_bBuild       = true;
   m_bFinished    = true;
   m_eversion     = version_stage;
   m_bReleased    = true;
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

void production_class::start_production(e_version eversion)
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

void production_class::defer_quit()
{
   if(!m_bReleased)
      return;
   if(m_iLoopCount > 0)
   {
      if(m_iLoop > m_iLoopCount)
      {
         System.PostThreadMessage(WM_QUIT, 0, 0);
      }
   }

}


int production_class::run()
{
   restart:
   if(m_iStep == 1)
   {

      if(m_eversion == version_basis)
      {
         m_strStdPostColor = "color: #882277;";
         m_strBackPostColor = "background-color: #CFC2CF;";
         m_strEmpPostColor = "color: #660060;";
      }
      else
      {
         m_strStdPostColor = "color: #448855;";
         m_strBackPostColor = "background-color: #A0CCAA;";
         m_strEmpPostColor = "color: #007700;";
      }
      
      m_strSignTool = System.dir().ca2("app/thirdparty/binary/signtool.exe");
      m_strSpc = "C:\\cecyn1.at.hotmail.com\\ccvotagus\\cgcl\\2011-05-ca2.p12";
      m_strSignPass = Application.file().as_string("C:\\cecyn1.at.hotmail.com\\ccvotagus\\cgcl\\2011-05-ca2.pass");

      m_iLoop++;
      defer_quit();

      m_strBase = Application.command().m_varTopicQuery["base_dir"];


   //   goto skipCompress;
   //goto skipBuild;
      if(!sync_source("app", NULL))
	      return 1;

      if(!sync_source("app-veriwell", NULL))
	      return 1;

      if(!sync_source("app-frontpage", NULL))
	      return 1;

      if(!sync_source("app-sysutils", NULL))
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

      string strSVNKey;
      string strAddRevision;

      strSVNKey = "app:" + strSVN;
      
      strSvnVersionCmd.Format("svnversion %s", System.dir().path(m_strBase, "app-veriwell"));
      strAddRevision = System.process().get_output(strSvnVersionCmd);
      strAddRevision.trim();
      strSVNKey += ", app-veriwell:SVN" + strAddRevision;

      strSvnVersionCmd.Format("svnversion %s", System.dir().path(m_strBase, "app-frontpage"));
      strAddRevision = System.process().get_output(strSvnVersionCmd);
      strAddRevision.trim();
      strSVNKey += ", app-frontpage:SVN" + strAddRevision;

      strSvnVersionCmd.Format("svnversion %s", System.dir().path(m_strBase, "app-sysutils"));
      strAddRevision = System.process().get_output(strSvnVersionCmd);
      strAddRevision.trim();
      strSVNKey += ", app-sysutils:SVN" + strAddRevision;

      m_bReleased = false;
      m_iLoop = -1;
      m_timeStart.FormatGmt(m_strStartTime, "%Y-%m-%d %H-%M-%S");
      add_status("Build starting at " + m_strStartTime + " - build version!");
      //twitter_auth();
      //twitter_twit("new build starting : " + m_strStartTime);
      {
         // good pratice to initialize authentication of ca2status.com with fontopus.com auth information
         string str;
         gen::property_set post;
         gen::property_set headers;
         gen::property_set params;
         
         Application.http().get("http://ca2.cc/status/");

         if(m_eversion == version_basis)
         {
            post["new_status"] = "<div style=\"display: block; " + m_strBackPostColor + "\"><h3 style=\"margin-bottom:0px; color: #552250;\">" + m_strStartTime + "</h3><span style=\"color: #882266; display: block; margin-bottom: 1.5em;\">Starting production of new <a href=\"http://ca2.cc/\">ca2</a> basis release.</span>";
         }
         else
         {
            post["new_status"] = "<div style=\"display: block; " + m_strBackPostColor + "\"><h3 style=\"margin-bottom:0px; color: #22552F;\">" + m_strStartTime + "</h3><span style=\"color: #228855; display: block; margin-bottom: 1.5em;\">Starting production of new <a href=\"http://ca2.cc/\">ca2</a> stage release.</span>";
         }
         
         Application.http().get("http://ca2.cc/status/", str, post, headers, params);

      //string strTwit = "by ca2production through ca2twit-lib : starting new build " + m_strBuild + " : check http://ca2.cc/status/?email=production@ca2.cc";
      //twitter_auth();
      //twitter_twit(strTwit);

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
      m_strTag = strTime + " " + strSVNKey;
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
         {
            string str;
            gen::property_set post;
            gen::property_set headers;
            gen::property_set params;
         
            post["new_status"] = "<div style=\"display: block; " + m_strBackPostColor + "\"><h5 style=\"margin-bottom:0px; " + m_strEmpPostColor + "\">" + m_strStartTime + "</h5><span style=\"" + m_strStdPostColor + m_strBackPostColor +" display: block; margin-bottom: 0.95em;\">" + ::time::get_current_time().FormatGmt( "%Y-%m-%d %H-%M-%S") +  " Cleaning...</span></div>";
         
            Application.http().get("http://ca2.cc/status/", str, post, headers, params);

         }
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
      Application.file().put_contents(System.dir().path(m_strBase, "app\\build.txt"), m_strBuild);
      Application.file().put_contents_utf8(System.dir().path(m_strBase, "app\\seed\\this_version_info.h"), strBuildH);
      Application.file().put_contents_utf8(System.dir().path(m_strBase, "app\\seed\\this_version_info.txt"), strBuildH + "\r\n\r\n" + strDedicaverse + "\r\n\r\n" + strCgclcst);

      if(!commit_for_new_build_and_new_release())
         return 2;


      m_strSubversionRevision = "SVN" + gen::str::itoa(atoi(strRevision) + 1);

      if(m_bBuild)
      {
         //build("app");
         build("app-veriwell");
      }

      {
         string str;
         gen::property_set post;
         gen::property_set headers;
         gen::property_set params;
         
         post["new_status"] = "<div style=\"display: block; " + m_strBackPostColor + "\"><h5 style=\"margin-bottom:0px; " + m_strEmpPostColor + "\">" + m_strStartTime + "</h5><span style=\"" + m_strStdPostColor + m_strBackPostColor +" display: block; margin-bottom: 0.95em;\">" + ::time::get_current_time().FormatGmt( "%Y-%m-%d %H-%M-%S") +  " Cleaning...</span></div>";
         
         Application.http().get("http://ca2.cc/status/", str, post, headers, params);

      }

      add_status("Cleaning site...");
      string strPath = System.dir().ca2("time\\stage\\app\\matter\\job.bat");


      //System.http().ms_download("http://spaignition.api.veriterse.net/clean", 
	   //   System.dir().votagus("time\\spaignition_update.txt"), NULL, post, headers, ca2::app(get_app()).user().get_user());
      add_status("Cleaning ccvotagus folder...");
      gen::process process;
      Application.file().put_contents(strPath, "rmdir /s /q C:\\ca2\\vrel\\stage");
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
      {
         string str;
         gen::property_set post;
         gen::property_set headers;
         gen::property_set params;
         
         post["new_status"] = "<div style=\"display: block; " + m_strBackPostColor + "\"><h5 style=\"margin-bottom:0px; " + m_strEmpPostColor + "\">" + m_strStartTime + "</h5><span style=\"" + m_strStdPostColor + m_strBackPostColor +" display: block; margin-bottom: 0.95em;\">" + ::time::get_current_time().FormatGmt( "%Y-%m-%d %H-%M-%S") +  " Copying...</span></div>";
         
         Application.http().get("http://ca2.cc/status/", str, post, headers, params);

      }
   }
   else if(m_iStep == 2)
   {
      string m_strStartTime;
      m_timeStart.FormatGmt(m_strStartTime, "%Y-%m-%d %H-%M-%S");
      {
         string str;
         gen::property_set post;
         gen::property_set headers;
         gen::property_set params;
         
         post["new_status"] = "<div style=\"display: block; " + m_strBackPostColor + "\"><h5 style=\"margin-bottom:0px; " + m_strEmpPostColor + "\">" + m_strStartTime + "</h5><span style=\"" + m_strStdPostColor + m_strBackPostColor +" display: block; margin-bottom: 0.95em;\">" + ::time::get_current_time().FormatGmt( "%Y-%m-%d %H-%M-%S") +  " Compressing...</span></div>";
         
         Application.http().get("http://ca2.cc/status/", str, post, headers, params);

      }
      compress();
      {
         string str;
         gen::property_set post;
         gen::property_set headers;
         gen::property_set params;
         
         post["new_status"] = "<div style=\"display: block; " + m_strBackPostColor + "\"><h5 style=\"margin-bottom:0px; " + m_strEmpPostColor + "\">" + m_strStartTime + "</h5><span style=\"" + m_strStdPostColor + m_strBackPostColor +" display: block; margin-bottom: 0.95em;\">" + ::time::get_current_time().FormatGmt( "%Y-%m-%d %H-%M-%S") +  " Resources...</span></div>";
         
         Application.http().get("http://ca2.cc/status/", str, post, headers, params);

      }
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
      if(!release_crxca2("x86"))
      {
         return 1;
      }
      /*if(!release_crxca2("x64"))
      {
         return 1;
      }*/
      System.dir().mk("C:\\home\\ccvotagus\\ca2_spa\\stage\\app\\");
      Application.file().put_contents("C:\\home\\ccvotagus\\ca2_spa\\stage\\app\\build.txt", m_strBuild);
      Application.file().put_contents(m_strCCVrelNew + "\\app\\build.txt", m_strBuild);
      System.dir().mk(System.dir().name(m_strTagPath));
      Application.file().put_contents(m_strTagPath, m_strTag);

      {
         string str;
         gen::property_set post;
         gen::property_set headers;
         gen::property_set params;
         
         post["new_status"] = "<div style=\"display: block; " + m_strBackPostColor + "\"><h5 style=\"margin-bottom:0px; " + m_strEmpPostColor + "\">" + m_strStartTime + "</h5><span style=\"" + m_strStdPostColor + m_strBackPostColor +" display: block; margin-bottom: 0.95em;\">" + ::time::get_current_time().FormatGmt( "%Y-%m-%d %H-%M-%S") +  " Packaging...</span></div>";
         
         Application.http().get("http://ca2.cc/status/", str, post, headers, params);

      }

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


      {
         string str;
         gen::property_set post;
         gen::property_set headers;
         gen::property_set params;
         
         post["new_status"] = "<div style=\"display: block; " + m_strBackPostColor + "\"><h5 style=\"margin-bottom:0px; " + m_strEmpPostColor + "\">" + m_strStartTime + "</h5><span style=\"" + m_strStdPostColor + m_strBackPostColor +" display: block; margin-bottom: 0.95em;\">" + ::time::get_current_time().FormatGmt( "%Y-%m-%d %H-%M-%S") +  " Releasing...</span></div>";
         
         Application.http().get("http://ca2.cc/status/", str, post, headers, params);

      }

      //Application.http().get("http://fontopus.com/update_plugins?authnone");

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
      
      string strEndTime;
      m_timeEnd.FormatGmt(strEndTime, "%Y-%m-%d %H-%M-%S");
      add_status("Build started at " + m_strStartTime);
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

      string strCmd = "\"" + m_strSignTool + "\" sign /f \"" + m_strSpc + "\" /p " + m_strSignPass + " \"" + strSrcFile + "\"";
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
   single_lock sl(&m_mutexCompress, TRUE);
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
   sl.unlock();

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
      array_ptr_alloc < manual_reset_event > eventa;
      eventa.set_size(uiProcessorCount);
      
      for(UINT ui = 0; ui < uiProcessorCount; ui++)
      {
         compress_thread * pthread = new compress_thread(this, eventa.ptr_at(ui));
         threada.add(pthread);
         pthread->m_dwThreadAffinityMask = 1 << ui;
         pthread->m_bAutoDelete = FALSE;
         pthread->m_p->m_bAutoDelete = FALSE;
         pthread->Begin();
      }
      sync_object_ptra syncobjectptra(eventa.m_ptra.get_data(), eventa.get_count());
      multi_lock ml(syncobjectptra);
      ml.lock();
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
   single_lock sl(&m_mutexCompress, TRUE);
   if(m_straCompress.get_size() <= 0)
      return false;
   string strNext = m_straCompress[0];
   m_straCompress.remove_at(0);
   sl.unlock();
   compress(strNext);
   return true;
}


production_class::compress_thread::compress_thread(production_class * pproduction, manual_reset_event * peventFinished) :
   ca(pproduction->get_app()),
   thread(pproduction->get_app()),
   m_pevFinished(peventFinished)
{
   m_pevFinished->ResetEvent();
   m_pproduction = pproduction;
}

int production_class::compress_thread::run()
{
   SetThreadAffinityMask(::GetCurrentThread(), m_dwThreadAffinityMask);
   SetThreadPriority(THREAD_PRIORITY_HIGHEST);
   while(m_pproduction->compress_next())
   {
   }
   m_pevFinished->SetEvent();
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


   if(!commit_source("app"))
      return false;

   if(!commit_source("app-veriwell"))
      return false;

   if(!commit_source("app-frontpage"))
      return false;

   if(!commit_source("app-sysutils"))
      return false;

	return true;
}

bool production_class::commit_source(const char * psz)
{
   string strStatus;
   strStatus = unitext("Commit ") + psz;
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
   System.dir().path(strBase, psz));
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
      str.Format("%d: Commit for new Build and new Release : %s ...", i, psz);
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
   Application.file().put_contents(
      strIndex,
      strContents);

   m_strIndexMd5 = System.file36().md5(strIndex);

   strBz = System.dir().path(m_strCCVotagus, strRelative) + ".bz"; 
   ::DeleteFileW(gen::international::utf8_to_unicode(strBz));
   compress(strRelative);

   string strRelativeMd5 = "app\\stage\\metastage\\index-" + m_strFormatBuild + ".md5";
   strMd5 =  System.dir().path(m_strVrel, strRelativeMd5);
   Application.file().put_contents(strMd5 , m_strIndexMd5);

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
   Application.file().put_contents(
      System.dir().path(m_strVrel, strRelative),
      strContents);
   ::DeleteFileW(gen::international::utf8_to_unicode(
      System.dir().path(m_strCCVotagus, strRelative) + ".bz"));
   compress(strRelative);
}


/*#!/usr/bin/env python
import os, sys, re, hashlib, zipfile, base64, M2Crypto
 
def signDir(source_dir, key_file, output_file):
  source_dir = os.path.abspath(source_dir)
 
  # Build file list
  filelist = []
  for dirpath, dirs, files in os.walk(source_dir):
    for file in files:
      abspath = os.path.join(dirpath, file)
      relpath = os.path.relpath(abspath, source_dir).replace('\\', '/')
      handle = open(abspath, 'rb')
      filelist.append((abspath, relpath, handle.read()))
      handle.close()
 
  # Generate manifest.mf and zigbert.sf data
  manifest_sections = []
  signature_sections = []
  def digest(data):
    md5 = hashlib.md5()
    md5.update(data)
    sha1 = hashlib.sha1()
    sha1.update(data)
    return 'Digest-Algorithms: MD5 SHA1\nMD5-Digest: %s\nSHA1-Digest: %s\n' % \
           (base64.b64encode(md5.digest()), base64.b64encode(sha1.digest()))
  def section(manifest, signature):
    manifest_sections.append(manifest)
    signature_sections.append(signature + digest(manifest))
  section('Manifest-Version: 1.0\n', 'Signature-Version: 1.0\n')
  for filepath, relpath, data in filelist:
    section('Name: %s\n%s' % (relpath, digest(data)), 'Name: %s\n' % relpath)
  manifest = '\n'.join(manifest_sections)
  signature = '\n'.join(signature_sections)
 
  # Generate zigbert.rsa (detached zigbert.sf signature)
  handle = open(key_file, 'rb')
  key_data = handle.read()
  handle.close()
  certstack = M2Crypto.X509.X509_Stack()
  first = True
  certificates = re.finditer(r'-----BEGIN CERTIFICATE-----.*?-----END CERTIFICATE-----', key_data, re.S)
  # Ignore first certificate, we will sign with this one. Rest of them needs to
  # be added to the stack manually however.
  certificates.next()
  for match in certificates:
    certstack.push(M2Crypto.X509.load_cert_string(match.group(0)))
 
  mime = M2Crypto.SMIME.SMIME()
  mime.load_key(key_file)
  mime.set_x509_stack(certstack)
  pkcs7 = mime.sign(M2Crypto.BIO.MemoryBuffer(signature),
                    M2Crypto.SMIME.PKCS7_DETACHED | M2Crypto.SMIME.PKCS7_BINARY)
  pkcs7_buffer = M2Crypto.BIO.MemoryBuffer()
  pkcs7.write_der(pkcs7_buffer)
 
  # Write everything into a ZIP file, with zigbert.rsa as first file
  zip = zipfile.ZipFile(output_file, 'w', zipfile.ZIP_DEFLATED)
  zip.writestr('META-INF/zigbert.rsa', pkcs7_buffer.read())
  zip.writestr('META-INF/zigbert.sf', signature)
  zip.writestr('META-INF/manifest.mf', manifest)
  for filepath, relpath, data in filelist:
    zip.writestr(relpath, data)
 
if __name__ == '__main__':
  if len(sys.argv) < 4:
    print 'Usage: %s source_dir key_file output_file' % sys.argv[0]
    sys.exit(2)
  signDir(sys.argv[1], sys.argv[2], sys.argv[3])*/











/*  def digest(data):
    md5 = hashlib.md5()
    md5.update(data)
    sha1 = hashlib.sha1()
    sha1.update(data)
    return 'Digest-Algorithms: MD5 SHA1\nMD5-Digest: %s\nSHA1-Digest: %s\n' % \
           (base64.b64encode(md5.digest()), base64.b64encode(sha1.digest()))
           */
string production_class::xpi_digest(primitive::memory & mem)
{
   primitive::memory memMd5;
   primitive::memory memSha1;
   System.hex_to_memory(memMd5, System.crypt().md5(mem));
   System.hex_to_memory(memSha1, System.crypt().sha1(mem));
   return string("Digest-Algorithms: MD5 SHA1\n") +
                 "MD5-Digest: " + System.base64().encode(memMd5) +  "\n" +
                 "SHA1-Digest: " + System.base64().encode(memSha1) + "\n";
           
}


void production_class::xpi_section(const char * pszManifest, const char * pszSignature)
{
   m_straManifest.add(pszManifest);
   primitive::memory memManifest(pszManifest);
   m_straSignature.add(string(pszSignature) + xpi_digest(memManifest));
}

void production_class::add_path(const char * pszDir, const char * pszRelative)
{
   m_straRelative.add(pszRelative);
   m_straPath.add(System.dir().path(pszDir, pszRelative));
}

void production_class::xpi_sign_dir(const char * pszDir)
{

   m_straRelative.remove_all();
   m_straPath.remove_all();

   add_path(pszDir, "META-INF\\zigbert.rsa");
   add_path(pszDir, "install.rdf");
   add_path(pszDir, "chrome.manifest");
   add_path(pszDir, "plugins\\installer.exe");
   add_path(pszDir, "plugins\\npca2.dll");
   add_path(pszDir, "skin\\classic\\ca2-5c-32.png");
   add_path(pszDir, "META-INF\\manifest.mf");
   add_path(pszDir, "META-INF\\zigbert.sf");

   string strSignerPath = "C:\\cecyn1.at.hotmail.com\\ccvotagus\\cgcl\\npca2signer.pem";
   string strKeyPath = "C:\\cecyn1.at.hotmail.com\\ccvotagus\\cgcl\\npca2key.pem";
   string strOthersPath = "C:\\cecyn1.at.hotmail.com\\ccvotagus\\cgcl\\npca2others.pem";
 
   
   // Generate manifest.mf and zigbert.sf data

   m_straManifest.remove_all();
   m_straSignature.remove_all();

   string strComment = "Created-By: ca2 production "+ m_strBuild + "\nComments: PLEASE DO NOT EDIT THIS FILE. YOU WILL BREAK IT.\n";


   xpi_section("Manifest-Version: 1.0\n" + strComment, "Signature-Version: 1.0\n" + strComment);
   
   primitive::memory mem;

   for(int i = 0; i < m_straPath.get_count(); i++)
   {
      string strRelative = m_straRelative[i];
      if(gen::str::begins_ci(strRelative, "META-INF\\"))
         continue;
      strRelative.replace("\\", "/");
      mem.allocate(0);
      Application.file().as_memory(m_straPath[i], mem);
      xpi_section("Name: " + strRelative + "\n" + xpi_digest(mem), "Name: " + strRelative + "\n");
   }


   string strManifest = m_straManifest.implode("\n");
   string strSignature = m_straSignature.implode("\n");

   Application.file().put_contents(System.dir().path(pszDir, "META-INF/manifest.mf"), strManifest);
   Application.file().put_contents(System.dir().path(pszDir, "META-INF/zigbert.sf"), strSignature);
  

   X509 * signer = NULL;
   {
      string strSigner = Application.file().as_string(strSignerPath);
      BIO * pbio = BIO_new_mem_buf((void *) (LPCTSTR) strSigner, strSigner.get_length());
      //signer = PEM_read_bio_X509_AUX(pbio, NULL, 0, NULL);
      signer = PEM_read_bio_X509(pbio, NULL, 0, NULL);
      BIO_free(pbio);
   }

   EVP_PKEY * pkey;
   {
      string strKey = Application.file().as_string(strKeyPath);
      BIO * pbio = BIO_new_mem_buf((void *) (LPCTSTR) strKey, strKey.get_length());
      pkey = PEM_read_bio_PrivateKey(pbio, NULL, NULL, NULL);
      BIO_free(pbio);
   }
   

   STACK * pstack509 = NULL;
   {
      string strOthers = Application.file().as_string(strOthersPath);
      raw_array < X509 * > xptra;
      int iStart = 0;
      int iFind;
      string strEnd = "-----END CERTIFICATE-----";
      string strCertificate;
      int iEndLen = strEnd.get_length();
      int iCount = 0;
      while((iFind = strOthers.find("-----BEGIN CERTIFICATE-----", iStart)) >= 0)
      {
         int iEnd = strOthers.find(strEnd, iFind);
         if(iEnd < 0)
            break;
         strCertificate = strOthers.Mid(iFind, iEnd + iEndLen - iFind);
         X509 * x;
         BIO * pbio = BIO_new(BIO_s_mem());
         BIO_puts(pbio, strCertificate);
         //x = PEM_read_bio_X509_AUX(pbio, NULL, 0, NULL);
         x = PEM_read_bio_X509(pbio, NULL, 0, NULL);
         BIO_free(pbio);
         if(x == NULL)
         {
            return;
         }
         xptra.add(x);
         iCount++;
         iStart = iEnd + iEndLen;
      }
      pstack509 = sk_X509_new_null();

      for(int i = 0; i < xptra.get_count(); i++)
      {
         sk_X509_push(pstack509, xptra[i]);
      }
   }

   BIO * input = BIO_new_mem_buf((void *) (LPCTSTR) strSignature, strSignature.get_length());

   PKCS7 * pkcs7 = PKCS7_sign(signer, pkey, pstack509, input, PKCS7_BINARY | PKCS7_DETACHED);

   BIO_free(input);
   sk_X509_free(pstack509);
   EVP_PKEY_free(pkey);
   X509_free(signer);

   BIO * output = BIO_new(BIO_s_mem());

   i2d_PKCS7_bio(output, pkcs7);

   char * pchData = NULL;
   long count = BIO_get_mem_data(output, &pchData);

   Application.file().put_contents(System.dir().path(pszDir, "META-INF/zigbert.rsa"), pchData, count);

   BIO_free(output);
   PKCS7_free(pkcs7);

}



bool production_class::release_npca2(const char * pszPlatform)
{
   
   string strPlatform(pszPlatform);

   string strDir;
   strDir = System.dir().path(m_strBase, "time/npca2/" + strPlatform);


   string strNpca2Version;

   strNpca2Version.Format(
      "%d.%d%02d.%d%02d.%d",
      atoi(m_strFormatBuild.Mid(0, 4)),
      atoi(m_strFormatBuild.Mid(5, 2)),
      atoi(m_strFormatBuild.Mid(8, 2)),
      atoi(m_strFormatBuild.Mid(11, 2)),
      atoi(m_strFormatBuild.Mid(14, 2)),
      atoi(m_strFormatBuild.Mid(17, 2))
      );
   
      string strVersionUrl;
   if(m_eversion == version_basis)
   {
      strVersionUrl = "/basis";
   }

   string strChromeManifest = Application.file().as_string(System.dir().path(m_strBase, "app/stage/app/matter/npca2/chrome.manifest"));
   strChromeManifest.replace("%BUILD%", strNpca2Version);
   strChromeManifest.replace("%PLATFORM%", strPlatform);
   strChromeManifest.replace("%VERSION%", strVersionUrl);
   Application.file().put_contents(System.dir().path(strDir, "npca2", "chrome.manifest"), strChromeManifest);

   string strIcon;
   if(m_eversion == version_basis)
   {
      strIcon = Application.dir().matter("fluidbasis-5c-32.png");
   }
   else
   {
      strIcon = Application.dir().matter("ca2-5c-32.png");
   }
   System.file().copy(System.dir().path(strDir, "npca2/skin/classic", "ca2-5c-32.png"), strIcon);

   string strInstall = Application.file().as_string(System.dir().path(m_strBase, "app/stage/app/matter/npca2/install.rdf"));
   strInstall.replace("%BUILD%", strNpca2Version);
   strInstall.replace("%PLATFORM%", strPlatform);
   strInstall.replace("%VERSION%", strVersionUrl);
   Application.file().put_contents(System.dir().path(strDir, "npca2", "install.rdf"), strInstall);


   string strWindows = Application.file().as_string(System.dir().path(m_strBase, "app/stage/app/matter/npca2/windows.rdf"));
   strWindows.replace("%BUILD%", strNpca2Version);
   strWindows.replace("%PLATFORM%", strPlatform);
   strWindows.replace("%VERSION%", strVersionUrl);
   Application.file().put_contents(System.dir().path(strDir, "windows.rdf"), strWindows);
   

   add_status("Signing npca2.dll ...");
   string strFile = System.dir().path(strDir, "npca2/plugins", "npca2.dll");
   System.file().copy(strFile, System.dir().path(m_strVrel, "stage/" + strPlatform + "/npca2.dll"));
   string strCmd = "\"" + m_strSignTool + "\" sign /f \"" + m_strSpc + "\" /p " + m_strSignPass + " \"" + strFile + "\"";
   System.process().synch(strCmd);

   

   add_status("Signing installer.exe ...");
   strFile = System.dir().path(strDir, "npca2/plugins", "installer.exe");
   System.file().copy(strFile, System.dir().path(m_strVrel, "stage/" + strPlatform + "/installer.exe"));
   strCmd = "\"" + m_strSignTool + "\" sign /f \"" + m_strSpc + "\" /p " + m_strSignPass + " \"" + strFile + "\"";
   System.process().synch(strCmd);

   add_status("Signing code ...");

   System.file().del(System.dir().path(strDir, "npca2.xpi"));

   create_xpi(pszPlatform, false);
   string strVersion;
   if(m_eversion == version_basis)
   {
      strVersion = "\\basis";
   }


   System.file().copy("C:\\netnode\\net\\netseed\\ds\\ca2\\front\\cc\\ca2\\_std\\_std\\xpi\\"+strPlatform+strVersion+"\\npca2.xpi", System.dir().path(strDir, "npca2.xpi"));
   System.file().copy("C:\\netnode\\net\\netseed\\ds\\ca2\\front\\cc\\ca2\\_std\\_std\\rdf\\"+strPlatform+strVersion+"\\windows.rdf", System.dir().path(strDir, "windows.rdf"));

   return true;
}

bool production_class::create_xpi(const char * pszPlatform, bool bSigned)
{

   string strPlatform(pszPlatform);

   string strDir;
   strDir = System.dir().path(m_strBase, "time/npca2/" + strPlatform);

   System.dir().rm(System.dir().path(strDir, "npca2/META-INF"));


   if(bSigned)
   {
      return create_signed_xpi(pszPlatform);
   }
   else
   {
      return create_unsigned_xpi(pszPlatform);
   }

}

bool production_class::create_signed_xpi(const char * pszPlatform)
{

   string strPlatform(pszPlatform);

   string strDir;
   strDir = System.dir().path(m_strBase, "time/npca2/" + strPlatform);

   add_status("Signing extension ...");

   xpi_sign_dir(System.dir().path(strDir, "npca2/"));

   string str;

   string strXpi = System.dir().path(strDir, "npca2.xpi") ;

   string strPath;

   gen::process process;

   DWORD dwExitCode;

   for(int i = 0; i < m_straRelative.get_count(); i++)
   {
      strPath = "zip \"" + strXpi + "\" \"" + m_straRelative[i] + "\"";
      if(!process.create_child_process(strPath, false,  System.dir().path(strDir, "npca2/")))
      {
         DWORD dw = GetLastError();
         string str;
         str.Format("Error compressing npca2: %d", dw);
         add_status(str);
         return 0;   
      }
      while(!process.has_exited(&dwExitCode))
      {
         Sleep(5000);
         str.Format("%d Compressing npca2 ...", i);
         add_status(str);
      }
   }
   return true;
}

bool production_class::create_unsigned_xpi(const char * pszPlatform)
{

   string strPlatform(pszPlatform);

   string strDir;
   strDir = System.dir().path(m_strBase, "time/npca2/" + strPlatform);

   add_status("Creating unsigned extension ...");
   string str;
   DWORD dwExitCode;
   string strXpi = System.dir().path(strDir, "npca2.xpi") ;
   gen::process process;
   string strPath = "zip -r -D \""+strXpi+"\" * ";
   if(!process.create_child_process(strPath, false,  System.dir().path(strDir, "npca2/")))
   {
      DWORD dw = GetLastError();
      string str;
      str.Format("Error compressing npca2: %d", dw);
      add_status(str);
      return 0;   
   }
   int i = 1;
   while(!process.has_exited(&dwExitCode))
   {
      Sleep(5000);
      str.Format("%d Compressing npca2 ...", i);
      add_status(str);
      i++;
   }

   return true;

}

bool production_class::release_iexca2(const char * pszPlatform)
{

   string strStatus;
   strStatus.Format("releasing iexca2");
   add_status(strStatus);

   string strPlatform(pszPlatform);


   System.dir().mk(System.dir().path(m_strBase, "time\\iexca2\\"+strPlatform));

   DWORD dwExitCode;
   string str;
   gen::process process;
   string strPath;
   strPath = System.dir().path(m_strBase, "app\\stage\\app\\matter\\makecabx86.bat");
   if(!process.create_child_process(strPath, false, System.dir().name(strPath)))
   {
      DWORD dw = GetLastError();
      string str;
      str.Format("Error creating iexca2.cab: %d", dw);
      add_status(str);
      return 0;   
   }
   int i;
   i = 1;
   while(!process.has_exited(&dwExitCode))
   {
      Sleep(5000);
      str.Format("%d Creating iexca2.cab ...", i);
      add_status(str);
      i++;
   }

   string strVersion;
   if(m_eversion == version_basis)
   {
      strVersion = "\\basis";
   }

   System.file().copy("C:\\netnode\\net\\netseed\\ds\\ca2\\front\\cc\\ca2\\_std\\_std\\cab\\"+strPlatform+ strVersion+ "\\iexca2.cab", System.dir().path(m_strBase, "time\\iexca2\\"+strPlatform+"\\iexca2.cab"));

   return true;

}

bool production_class::release_crxca2(const char * pszPlatform)
{
   
   string strPlatform(pszPlatform);

   string strDir;
   strDir = System.dir().path(m_strBase, "time/crxca2/" + strPlatform + "/crxca2");

   string strCrxca2Version;

   strCrxca2Version.Format(
      "%d.%d%02d.%d%02d.%d",
      atoi(m_strFormatBuild.Mid(0, 4)),
      atoi(m_strFormatBuild.Mid(5, 2)),
      atoi(m_strFormatBuild.Mid(8, 2)),
      atoi(m_strFormatBuild.Mid(11, 2)),
      atoi(m_strFormatBuild.Mid(14, 2)),
      atoi(m_strFormatBuild.Mid(17, 2))
      );

   string strManifestJson = Application.file().as_string(System.dir().path(m_strBase, "app/stage/app/matter/crxca2/manifest.json"));
   strManifestJson.replace("%BUILD%", strCrxca2Version);
   strManifestJson.replace("%PLATFORM%", strPlatform);
   Application.file().put_contents(System.dir().path(strDir,  "manifest.json"), strManifestJson);

   string strIcon;
   if(m_eversion == version_basis)
   {
      strIcon = Application.dir().matter("fluidbasis-5c-32.png");
   }
   else
   {
      strIcon = Application.dir().matter("ca2-5c-32.png");
   }
   System.file().copy(System.dir().path(strDir, "ca2-5c-32.png"), strIcon);

   add_status("Signing npca2.dll ...");
   string strFile = System.dir().path(strDir, "npca2.dll");
   System.file().copy(strFile, System.dir().path(m_strVrel, "stage/" + strPlatform + "/npca2.dll"));
   string strCmd = "\"" + m_strSignTool + "\" sign /f \"" + m_strSpc + "\" /p " + m_strSignPass + " \"" + strFile + "\"";
   System.process().synch(strCmd);

   add_status("Signing installer.exe ...");
   strFile = System.dir().path(strDir, "installer.exe");
   System.file().copy(strFile, System.dir().path(m_strVrel, "stage/" + strPlatform + "/installer.exe"));
   strCmd = "\"" + m_strSignTool + "\" sign /f \"" + m_strSpc + "\" /p " + m_strSignPass + " \"" + strFile + "\"";
   System.process().synch(strCmd);

   add_status("Creating crxca2.crx ...");
   strCmd = "C:\\Users\\production\\AppData\\Local\\Google\\Chrome\\Application\\chrome.exe --no-message-box --pack-extension=\"" +strDir + "\" --pack-extension-key=\"C:\\cecyn1.at.hotmail.com\\ccvotagus\\cgcl\\npca2key.pem\"";
   System.process().synch(strCmd);

   string strVersion;
   if(m_eversion == version_basis)
   {
      strVersion = "\\basis";
   }


   System.file().copy("C:\\netnode\\net\\netseed\\ds\\ca2\\front\\cc\\ca2\\_std\\_std\\crx\\"+strPlatform+strVersion+"\\crxca2.crx", System.dir().path(System.dir().name(strDir), "crxca2.crx"));

   return true;
}


void production_class::add_status(const char * psz)
{
   single_lock sl(&m_mutexStatus, TRUE);
   m_straStatus.add(psz);
   m_pview->SendMessage(WM_USER, 1);
}

void production_class::change_status(const char * psz)
{
   single_lock sl(&m_mutexStatus, TRUE);
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
   string str;
   gen::property_set post(get_app());
   gen::property_set headers(get_app());
   gen::property_set set(get_app());
   set["disable_ca2_sessid"] = true;
   Application.http().get(m_strRelease, str, post, headers, set);
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
      string strEndTime;
      m_timeEnd.FormatGmt(strEndTime, "%Y-%m-%d %H-%M-%S");
      if(m_eversion == version_basis)
      {
         post["new_status"] = "<div style=\"display: block; background-color: #FFE0FF; \"><h2 style=\"margin-bottom:0px; color: #FF55CC;\">" + m_strBuild + "</h2><span style=\"color: #882255; display: block; margin-bottom: 1.5em;\">"+m_strBuildTook+" and finished at "+ strEndTime + "<br>New release of <a href=\"http://fluidbasis.com/\" class=\"fluidbasis\" >fluidbasis</a> applications labeled " + m_strBuild + " is ready for download through compatible gateways.<br>Check <a href=\"http://symberg.com/\" class=\"fluidbasis\" >symberg.com</a> or <a href=\"http://hardaxs.com/\" class=\"fluidbasis\" >hardaxs.com</a> for simple gateway implementations.</span></div>";
      }
      else
      {
         post["new_status"] = "<div style=\"display: block; background-color: #E0FFCC; \"><h2 style=\"margin-bottom:0px; color: #55CCAA;\">" + m_strBuild + "</h2><span style=\"color: #228855; display: block; margin-bottom: 1.5em;\">"+m_strBuildTook+" and finished at "+ strEndTime + "<br>New release of <a href=\"http://ca2.cc/\">ca2</a> applications labeled " + m_strBuild + " is ready for download through compatible gateways.<br>Check <a href=\"http://bergedge.com/\">bergedge.com</a> or <a href=\"http://veriaxs.com/\">veriaxs.com</a> for simple gateway implementations.</span></div";
      }
      string str;
      Application.http().get("http://ca2.cc/status/", str, post, headers, params);
      string strTwit;
      strTwit = "ca2twit-lib : new build " + m_strBuild + " : http://ca2.cc/status/?email=production%40ca2.cc";
      twitter_auth();
      twitter_twit(strTwit);
      m_bReleased = true;
      defer_quit();
   }
   else if(m_iRelease > 0)
   {
      string strStatus;
      strStatus.Format("There are %d releases in command list!!", m_iRelease);
      add_status(strStatus);
   }
}


bool production_class::twitter_auth()
{
   ::ca4::twit twitterObj(get_app());
   string tmpStr( "" );
   string replyMsg( "" );

    /* OAuth flow begins */
    /* Step 0: Set OAuth related params. These are got by registering your app at twitter.com */
   if(m_eversion == version_basis)
   {
    twitterObj.get_oauth().setConsumerKey(string( "mKYvWA6cZkUEUwjoygUuVw" ) );
    twitterObj.get_oauth().setConsumerSecret(string( "JwtNLBLyXlPvGLqKA4c8w4XH0PPLmkoVzm0TOocvSyY" ) );
   }
   else
   {
    twitterObj.get_oauth().setConsumerKey(string( "K0pfcpC7Ua1ygWiMWHHSQ" ) );
    twitterObj.get_oauth().setConsumerSecret(string( "LmgKZmcM5NExmp8cPisHvtuYGxU0KMKH61wNYc0Pn8Q" ) );
   }

    string strPathKey = Application.dir().userappdata("twitterClient_token_key.txt");
    string strPathSecret = Application.dir().userappdata("twitterClient_token_secret.txt");
    /* Step 1: Check if we alredy have OAuth access token from a previous run */
//    char szKey[1024];
    string myOAuthAccessTokenKey = Application.file().as_string(strPathKey);
    string myOAuthAccessTokenSecret = Application.file().as_string(strPathSecret);

    if( myOAuthAccessTokenKey.has_char() && myOAuthAccessTokenSecret.has_char() )
    {
        /* If we already have these keys, then no need to go through auth again */
        twitterObj.get_oauth().setOAuthTokenKey( myOAuthAccessTokenKey );
        twitterObj.get_oauth().setOAuthTokenSecret( myOAuthAccessTokenSecret );
    }
    else
    {
        /* Step 2: Get request token key and secret */
        twitterObj.oAuthRequestToken( tmpStr );

        /* Step 3: Ask user to visit web link and get PIN */
        string szOAuthVerifierPin;

        ::twitter::authorization authapp(get_app(), tmpStr, "twitter\\authorization.xhtml", true);
        szOAuthVerifierPin = authapp.get_pin();

        tmpStr = szOAuthVerifierPin;
        twitterObj.get_oauth().setOAuthPin( tmpStr );

        /* Step 4: Exchange request token with access token */
        twitterObj.oAuthAccessToken();

        /* Step 5: Now, save this access token key and secret for future use without PIN */
        twitterObj.get_oauth().getOAuthTokenKey( myOAuthAccessTokenKey );
        twitterObj.get_oauth().getOAuthTokenSecret( myOAuthAccessTokenSecret );

        /* Step 6: Save these keys in a file or wherever */

        Application.file().put_contents(strPathKey, myOAuthAccessTokenKey);
        Application.file().put_contents(strPathSecret, myOAuthAccessTokenSecret);

    }

    return true;
}
string production_class::twitter_twit(const char * pszMessage)
{

      ::ca4::twit twitterObj(get_app());
   string tmpStr( "" );
   string replyMsg( "" );

    /* OAuth flow begins */
    /* Step 0: Set OAuth related params. These are got by registering your app at twitter.com */
   if(m_eversion == version_basis)
   {
    twitterObj.get_oauth().setConsumerKey(string( "mKYvWA6cZkUEUwjoygUuVw" ) );
    twitterObj.get_oauth().setConsumerSecret(string( "JwtNLBLyXlPvGLqKA4c8w4XH0PPLmkoVzm0TOocvSyY" ) );
   }
   else
   {
    twitterObj.get_oauth().setConsumerKey(string( "K0pfcpC7Ua1ygWiMWHHSQ" ) );
    twitterObj.get_oauth().setConsumerSecret(string( "LmgKZmcM5NExmp8cPisHvtuYGxU0KMKH61wNYc0Pn8Q" ) );
   }

    string strPathKey = Application.dir().userappdata("twitterClient_token_key.txt");
    string strPathSecret = Application.dir().userappdata("twitterClient_token_secret.txt");
    /* Step 1: Check if we alredy have OAuth access token from a previous run */
//    char szKey[1024];
    string myOAuthAccessTokenKey = Application.file().as_string(strPathKey);
    string myOAuthAccessTokenSecret = Application.file().as_string(strPathSecret);

    if( myOAuthAccessTokenKey.has_char() && myOAuthAccessTokenSecret.has_char() )
    {
        /* If we already have these keys, then no need to go through auth again */
        twitterObj.get_oauth().setOAuthTokenKey( myOAuthAccessTokenKey );
        twitterObj.get_oauth().setOAuthTokenSecret( myOAuthAccessTokenSecret );
    }
    else
    {
       return "failed";
    }

    /* OAuth flow ends */

   // /* Set twitter username and password */
    //twitterObj.setTwitterUsername( userName );
    //twitterObj.setTwitterPassword( passWord );

    /* Post a new status message */
    int iRetry = 0;
Retry2:
    tmpStr = pszMessage;
    replyMsg = "";
    if( twitterObj.statusUpdate( tmpStr ) )
    {
        replyMsg=twitterObj.get_response(  );
        //printf( "\ntwitterClient:: twitCurl::statusUpdate web response:\n%s\n", replyMsg.c_str() );
    }
    else
    {
       if(iRetry >= 3)
       {
          replyMsg ="failed";
       }
       else
       {
         goto retry1;
       }
         
        //printf( "\ntwitterClient:: twitCurl::statusUpdate error:\n%s\n", replyMsg.c_str() );
    }
    return replyMsg;
retry1:
    System.file().del(strPathKey);
    System.file().del(strPathSecret);
    twitter_auth();
    iRetry++;
    goto Retry2;

}

    /* Destroy a status message */
    /*memset( statusMsg, 0, 1024 );
    printf( "\nEnter status message id to delete: " );
    gets( statusMsg );
    tmpStr = statusMsg;
    replyMsg = "";
    if( twitterObj.statusDestroyById( tmpStr ) )
    {
        twitterObj.getLastWebResponse( replyMsg );
        printf( "\ntwitterClient:: twitCurl::statusDestroyById web response:\n%s\n", replyMsg.c_str() );
    }
    else
    {
        twitterObj.getLastCurlError( replyMsg );
        printf( "\ntwitterClient:: twitCurl::statusDestroyById error:\n%s\n", replyMsg.c_str() );
    }

    /* Get user timeline */
    /*replyMsg = "";
    printf( "\nGetting user timeline\n" );
    if( twitterObj.timelineUserGet() )
    {
        twitterObj.getLastWebResponse( replyMsg );
        printf( "\ntwitterClient:: twitCurl::timelineUserGet web response:\n%s\n", replyMsg.c_str() );
    }
    else
    {
        twitterObj.getLastCurlError( replyMsg );
        printf( "\ntwitterClient:: twitCurl::timelineUserGet error:\n%s\n", replyMsg.c_str() );
    }

    /* Get public timeline */
    /*replyMsg = "";
    printf( "\nGetting public timeline\n" );
    if( twitterObj.timelinePublicGet() )
    {
        twitterObj.getLastWebResponse( replyMsg );
        printf( "\ntwitterClient:: twitCurl::timelinePublicGet web response:\n%s\n", replyMsg.c_str() );
    }
    else
    {
        twitterObj.getLastCurlError( replyMsg );
        printf( "\ntwitterClient:: twitCurl::timelinePublicGet error:\n%s\n", replyMsg.c_str() );
    }

    /* Get friend ids */
    /*replyMsg = "";
    printf( "\nGetting friend ids\n" );
    tmpStr = "techcrunch";
    if( twitterObj.friendsIdsGet( tmpStr, false ) )
    {
        twitterObj.getLastWebResponse( replyMsg );
        printf( "\ntwitterClient:: twitCurl::friendsIdsGet web response:\n%s\n", replyMsg.c_str() );
    }
    else
    {
        twitterObj.getLastCurlError( replyMsg );
        printf( "\ntwitterClient:: twitCurl::friendsIdsGet error:\n%s\n", replyMsg.c_str() );
    }

    /* Get trends */
    /*if( twitterObj.trendsDailyGet() )
    {
        twitterObj.getLastWebResponse( replyMsg );
        printf( "\ntwitterClient:: twitCurl::trendsDailyGet web response:\n%s\n", replyMsg.c_str() );
    }
    else
    {
        twitterObj.getLastCurlError( replyMsg );
        printf( "\ntwitterClient:: twitCurl::trendsDailyGet error:\n%s\n", replyMsg.c_str() );
    }*/

    //return 0;



void production_class::build(const char * psz)
{
   
   string strApp(psz);

   add_status("Building ca2 fontopus ccvotagus " + strApp + "...");
   {
      string str;
      gen::property_set post;
      gen::property_set headers;
      gen::property_set params;
         
      post["new_status"] = "<div style=\"display: block; " + m_strBackPostColor + "\"><h5 style=\"margin-bottom:0px; " + m_strEmpPostColor + "\">" + m_strStartTime + "</h5><span style=\"" + m_strStdPostColor + m_strBackPostColor +" display: block; margin-bottom: 0.95em;\">" + ::time::get_current_time().FormatGmt( "%Y-%m-%d %H-%M-%S") +  " Building " + strApp + "...</span></div>";
         
      Application.http().get("http://ca2.cc/status/", str, post, headers, params);

   }
   gen::process process;
   string strPath;
   if(Application.m_eversion == version_basis)
   {
      strPath = System.dir().ca2(strApp + "\\stage\\app\\matter\\stage_build.bat");
   }
   else
   {
      strPath = System.dir().ca2(strApp + "\\stage\\app\\matter\\basis_build.bat");
   }
   if(!process.create_child_process(strPath, false))
   {
      DWORD dw = GetLastError();
      string str;
      str.Format("Error creating build process: %d for build of " + strApp, dw);
      add_status(str);
      return;   
   }
   int i = 1;
   DWORD dwExitCode;
   string str;
   while(!process.has_exited(&dwExitCode))
   {
      Sleep(5000);
      str.Format("%d Building ca2 fontopus ccvotagus " + strApp + "...", i);
      add_status(str);
      i++;
   }

}