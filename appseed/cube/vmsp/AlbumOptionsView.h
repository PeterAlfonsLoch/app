#pragma once

class CLASS_DECL_CA2_CUBE AlbumOptionsView : public form_view
{
public:
   AlbumOptionsView(::ca::application * papp);           

//   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

   virtual ~AlbumOptionsView();
#ifdef _DEBUG
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif

};

