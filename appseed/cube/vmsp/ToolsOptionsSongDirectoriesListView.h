#pragma once

class CLASS_DECL_CA2_CUBE CToolsOptionsSongDirectoriesListView : public simple_list_view
{
public:
   CToolsOptionsSongDirectoriesListView(::ca::application * papp);
   // // DECLARE_DYNCREATE(CToolsOptionsSongDirectoriesListView)

// Attributes
public:

   virtual bool _001GetItemText(
               string &str,
               index iItem,
               index iSubItem, 
               index iListItem);


// Operations
public:
   virtual void _001InsertColumns();
   virtual index _001GetItemCount();

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CToolsOptionsSongDirectoriesListView)
   protected:
   virtual void OnDraw(::ca::graphics * pgraphics);      // overridden to draw this ::view
   virtual void on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint);
   //}}AFX_VIRTUAL

// Implementation
protected:
   virtual ~CToolsOptionsSongDirectoriesListView();
#ifdef _DEBUG
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif

};

