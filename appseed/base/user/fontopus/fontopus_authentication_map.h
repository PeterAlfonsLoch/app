#pragma once


namespace fontopus
{


   class CLASS_DECL_BASE authentication_map :
      virtual public string_map < user_authentication >
   {
   public:

      static authentication_map m_authmap;

   };


} // namespace fontopus



