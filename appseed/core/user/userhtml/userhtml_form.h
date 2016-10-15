#pragma once



class CLASS_DECL_CORE html_form :
   virtual public ::user::form_view
{
public:


   string                        m_strPath;
   string                        m_strOpenOnCreate;
   rect                          m_rectOpen;

   sp(::html::form)              m_phtmlform;



   html_form(::aura::application * papp);
   virtual ~html_form();

   virtual void _001OnDraw(::draw2d::graphics * pgraphics);
   virtual void _001DrawChildren(::draw2d::graphics * pgraphics);

   //virtual void on_layout(::html::data * phtmldata);
   virtual void on_layout();

   virtual void install_message_handling(::message::dispatch * pinterface);

   virtual string get_path();

   virtual bool open_document(var varFile);


   ::html::data * get_html_data();

   html_document * get_document();


   DECL_GEN_SIGNAL(_001OnCreate);
   DECL_GEN_SIGNAL(_001OnLButtonDown);
   DECL_GEN_SIGNAL(_001OnMouseMove);
   DECL_GEN_SIGNAL(_001OnMouseLeave);
   DECL_GEN_SIGNAL(_001OnLButtonUp);
   DECL_GEN_SIGNAL(_001OnImageLoaded);
   DECL_GEN_SIGNAL(_001OnKeyDown);
   DECL_GEN_SIGNAL(_001OnDestroy);



   virtual void _001GetText(string & str) const;
   virtual void _001SetText(const string & str, ::action::context actioncontext);


   virtual void GetClientBox(::html::box & box);


   virtual void defer_implement();

   virtual void defer_layout();


   virtual bool get_edit_mode();
   virtual void set_edit_mode(bool bSet = true);
   virtual bool load_html(const string & str);


};
