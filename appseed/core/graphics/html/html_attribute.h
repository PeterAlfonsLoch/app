#pragma once


namespace html
{


   class attribute :
      virtual public element
   {
   public:


      string   m_strName;
      string   m_strValue;


      void set_name(const char * pszName);
      string get_name() const;

      void set_value(const char * pszValue);
      string get_value() const;


   };


   class attribute_array : public spa(attribute)
   {
   public:


      attribute * get(const char * pszName);
      const attribute * get(const char * pszName) const;
      string get_value(const char * pszName) const;


   };



} // namespace html


