#pragma once
namespace user{

   class CLASS_DECL_BASE schema_layered_frame:
      virtual public ::user::schema
   {
   public:


      virtual bool get_translucency(ETranslucency & etranslucency);

   };
} // namespace user