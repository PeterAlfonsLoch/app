#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE folder_list :
      virtual public ::user::impact,
      virtual public ::user::list,
      virtual public data_interface
   {
   public:

      enum EMode
      {
         ModeNormal, // a bit ridiculous that folder list
         ModeConfigurationItem,
      };

      class Folder
      {
      public:
         string      m_strPath;
         string      m_wstrName;
         int32_t          m_iImage;
      };
      class FolderArray :
         protected array < Folder, Folder & >
      {

      public:
         void AddFolder(Folder & folder);
         ::count GetFolderCount();
#ifdef WINDOWSEX
         void clear(LPITEMIDLIST lpiidlPreserve1, LPITEMIDLIST lpiidlPreserve2);
#endif
         void clear();
         Folder & GetFolder(index i);
      };

      FolderArray         m_foldera;
      map < ::visual::icon *, ::visual::icon *, int32_t, int32_t > m_iconmap;


      simple_list_header_control    m_headerctrl;
      sp(manager)        m_pfilemanager;

      
      folder_list (sp(::base::application) papp);
      virtual ~folder_list ();
      
      virtual void install_message_handling(::message::dispatch * pinterface);
      virtual void OnDraw(::draw2d::graphics * pgraphics);      // overridden to draw this ::user::impact
      virtual void on_update(sp(::user::impact) pSender, LPARAM lHint, object* pHint);
      virtual bool pre_create_window(CREATESTRUCT& cs);

      

      DECL_GEN_SIGNAL(_001OnLButtonDblClk);
      DECL_GEN_SIGNAL(_001OnCancelMode);

#ifdef DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
#endif


      virtual void _017Synchronize(::action::context actioncontext);

      ::fs::item & GetFileManagerItem();

      virtual void _001GetItemImage(::user::list_item * pitem);
      void _017UpdateList(const char * lpcszParent, ::action::context actioncontext);
      virtual void _001CreateImageList(::user::list_column * column);
      void _017UpdateList(::action::context actioncontext);
      void _017Browse(const char * lpcsz, ::action::context actioncontext);
      void _017Browse(const wchar_t * lpcsz, ::action::context actioncontext);
      virtual void _001GetItemText(::user::list_item * pitem);
      virtual count _001GetItemCount();
      virtual void _001InsertColumns();

      virtual COLORREF get_background_color();

   };


} // namespace filemanager




