#pragma once


#ifndef WINDOWS


typedef void * HKL;


#endif


namespace user
{

   class CLASS_DECL_AXIS keyboard_layout_id
   {
   public:


      string                     m_strName;
      string                     m_strPath;
      string                     m_countrycode;
      comparable_array < HKL >   m_hkla;
      string                     m_keylayout;


      keyboard_layout_id();
      keyboard_layout_id(const keyboard_layout_id & id);


      keyboard_layout_id & operator = (const keyboard_layout_id & id);


      bool operator < (const keyboard_layout_id & layout) const;
      bool operator <= (const keyboard_layout_id & layout) const;
      bool operator == (const keyboard_layout_id & layout) const;


   };

   class CLASS_DECL_AXIS keyboard_layout_ida :
      virtual public comparable_array < keyboard_layout_id >
   {
   public:
   };


   class CLASS_DECL_AXIS keyboard_layout :
      virtual public ::object,
      virtual public keyboard_layout_id
   {
   public:


//      int_to_string         m_mapChar;
  //    int_to_string         m_mapKey;
      int_to_string         m_mapCode;

      string                              m_strEscape;
      property_set                   m_setEscape;


      keyboard_layout(sp(::aura::application) papp);

      bool load(const char * pszPath);

      string process_key(int32_t iCode);

      string process_char(const char * pszChar);

      string process_escape(const char * pszChar);

      void process_escape(sp(::xml::node) pnode, property_set & set);

      string get_current_system_layout();

      bool initialize(::user::keyboard_layout_id * playoutid, const char * pszPath);

   };

} // namespace user
