#pragma once

namespace loginstartup
{

class CLASS_DECL_CA2_LOGINSTARTUP form_callback :
   virtual public ex1::form_callback
{
public:
   form_callback();
   virtual ~form_callback();

   void on_update(ex1::form * pview, BaseView* pSender, LPARAM lHint, base_object* phint);
   virtual bool BaseOnControlEvent(ex1::form * pview, BaseControlEvent * pevent);
};

} // namespace loginstartup