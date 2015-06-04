


simple_mesh_data::simple_mesh_data(::aura::application * papp) :
object(papp),
::user::mesh_data(papp)
{


}


simple_mesh_data::~simple_mesh_data()
{

}



void simple_mesh_data::_001GetItemText(::user::mesh_item * pitem)
{

   if(pitem->m_iItem < 0)
   {

      return_(pitem->m_bOk,false);

   }

   auto passoc = m_map.PLookup(pitem->m_iItem);

   if(passoc != NULL)
   {

      auto passoc2 = passoc->m_element2.PLookup(pitem->m_iColumn);

      if(passoc2 != NULL)
      {

         pitem->m_strText = passoc2->m_element2;

         return_(pitem->m_bOk,true);

      }

   }


   return_(pitem->m_bOk,false);

}


int_ptr simple_mesh_data::_001GetItemCount()
{

   return 32768;

}


int_ptr simple_mesh_data::_001GetColumnCount(::user::mesh * pmesh)
{
   
   return 32768;

}


void simple_mesh_data::clear()
{

   m_map.remove_all();

}


