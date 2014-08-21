#pragma once


namespace filehandler
{


   class CLASS_DECL_sphere view :
      public form_view
   {
   public:


      class list;


      class CLASS_DECL_sphere item :
         virtual public ::object
      {
      public:
         

         string         m_strApp;
         int32_t        m_iIndex;

         rect           m_rectItem;
         rect           m_rectStatusImage;
         rect           m_rectName;

         item(sp(::axis::application) papp);

         void parse(const char * pszApp);

         void draw(sp(view) pview, ::draw2d::graphics * pdc, list * plist);

      };

      class CLASS_DECL_sphere list :
         virtual public spa(item)
      {
      public:

         int32_t m_iItemHeight;

         list(sp(::axis::application) papp);


         void parse(handler * phandler, const char * pszTopic);

         void layout(LPCRECT lpcrect);
         void draw(sp(view) pview, ::draw2d::graphics * pdc);

      };



      ::xml::document         m_document;
      sp(list)                m_plistWorking;
      sp(list)                m_plist;

      ::draw2d::font_sp       m_spfont;


      view(sp(::axis::application) papp);


      virtual void _001OnDraw(::draw2d::graphics * pdc);
      
      virtual void install_message_handling(::message::dispatch * pdispatch);

      virtual void refresh();

      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnTimer);
      DECL_GEN_SIGNAL(_001OnLButtonUp);

      virtual void layout();


      index hit_test(point pt, e_element & eelement);


      void layout_list(list * plist);

      virtual bool get_font(::draw2d::font_sp & font);

   };



} // namespace filehandler





