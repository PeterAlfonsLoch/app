#pragma once

namespace xml
{
   
   class node;


   typedef ::gen::property attr;


   class CLASS_DECL_ca attr_array :
      public gen::property_set
   {
   public:
      attr_array(::ca::application * papp);
      attr_array(node * pnodeParent);
      node *   m_pnodeParent;
   };


/*   class CLASS_DECL_ca attr
   {
   public:
      attr();
      virtual ~attr();

      class CLASS_DECL_ca base_array :
         public array_ptr_alloc < attr >,
         public gen::str_str_interface
      {
      public:
         base_array();
         base_array(node * pnodeParent);
         node *   m_pnodeParent;
         bool contains(base_array & attra);
         bool contains(stringa & straNames);
         index find(attr & attr, index iStart = 0);
         var get_value(const char * pszName);
         bool get_value(const char * pszName, string & strValue, index iStart = 0);
         bool get_value(const char * pszName, int & iValue, index iStart = 0);
         void str_str_interface_set(const char * pszKey, const char * pszValue);
         const string_composite str_str_interface_get_value(int i) const;
         string_composite str_str_interface_get_value(int i);
         const string_composite str_str_interface_get_key(int i) const;
         int str_str_interface_get_count() const;
      };


      virtual void SetName(const char * lpcszName);
      virtual void SetValue(const char * lpcszValue);

      virtual void get_name(string & lpcszName);
      virtual void get_value(string & strValue);

      virtual void SetValue(int iValue);
      virtual void get_value(int & iValue);

      attr & operator = (const attr & attr);
      string   get_xml(disp_option * opt = &g_optDefault);
      //The name of the attr
      string m_strName;
      //The value of the attr
      string m_strValue;

      node *   m_pnodeParent;

      attr(const attr & attr);

      bool operator == (const attr & attr) const;

   };*/

} // namespace xml