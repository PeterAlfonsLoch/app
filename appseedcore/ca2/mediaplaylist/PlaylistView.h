#pragma once

class PlaylistDoc;

class CLASS_DECL_ca CPlaylistView : public simple_list_view
{
public:


   CPlaylistView(::ca::application * papp);
   virtual ~CPlaylistView();


   PlaylistDoc * get_document();

   virtual void on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint);
#ifdef _DEBUG
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif

   virtual void _001InsertColumns();
};

