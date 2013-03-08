#pragma once


namespace user
{

   class keyboard_layout;

   class CLASS_DECL_ca keyboard :
      virtual public ::ca::object
   {
   public:

      ::collection::int_map < ::user::e_key >         m_mapKey;
      keyboard_layout *                               m_playout;

      keyboard(::ca::application * papp);

      virtual class keyboard_layout & layout();

      bool load_layout(const char * pszPath, bool bUser);

      string process_key(::user::e_key ekey);

      string process_char(const char * pszChar);

      string process_escape(const char * pszChar);

      void process_escape(::xml::node * pnode, ::ca::property_set & set);

      string get_current_system_layout();

      bool initialize(::user::keyboard_layout_id * playoutid, const char * pszPath);

      void translate_os_key_message(::ca::message::key * pkey);

      virtual void load_os_layout(const char * pszPath);

   };

} // namespace user