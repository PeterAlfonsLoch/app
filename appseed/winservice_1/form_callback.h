#pragma once

namespace command
{

class CLASS_DECL_CA2_WINSERVICE_1 form_callback :
   virtual public ex1::form_callback
{
public:
   form_callback();
   virtual ~form_callback();

   void OnUpdate(ex1::form_interface * pview, BaseView* pSender, LPARAM lHint, base_object* phint);
   virtual bool BaseOnControlEvent(ex1::form_interface * pview, BaseControlEvent * pevent);
};

} // namespace command