#pragma once

class var;
class CLASS_DECL_ca variable_strict_compare
{
public:
   variable_strict_compare(const var & var);
   variable_strict_compare(const variable_strict_compare & compare);

   const var & m_var;

   bool operator == (const var & var) const;
   bool operator == (const char * psz) const;
   bool operator == (const string & str) const;
   bool operator == (double d) const;
   bool operator == (int i) const;
   bool operator == (bool b) const;

   bool operator != (const var & var) const;
   bool operator != (const char * psz) const;
   bool operator != (const string & str) const;
   bool operator != (double d) const;
   bool operator != (int i) const;
   bool operator != (bool b) const;

   friend bool CLASS_DECL_ca operator == (const char * psz, const variable_strict_compare & var);
   friend bool CLASS_DECL_ca operator == (const string & str, const variable_strict_compare & var);
   friend bool CLASS_DECL_ca operator == (double d, const variable_strict_compare & var);
   friend bool CLASS_DECL_ca operator == (int i, const variable_strict_compare & var);
   friend bool CLASS_DECL_ca operator == (bool b, const variable_strict_compare & var);

   friend bool CLASS_DECL_ca operator != (const char * psz, const variable_strict_compare & var);
   friend bool CLASS_DECL_ca operator != (const string & str, const variable_strict_compare & var);
   friend bool CLASS_DECL_ca operator != (double d, const variable_strict_compare & var);
   friend bool CLASS_DECL_ca operator != (int i, const variable_strict_compare & var);
   friend bool CLASS_DECL_ca operator != (bool b, const variable_strict_compare & var);

};

