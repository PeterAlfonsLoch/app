#pragma once



namespace xml
{


   template < int32_t m_iNodeNameIndex, class TYPE >
   void
      smart_pointer_array<m_iNodeNameIndex, TYPE>::
      xml_export(output_tree & xmlof)
   {
      xmlof.set_attr("count", this->get_size());
      for (int32_t i = 0; i < this->get_size(); i++)
      {
         node * pnode = xmlof.export_node(xmlof.get_node_name(m_iNodeNameIndex), this->operator()(i));
         pnode->add_attr("array_index", i);
      }
   }


   template < int32_t m_iNodeNameIndex, class TYPE >
   void
      smart_pointer_array<m_iNodeNameIndex, TYPE>::
      xml_import(input_tree & xmlif)
   {
      int32_t iSize;
      xmlif.get_attr("count", iSize);
      this->set_size_create(iSize);
      for (int32_t i = 0; i < this->get_size(); i++)
      {
         attr_array attra(this->get_app());
         attra.add("array_index", i);
         xmlif.import_node(xmlif.get_node_name(m_iNodeNameIndex), attra, this->operator()(i));
      }
   }

} // namespace xml


  //
  //namespace file
  //{
  //
  //
  //   template < class T >
  //   bool system::output(::aura::application * papp,const char * pszOutput,T * p,bool (T::*lpfnOuput)(::file::ostream &,const char *),const char * lpszSource)
  //   {
  //
  //      System.dir().mk(System.dir().name(pszOutput),papp);
  //
  //      ::file::file_sp fileOut = papp->m_paurasession->file_get_file(pszOutput,::file::mode_create | ::file::type_binary | ::file::mode_write);
  //
  //      if(fileOut.is_null())
  //         return false;
  //
  //      ::file::ostream ostream(fileOut);
  //
  //      return (p->*lpfnOuput)(ostream,lpszSource);
  //
  //   }
  //
  //
  //   template < class T >
  //   bool system::output(::aura::application * papp,const char * pszOutput,T * p,bool (T::*lpfnOuput)(::file::ostream &,::file::istream &),const char * lpszInput)
  //   {
  //
  //      System.dir().mk(System.dir().name(pszOutput),papp);
  //
  //      ::file::file_sp fileOut = papp->m_paurasession->file_get_file(pszOutput,::file::mode_create | ::file::type_binary | ::file::mode_write);
  //
  //      if(fileOut.is_null())
  //         return false;
  //
  //      ::file::file_sp fileIn = papp->m_paurasession->file_get_file(lpszInput,::file::type_binary | ::file::mode_read);
  //
  //      if(fileIn.is_null())
  //         return false;
  //
  //      ::file::ostream ostream(fileOut);
  //
  //      ::file::istream istream(fileIn);
  //
  //      return (p->*lpfnOuput)(ostream,istream);
  //
  //   }
  //
  //
  //   template < class T >
  //   bool system::output(::aura::application * papp,const char * pszOutput,T * p,bool (T::*lpfnOuput)(::file::ostream &,::file::istream &),::file::istream & istream)
  //   {
  //
  //      ::file::ostream ostream(get(pszOutput,papp));
  //
  //      return (p->*lpfnOuput)(ostream,istream);
  //
  //   }
  //
  //
  //} // namespace file
  //
  //



