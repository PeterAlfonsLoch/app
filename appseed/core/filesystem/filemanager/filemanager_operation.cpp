#include "framework.h"


namespace filemanager
{


   operation::operation(sp(::base::application) papp):
      element(papp)
   {

      m_oswindowCallback = NULL;

      m_bReplaceAll = false;

      m_eoperation = operation_none;

      m_iBufferSize = 1024 * 1024;

   }

   operation::~operation()
   {
   }


   e_operation operation::get_operation()
   {
      return m_eoperation;
   }

   void operation::set_operation(e_operation eoperation)
   {
      m_eoperation = eoperation;
   }

   bool operation::set_copy(stringa & stra,const char * pszDestBase,const char * pszSrcBase,bool bExpand)
   {
      set_operation(operation_copy);
      if(bExpand)
      {
         expand(m_stra,stra);
      }
      else
      {
         m_stra = stra;
      }
      m_str = System.dir().path(pszDestBase,"");
      string strBase;
      if(pszSrcBase != NULL)
      {
         strBase = System.dir().path(pszSrcBase,"");
      }
      else
      {
         strBase = System.dir().name(stra[0]);
         string strCompare;
         for(int32_t i = 1; i < stra.get_size(); i++)
         {
            strCompare = System.dir().name(stra[i]);
            for(int32_t j = 0; j < min(strCompare.get_length(),strBase.get_length()); j++)
            {
               if(strCompare[j] != strBase[j])
               {
                  strBase = System.dir().name(strCompare.Left(j));
                  break;
               }
            }
         }
      }
      m_strBase = strBase;
      m_dRead = 0.0;
      m_iFile = 0;
      if(!initialize())
         return false;
      return true;
   }

   bool operation::set_move(stringa & stra,const char * psz)
   {
      set_operation(operation_move);
      m_stra = stra;
      m_str = psz;
      m_dRead = 0.0;
      m_iFile = 0;
      if(!initialize())
         return false;
      return true;
   }

   bool operation::set_delete(stringa & stra)
   {
      set_operation(operation_delete);
      m_stra = stra;
      m_dRead = 0.0;
      m_iFile = 0;
      if(!initialize())
         return false;
      return true;
   }

   bool operation::open_src_dst(const char * pszSrc,const char * pszDst)
   {

      if(session().dir().is(pszSrc) && !::str::ends_ci(pszSrc,".zip"))
      {
         session().dir().mk(System.dir().name(pszDst));
         return false;
      }

      m_fileSrc = Application.file().get_file(pszSrc,::file::mode_read | ::file::type_binary | ::file::share_deny_write);

      if(m_fileSrc.is_null())
      {

         TRACE("\n Could not open source file(%d)=%s",m_iFile,pszSrc);

         return false;

      }

      if(!m_bReplaceAll)
      {
         /*      if(System.file().exists(pszDst))
               {
               property_set propertyset;
               propertyset["srcfile"].get_value().set_string(pszSrc);
               propertyset["dstfile"].get_value().set_string(pszDst);
               System.message_box("filemanager\\do_you_want_to_replace_the_file.xml", propertyset);
               return false;
               }*/
      }

      session().dir().mk(System.dir().name(pszDst));

      m_fileDst = Application.file().get_file(pszDst,::file::mode_write | ::file::type_binary | ::file::mode_create);


      if(m_fileDst.is_null())
      {

         TRACE("\n Could not open dest file(%d)=%s",m_iFile,pszDst);

         property_set propertyset;

         propertyset["filepath"] = pszDst;

         System.message_box("filemanager\\not_accessible_destination_file.xhtml",propertyset);

         return false;

      }

      TRACE("\n%d Opened %s %s",m_iFile,pszSrc,pszDst);

      return true;

   }


   bool operation::start()
   {
      switch(m_eoperation)
      {
      case operation_copy:
      {
                                         m_iFile = 0;
                                         m_pchBuffer = (char *)malloc(m_iBufferSize);
                                         string strName = System.dir().path(
                                            m_str,m_stra[m_iFile].Mid(m_strBase.get_length()));
                                         if(m_str == m_strBase)
                                         {
                                            make_duplicate_name(strName,m_str);
                                         }
                                         if(!open_src_dst(m_stra[m_iFile],strName))
                                            return false;
      }
         break;
      case operation_delete:
      {
      }
         break;
      case operation_move:
      {
                                         m_iFile = 0;
                                         m_pchBuffer = (char *)malloc(m_iBufferSize);
                                         if(!open_src_dst(m_stra[m_iFile],
                                            System.dir().path(
                                            m_str,System.file().name_(m_stra[m_iFile]))))
                                            return false;
      }
         break;
      default:

         break;
      }
      return true;
   }

   bool operation::step()
   {
      switch(m_eoperation)
      {
      case operation_copy:
      {
                                         if(m_iFile >= m_stra.get_size())
                                            return false;
                                         primitive::memory_size uiRead = m_fileSrc->read(m_pchBuffer,m_iBufferSize);
                                         if(uiRead > 0)
                                         {
                                            m_fileDst->write(m_pchBuffer,uiRead);
                                            m_daRead[m_iFile] += uiRead;
                                            m_dRead += uiRead;
                                         }
                                         else
                                         {

                                            {

                                               string strDestPath = m_fileDst->GetFilePath();

                                               m_fileDst->close();

                                               ::file::file_status st;

                                               bool bOk = true;

                                               try
                                               {

                                                  m_fileSrc->GetStatus(st);

                                               }
                                               catch(...)
                                               {

                                                  bOk = false;

                                               }

                                               if(bOk)
                                               {

                                                  try
                                                  {

                                                     System.os().set_file_status(strDestPath,st);

                                                  }
                                                  catch(...)
                                                  {

                                                     bOk = false;

                                                  }

                                                  if(!bOk)
                                                  {

                                                     TRACE("Failed to set status of destination file '%s' using file status of '%s' file",strDestPath,m_fileSrc->GetFilePath());

                                                  }

                                               }
                                               else
                                               {

                                                  TRACE("Failed to get status of source file '%s' for setting file status of '%s' file",m_fileSrc->GetFilePath(),strDestPath);

                                               }

                                               m_fileSrc->close();

                                            }
                                            m_iFile++;
                                            while(m_iFile < m_stra.get_size() && session().dir().is(m_stra[m_iFile]) && !::str::ends_ci(m_stra[m_iFile],".zip"))
                                            {
                                               m_iFile++;
                                            }
                                            if(m_iFile >= m_stra.get_size())
                                               return false;
                                            string strName = System.dir().path(
                                               m_str,m_stra[m_iFile].Mid(m_strBase.get_length()));
                                            if(m_str == m_strBase)
                                            {
                                               make_duplicate_name(strName,m_str);
                                            }
                                            if(!open_src_dst(m_stra[m_iFile],strName))
                                            {

                                               return false;
                                            }
                                         }
                                         return true;
      }
      case operation_delete:
      {
                                           if(m_iFile >= m_stra.get_size())
                                              return false;
                                           System.file().del(m_stra[m_iFile]);
                                           m_iFile++;
      }
         break;
      case operation_move:
      {
                                         if(m_iFile >= m_stra.get_size())
                                            return false;
                                         primitive::memory_size uiRead = m_fileSrc->read(m_pchBuffer,m_iBufferSize);
                                         m_fileDst->write(m_pchBuffer,uiRead);
                                         m_daRead[m_iFile] += uiRead;
                                         m_dRead += uiRead;
                                         if(uiRead == 0)
                                         {
                                            m_fileSrc->close();
                                            m_fileDst->close();
                                            System.file().del(m_stra[m_iFile]);
                                            m_iFile++;
                                            if(m_iFile >= m_stra.get_size())
                                               return false;
                                            if(!open_src_dst(m_stra[m_iFile],
                                               System.dir().path(
                                               m_str,System.file().name_(m_stra[m_iFile]))))
                                               return false;
                                         }
      }
         break;
      default:

         break;
      }
      return true;
   }

   bool operation::finish()
   {
      switch(m_eoperation)
      {
      case operation_copy:
      {
                                         free(m_pchBuffer);
      }
         break;
      case operation_delete:
      {
      }
         break;
      case operation_move:
      {
                                         free(m_pchBuffer);
      }
         break;
      default:

         break;
      }
      if(m_oswindowCallback != NULL)
      {
         m_oswindowCallback->send_message(m_uiCallbackMessage,m_wparamCallback);
      }
      return true;
   }


   bool operation::initialize()
   {

      m_dSize = 0.0;

      var varLen;

      for(int32_t i = 0; i < m_stra.get_size(); i++)
      {

         if(session().dir().is(m_stra[i]) && !::str::ends_ci(m_stra[i],".zip"))
         {

            m_daSize.add(0.0);

            m_daRead.add(0.0);

         }
         else
         {

            varLen = Application.file().length(m_stra[i]);

            if(varLen.is_null())
            {

               m_daSize.add(0.0);

               m_daRead.add(0.0);

            }
            else
            {

               m_dSize += (uint32_t)varLen;

               m_daSize.add((double)(uint32_t)varLen);

               m_daRead.add(0.0);

            }

         }

      }

      return true;

   }


   int32_t operation::get_item_count()
   {

      return (int32_t)m_stra.get_size();

   }


   string operation::get_item_message(int32_t iItem)
   {

      string str;

      str.Format("Copying %s (%s) to %s",System.file().name_(m_stra[iItem]),System.dir().name(m_stra[iItem]),m_str);

      return str;

   }


   double operation::get_item_progress(int32_t iItem)
   {

      if(m_daSize[iItem] == 0.0)
      {
         if(m_iFile > iItem)
         {
            return 1.0;
         }
         else
         {
            return 0.0;
         }
      }
      return m_daRead[iItem] / m_daSize[iItem];
   }

   double operation::get_item_read(int32_t iItem)
   {
      return m_daRead[iItem];
   }

   double operation::get_item_size(int32_t iItem)
   {
      return m_daSize[iItem];
   }

   void operation::make_duplicate_name(string & str,const char * psz)
   {
      string strDir = System.dir().path(psz,"");
      string strName = str.Mid(strDir.get_length());
      string strExtension;
      bool bDir;
      strsize iFind = strName.find("\\");
      bDir = iFind > 0;
      if(bDir)
      {
         strExtension = "\\" + strName.Mid(iFind + 1);
         strName = strName.Left(iFind);
      }
      else
      {
         strName = System.file().title_(str);
         strExtension = "." + System.file().extension(str);
      }
      string strFormat;
      for(int32_t i = 1; i < 1000; i++)
      {
         strFormat.Format("-Copy-%03d",i);
         str = System.dir().path(strDir,strName + strFormat + strExtension);
         if(!Application.file().exists(str))
            return;
      }
   }

   void operation::expand(stringa & straExpanded,stringa & straExpand)
   {
      for(int32_t i = 0; i < straExpand.get_size(); i++)
      {
         if(session().dir().is(straExpand[i]) && !::str::ends_ci(m_stra[i],".zip"))
         {
            session().dir().rls(straExpand[i],&straExpanded);
         }
         else
         {
            straExpanded.add(straExpand[i]);
         }
      }
   }


} // namespace filemanager























