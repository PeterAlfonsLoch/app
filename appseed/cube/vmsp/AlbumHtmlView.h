#pragma once

class CLASS_DECL_CA2_CUBE AlbumHtmlView :
   public html_view//,
//   public DBInterface
{
public:
   AlbumHtmlView(::ca::application * papp);
   // // DECLARE_DYNCREATE(AlbumHtmlView)

// html Data
public:
   //{{AFX_DATA(AlbumHtmlView)
      // NOTE: the ClassWizard will add data members here
   //}}AFX_DATA

// Attributes
public:
    string     m_strBasePath;
    string     m_strLastFilePath;
    string     m_strFilePath;
    bool GetGoForwardEnable();
    bool GetGoBackEnable();

protected:
//    CDBSongSet *     m_pSongsSet;
    bool            m_bGoForwardEnable;
    bool            m_bGoBackEnable;
    //COleStreamFile  m_oleStreamFile; 
public:
   VMSRESULT ReserveSong(const char * lpcszFilePath);
   VMSRESULT WriteFile(const char * lpcsz, ex1::filesp & file);
   void _GoHome();

   virtual void OnInitialUpdate();
   virtual void OnBeforeNavigate2(html::data * pdata, const char * lpszURL, DWORD nFlags, const char * lpszTargetFrameName, byte_array& baPostedData, const char * lpszHeaders, BOOL* pbCancel);
   virtual void OnCommandStateChange(long nCommand, BOOL bEnable);
   virtual void OnStatusTextChange(const char * lpszText);
   virtual void OnDocumentComplete(const char * lpszURL);
   protected:
//   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

   virtual ~AlbumHtmlView();
#ifdef _DEBUG
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif

   // Generated message ::collection::map functions
   //{{AFX_MSG(AlbumHtmlView)
   afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
      afx_msg void OnGoback();
   afx_msg void OnGoforward();
   afx_msg void OnGohome();
   afx_msg void OnUpdateGoback(cmd_ui * pcmdui);
   afx_msg void OnUpdateGoforward(cmd_ui * pcmdui);
   afx_msg void OnUpdateGohome(cmd_ui * pcmdui);
   afx_msg void OnFilePrint();
   afx_msg void OnUpdateFilePrint(cmd_ui * pcmdui);
   afx_msg void OnFilePrintPreview();
   afx_msg void OnUpdateFilePrintPreview(cmd_ui * pcmdui);
   afx_msg void OnFilePrintSetup();
   afx_msg void OnUpdateFilePrintSetup(cmd_ui * pcmdui);
   //}}AFX_MSG
   ()
};

