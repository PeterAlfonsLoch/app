#pragma once

namespace vmssyncheditor
{

   class document;

class token_list_view :
   public SimpleFormListView
{
public:
   token_list_view(::ca::application * papp);

	document * get_document();

	bool GetToken(int i, string & str);
	bool SetToken(int i, LPCSTR lpcsz, data_update_hint * puh = NULL);
	void _001OnClick(UINT uiFlags, point point, int iItem, int iSubItem);
   bool _001GetItemText(string &wstr, int iItem, int iSubItem, int iListItem);
	virtual void _001InsertColumns();

	DECL_GEN_VSIGNAL(data_on_after_change)

   DECL_GEN_SIGNAL(_001OnInitialUpdate)
	virtual void OnUpdate(view* pSender, LPARAM lHint, base_object* pHint);
protected:
	virtual ~token_list_view();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

   virtual int _001GetItemCount();

   bool _001OnMessageNotify(WPARAM wparam, LPARAM lparam, LRESULT & lresult);
};

#ifndef _DEBUG
inline document* token_list_view::get_document() // non-debug version is inline
{
	return (document*)m_pDocument;
}
#endif // _DEBUG

} // namespace vmssyncheditor