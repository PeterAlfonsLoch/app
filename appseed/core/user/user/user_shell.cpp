//#include "framework.h"



namespace filemanager
{

   namespace _shell
   {

      string _017FilePathGetParent(const char * lpcsz)
      {
         stringa stra;
         stra.add("/");
         stra.add("\\");
         stringa stra2;
         stra2.add_smallest_tokens(lpcsz, stra, FALSE);
         string str;
         for(int32_t i = 0; i < stra2.get_size() - 1; i++)
         {
            str += stra2[i];
            str += "\\";
         }
         return str;
      }

   EFolder GetFolderType(::aura::application * papp, const char * lpcsz)
   {
      return GetFolderType(papp, ::str::international::utf8_to_unicode(lpcsz));
   }

   EFolder GetFolderType(::aura::application * papp, const unichar * lpcszPath)
   {

      string strPath;

      ::str::international::unicode_to_utf8(strPath, lpcszPath);

      if(dir::is(strPath))
      {
         return FolderFileSystem;
      }
      else if(zip::Util().IsUnzipable(papp, strPath))
      {
         return FolderZip;
      }
      else
      {
         return FolderNone;
      }

   }
/*
   void GetChildren(stringa & stra, const char * lpcszPath)
   {
      string wstrBase(lpcszPath);
      WIN32_FIND_DATAW fd;
      if(wstrBase.get_length() == 0)
      {
         wstrBase = "\\";
      }
      else
      {
         if(wstrBase.find('\\') >= 0)
         {
            if(wstrBase.Right(1) != "\\")
               wstrBase += "\\";
         }
         else if(wstrBase.find('/') >= 0)
         {
            if(wstrBase.Right(1) != "/")
               wstrBase += "/";
         }
         else
         {
            wstrBase += "\\";
         }
      }
      string wstrMask(wstrBase);
      wstrMask += "*.*";
      wstring wstr = ::str::international::utf8_to_unicode(lpcszPath);
      HANDLE h = ::FindFirstFileExW(wstr, FindExInfoStandard, &fd, FindExSearchNameMatch, NULL, 0);

      if(h == NULL)
         return;

      while(true)
      {
         stra.add(::str::international::unicode_to_utf8(fd.cFileName));
         if(!FindNextFileW(h, &fd))
            break;
      }

      stra.remove(".");
      stra.remove("..");
      for(int32_t i = 0; i < stra.get_size(); i++)
      {
         stra[i] = wstrBase + stra[i];
      }

      FindClose(h);

   }
*/

   ImageKey::ImageKey()
   {
      m_iIcon = 0x80000000;
   }

   ImageKey::ImageKey(const ImageKey & key)
   {
      m_strPath         = key.m_strPath;
      m_iIcon           = key.m_iIcon;
      m_strExtension    = key.m_strExtension;
   }


   bool ImageKey::operator == (const ImageKey & key) const
   {
      return m_iIcon == key.m_iIcon
         && m_strExtension == key.m_strExtension
         && m_strPath == key.m_strPath;
   }





   ImageSet::ImageSet(::aura::application * papp) :
      object(papp),
      m_mutex(papp)
   {
      m_pil16 = canew(image_list(papp));
      m_pil16->create(16, 16, 0, 10, 10);
      m_pil48 = canew(image_list(papp));
      m_pil48->create(48, 48, 0, 10, 10);
      m_pil48Hover = canew(image_list(papp));
      m_pil48Hover->create(48, 48, 0, 10, 10);
   }

   ImageSet::~ImageSet()
   {

   }

   void ImageSet::initialize()
   {

      single_lock sl(&m_mutex, true);

      m_pil16->add_matter("filemanager\\check_off_16.png");
      m_pil16->add_matter("filemanager\\check_on_16.png");
      m_pil48->add_matter("filemanager\\check_off_16.png");
      m_pil48->add_matter("filemanager\\check_on_16.png");
      m_pil48Hover->add_matter("filemanager\\check_off_16.png");
      m_pil48Hover->add_matter("filemanager\\check_on_16.png");

   }

   int32_t ImageSet::GetImage(oswindow oswindow, const char * lpcsz, EFileAttribute eattribute, EIcon eicon, COLORREF crBk)
   {

      if(argb_get_a_value(crBk) != 255)
      {

         crBk = 0;

      }


      int32_t iImage = 0x80000000;

#ifdef WINDOWSEX

      ImageKey imagekey;

      string str(lpcsz);

      imagekey.m_strPath.Format(":%s:%d:%d", lpcsz, eattribute, eicon);

      imagekey.m_strExtension = str.Mid(str.reverse_find('.'));

      imagekey.m_iIcon = 0;

      if(m_imagemap.Lookup(imagekey,iImage))
         return iImage;

      iImage = GetImage(oswindow,lpcsz,NULL,eicon,eattribute == FileAttributeDirectory, crBk);

      m_imagemap.set_at(imagekey,iImage);

#endif

      if(crBk != 0)
      {

         synch_lock sl1(m_pil48Hover->m_pmutex);
         synch_lock sl2(m_pil48->m_pmutex);

         {
            ::draw2d::dib_sp dib(allocer());
            dib->create(48,48);
            dib->Fill(255,argb_get_r_value(crBk),argb_get_g_value(crBk),argb_get_b_value(crBk));
            dib->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_blend);

            m_pil48Hover->draw(dib->get_graphics(),iImage,null_point(),0);
            m_pil48Hover->m_spdib->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);
            m_pil48Hover->m_spdib->get_graphics()->BitBlt(iImage * 48,0,48,48,dib->get_graphics());
            m_pil48Hover->m_spdib->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_blend);

         }
         {
            ::draw2d::dib & d = *m_pil48Hover->m_spdib;
            size s = m_pil48->m_spdib->m_size;
            ::draw2d::dib_sp dib(allocer());
            dib->create(d.size());
            dib->Fill(255,argb_get_r_value(crBk),argb_get_g_value(crBk),argb_get_b_value(crBk));
            dib->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_blend);
            dib->get_graphics()->BitBlt(null_point(),d.size(),d.get_graphics());
            dib->get_graphics()->FillSolidRect(0,0,d.size().cx,d.size().cy,ARGB(123,argb_get_r_value(crBk),argb_get_g_value(crBk),argb_get_b_value(crBk)));
            m_pil48->m_spdib->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);
            m_pil48->m_spdib->get_graphics()->BitBlt(null_point(),d.size(),dib->get_graphics());
            m_pil48->m_spdib->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_blend);

         }

      }

      return iImage;


   }



   int32_t ImageSet::GetImageByExtension(oswindow oswindow,const ::file::path & pszPath,EIcon eicon,bool bFolder, COLORREF crBk)
   {

#ifdef WINDOWSEX

      return GetFooImage(oswindow,eicon,bFolder,pszPath.ext(), crBk);

#else

      return 0x80000000;

#endif // WINDOWSEX


      /*

      single_lock sl(&m_mutex, true);

      int32_t iImage = 0x80000000;

#ifdef WINDOWSEX

      if(pszPath == NULL)
         return 0x80000000;

      string strPath(pszPath);

      string strExtension = file_extension_dup(strPath);

      int32_t iType;
      switch(eicon)
      {
      case IconNormal:
         iType = 0;
         break;
      case IconOpen:
         iType = GIL_OPENICON;
         break;
      default:
         // unexpected icon type
         ASSERT(FALSE);
         return 0x80000000;
      }



      HICON hicon16 = NULL;
      HICON hicon48 = NULL;
//      HRESULT hrIconLocation;
//      HRESULT hrExtract;
      ImageKey imagekey;


      string strExtra;


      int32_t iIcon = 0x80000000;
      UINT uiFlags = 0;

      SHFILEINFO shfi16;
      SHFILEINFO shfi48;


      imagekey.m_iIcon         = 0x80000000;
      if(bFolder && !strExtension.has_char())
      {
         imagekey.m_strExtension  = "folder";
      }
      else
      {
         imagekey.m_strExtension  = strExtension;
      }
      imagekey.m_strPath.Empty();

      if(!m_imagemap.Lookup(imagekey, iImage))
      {

         try
         {
            if(imagekey.m_strExtension == "folder")
            {
               SHGetFileInfo(
                  "foo",
                  FILE_ATTRIBUTE_DIRECTORY,
                  &shfi16,
                  sizeof(shfi16),
                  SHGFI_USEFILEATTRIBUTES
                  | SHGFI_ICON
                  | SHGFI_SMALLICON);
               SHGetFileInfo(
                  "foo",
                  FILE_ATTRIBUTE_DIRECTORY,
                  &shfi48,
                  sizeof(shfi48),
                  SHGFI_USEFILEATTRIBUTES
                  | SHGFI_ICON
                  | SHGFI_LARGEICON);
            }
            else
            {
               strPath = "foo." +imagekey.m_strExtension;
               SHGetFileInfo(
                  strPath,
                  FILE_ATTRIBUTE_NORMAL,
                  &shfi16,
                  sizeof(shfi16),
                  SHGFI_USEFILEATTRIBUTES
                  | SHGFI_ICON
                  | SHGFI_SMALLICON);
               SHGetFileInfo(
                  strPath,
                  FILE_ATTRIBUTE_NORMAL,
                  &shfi48,
                  sizeof(shfi48),
                  SHGFI_USEFILEATTRIBUTES
                  | SHGFI_ICON
                  | SHGFI_LARGEICON);
            }
            iImage = m_pil16->add_icon_os_data(shfi16.hIcon);
            m_pil48Hover->add_icon_os_data(shfi48.hIcon);
            System.visual().imaging().Createcolor_blend_ImageList(
               m_pil48,
               m_pil48Hover,
               RGB(255, 255, 240),
               64);

            m_imagemap.set_at(imagekey, iImage);
         }
         catch(...)
         {
         }

      }


#endif

      */

      //return iImage;

   }


   int32_t ImageSet::GetImage(
      oswindow oswindow,
      const char * psz,
      const unichar * lpcszExtra,
      EIcon eicon,
      bool bFolder, 
      COLORREF crBk)
   {

      single_lock sl(&m_mutex, true);

      string strPath(psz);

      int32_t iImage = 0x80000000;

      if(::str::ends_ci(strPath, ".core"))
      {
         string str = Application.file().as_string(strPath);
         if(::str::begins_eat_ci(str,"ca2prompt\r\n"))
         {
            str.trim();
#ifdef WINDOWSEX
            HICON hicon16 = (HICON) ::LoadImage(NULL,Application.dir().matter(str + "/mainframe/icon.ico"),IMAGE_ICON,16,16,LR_LOADFROMFILE);
            HICON hicon48 = (HICON) ::LoadImage(NULL,Application.dir().matter(str + "/mainframe/icon.ico"),IMAGE_ICON,48,48,LR_LOADFROMFILE);
            synch_lock sl1(m_pil48Hover->m_pmutex);
            synch_lock sl2(m_pil48->m_pmutex);
            iImage = m_pil16->add_icon_os_data(hicon16);
            m_pil48Hover->add_icon_os_data(hicon48);

            if(crBk == 0)
            {
               System.visual().imaging().Createcolor_blend_ImageList(
                  m_pil48,
                  m_pil48Hover,
                  RGB(255,255,240),
                  64);
            }
            else
            {
               *m_pil48 = *m_pil48Hover;
            }

#endif
         }
         return iImage;
      }
      // try to find "uifs:// http:// ftp:// like addresses"
      // then should show icon by extension or if is folder
      strsize iFind = ::str::find_ci("://", strPath);
      strsize iFind2 = ::str::find_ci(":",strPath);
      if(iFind >= 0 || iFind2 >= 2)
      {
         string strProtocol = strPath.Left(MAX(iFind, iFind2));
         int32_t i = 0;
         while(i < strProtocol.get_length() && isalnum_dup(strProtocol[i]))
         {
            i++;
         }
         if(i > 0 && i == strProtocol.get_length())
         {
            // heuristically valid protocol
            return GetImageByExtension(oswindow, strPath, eicon, bFolder, crBk);
         }
         if(bFolder)
         {
            return GetImageByExtension(oswindow, strPath, eicon, bFolder,crBk);
         }
      }

#ifdef WINDOWSEX


      string str(psz);

      if(str == "foo")
      {

         iImage = GetFooImage(oswindow,eicon,bFolder,"", crBk);

      }
      else
      {

         if(::str::begins_eat(str,"foo."))
         {

            iImage = GetFooImage(oswindow,eicon,bFolder,str,crBk);

         }
         else
         {

            LPITEMIDLIST lpiidlAbsolute;

            _017ItemIDListParsePath(oswindow, &lpiidlAbsolute,psz);

            iImage = GetImage(oswindow,lpiidlAbsolute,lpcszExtra,eicon, crBk);

            _017ItemIDListFree(lpiidlAbsolute);

         }

      }

#endif

      return iImage;

   }




} // namespace _shell





} // namespace filemanager



#ifdef WINDOWSEX

#include "user_shell_windows.cpp"

#endif