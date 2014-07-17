#pragma once


namespace user
{


   class CLASS_DECL_CORE static_control :
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
         ::draw2d::bitmap *             m_pbitmap;
         ::visual::icon *           m_picon;
         ::visual::cursor *         m_pcursor;
      };


      e_type                              m_etype;

      bool                                m_bLButtonDown;
      bool                                m_bHover;
      COLORREF                            m_crHover;


      static_control(sp(::base::application) papp);
      virtual ~static_control();


      virtual void install_message_handling(::message::dispatch * pdispatch);


      virtual bool create(sp(::user::interaction) puiParent, id id);


      HENHMETAFILE SetEnhMetaFile(HENHMETAFILE hMetaFile);
      HENHMETAFILE GetEnhMetaFile();
      void set_icon(::visual::icon * picon);
      ::visual::icon * get_icon();
      void set_bitmap(::draw2d::bitmap * pbitmap);
      ::draw2d::bitmap * get_bitmap();
      void set_cursor(::visual::cursor * pcursor);
      ::visual::cursor * get_cursor();

      e_type get_type();


      virtual void _001OnDraw(::draw2d::graphics * pdc);


      virtual bool OnChildNotify(::message::base * pbase);

      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnLButtonDown);
      DECL_GEN_SIGNAL(_001OnLButtonUp);
      DECL_GEN_SIGNAL(_001OnMouseMove);
      DECL_GEN_SIGNAL(_001OnMouseLeave);


   };


} // namespace user


