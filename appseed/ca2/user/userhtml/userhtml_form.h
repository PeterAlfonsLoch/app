#pragma once



class CLASS_DECL_ca2 html_form :
   virtual public ::user::form
{
public:


   string                        m_strPath;
   string                        m_strOpenOnCreate;
   rect                          m_rectOpen;
   html::elemental *             m_pelementalLButtonDown;
   spa(::html::elemental)        m_elementalptraMouseMove;
   sp(html::data)                m_sphtmldata;



   html_form(sp(::ca2::application) papp);
   virtual ~html_form();

   virtual void _001OnDraw(::ca2::graphics * pdc);
   virtual void _001DrawChildren(::ca2::graphics *pdc);

   //virtual void layout(::html::data * phtmldata);
   virtual void layout();

   virtual void install_message_handling(::ca2::message::dispatch * pinterface);

   virtual string get_path();

   virtual bool open_document(var varFile);


   ::html::data * get_html_data();
   const ::html::data * get_html_data() const;


   DECL_GEN_SIGNAL(_001OnCreate);
   DECL_GEN_SIGNAL(_001OnLButtonDown)
   DECL_GEN_SIGNAL(_001OnMouseMove)
   DECL_GEN_SIGNAL(_001OnLButtonUp)
   DECL_GEN_SIGNAL(_001OnImageLoaded)
   DECL_GEN_SIGNAL(_001OnKeyDown)



   virtual void _001GetText(string & str);
   virtual void _001SetText(const char * psz);


   virtual void GetClientBox(::html::box & box);


   virtual void defer_implement();

   virtual void defer_layout();


};