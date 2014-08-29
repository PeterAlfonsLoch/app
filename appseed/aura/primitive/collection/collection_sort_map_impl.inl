#pragma once


template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
void sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE, m_bMultiKey >::add_pair(ARG_KEY key,ARG_VALUE newValue)
{

   if(m_pnode == NULL)
   {
      m_pnode = new node(key,newValue);
      return;
   }

   node * pnode = m_pnode;

   while(true)
   {
      if(compare(key,pnode->m_element1))
      {

         if(pnode->left == NULL)
         {

            pnode->left = new node(key,newValue);

            return;

         }
         else
         {

            pnode = pnode->left;

         }

      }
      else if(m_bMultiKey || compare(pnode->m_element1, key))
      {

         if(pnode->right == NULL)
         {

            pnode->right = new node(key, newValue);

            return;

         }
         else
         {

            pnode = pnode->right;

         }

      }
      else
      {
         
         pnode->m_element2 = newValue;

         return;

      }

   }


}


template < class KEY,class ARG_KEY,class VALUE,class ARG_VALUE,class COMPARE, bool m_bMultiKey >
void sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE, m_bMultiKey >::insert(const pair < KEY,VALUE > & pair)
{

   add_pair(pair.m_element1,pair.m_element2);

}


template < class type_map >
sort_attrib_map < type_map > & sort_attrib_map < type_map >::operator = (const sort_attrib_map & attribmap)
{

   if(this != &attribmap)
   {

      this->remove_all();

      typename type_map::pair * ppair;

      for(index i = 0; i < attribmap.m_ptra.get_count(); i++)
      {

         ppair      = new typename type_map::pair(attribmap.m_ptra[i]->m_element1);

         ppair->m_element2    = attribmap.m_ptra[i]->m_element2;

         this->m_ptra.add(ppair);

      }

   }

   return *this;

}
