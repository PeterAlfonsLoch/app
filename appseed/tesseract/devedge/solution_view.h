#pragma once

namespace devedge
{


   class solution_view :
      virtual public ::userbase::view,
      virtual public ::user::tree
   {
   public:
      solution_view(::ca::application * papp);

      ::ex1::tree_item *       m_pitemSolution;

      virtual void install_message_handling(::user::win::message::dispatch * pinterface);

      void load();

      void _001OnOpenItem(::ex1::tree_item *pitem);

   };

} // namespace devedge