#include "framework.h"
#include "InFile.h"


namespace zip
{


   Util::Util()
   {
   }

   Util::~Util()
   {

   }

   void Util::ls(sp(::base::application) papp, const char * lpszFileName, bool bRecursive, stringa * pstraPath, stringa * pstraTitle, stringa * pstraRelative, bool_array * pbaIsDir, int64_array * piaSize, e_extract eextract)
   {
      string strZip;
      string strRemain;
      string strLastZip;
      if(::str::ends_ci(lpszFileName, ".zip"))
      {
         strZip = lpszFileName;
         strLastZip = strZip;
         strZip += ":";
      }
      else if(::str::find_ci(".zip:", lpszFileName) >= 0)
      {
         strZip = lpszFileName;
         strRemain = strZip.Mid(strZip.reverse_find(".zip:") + strlen(".zip:"));
         strLastZip = strZip.Left(strZip.reverse_find(".zip:") + strlen(".zip"));
      }
      else
         return;

      InFile infile(papp);

      if(!infile.unzip_open(strZip, 0))
      {
         return;
      }

      unzFile pf = infile.get_zip_file()->m_pfUnzip;
      string str;
      string wstrFolder;
      stringa wstraFolder;

      strRemain.replace("\\", "/");
      ::str::begins_eat(strRemain, "/");
      if(strRemain.has_char())
      {
         if(!::str::ends(strRemain, "/"))
            strRemain += "/";
      }

      unz_file_info fi;
      if(pf != NULL)
      {
         while(true)
         {
            //string strPathBuffer;
            //System.file().time_square(strPathBuffer);      // buffer for path


             CHAR szTitle[_MAX_PATH];

            unzGetCurrentFileInfo(
               pf,
               &fi,
               szTitle,
               _MAX_PATH,
               NULL, // extra Field
               0,
               NULL, // comment
               0);
            string strTitle(szTitle);
            if(strRemain != strTitle && ((strRemain.is_empty() &&
               (strTitle.find("/") < 0  || strTitle.find("/") == (strTitle.get_length() - 1)))
            || (strRemain.has_char() && ::str::begins_eat_ci(strTitle, strRemain))))
            {
               if(bRecursive || strTitle.find("/") < 0 || strTitle.find("/") == (strTitle.get_length() - 1))
               {
                  if(pstraPath != NULL)
                  {
                     pstraPath->add(strLastZip + ":" + strRemain + strTitle);
                  }
                  if(pstraTitle != NULL)
                  {
                     pstraTitle->add(strTitle);
                  }
                  if(pstraRelative != NULL)
                  {
                     pstraRelative->add(strRemain + strTitle);
                  }
                  if(pbaIsDir != NULL)
                  {
                     pbaIsDir->add(::str::ends(szTitle, "/")
                                || ::str::ends(szTitle, "\\")
                                || ::str::ends(szTitle, ".zip"));
                  }
                  if(piaSize != NULL)
                  {
                     piaSize->add(fi.uncompressed_size);
                  }
               }
            }
            if(unzGoToNextFile(pf) != UNZ_OK)
            {
               break;
            }
         }
      }
   }

   void Util::ls_dir(sp(::base::application) papp, const char * lpcsz, stringa * pstraPath, stringa * pstraTitle)
   {
      stringa straPath;
      stringa straTitle;
      bool_array baIsDir;
      ls(papp, lpcsz, false, &straPath, &straTitle, NULL, &baIsDir);

      string strPath;

      for(int32_t i = 0; i < straPath.get_size(); i++)
      {
         if(baIsDir[i])
         {
            strPath = straPath[i];
            if(strPath.has_char() && pstraPath->add_unique(strPath) >= 0 && pstraTitle != NULL)
            {
               pstraTitle->add(straTitle[i]);
            }
         }
         else
         {
            strPath = Sys(papp).dir().name(straPath[i]);
            if(strPath.has_char() && pstraPath->add_unique(strPath) >= 0 && pstraTitle != NULL)
            {
               pstraTitle->add(Sys(papp).dir().name(straTitle[i]));
            }
         }

      }

   }



   bool Util::HasSubFolder(sp(::base::application) papp, const char * lpszFileName)
   {
      string strZip;
      if(::str::ends_ci(lpszFileName, ".zip"))
      {
         strZip = lpszFileName;
         strZip += ":";
      }
      else if(::str::find_ci(".zip:", lpszFileName) > 0)
      {
         strZip = lpszFileName;
      }
      else
         return false;

      InFile infile(papp);

      strZip.replace("\\", "/");
      if(!::str::ends_ci(strZip, "/"))
      {
         strZip += "/";
      }

      return infile.unzip_open(strZip, 0) != FALSE;


      //string wstrFileName(lpszFileName);
//      smart_pointer_array < File, File & > filea;

      /*int32_t iStart = 0;
      int32_t iFind;
      iFind  = wstrFileName.find(L".zip", iStart);*/


  /*    stringa wstraPath;
      cregexp_util::add_tokens(wstraPath, lpszFileName, "((([A-Z]:)|([^:]))[^:]+\\.zip)",1);

      if(wstraPath.get_size() == 0)
         return false;


      filea.add(new File(get_app()));
      if(!filea.last_element().open(wstraPath[0]))
         return false;


      stringa wstraPrefix;
      string str;
      int32_t i;
      smart_pointer_array < InFile, InFile & > izfilea;
   //   smart_pointer_array < buffered_buffer, buffered_buffer & > bzfilea;
      for(i = 1; i < wstraPath.get_size(); i++)
      {
         izfilea.add(new InFile(get_app()));
         str =  wstraPath[i];
         izfilea.last_element().open(&filea.last_element(), str);
     //    bzfilea.add(new buffered_buffer(&izfilea.last_element(), 1024 * 1024, 1024 * 1024));
         filea.add(new File(get_app()));
         //filea.last_element().open(&bzfilea.last_element());
         filea.last_element().open(&izfilea.last_element());
         wstraPrefix.add(wstraPath[i]);
      }

      string wstrPrefix;
      wstraPrefix.implode(wstrPrefix, ":");

      if(wstrPrefix.get_length() > 0)
      {
         wstrPrefix += ":";
      }

      unzFile pf = filea.last_element().m_pf;
      string wstrFolder;
      stringa wstraFolder;
      string wstrZip;
      if(pf != NULL)
      {
         while(true)
         {
   //         if(unzOpenCurrentFile(pf) == UNZ_OK)
            {
               const int32_t BUFSIZE = 4096;
               WCHAR lpPathBuffer[BUFSIZE];
               GetTempPathW(BUFSIZE,   // length of the buffer
                  lpPathBuffer);      // buffer for path


                CHAR szTitle[_MAX_PATH];

               unzGetCurrentFileInfo(
                  pf,
                  NULL,
                  szTitle,
                  _MAX_PATH,
                  NULL, // extra Field
                  0,
                  NULL, // comment
                  0);

               str = szTitle;
               if(str.Right(1) == "/")
               {
                  return true;
               }
               wstrZip = lpszFileName;
               wstrZip += ":";
               wstrZip + str;
               if(IsUnzipable(wstrZip))
               {
                  return true;
               }

     //          unzCloseCurrentFile(pf);
            }
            if(unzGoToNextFile(pf) != UNZ_OK)
            {
               break;
            }
         }
      }*/
      return false;
   }

   bool Util::exists(sp(::base::application) papp, const char * pszPath)
   {
      return extract(papp, pszPath, NULL);
   }

   bool Util::extract(sp(::base::application) papp, const char * lpszFileName, const char * lpszExtractFileName)
   {

      InFile infile(papp);

      if(!infile.unzip_open(lpszFileName, 0))
      {
         return false;
      }

      if(lpszExtractFileName == NULL)
         return true;

      ::file::binary_buffer_sp spfile = Sess(papp).file().get_file(lpszExtractFileName, ::file::mode_create | ::file::mode_write | ::file::defer_create_directory);

      if(spfile.is_set())
      {
         return infile.dump(spfile);
      }
      else
      {
         return false;
      }

   }

   bool Util::extract_all(const char * pszDir, ::file::buffer_sp  pfile)
   {

      InFile infile(pfile->get_app());

      if(!infile.unzip_open(pfile))
      {
         return false;
      }

      unzFile pf = infile.get_zip_file()->m_pfUnzip;
      string str;
      string wstrFolder;
      stringa wstraFolder;


      unz_file_info fi;
      if(pf != NULL)
      {
         while(true)
         {

            CHAR szTitle[_MAX_PATH];

            unzGetCurrentFileInfo(
               pf,
               &fi,
               szTitle,
               _MAX_PATH,
               NULL, // extra Field
               0,
               NULL, // comment
               0);
            string strTitle(szTitle);
            if(::str::ends(szTitle, "/") || ::str::ends(szTitle, "\\"))
            {
            }
            else if(infile.locate(strTitle))
            {

               ::file::binary_buffer_sp spfile = Sess(pfile->get_app()).file().get_file(
                  Sys(pfile->get_app()).dir().path(pszDir, strTitle),
                  ::file::mode_create | ::file::mode_write | ::file::defer_create_directory);


               if(spfile.is_set())
               {
                  infile.dump(spfile);
               }
               else
               {
               //   return false;
               }
            }
            if(unzGoToNextFile(pf) != UNZ_OK)
            {
               break;
            }
         }
      }

      return true;

   }

   bool Util::IsUnzipable(sp(::base::application) papp, const char * lpszFileName)
   {
      string str(lpszFileName);
      if(str.get_length() < 4)
         return false;
      if(str.Right(4) != ".zip")
         return false;

      File file(papp);

      return file.unzip_open(lpszFileName);
   }

} // namespace zip

