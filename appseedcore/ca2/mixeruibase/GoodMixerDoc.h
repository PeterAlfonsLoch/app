#pragma once

class CMixer;
class CMixerDestination;

class CLASS_DECL_ca GoodMixerDoc : 
   public MixerDoc
{
public:


   GoodMixerDoc(::ca::application * papp);
   virtual ~GoodMixerDoc();


#ifdef _DEBUG
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif

};
