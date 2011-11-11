#pragma once

namespace html
{

   class attribute
   {
   public:

      void set_name(const char * pszName);
      string get_name();

      void set_value(const char * pszValue);
      string get_value();

   protected:
      string   m_strName;
      string   m_strValue;
   };


   class attribute_array : public array_ptr_alloc < attribute, attribute & >
   {
   public:
      attribute * get(const char * pszName);
      string get_value(const char * pszName);
   };



} // namespace html