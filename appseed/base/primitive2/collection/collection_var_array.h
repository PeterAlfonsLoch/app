#pragma once




class CLASS_DECL_BASE var_array : 
   public ::file::serializable_array < array < var > >
{
public:


   var_array(sp(::axis::application) papp = NULL);
   var_array(const stringa & stra);
   var_array(const int_array & inta);
   var_array(const property_set & propset);
   var_array(const var_array & vara);
   virtual ~var_array();


   index add(var var);
   ::count add(const var_array & vara);

   string implode(const char * pszGlue) const;

   index find_first_ci(const char * psz, index find = 0, index last = -1) const;
   index find_first(const char * psz, index find = 0, index last = -1) const;
   index find_first(const var & var, index find = 0, index last = -1) const;

   bool contains_ci(const char * lpcsz, index find = 0, index last = -1, ::count countMin = 1, ::count countMax = -1) const;
   bool contains(const char * lpcsz, index find = 0, index last = -1, ::count countMin = 1, ::count countMax = -1) const;
   bool contains(const var & var, index find = 0, index last = -1, ::count countMin = 1, ::count countMax = -1) const;

   ::count remove_first_ci(const char * lpcsz, index find = 0, index last = -1);
   ::count remove_first(const char * lpcsz, index find = 0, index last = -1);
   ::count remove_first(const var & var, index find = 0, index last = -1);

   ::count remove_ci(const char * lpcsz, index find = 0, index last = -1, ::count countMin = 0, ::count countMax = -1);
   ::count remove(const char * lpcsz, index find = 0, index last = -1, ::count countMin = 0, ::count countMax = -1);
   ::count remove(const var & var, index find = 0, index last = -1, ::count countMin = 0, ::count countMax = -1);
   
   ::count remove(const var_array & vara);

   var_array & operator -=(var var);
   var_array & operator -=(var_array vara);
   var_array operator -(var var) const;
   var_array operator -(var_array vara) const;
   var_array & operator +=(var var);
   var_array & operator +=(var_array vara);
   var_array operator +(var var) const;
   var_array operator +(var_array vara) const;

   var_array & operator = (const stringa & stra);
   var_array & operator = (const int_array & inta);
   var_array & operator = (const property_set & propset);
   var_array & operator = (const var_array & vara);


   void parse_json(const char * & pszJson);
   void parse_json(const char * & pszJson, const char * pszEnd);

   string get_json();


};



