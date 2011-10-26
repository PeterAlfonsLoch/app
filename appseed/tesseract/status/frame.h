#pragma once

namespace status
{

class CLASS_DECL_CA2_TESSERACT frame : public simple_frame_window
{
   
public:
   frame(::ca::application * papp);
   // // DECLARE_DYNCREATE(frame)

public:
   
public:
   virtual ~frame();
#ifdef _DEBUG
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif


protected:


};

} // namespace status