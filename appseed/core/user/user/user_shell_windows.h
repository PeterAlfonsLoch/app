#pragma once


#include <shlobj.h>
#include <Shellapi.h>
#include <CommonControls.h>


namespace user
{

   
   namespace shell
   {

      CLASS_DECL_CORE int32_t _017ItemIDListGetLen(LPITEMIDLIST lpiidl);

      class CLASS_DECL_CORE windows :
         virtual public ::user::shell::shell
      {
      public:

         class folder
         {
         public:

            ::windows::comptr < IShellFolder>      m_lpsf;
            wstring                                m_wstr;
            int                                    m_iRef = 0;
            string                                 m_str;

         };

         ::windows::comptr < IImageList >                            m_pilExtraLarge;
         ::windows::comptr < IMalloc >                               m_pmalloc;
         ::windows::comptr < IShellFolder >                          m_pfolderDesktop;
         string_map < folder, const folder  & >                      m_mapFolder;

         delay_thread *                                              m_pdelayRelease;



         windows(::aura::application * papp);
         virtual ~windows();


         void initialize();


         virtual void open_folder(oswindow oswindow, const string & strFolder);
         virtual void close_folder(const string & strFolder);

         virtual int32_t get_image_foo(oswindow oswindow, const string & strExtension, e_file_attribute eattribute, e_icon eicon, COLORREF crBk = 0) override;
         virtual int32_t get_image(oswindow oswindow, const string & strPath, e_file_attribute eattribute, e_icon eicon, COLORREF crBk = 0) override;

         virtual ::user::shell::e_folder get_folder_type(::aura::application * papp, const unichar * lpcszPath) override;
         virtual ::user::shell::e_folder get_folder_type(::aura::application * papp, const char * lpcszPath) override;

         virtual void get_image_prologue(COLORREF crBk, int iImage);


         //virtual bool do_call();
         //int32_t calc_image_foo(oswindow oswindow, const string & strExtension, e_file_attribute eattribute, e_icon eicon, COLORREF crBk = 0);
         //int32_t calc_get_image(oswindow oswindow, const string & strPath, e_file_attribute eattribute, e_icon eicon, COLORREF crBk = 0);




         int32_t get_image(oswindow oswindow, image_key key, const unichar * lpcszExtra, COLORREF crBk);
         int32_t get_image_by_extension(oswindow oswindow, image_key & key, COLORREF crBk);
         bool get_icon(oswindow oswindow, const char * lpcsz, const unichar * lpcszExtra, e_icon eicon, HICON * phicon16, HICON * phicon48);
         bool get_icon(oswindow oswindow, IShellFolder * lpsf, LPITEMIDLIST lpiidlAbsolute, LPITEMIDLIST lpiidlChild, const unichar * lpcszExtra, e_icon eicon, HICON * phicon16, HICON * phicon48);
         bool get_icon(oswindow oswindow, LPITEMIDLIST lpiidlAbsolute, const unichar * lpcszExtra, e_icon eicon, HICON * phicon16, HICON * phicon48);
         int32_t get_image(oswindow oswindow, IShellFolder * lpsf, const char * pszPath, LPITEMIDLIST lpiidlChild, const unichar * lpcszExtra, e_icon eicon);
         int32_t get_image(oswindow oswindow, image_key key, LPITEMIDLIST lpiidlAbsolute, LPITEMIDLIST lpiidlChild, const unichar * lpcszExtra, COLORREF crBk);
         int32_t get_image(oswindow oswindow, image_key key, LPITEMIDLIST lpiidlAbsolute, const unichar * lpcszExtra, COLORREF crBk);
         int32_t get_foo_image(oswindow oswindow, image_key key, COLORREF crBk);



         ::windows::comptr < IShellFolder> _017GetShellParentFolder(LPITEMIDLIST lpiidlChild);
         ::windows::comptr < IShellFolder> _017GetShellFolder(const string & str, LPITEMIDLIST lpiidlChild);
         void _017ItemIDListParsePath(oswindow oswindow, LPITEMIDLIST * lpiidl, const char * lpcsz);






         virtual index GetCSIDLSort(index iCsidl);
         virtual index GetCSIDL(LPITEMIDLIST lpiidl);
         virtual void GetAscendants(LPITEMIDLIST lpiidl, array < LPITEMIDLIST, LPITEMIDLIST > & lpiidla);
         virtual void Free(array < LPITEMIDLIST, LPITEMIDLIST > & lpiidla);

         //      string CLASS_DECL_CORE _017FilePathGetParent(const char * lpcsz);

         HICON CalcIcon(LPITEMIDLIST lpiidl, const char * lpcszExtra, int32_t cx, int32_t cy);
         bool _017HasSubFolder(::aura::application * papp, LPITEMIDLIST lpiidl, const char * lpcszExtra);
         //      void CLASS_DECL_CORE GetChildren(stringa & stra, const char * lpcszPath);
         LPITEMIDLIST _017ItemIDListGetLast(LPITEMIDLIST lpiidl);
         LPITEMIDLIST _017ItemIDListDup(LPITEMIDLIST lpiidl);
         LPITEMIDLIST _017ItemIDListGetFolderParent(LPITEMIDLIST lpiidl);
         LPITEMIDLIST _017ItemIDListGetAbsolute(LPITEMIDLIST lpiidlParent, LPITEMIDLIST lpiidl);
         bool _017ItemIDListIsEqual(LPITEMIDLIST lpiidl1, LPITEMIDLIST lpiidl2);


         void _017ItemIDListFree(LPITEMIDLIST lpiidl);

         //int run();


      };


   } // namespace windows


} // namespace filemanager


