#pragma once



class CLASS_DECL_CORE html_form :
   virtual public ::user::form
{
public:


   string                        m_strPath;
   string                        m_strOpenOnCreate;
   rect                          m_rectOpen;
   html::elemental *             m_pelementalLButtonDown;
   html::elemental *             m_pelementalHover;
   spa(::html::elemental)        m_elementalptraMouseMove;
   sp(html::data)                m_sphtmldata;



   html_form(sp(::base::application) papp);
   virtual ~html_form();

   virtual void _001OnDraw(::draw2d::graphics * pdc);
   virtual void _001DrawChildren(::draw2d::graphics *pdc);

   //virtual void layout(::html::data * phtmldata);
   virtual void layout();

   virtual void install_message_handling(::message::dispatch * pinterface);

   virtual string get_path();

   virtual bool open_document(var varFile);


   ::html::data * get_html_data();
   const ::html::data * get_html_data() const;


   DECL_GEN_SIGNAL(_001OnCreate);
   DECL_GEN_SIGNAL(_001OnLButtonDown);
   DECL_GEN_SIGNAL(_001OnMouseMove);
   DECL_GEN_SIGNAL(_001OnMouseLeave);
   DECL_GEN_SIGNAL(_001OnLButtonUp);
   DECL_GEN_SIGNAL(_001OnImageLoaded);
   DECL_GEN_SIGNAL(_001OnKeyDown);



   virtual void _001GetText(string & str) const;
   virtual void _001SetText(const string & str, ::action::context actioncontext);


   virtual void GetClientBox(::html::box & box);


   virtual void defer_implement();

   virtual void defer_layout();


};
