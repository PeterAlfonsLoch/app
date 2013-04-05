#pragma once


namespace userbase
{


   class CLASS_DECL_ca2 base_static :
      virtual public ::user::control
   {
   public:

      enum e_type
      {
         type_text,
         type_icon,
         type_bitmap,
         type_cursor,
      };


      union
      {
         ::ca::bitmap *             m_pbitmap;
         ::visual::icon *           m_picon;
         ::visual::cursor *         m_pcursor;
      };


      e_type                         m_etype;


      base_static(::ca::applicationsp papp);
      virtual ~base_static();


      virtual bool create(sp(::user::interaction) puiParent, id id);


      HENHMETAFILE SetEnhMetaFile(HENHMETAFILE hMetaFile);
      HENHMETAFILE GetEnhMetaFile();
      void set_icon(::visual::icon * picon);
      ::visual::icon * get_icon();
      void set_bitmap(::ca::bitmap * pbitmap);
      ::ca::bitmap * get_bitmap();
      void set_cursor(::visual::cursor * pcursor);
      ::visual::cursor * get_cursor();

      e_type get_type();


#ifdef WINDOWSEX

      virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

#endif


      virtual bool OnChildNotify(UINT, WPARAM, LPARAM, LRESULT*);


   };


} // namespace userbase


