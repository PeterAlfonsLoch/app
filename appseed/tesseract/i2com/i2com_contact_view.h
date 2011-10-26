#pragma once


namespace i2com
{


   class CLASS_DECL_CA2_TESSERACT contact_view :
      public form_view
   {
   public:


      class CLASS_DECL_CA2_TESSERACT contact
      {
      public:
         
         int      m_iIndex;
         string   m_strId;
         string   m_strName;
         string   m_strPresenceStatus;
         string   m_strEmail;


         void parse(::xml::node * pnode);


      };

      class CLASS_DECL_CA2_TESSERACT contact_list :
         public array_ptr_alloc < contact >
      {
      public:

         bool  m_bUserPresenceLicensed;

         void parse(::xml::document * pdoc);

      };

      class CLASS_DECL_CA2_TESSERACT draw_contact
      {
      public:

         rect        m_rectItem;
         rect        m_rectStatusImage;
         rect        m_rectName;

         void draw(::i2com::contact_view * pview, ::ca::graphics * pdc, contact_list * plist, contact * pcontact);

      };

      class CLASS_DECL_CA2_TESSERACT draw_contact_list :
         public array_ptr_alloc < draw_contact >
      {
      public:


         int m_iItemHeight;

         draw_contact_list();

         void layout(LPCRECT lpcrect, contact_list * plist);
         void draw(::i2com::contact_view * pview, ::ca::graphics * pdc, contact_list * plist);

      };

      ::xml::document         m_document;
      contact_list            m_list;
      draw_contact_list       m_drawlist;


      contact_view(::ca::application * papp);


      virtual void _001OnDraw(::ca::graphics * pdc);
      
      virtual void install_message_handling(::user::win::message::dispatch * pdispatch);

      virtual void refresh();

      DECL_GEN_SIGNAL(_001OnCreate)
      DECL_GEN_SIGNAL(_001OnTimer)
      DECL_GEN_SIGNAL(_001OnLButtonUp)

      virtual void layout();


      int hit_test(point pt, e_element & eelement);


   };


} // namespace i2com


