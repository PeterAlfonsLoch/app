#pragma once


#if defined(LINUX) || defined(MACOS)


typedef void * HKL;


#endif


namespace user
{

   class CLASS_DECL_ca keyboard_layout_id
   {
   public:


      string                     m_strName;
      string                     m_strPath;
      comparable_array < HKL >   m_hkla;


      keyboard_layout_id();
      keyboard_layout_id(const keyboard_layout_id & id);


      keyboard_layout_id & operator = (const keyboard_layout_id & id);


      bool operator < (const keyboard_layout_id & layout) const;
      bool operator <= (const keyboard_layout_id & layout) const;
      bool operator == (const keyboard_layout_id & layout) const;


   };

   class CLASS_DECL_ca keyboard_layout_ida :
      virtual public comparable_array < keyboard_layout_id >
   {
   public:
   };


   class CLASS_DECL_ca keyboard_layout :
      virtual public ::radix::object,
      virtual public keyboard_layout_id
   {
   public:


      ::collection::int_to_string         m_mapChar;
      ::collection::int_to_string         m_mapKey;
      ::collection::int_to_string         m_mapCode;

      string                              m_strEscape;
      gen::property_set                   m_setEscape;


      keyboard_layout(::ca::application * papp);

      bool load(const char * pszPath);

      string process_key(int iCode, int iKey, int iFlags);

      string process_char(const char * pszChar);

      string process_escape(const char * pszChar);

      void process_escape(::xml::node * pnode, gen::property_set & set);

      string get_current_system_layout();

      bool initialize(::user::keyboard_layout_id * playoutid, const char * pszPath);

   };

} // namespace user
