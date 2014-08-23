#include "framework.h"


namespace filemanager
{


   data::data(sp(::aura::application) papp) :
      element(papp),
      ::data::data(papp)
   {

      m_iIconSize                = 16;
      m_bListText                = true;
      m_bListSelection           = true;
      m_bFileSize                = false;
      m_bPassBk                  = false;
      m_bIconView                = false;
      m_pholderFileList          = NULL;
      m_ptreeFileTreeMerge       = NULL;
      m_pdocumentSave            = NULL;
      m_pmanagertemplate         = NULL;
      m_bSetBergedgeTopicFile    = false;
      m_bTransparentBackground   = true;

      m_spfont.alloc(allocer());

      m_spfont->create_pixel_font("Verdana",14);


   }


   data::~data()
   {

   }

   void data::OnFileManagerOpenContextMenuFolder(sp(::fs::item)  item, stringa & straCommand, stringa & straCommandTitle, ::action::context actioncontext)
   {

      ASSERT(m_pcallback != NULL);

      if(m_pcallback != NULL)
      {

         m_pcallback->OnFileManagerOpenContextMenuFolder(this, item, straCommand, straCommandTitle, actioncontext);

      }

   }


   void data::OnFileManagerOpenContextMenuFile(const ::fs::item_array & itema, ::action::context actioncontext)
   {

      ASSERT(m_pcallback != NULL);

      if(m_pcallback != NULL)
      {

         m_pcallback->OnFileManagerOpenContextMenuFile(this, itema, actioncontext);

      }

   }


   void data::OnFileManagerOpenContextMenu(::action::context actioncontext)
   {

      ASSERT(m_pcallback != NULL);

      if(m_pcallback != NULL)
      {

         m_pcallback->OnFileManagerOpenContextMenu(this, actioncontext);

      }

   }


   void data::OnFileManagerOpenFile(const ::fs::item_array & itema, ::action::context actioncontext)
   {

      ASSERT(m_pcallback != NULL);

      if(is_saving() && itema.get_count() == 1)
      {

         sp(manager) pdoc =  (m_pmanager);
         update_hint uh;
         uh.m_pmanager = m_pmanager;
         uh.m_strPath = itema[0].m_strPath;
         uh.set_type(update_hint::TypeSaveAsOK);
         pdoc->update_all_views(NULL, 0, &uh);
         m_pdocumentSave = NULL;

      }
      else if(m_pcallback != NULL)
      {
         
         var varFile;

         var varQuery;

         if(itema.get_count() == 2 && m_id == "left_file")
         {
            {
               varFile = itema[0].m_strPath;
               varQuery["id"] = "left_file";
               m_pcallback->request_file_query(varFile, varQuery);
            }

            {
               varFile = itema[1].m_strPath;
               varQuery["id"] = "right_file";
               m_pcallback->request_file_query(varFile, varQuery);
            }
         }
         else if(itema.get_count() == 2 && m_id == "right_file")
         {
            {
               varFile = itema[0].m_strPath;
               varQuery["id"] = "right_file";
               m_pcallback->request_file_query(varFile, varQuery);
            }

            {
               varFile = itema[1].m_strPath;
               varQuery["id"] = "left_file";
               m_pcallback->request_file_query(varFile, varQuery);
            }
         }
         else
         {

            varFile = itema.get_var_file();

            varQuery = itema.get_var_query();

            varQuery["id"] = m_id;

            m_pcallback->request_file_query(varFile, varQuery);

         }

      }

   }


   void data::OnFileManagerOpenFolder(sp(::fs::item)  item, ::action::context actioncontext)
   {

      ASSERT(m_pcallback != NULL);

      if(m_pcallback != NULL)
      {

         m_pcallback->OnFileManagerOpenFolder(this, item, actioncontext);

      }

   }


   void data::OnFileManagerItemUpdate(cmd_ui * pcmdui, const ::fs::item_array & itema)
   {

      ASSERT(m_pcallback != NULL);

      if(m_pcallback != NULL)
      {

         m_pcallback->OnFileManagerItemUpdate(this, pcmdui, itema);

      }

   }


   void data::OnFileManagerItemCommand(const char * pszId, const ::fs::item_array & itema)
   {

      ASSERT(m_pcallback != NULL);

      if(m_pcallback != NULL)
      {

         m_pcallback->OnFileManagerItemCommand(this, pszId, itema);

      }

   }


   void data::FileManagerBrowse(sp(::fs::item) item, ::action::context actioncontext)
   {

      ASSERT(m_pmanager != NULL);

      if(m_pmanager != NULL)
      {

         m_pmanager->FileManagerBrowse(item, actioncontext);

      }

   }

   void data::FileManagerBrowse(const char * lpcsz, ::action::context actioncontext)
   {
      
      ASSERT(m_pmanager != NULL);
      
      if(m_pmanager != NULL)
      {

         m_pmanager->FileManagerBrowse(lpcsz, actioncontext);

      }

   }


   bool data::is_saving()
   {

      return m_pdocumentSave != NULL;

   }


   bool data::get_color(COLORREF & cr,::user::e_color ecolor)
   {

      if(ecolor == ::user::color_text)
      {

         cr = ARGB(255,0,0,0);

         return true;

      }
      else if(ecolor == ::user::color_background)
      {

         if(m_bTransparentBackground)
         {

            if(is_saving())
            {

               cr = ARGB(184,255,210,180);

            }
            else
            {

               cr = ARGB(184,255,255,250);

            }

         }
         else
         {

            if(is_saving())
            {

               cr = ARGB(255,255,210,180);

            }
            else
            {

               cr = ARGB(255,255,255,250);

            }

         }

         return true;

      }
      else
      {

         return ::user::schema::get_color(cr,ecolor);

      }

   }


   bool data::get_font(::draw2d::font_sp & font)
   {

      if(m_spfont.is_null())
         return false;
      
      font = m_spfont;

      return true;

   }


   bool data::get_translucency(::user::ETranslucency & etranslucency)
   {

      if(m_bTransparentBackground)
      {

         etranslucency = ::user::TranslucencyPresent;

      }
      else
      {

         etranslucency = ::user::TranslucencyNone;

      }

      return true;

   }


   sp(::filemanager::manager_template) data::get_filemanager_template()
   {

      return m_pmanagertemplate;

   }


} // namespace filemanager





