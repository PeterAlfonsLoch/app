#pragma once

class CLASS_DECL_ca simple_status_bar :
   public ::userbase::status_bar
{
public:
   simple_status_bar(::ax::application * papp);

   virtual void _001OnDraw(::ax::graphics * pdc);
   virtual ~simple_status_bar();

};
