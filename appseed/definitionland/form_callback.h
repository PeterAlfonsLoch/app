#pragma once

namespace definitionland
{

class CLASS_DECL_CA2_DEFINITIONLAND form_callback :
   virtual public guiex::form_callback
{
public:
   form_callback();
   virtual ~form_callback();

   void OnUpdate(form_view * pview, BaseView* pSender, LPARAM lHint, base_object* phint);
   virtual bool BaseOnControlEvent(form_view * pview, BaseControlEvent * pevent);
};

} // namespace definitionland