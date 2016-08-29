#pragma once


namespace estamira
{


   class CLASS_DECL_ESTAMIRA application :
      virtual public ::hellomultiverse::application,
      virtual public ::multimedia::application
   {
   public:


      sp(::estamira::game)       m_pgame;


      application();
      virtual ~application();


      virtual bool initialize_instance();
      virtual int32_t  exit_instance();

   };


} // namespace estamira





