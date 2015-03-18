#pragma once


namespace file
{

//   inline path::path(const var & var,e_path epath): path(var.get_file_path(),epath){}
   inline path::path(const property & property,e_path epath): path(property.get_value().get_file_path(),epath){}
   inline path & path::operator = (const var & var) { return operator = (var.get_string()); }
   inline path & path::operator += (const var & var) { return operator += (var.get_string()); }
   inline path path::operator + (const var & var) const { return operator + (var.get_string()); }
   inline path path::operator + (const property & property) const { return operator + (property.get_string()); }
   inline path path::operator + (const id & id) const { return operator + (id.to_string()); }
   inline path path::operator / (const property & property) const { return operator /(::file::path(property)); }
   inline path path::folder() const { return ::file::path(::dir::name((const string &)*this),m_epath); }
   inline path path::sibling(const path & path) const   { return ::file::path(::dir::name((const string &)*this) + sep() + string(path).trim_left("\\/"),m_epath); }
   inline path path::sibling(const string & str) const   { return ::file::path(::dir::name((const string &)*this) + sep() + string(str).trim_left("\\/"),m_epath); }
   inline path path::sibling(const char * psz) const   { return ::file::path(::dir::name((const string &)*this) + sep() + string((const string &)psz).trim_left("\\/"),m_epath); }
   inline string path::extension() const { return file_extension_dup(operator const char *()); }
   inline patha path::ascendants_path() const { patha patha; return ascendants_path(patha); }
   inline patha path::ascendants_name() const { patha patha; return ascendants_name(patha); }
//   inline path path::folder() const { return ::dir::name(*this); }
   inline bool path::operator == (const var & var) const { return operator == (string(var)); }


} // namespace file


inline ::file::path operator + (const string & str,const ::file::path & path) { return ::file::path(str + string(path)); }
inline ::file::path operator + (const char * psz,const ::file::path & path) {  return ::file::path(psz + string(path)); }
inline ::file::path operator + (const var & var,const ::file::path & path) { return ::file::path(var.get_string() + string(path)); }
inline ::file::path operator / (const string & str,const ::file::path & path) { ::file::path p(str);  return p / path; }
inline ::file::path operator / (const char * psz,const ::file::path & path) { ::file::path p(psz);  return p / path; }
inline ::file::path operator / (const var & var,const ::file::path & path) { ::file::path p(var.get_file_path());  return p / path; }
