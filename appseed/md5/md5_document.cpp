#include "StdAfx.h"
#include <openssl/md5.h>

namespace md5
{

   document::document(::ca::application * papp) :
      ca(papp),
      ::ca::data_container(papp),
      ::document(papp),
      ::userbase::document(papp),
      m_thread(papp)
   {
      m_thread.m_strStatus = "no file opened";
   }

   BOOL document::on_new_document()
   {
	   if (!::userbase::document::on_new_document())
		   return FALSE;

      m_thread.m_strStatus = "no file opened";

      update_all_views(NULL, 0);

	   return TRUE;
   }

   document::~document()
   {
   }


#ifdef _DEBUG
   void document::assert_valid() const
   {
      ::userbase::document::assert_valid();
   }

   void document::dump(dump_context& dc) const
   {
	   ::userbase::document::dump(dc);
   }
#endif //_DEBUG


   void document::data_on_after_change(gen::signal_object * pobj)
   {
   }

   bool document::on_open_document(var lpszPathName)
   {
      m_strCheckMd5.Empty();
      m_thread.m_strFile.Empty();

      string strFile(lpszPathName);
      if(gen::str::ends_eat_ci(strFile, ".md5"))
      {
         m_strCheckMd5 = Application.file().as_string(lpszPathName);
         m_thread.m_strFile = strFile;
         if(!System.file().exists(strFile))
         {
            stringa straPath;
            stringa straTitle;
            System.dir().ls_pattern(System.dir().name(strFile), System.file().name_(strFile) + ".*", &straPath, &straTitle);
            for(int i = 0; i < straPath.get_size(); i++)
            {
               if(gen::str::ends_ci(straPath[i], ".md5"))
               {
                  continue;
               }
               else
               {
                  // TODO: do md5 of all that matches.
                  // gets the first not md5
                  m_thread.m_strFile = straPath[i];
                  break;
               }
            }
         }
      }
      else
      {
         m_thread.m_strFile = strFile;
         if(System.file().exists(strFile + ".md5"))
         {
            m_strCheckMd5 = Application.file().as_string(strFile + ".md5");
         }
         else
         {
            strsize iFind = 0;
            while((iFind = strFile.reverse_find('.', iFind - 1)) >= 0)
            {
               if(System.file().exists(strFile.Left(iFind) + ".md5"))
               {
                  m_strCheckMd5 = Application.file().as_string(strFile.Left(iFind) + ".md5");
                  break;
               }
            }
         }

      }


      if(false)
      {
         Application.simple_message_box(NULL, "file " + m_thread.m_strFile + " is not a md5 file");
         m_thread.m_strFile.Empty();
         return false;
      }

      

      //string strFileMd5 = System.file().replace_extension(m_thread.m_strFile, "md5");

      

      if(!System.file().exists(m_thread.m_strFile))
      {
         Application.simple_message_box(NULL, "could not open file " + m_thread.m_strFile);
         return FALSE;
      }

      m_thread.Begin();

      return TRUE;
   }


   document::thread::thread(::ca::application * papp) :
      ca(papp),
      radix::thread(papp),
      simple_thread(papp)
   {
      m_dProgress = 0.0;
      m_bReady = false;
   }

   int document::thread::run()
   {
      ex1::filesp spfile;
      
      spfile(Application.get_file(m_strFile, ::ex1::file::type_binary | ::ex1::file::mode_read));

      if(spfile.is_null())
      {
         m_strStatus = "could not open file";
         return 0;
      }
      __int64 iLength = spfile->get_length();
      int iBufSize = 1024 * 256;
      unsigned char * buf = new unsigned char[iBufSize];
      MD5_CTX ctx;
      MD5_Init(&ctx);
      int iRead;
      __int64 iReadTotal = 0;
      spfile->seek_to_begin();
      while((iRead = spfile->read(buf, iBufSize)) > 0)
      {
         MD5_Update(&ctx, buf, iRead);
         iReadTotal += iRead;
         m_dProgress = (double) iReadTotal / (double) iLength;
      }
      MD5_Final(buf,&ctx);
      string str;
      string strFormat;
      for(int i = 0; i < 16; i++)
      {
         strFormat.Format("%02x", buf[i]);
         str += strFormat;
      }
      delete [] buf;
      m_strMd5 = str;
      m_bReady = true;
      m_strStatus = "md5 calculation ready";
      m_dProgress = 1.0;
      return 0;
   }

} // namespace md5