#pragma once

class simple_tool_bar;

namespace userbase
{

   class tool_bar;

   class CLASS_DECL_ca image_manager :
      virtual public ::radix::object
   {
   public:
      //void LoadToolbar(tool_bar & toolbar, UINT * user);
      //void LoadToolbar(simple_tool_bar & toolbar, UINT * user);
      image_list & GetImageList();
      image_list & GetImageListDisable();
      bool Initialize(::ax::application * papp, UINT uiaMenuV003Map [][2]);
      image_manager();
      virtual ~image_manager();

      image_list * m_pimagelist;
      image_list * m_pimagelistDisable;
      ///CBaseNumericDiscreteRelation < UINT, UINT, UINT, UINT > m_rel;
      ::collection::map < id, id, UINT, UINT > m_rel;

   };

} // namespace userbase