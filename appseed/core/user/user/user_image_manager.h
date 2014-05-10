#pragma once

class simple_tool_bar;

namespace user
{

   class tool_bar;

   class CLASS_DECL_CORE image_manager :
      virtual public ::object
   {
   public:
      //void LoadToolbar(tool_bar & toolbar, UINT * user);
      //void LoadToolbar(simple_tool_bar & toolbar, UINT * user);
      image_list & GetImageList();
      image_list & GetImageListDisable();
      bool Initialize(sp(::base::application) papp, UINT uiaMenuV003Map [][2]);
      image_manager();
      virtual ~image_manager();

      sp(image_list) m_pimagelist;
      sp(image_list) m_pimagelistDisable;
      ///CBaseNumericDiscreteRelation < UINT, UINT, UINT, UINT > m_rel;
      map < id, id, UINT, UINT > m_rel;

   };

} // namespace user