#pragma once

namespace windesk
{

class CLASS_DECL_CA2_WINDESK menu_right_view :
   public ::userbase::view
{
public:
   menu_right_view(::ca::application * papp);

   virtual void OnDraw(::ca::graphics * pdc);
};

} // namespace windesk