#pragma once

class Mixer;
class MixerDestination;

class CLASS_DECL_ca MixerDoc : public ::userbase::document
{
public:


   MixerDoc(::ca::application * papp);
   

   virtual BOOL on_new_document();
   virtual ~MixerDoc();
#ifdef _DEBUG
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif


};

