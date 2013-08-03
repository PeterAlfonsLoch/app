#pragma once


namespace filehandler
{


   class CLASS_DECL_sphere view :
      public form_view
   {
   public:


      class CLASS_DECL_sphere item :
         virtual public ::ca2::object
      {
      public:
         

         string      m_strApp;
         int32_t         m_iIndex;


         void parse(const char * pszApp);


      };

      class CLASS_DECL_sphere list :
         public smart_pointer_array < item >
      {
      public:


         void parse(handler * phandler, const char * pszTopic);


      };

      class CLASS_DECL_sphere draw_item :
         virtual public ::ca2::object
      {
      public:

         rect        m_rectItem;
         rect        m_rectStatusImage;
         rect        m_rectName;
         
         void draw(sp(view) pview, ::draw2d::graphics * pdc, list * plist, item * pcontact);

      };

      class CLASS_DECL_sphere draw_list :
         public array < draw_item >
      {
      public:


         int32_t m_iItemHeight;

         draw_list();

         void layout(LPCRECT lpcrect, list * plist);
         void draw(sp(view) pview, ::draw2d::graphics * pdc, list * plist);

      };

      ::xml::document         m_document;
      list                    m_list;
      draw_list               m_drawlist;


      view(sp(::ca2::application) papp);


      virtual void _001OnDraw(::draw2d::graphics * pdc);
      
      virtual void install_message_handling(::ca2::message::dispatch * pdispatch);

      virtual void refresh();

      DECL_GEN_SIGNAL(_001OnCreate)
      DECL_GEN_SIGNAL(_001OnTimer)
      DECL_GEN_SIGNAL(_001OnLButtonUp)

      virtual void layout();


      index hit_test(point pt, e_element & eelement);


   };



} // namespace filehandler





