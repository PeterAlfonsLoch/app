#include "StdAfx.h"
#include <math.h>




int LangFromOS();





int run_file(const char * pszFile, int nCmdShow);









#ifdef SUPORTA_MATEMATICA_AVANCADA
double g_dPi = asin_dup(1.0) * 4;
#endif


namespace spa
{

   window g_window;

} // namespace spa









/*
vsstring Login()
{
   if(stricmp_dup(g_pedit->m_str, "ca") == 0
      && stricmp_dup(g_pedit->m_pnext->m_str, "ca") == 0)
   {
      return "OK";
   }
   vsstring document;
   vsstring strPost;
   strPost = "entered_login=";
   strPost += g_pedit->m_str;
   strPost += "&entered_password=";
   strPost += g_pedit->m_pnext->m_str;
   document = ms_post("https://votagus.net/ca2api/auth", strPost);
	return document;
}
*/





/*bool Get(const vsstring& url_in,vsstring & document)
{
   bool https = !strcasecmp(url.substr(0,8), "https://");
	int port = https ? 443 : 80;
	vsstring url = url_in;
	vsstring file; // get filename at end of url
	vsstring dir; // get filename at end of url
	{
		Parse pa(url,"/");
		vsstring tmp = pa.getword();
      vsstring lastfile;
		while (tmp.size())
		{
			file = tmp;
         dir = "/" + lastfile;
         lastfile = file;
			tmp = pa.getword();
		}
	}
	SocketHandler h;
	bool complete = false;

	if (!strcasecmp(protocol,"http") || https)
	{
		HttpGetSocket s(h, host, port, dir, file);
		unsigned char *p = new unsigned char[32000]; // max doc size
		memset_dup(p, 0, 32000);
		s.SetDataPtr(p, 31999); // preserve zero at end of document
/*		if (https)
		{
			s.EnableSSL();
		}*/
/*		h.Add(&s);
		h.Select(1,0);
		while (h.GetCount())
		{
			h.Select(1,0);
		}
		complete = s.Complete();
		if (complete)
		{
			document = static_cast<vsstring>( (char *)s.GetDataPtr());
		}
		delete[] s.GetDataPtr();
	}
	else
	{
		printf_dup("Unknown protocol: '%s'\n",protocol);
	}
	if (complete)
	{
		printf_dup("%s\n", document);
	}
	return complete;
}*/
























vsstring url_query_param(int & iParam, const char * pszParam)
{
   vsstring str;
   if(iParam == 0)
   {
      iParam++;
      str = "?";
      return str + pszParam;
   }
   else
   {
      iParam++;
      str = "&";
      return str + pszParam;
   }
}














int synch_spaadmin(const char * pszCommandLine)
{

   ::spa::installer * pinstaller    = new ::spa::installer();

   pinstaller->m_bStarterStart      = true;

   pinstaller->m_bSynch             = true;

   return pinstaller->spaadmin_main(pszCommandLine);

}


int start_spaadmin(const char * pszCommandLine)
{

   ::spa::installer * pinstaller    = new ::spa::installer();

   pinstaller->m_bStarterStart      = true;

   pinstaller->m_bSynch             = false;

   return pinstaller->spaadmin_main(pszCommandLine);

}


vsstring get_installation_lock_file_path()
{
   
   vsstring strPath;

   strPath = dir::path(dir::afterca2(), "install.lock");

   return strPath;

}


void installation_file_lock(bool bLock)
{
   
   vsstring strPath;

   strPath = get_installation_lock_file_path();

   int iRetry = 84;

   if(bLock)
   {
      while(!file_exists_dup(strPath) && iRetry > 0)
      {
         file_put_contents_dup(strPath, "installing...");
         Sleep(584);
         iRetry--;
      }
   }
   else
   {
      while(file_exists_dup(strPath) && iRetry > 0)
      {
#ifdef WINDOWS
         ::DeleteFile(strPath);
#else
         unlink(strPath);
#endif
         Sleep(584);
         iRetry--;
      }
   }

}

bool is_installation_lock_file_locked()
{
 
   vsstring strPath;

   strPath = get_installation_lock_file_path();
   
   if(file_exists_dup(strPath))
      return true;

   return false;

}


installation_lock_file_lock::installation_lock_file_lock()
{
   installation_file_lock(true);
}

installation_lock_file_lock::~installation_lock_file_lock()
{
   installation_file_lock(false);
}

