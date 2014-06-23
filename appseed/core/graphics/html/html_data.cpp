#include "framework.h"


string url_dir_name_for_relative(const char * pszPath);
string defer_solve_relative_compresions(const char * pszAbsolute);
string defer_solve_relative_name(const char * pszRelative, const char * pszAbsolute);


string url_dir_name_for_relative(const char * pszPath)
{
   string strDir(pszPath);

   if (str::ends(strDir, "/"))
      return strDir;

   str::ends_eat(strDir, "/");

   strsize iFind = strDir.reverse_find("/");

   if (iFind < 0)
      return "/";

   return strDir.substr(0, iFind + 1);

}

string defer_solve_relative_compresions(const char * pszAbsolute)
{
   string strAbsolute(pszAbsolute);

   strAbsolute.replace("/./", "/");

   strsize iFind;
   strsize iFind2;

   while ((iFind = strAbsolute.find("/../")) >= 0)
   {
      iFind2 = strAbsolute.reverse_find("/", iFind - 1);
      if (iFind2 <= 0)
      {
         strAbsolute = strAbsolute.substr(iFind + 3);
      }
      else
      {
         strAbsolute = strAbsolute.substr(0, iFind2) + strAbsolute.substr(iFind + 3);
      }
   }

   return strAbsolute;
}

string defer_solve_relative_name(const char * pszRelative, const char * pszAbsolute)
{
   string strRelative(pszRelative);
   string strAbsolute(pszAbsolute);
   if (strRelative.is_empty())
      return "";
   if (strAbsolute.is_empty())
      return defer_solve_relative_compresions(strRelative);
   if (str::begins_ci(strRelative, "http://"))
      return defer_solve_relative_compresions(strRelative);
   if (str::begins_ci(strRelative, "https://"))
      return defer_solve_relative_compresions(strRelative);
   if (str::begins_ci(strRelative, "ftp://"))
      return defer_solve_relative_compresions(strRelative);
   if (str::begins_ci(strRelative, "ext://"))
      return defer_solve_relative_compresions(strRelative);
   
   index iFind = strRelative.find(":\\");

   if (iFind >= 0)
   {
      index i = 0;
      for (; i < iFind; i++)
      {
         if (!isalpha_dup(strRelative[i]) && !isdigit_dup(strRelative[i]))
            break;
      }

      if (i == iFind)
         return defer_solve_relative_compresions(strRelative);

   }

   strAbsolute = ::url_dir_name_for_relative(strAbsolute);

   if (!str::ends(strAbsolute, "/"))
      strAbsolute += "/";
   strRelative = strAbsolute + strRelative;


   return defer_solve_relative_compresions(strRelative);

}

namespace html
{

   data::image::image(sp(::base::application) papp) :
      element(papp),
      m_spdib(allocer())
   {
   }

   bool data::image::load_image()
   {
      return m_spdib.load_from_file(m_strPath);
   }


   data::data(sp(::base::application) papp) :
      element(papp),
      ::data::data(papp),
      m_imagea(papp),
      m_uiptra(papp),
      m_elemental(this)
   {
      m_elemental.m_pdata        = this;
      m_pcookies                 = NULL;
      m_puser                    = NULL;
      m_pform                    = NULL;
      m_bEdit                    = false;
      m_pui                    = NULL;
      m_bImplemented             = false;
      m_bImplement               = false;
      m_bLayout                  = false;
      m_ptag                     = NULL;
      m_pcallback                = NULL;
   }

   data::~data()
   {
      if(m_ptag != NULL)
      {
         delete m_ptag;
         m_ptag = NULL;
      }
   }

   font * data::get_font(elemental * pelemental)
   {
      int32_t iFont = -1;
      if(pelemental->m_pimpl->m_bHover)
      {
         if(!pelemental->m_pimpl->m_mapFont.Lookup("hover", iFont))
         {
            iFont = create_font(pelemental);
            pelemental->m_pimpl->m_mapFont.set_at("hover", iFont);
         }
         return m_fonta.element_at(iFont);
      }
      else if(pelemental->m_pimpl->has_link())
      {
         if(!pelemental->m_pimpl->m_mapFont.Lookup("link", iFont))
         {
            iFont = create_font(pelemental);
            pelemental->m_pimpl->m_mapFont.set_at("link", iFont);
         }
         return m_fonta.element_at(iFont);
      }
      else
      {
         if(!pelemental->m_pimpl->m_mapFont.Lookup("", iFont))
         {
            iFont = create_font(pelemental);
            pelemental->m_pimpl->m_mapFont.set_at("", iFont);
         }
         return m_fonta.element_at(iFont);
      }

   }


   int32_t data::create_font(elemental * pelemental)
   {
      
      string strSubClass;

      class font font;

      if(!pelemental->m_pimpl->m_bHover
      || !pelemental->m_style.get_text("font-family", "hover", this, pelemental, font.m_strFamily))
      {
         if(!pelemental->m_pimpl->has_link()
            || !pelemental->m_style.get_text("font-family", "link", this, pelemental, font.m_strFamily))
         {
            pelemental->m_style.get_text("font-family", "", this, pelemental, font.m_strFamily);
         }
      }
      if(!pelemental->m_pimpl->m_bHover
      || !pelemental->m_style.get_text("font-size", "hover", this, pelemental, font.m_strSize))
      {
         if(!pelemental->m_pimpl->has_link()
            || !pelemental->m_style.get_text("font-size", "link", this, pelemental, font.m_strSize))
         {
            pelemental->m_style.get_text("font-size", "", this, pelemental, font.m_strSize);
         }
      }
      if(!pelemental->m_pimpl->m_bHover
      || !pelemental->m_style.get_text("font-weight", "hover", this, pelemental, font.m_strWeight))
      {
         if(!pelemental->m_pimpl->has_link()
            || !pelemental->m_style.get_text("font-weight", "link", this, pelemental, font.m_strWeight))
         {
            pelemental->m_style.get_text("font-weight", "", this, pelemental, font.m_strWeight);
         }
      }
      if(pelemental->m_pimpl->m_bHover
      && !pelemental->m_style.get_text("text-decoration", "hover", this, pelemental, font.m_strTextDecoration))
      {
         if(pelemental->m_pimpl->has_link()
            && !pelemental->m_style.get_text("text-decoration", "link", this, pelemental, font.m_strTextDecoration))
         {
            pelemental->m_style.get_text("text-decoration", "", this, pelemental, font.m_strTextDecoration);
         }
      }
      font.m_strFamily.trim();
      font.m_strSize.trim();
      font.m_strWeight.trim();
      font.m_strTextDecoration.trim();
      for(int32_t i = 0; i < m_fonta.get_count(); i++)
      {
         if(m_fonta[i] == font)
            return i;
      }
      class font * pfont = new class font(font);
      pfont->create(get_app());
      m_fonta.add(pfont);
      pfont->m_iIndex = (int32_t) m_fonta.get_upper_bound();
      return (int32_t) pfont->m_iIndex;
   }

   void data::delete_contents()
   {
      ::data::lock lock(this);
      m_elemental.m_propertyset.clear();
      m_elemental.m_pbase = NULL;
      delete m_elemental.m_pimpl;
//      for(int32_t i = 0; i < m_elemental.m_elementalptra.get_size(); i++)
  //    {
    //     delete m_elemental.m_elementalptra[i];
      //}
      m_elemental.m_elementalptra.remove_all();
      m_elemental.m_pimpl = NULL;
      m_bImplemented = false;
   }

   void data::delete_implementation()
   {
      m_elemental.delete_implementation();
      m_bImplemented = false;
   }

   void data::load(const char * psz)
   {
      delete_contents();

      lite_html_reader htmlreader(get_app());
      ::html::reader reader;
      htmlreader.setEventHandler(&reader);
      htmlreader.read(psz);
      if(m_ptag != NULL)
      {
         delete m_ptag;
      }
      m_ptag = reader.detach_main_tag();
      if(m_ptag == NULL)
      {
         m_ptag = new tag(NULL);
         value * pvalue = new value(m_ptag);
         m_ptag->baseptra().add(pvalue);
         pvalue->set_value(" ");
      }
      m_elemental.load(this, m_ptag);
   }

   void data::implement(::draw2d::graphics * pdc)
   {
      int32_t iCount = 24;
      while(m_bImplement && iCount >= 0)
      {
         Sleep(100);
         iCount--;
      }
      if(m_bImplement)
         return;
      keeper < bool > keepImplement(&m_bImplement, true, false, true);
      m_pdc = pdc;
      m_focusptra.remove_all();
      m_elemental.implement(this);
      IGUI_WIN_MSG_LINK(WM_KEYDOWN, m_pui, this, &data::_001OnKeyDown);
      m_bImplemented = true;
   }


   void data::_001OnKeyDown(signal_details * pobj)
   {

      SCAST_PTR(::message::key, pkey, pobj)

      if(pkey->m_ekey == ::user::key_tab)
      {

         user::keyboard_focus * pfocus = Application.user()->get_keyboard_focus();

         if(pfocus != NULL)
            pfocus = pfocus->keyboard_get_next_focusable();

         if(pfocus != NULL)
            Application.user()->set_keyboard_focus(pfocus);

         pkey->m_bRet = true;

         return;

      }

   }


   void data::layout(::draw2d::graphics * pdc)
   {


      synch_lock sl(&user_mutex());


      int32_t iCount = 24;
      while(m_bLayout && iCount >= 0)
      {
         Sleep(100);
         iCount--;
      }
      if(m_bLayout)
         return;
      if(!m_bImplemented)
         implement(pdc);
      keeper < bool > keepLayout(&m_bLayout, true, false, true);
      m_pdc = pdc;
      m_layoutstate1.reset();
      m_layoutstate2.reset();
      m_layoutstate3.reset();
      m_elemental.layout(this);

   }


   void data::_001OnDraw(::draw2d::graphics * pdc)
   {
      
      if(m_bImplement || m_bLayout)
         return;
      
      if(is_locked())
         return;
      
      m_pdc = pdc;
      
      m_elemental._001OnDraw(this);

   }


   elemental * data::get_element_by_name(id id)
   {

      return m_elemental.get_element_by_name(id);

   }


   elemental * data::get_element_by_id(id id)
   {

      return m_elemental.get_element_by_id(id);

   }


   void data::layout_state1::reset()
   {

      m_bHasChar  = false;

      m_cxMax.remove_all();

      m_cxMax.add(0.f);

      m_cxa.remove_all();

      m_cxa.add(0.f);

      m_cya.remove_all();

      m_cya.add(0.f);

      m_cy = 0.f;

   }


   void data::layout_state2::reset()
   {
      m_iBody = 0;
      m_y = 0;
      m_cy = 0;
      m_x = 0;
      m_cx = 0;
   }


   void data::layout_state3::reset()
   {

//      m_cyStack.remove_all();
      m_yParent.remove_all();
      m_cya.remove_all();
      m_xParent.remove_all();
      m_x = 0.f;

      m_iBody = 0;
      m_y = 0;
      //m_cyStack.add(0.f);
      m_cya.add(0.f);
      m_xParent.add(0.f);
      m_yParent.add(0.f);
      //m_iy = 0;
      m_x = 0.f;
      m_cx = 0;

   }


   int32_t data::get_image_index(const char * pszUrl)
   {
      string strUrl(pszUrl);
      if(strUrl.find(":") >= 0)
      {
      }
      else if(strUrl[0] == '\\')
      {
      }
      else if(::str::begins(m_strPathName, "http://") ||
         ::str::begins(m_strPathName, "https://"))
      {
         strUrl = System.url().path(m_strPathName, strUrl);
      }
      else
      {
         strUrl = System.dir().path(
            System.dir().name(m_strPathName), strUrl);
         strUrl.replace("/", "\\");
      }
      for(int32_t i = 0; i < m_imagea.get_size(); i++)
      {
         if(m_imagea[i].m_strPath == strUrl)
            return i;
      }
      image * pimage = m_imagea.add_new();
      pimage->m_iIndex = (int32_t) m_imagea.get_upper_bound();
      pimage->m_strPath = strUrl;
      load_image_asynch(pimage);
      return (int32_t) pimage->m_iIndex;
   }

   void data::load_image_asynch(image * pimage)
   {
      class load_image * ploadimage = new class load_image;
      ploadimage->m_pimage = pimage;
      ploadimage->m_pdocument = this;
      __begin_thread(get_app(), LoadImageProc, ploadimage);
   }

   UINT c_cdecl data::LoadImageProc(LPVOID lpParam)
   {
      class load_image * ploadimage = (class load_image *) lpParam;
      if(ploadimage->m_pdocument->load_image(ploadimage->m_pimage))
      {
         ploadimage->m_pdocument->on_image_loaded(ploadimage->m_pimage);
      }
      delete ploadimage;
      return 0;
   }

   bool data::load_image(image * pimage)
   {
      synch_lock lockImage(pimage);
      bool bRet = false;
      try
      {
         bRet = pimage->load_image();
      }
      catch(...)
      {
         bRet = false;
      }
      return bRet;
   }

   
   void data::on_image_loaded(image * pimage)
   {
      
      UNREFERENCED_PARAMETER(pimage);
      
      if(m_pui != NULL)
      {
         
         m_pui->post_message(message_on_image_loaded);
         
      }
      
   }
   

   bool data::contains(sp(::user::interaction) pui)
   {
      
      return m_uiptra.contains(pui);
      
   }
   

   bool data::on_create_interaction(sp(::user::interaction) pui)
   {
      m_uiptra.add_unique(pui);
      return true;
   }


   bool data::open_link(const char * pszPath)
   {
      if(m_pform != NULL && m_pform->get_document() != NULL)
      {
         return m_pform->get_document()->on_open_document(pszPath);
      }
      string strPath(pszPath);
      if(strPath.find(":") >= 0)
      {
         return open_document(strPath);
      }
      else if(strPath.Left(1) == "/" || strPath.Left(1) == "\\")
      {
         return open_document(strPath);
      }
      else
      {
         return open_document(System.dir().path(System.dir().name(m_strPathName), strPath));
      }
   }

   bool data::open_document(var varFile)
   {

      int32_t iRetry = 0;

restart:

      ::data::lock lock(this);

      if (varFile.get_type() == var::type_propset && varFile.propset()["url"].get_string().has_char())
      {
         varFile["url"] = defer_solve_relative_name(varFile["url"], m_strPathName);
      }
      else if (varFile.get_type() == var::type_string || varFile.get_type() == var::type_pstring)
      {
         varFile = defer_solve_relative_name(varFile, m_strPathName);
      }

      string strPathName;


      if(varFile.get_type() == var::type_propset && varFile.propset()["url"].get_string().has_char())
      {
         strPathName = varFile.propset()["url"];
      }
      else if(varFile.cast < ::file::binary_buffer > () != NULL)
      {
         strPathName = System.datetime().international().get_gmt_date_time() + ".html";
      }
      else
      {
         strPathName = varFile;
      }
      if(strPathName.Mid(3) == "wb:")
         return FALSE;



      byte_array ba;
      bool bCancel = FALSE;
      OnBeforeNavigate2(
         varFile,
         0,
         0,
         ba,
         NULL,
         &bCancel);
      if(bCancel)
         return FALSE;
      if(m_strUser.get_length() > 0)
      {
         ::fontopus::user * puser = m_puser != NULL ? m_puser : &ApplicationUser;
         ASSERT(puser != NULL);
         string data;
         property_set set = m_propset["http_propset"].propset();

         set["post"]["entered_login"] = m_strUser;
         set["post"]["entered_password"] = m_strPassword;
         if(!m_strLicense.is_empty())
         {
            set["post"]["entered_license"] = m_strLicense;
         }

         puser->m_strLogin = m_strUser;

         set["user"] = puser;
         set["cookies"] = puser->m_phttpcookies;

         string filename;
         filename = System.file().time_square(get_app());
         System.http().download("https://api.ca2.cc/auth", filename, set);
         string strResponse = Application.file().as_string(filename);
      }

      var varQuery = m_propset["http_propset"].propset();
      varQuery.propset()["app"] = get_app();

      //varQuery.propset()["headers"].propset()[__id(accept)] = "text/xml,application/xml,application/xhtml+xml,text/html;q=0.9,text/plain;q=0.8,video/x-mng,image/png,image/jpeg,image/gif;q=0.2,*/*;q=0.1";
      varQuery.propset()["headers"].propset()[__id(accept)] = "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8";
//      varQuery.propset()["headers"].propset()["Accept-Language"] = "en-us,en;q=0.5";
      //varQuery.propset()["headers"].propset()["Accept-Encoding"] = "gzip,deflate";
//      varQuery.propset()["headers"].propset()["Accept-Charset"] = "ISO-8859-1,utf-8;q=0.7,*;q=0.7";
      varQuery.propset()["headers"].propset()["Cache-Control"] = "max-age=0";

      string str = Application.file().as_string(varFile, varQuery);

      if(!varQuery.propset()["get_headers"].propset()["Location"].is_empty())
      {
         string strLocation = varQuery.propset()["get_headers"].propset()["Location"];
         iRetry++;
         if(iRetry > 8)
         {
            str = "<html>";
            str += "<head>";
            str += "</head>";
            str += "<body>";
            str += "<h1>Redirecionamento Incorreto</h1>";
            str += "</body>";
            str += "</html>";
         }
         else
         {
            varFile = System.url().override_if_set_at_source(varFile, varQuery["get_headers"].propset()["Location"]);
            goto restart;
         }
      }

      if(str.is_empty())
      {
         string strCandidate = System.dir().relpath(m_strPathName, varFile);
         str = Application.file().as_string(strCandidate);
         if(str.is_empty())
         {
            return FALSE;
         }
         strPathName = strCandidate;
/*         string strPath(lpszPathName);
         ::fontopus::user * puser = m_puser != NULL ? m_puser : &ApplicationUser;
         if(puser != NULL && puser->m_strSessid.has_char())
         {
            System.url().string_set(strPath, "sessid", puser->m_strSessid);
         }*/
         /*if(!System.sync_load_url(str, strPath,
            puser, m_pcookies))
                      return FALSE;*/
      }
      delete_contents();


      m_strPathName = strPathName;
      m_strSource = str;
      //if(m_propset["bReplaceEx1"])
      {
        m_propertyset.replace_gen(str);
      }
      TRACE0(str);
      if(str.has_char())
      {
         load(str);
      }

      return TRUE;
   }

   void data::OnBeforeNavigate2(var & varFile, uint32_t nFlags, const char * lpszTargetFrameName, byte_array& baPostedData, const char * lpszHeaders, bool* pbCancel)
   {
      if(m_pcallback != NULL)
      {
         m_pcallback->OnBeforeNavigate2(this, varFile, nFlags, lpszTargetFrameName, baPostedData, lpszHeaders, pbCancel);
      }
      else if(m_pform != NULL)
      {
         m_pform->OnBeforeNavigate2(varFile, nFlags, lpszTargetFrameName, baPostedData, lpszHeaders, pbCancel);
      }
   }

   ::user::form * data::get_form()
   {
      return m_pform;
   }

   sp(::user::interaction) data::get_frame()
   {
      return  (get_form()->GetParentFrame());
   }


   void data::implement_and_layout(html_form * pform)
   {

      ::draw2d::memory_graphics pdc(allocer());

      m_pui  = pform;

      m_pform  = pform;

      implement(pdc);

      pform->GetClientBox(m_box);

      if(m_box.area() <= 0.f)
         return;

      layout(pdc);

   }


} // namespace html




