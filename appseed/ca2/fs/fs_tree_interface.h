#pragma once


namespace fs
{


   class CLASS_DECL_ca2 tree_interface :
      public ::user::tree
   {
   public:


      string                  m_strPath;
      critical_section        m_csBrowse;
      bool                    m_bCreateImageList;
      bool                    m_bCreateImageListRedraw;
      int                     m_iAnimate;
      bool                    m_bTimer123;
      stringa                 m_straUpdatePtrFilter;
      stringa                 m_straMissingUpdate;
      bool                    m_bDelayedListUpdate;
      ex1::tree_item *        m_pdataitemCreateImageListStep;
      int                     m_iDefaultImage;
      int                     m_iDefaultImageSelected;

         
      tree_interface(::ca::application * papp);
      virtual ~tree_interface();


      virtual bool initialize();

      void update_list();

      void _001OnItemExpand(::ex1::tree_item * pitem);
      void _017UpdateList(const char * lpcsz, ex1::tree_item * pitemParent, int iLevel);

      document * get_document();
      virtual tree_data * get_fs_tree_data();

      virtual void _001InsertColumns();
      virtual void _001UpdateImageList(ex1::tree_item * pitem);

   

      virtual void _017Synchronize();
      void install_message_handling(::gen::message::dispatch * pinterface);
   

      void _StartCreateImageList();
      void _StopCreateImageList();
      void _CreateImageListStep();

      // user::tree
      virtual void _001OnOpenItem(::ex1::tree_item * pitem);
      virtual void _001OnItemCollapse(::ex1::tree_item * pitem);


      virtual void _017OpenFolder(const item & item);
      
      virtual COLORREF get_background_color();

      void _017PreSynchronize();
      void TakeAnimationSnapshot();
      virtual void StartAnimation();
      void GetSelectedFilePath(stringa & stra);
      virtual bool _001IsTranslucent();

      void _017Browse(const char * lpcsz, bool bForceUpdate = false);
      void _017UpdateList();
      void _017UpdateZipList(const char * lpcsz, ex1::tree_item * pitemParent, int iLevel);
      void _017EnsureVisible(const char * lpcsz);
      
      ex1::tree_item * find_item(const char * lpcsz);

      ex1::tree_item * find_absolute(const char * lpcsz);
      void clear(const char * lpcszPreserve1, const char * lpcszPreserve2);
      void arrange(e_arrange earrange);

      DECL_GEN_SIGNAL(_001OnTimer)

   protected:


      void _StartDelayedListUpdate();
      void _StopDelayedListUpdate();
      void _DelayedListUpdate();


   };


} // namespace fs


