#pragma once


namespace xml
{


   class output_tree;


   class CLASS_DECL_AURA exportable :
      virtual public ::object
   {
   public:


      exportable();


      virtual void xml_export(output_tree & xmlof) = 0;


   };


} // namespace xml







