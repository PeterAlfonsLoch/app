#pragma once


namespace draw2d_cairo
{


   class CLASS_DECL_DRAW2D_CAIRO path :
      virtual public ::draw2d_cairo::object,
      virtual public ::draw2d::path
   {
   public:





      path(sp(::base::application) papp);
      virtual ~path();


   };









} // namespace draw2d_cairo



