#pragma once

class syllomatter_document;
class syllomatter_list_view;


class CLASS_DECL_CA2_TESSERACT syllomatter_view :
   public form_view
{
public:
   syllomatter_view(::ca::application * papp);

   class extract : 
      virtual public ::radix::object
   {
   public:
      extract(::ca::application * papp);
      syllomatter_view *   m_pview;
      string               m_strCopy;
      string               m_strCheck;
      string               m_strLogFilePath;
   };

   int      m_iBufSize;
   char *   m_buf1;
   char *   m_buf2;
   int m_iMessageId;

   virtual ~syllomatter_view();
#ifdef _DEBUG
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif

   virtual void _001OnDraw(::ca::graphics * pdc);

   void on_document_complete(const char * pszUrl);

   syllomatter_list_view * get_list();

   virtual void install_message_handling(::user::win::message::dispatch * pinterface);
   virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
   virtual void OnDraw(::ca::graphics * pgraphics);      // overridden to draw this ::view
   DECL_GEN_SIGNAL(_001OnInitialUpdate)
   virtual void on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint);

   bool BaseOnControlEvent(::user::control_event * pevent);

   void start_syllomatter_extract(const char * pszCopy, const char * pszCheck);
   static UINT AFX_CDECL ThreadProc_syllomatter_extract(LPVOID lpParam);
   void syllomatter_extract(extract * pextract);
   int syllomatter_defer_extract(extract * pextract, const char * pszTopic);
   int bin_cmp(const char * pszFilePath1, const char * pszFilePath2);

   syllomatter_document * get_document();

   DECL_GEN_SIGNAL(_001OnDestroy)
   DECL_GEN_SIGNAL(_001OnSize)
   DECL_GEN_SIGNAL(_001OnPaint)
   DECL_GEN_SIGNAL(_001OnCreate)
   DECL_GEN_SIGNAL(_001OnContextMenu)
   DECL_GEN_SIGNAL(_001OnSetCursor)
   DECL_GEN_SIGNAL(_001OnEraseBkgnd)
   DECL_GEN_SIGNAL(_001OnUpdateViewEncoding)
   DECL_GEN_SIGNAL(_001OnViewEncoding)
   DECL_GEN_SIGNAL(_001OnWavePlayerEvent)

   virtual void _001OnTabClick(int iTab);
   
};

