#pragma once


namespace user
{


   namespace shell
   {


      enum e_file_attribute
      {

         file_attribute_normal,
         file_attribute_directory,

      };

      enum e_folder
      {

         folder_none,
         folder_file_system,
         folder_zip,

      };


      enum e_icon
      {
         
         icon_normal,
         icon_open,

      };


      class image_key
      {
      public:

         char *                        m_pszPath;
         char *                        m_pszShellThemePrefix;
         cflag < e_file_attribute >    m_eattribute;
         cflag < e_icon >              m_eicon;
         int32_t                       m_iIcon;
         char *                        m_pszExtension;



         image_key();

         operator uint32_t () const
         {
            return m_iIcon;
         }

         bool operator == (const image_key & key) const;

         void set_path(const string & strPath, bool bSetExtension = true);
         void set_extension(const string & strPath);

      };

      class image_key_store :
         public image_key
      {
      public:

         image_key_store();
         image_key_store(const image_key & key);
         ~image_key_store();

      };


      inline bool image_key::operator == (const image_key & key) const
      {
         return m_eattribute == key.m_eattribute
            && m_eicon == key.m_eicon
            && m_iIcon == key.m_iIcon
            && strcmp(m_pszExtension, key.m_pszExtension) == 0
            && strcmp(m_pszShellThemePrefix, key.m_pszShellThemePrefix) == 0
            && strcmp(m_pszPath, key.m_pszPath) == 0;
      }




      class CLASS_DECL_CORE shell :
         virtual public ::object
         //,         virtual public ::thread

      {
      public:

         sp(image_list)                                                 m_pil16;
         sp(image_list)                                                 m_pil48;
         sp(image_list)                                                 m_pil48Hover;
         map < image_key_store, const image_key &, int32_t, int32_t >   m_imagemap;

         string                                                         m_strShellThemePrefix;
         stringa                                                        m_straThemeableIconName;

         shell(::aura::application * papp);
         virtual ~shell();

         virtual void open_folder(oswindow oswindow, const string & strFolder);
         virtual void close_folder(const string & strFolder);

         virtual int32_t get_image_foo(oswindow oswindow, const string & strExtension, e_file_attribute eattribute, e_icon eicon, COLORREF crBk = 0) = 0;
         virtual int32_t get_image(oswindow oswindow, const string & strPath, e_file_attribute eattribute, e_icon eicon, COLORREF crBk = 0) = 0;
         //virtual int32_t get_image(oswindow oswindow, image_key key, const unichar * lpcszExtra, COLORREF crBk) = 0;
         //virtual int32_t get_image_by_extension(oswindow oswindow, image_key & key, COLORREF crBk) = 0;

         inline image_list * GetImageList16()
         {
            return m_pil16;
         }
         inline image_list * GetImageList48()
         {
            return m_pil48;
         }
         inline image_list * GetImageList48Hover()
         {
            return m_pil48Hover;
         }

         void initialize();

         virtual e_folder get_folder_type(::aura::application * papp, const unichar * lpcszPath) = 0;
         virtual e_folder get_folder_type(::aura::application * papp, const char * lpcszPath) = 0;


      };


   } // namespace shell


} // namespace user


template < >
inline UINT HashKey<const ::user::shell::image_key &>(const ::user::shell::image_key & key)
{
   // default identity hash - works for most primitive values
   return (UINT)harmannieves_camwhite_hash(key.m_pszPath,
      harmannieves_camwhite_hash(key.m_pszShellThemePrefix,
         harmannieves_camwhite_hash(key.m_pszExtension,
            key.m_iIcon | (((int)key.m_eicon) << 8) | (((int)key.m_eattribute) << 16))));
}
