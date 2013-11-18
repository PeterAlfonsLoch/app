#pragma once


#define WM_SIZEPARENT       0x0361  // lParam = &__SIZEPARENTPARAMS



namespace user
{


   CLASS_DECL_BASE sp(::user::interaction) get_parent_owner(sp(::user::interaction) pui);
   CLASS_DECL_BASE bool is_descendant(sp(::user::interaction) puiParent, sp(::user::interaction) puiChild);


} // namespace user





