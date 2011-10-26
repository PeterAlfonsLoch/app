#pragma once

namespace i2com
{

class CLASS_DECL_CA2_TESSERACT child_frame :
   public simple_child_frame
{
public:
   child_frame(::ca::application * papp);

     simple_toolbar        m_toolbar;
public:
   bool CreateBars();
   bool DestroyBars();
   public:
   virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg); 

   virtual ~child_frame();

   DECL_GEN_SIGNAL(_001OnAppLanguage)
   DECL_GEN_SIGNAL(_001OnCreate)

};

} // namespace i2com