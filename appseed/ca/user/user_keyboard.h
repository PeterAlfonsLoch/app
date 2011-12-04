#pragma once


namespace user
{

   class keyboard_layout;

   class CLASS_DECL_ca keyboard :
      virtual public ::radix::object
   {
   public:

      keyboard_layout * m_playout;

      keyboard(::ca::application * papp);

      virtual class keyboard_layout & layout();

      bool load_layout(const char * pszPath, bool bUser);

      string process_key(int iCode, int iKey, int iFlags);

      string process_char(const char * pszChar);

      string process_escape(const char * pszChar);

      void process_escape(::xml::node * pnode, gen::property_set & set);

      string get_current_system_layout();

      bool initialize(::user::keyboard_layout_id * playoutid, const char * pszPath);

   };

} // namespace user