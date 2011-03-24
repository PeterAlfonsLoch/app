#pragma once


namespace alarm
{

   class document;

   class CLASS_DECL_CA2_ALARM view :
      virtual public ::userbase::view
   {
   public:


      view(::ca::application * papp);
	   virtual ~view();
   #ifdef _DEBUG
	   virtual void assert_valid() const;
	   virtual void dump(dump_context& dc) const;
   #endif

      virtual void _001OnDraw(::ca::graphics * pdc);


      virtual void _001InstallMessageHandling(user::win::message::dispatch * pinterface);
      virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
      //virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
//      virtual void OnBeginPrinting(::ca::graphics* pDC, CPrintInfo* pInfo);
  //    virtual void OnEndPrinting(::ca::graphics* pDC, CPrintInfo* pInfo);
	 //  virtual void OnDraw(::ca::graphics* pDC);      // overridden to draw this view
	   virtual void on_update(::view * psender, LPARAM lHint, ::radix::object * phint);

   };

} // namespace alarm