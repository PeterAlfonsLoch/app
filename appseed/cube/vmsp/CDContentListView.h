#if !defined(AFX_CDCONTENTLISTVIEW_H__50F581D7_3482_44A9_B854_384B80E43FAA__INCLUDED_)
#define AFX_CDCONTENTLISTVIEW_H__50F581D7_3482_44A9_B854_384B80E43FAA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CDContentListView.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CDContentListView ::view

class CLASS_DECL_CA2_CUBE CDContentListView :
   public simple_list_view
{
public:
   CDContentListView(::ca::application * papp);
   // // DECLARE_DYNCREATE(CDContentListView)

// Attributes
public:

// Operations
public:

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CDContentListView)
   protected:
   virtual void OnDraw(::ca::graphics * pgraphics);      // overridden to draw this ::view
   //}}AFX_VIRTUAL

// Implementation
protected:
   virtual ~CDContentListView();
#ifdef _DEBUG
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif

   // Generated message ::collection::map functions
protected:
   //{{AFX_MSG(CDContentListView)
      // NOTE - the ClassWizard will add and remove member functions here.
   //}}AFX_MSG
   ()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CDCONTENTLISTVIEW_H__50F581D7_3482_44A9_B854_384B80E43FAA__INCLUDED_)
