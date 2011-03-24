#pragma once

class CLASS_DECL_CA2_CUBE CDDeviceListView :
   public simple_list_view
{
public:
   CDDeviceListView(::ca::application * papp);
   // // DECLARE_DYNCREATE(CDDeviceListView)

// Attributes
public:
   
// Operations
public:
   bool CacheCDList();

// Overrides
   virtual bool _001GetItemText(string &str, index iItem, index iSubItem, index iListItem);
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CDDeviceListView)
   protected:
   virtual void OnDraw(::ca::graphics * pgraphics);      // overridden to draw this ::view
   virtual void on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint);
   //}}AFX_VIRTUAL
   virtual index _001GetItemCount();

// Implementation
protected:
   virtual ~CDDeviceListView();
#ifdef _DEBUG
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif

};

