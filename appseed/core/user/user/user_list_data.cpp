

namespace user
{

 
   list_data::list_data(::aura::application * papp) :
      object(papp),
      mesh_data(papp)
   {
    
   }

   
   list_data::~list_data()
   {

   }


   count list_data::_001GetColumnCount(mesh * pmesh)
   {

      return pmesh->m_plist->m_columna.VisibleGetCount();;

   }



} // namespace user






