#pragma once


namespace visual
{


   class CLASS_DECL_BASE font_list_data :
      virtual public ::object
   {
   public:

      class CLASS_DECL_BASE text_box
      {
      public:
         
         ::draw2d::dib_sp     m_dib;
         ::draw2d::font_sp    m_font;
         rect                 m_rect;
         bool                 m_bOk;
         size                 m_size;

         text_box();
         void update(font_list_data * pdata, int iBox, string strText);
      };

      class CLASS_DECL_BASE item
      {
      public:

         text_box             m_box[3];
         string               m_strName;
         string               m_strFont;
         string               m_strSample;

         

      };


      stringa                                   m_straNameEnum;
      stringa                                   m_straFontEnum;

      string                                    m_strText;
      string                                    m_strTextLayout;

      ::draw2d::font::csa                       m_csa;
      ptr_array < item >                        m_itemptra;
      rect                                      m_rectClient;
      rect                                      m_rectMargin;
      int                                       m_iSel;
      int                                       m_iHover;

      uint32_array                              m_dwaBg;
      uint32_array                              m_dwaFg;


      
      font_list_data(::aura::application * papp);
      virtual ~font_list_data();


      virtual void update();

      virtual index find_name(string str);

      virtual index hit_test(point pt);

      virtual void _001OnDraw(::draw2d::graphics * pgraphics);

      virtual void on_layout();


   };


} // namespace visual





