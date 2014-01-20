#include "framework.h"


namespace xml
{


   entity::entity()
   {
   }

   entity::entity(char chEntity, const char * pszReference)
   {
      m_chEntity  = chEntity;
      m_strRef    = pszReference;
      m_iRefLen   = (int32_t) strlen(pszReference);
   }

   entity::entity(const entity & entity)
   {
      operator = (entity);
   }

   entity & entity::operator = (const entity & entity)
   {
      if(this != &entity)
      {
         m_chEntity  = entity.m_chEntity;
         m_strRef    = entity.m_strRef;
         m_iRefLen   = entity.m_iRefLen;
      }
      return *this;
   }


   void entities::add_entity(char chEntity, const char * pszReference)
   {
      add(entity(chEntity, pszReference));
   }

   entity * entities::get_entity( int32_t m_chEntity )
   {
      for( int32_t i = 0 ; i < this->get_size(); i ++ )
      {
         if( this->element_at(i).m_chEntity == m_chEntity )
            return (class entity *)(&this->element_at(i));
      }
      return NULL;
   }

   entity * entities::get_entity(const char * pszEntity)
   {
      for( int32_t i = 0 ; i < this->get_size(); i ++ )
      {
         const char * pszRef = this->element_at(i).m_strRef;
         const char * psz = pszEntity;
         while(*pszRef)
            if(*pszRef++ != *psz++)
               break;
         if(!*pszRef)   // found!
            return (class entity *)(&this->element_at(i));
      }
      return NULL;
   }

   int32_t entities::get_entity_count( const char * str )
   {
      int32_t nCount = 0;
      char * ps = (char *)str;
      while( ps && *ps )
         if( get_entity( *ps++ ) ) nCount ++;
      return nCount;
   }

   int32_t entities::ref_to_entity( const char * estr, char * str, int32_t strlen )
   {
      char * pes = (char *)estr;
      char * ps = str;
      char * ps_end = ps+strlen;
      while( pes && *pes && ps < ps_end )
      {
         entity * ent = get_entity( pes );
         if( ent )
         {
            // copy m_chEntity meanning char
            *ps = ent->m_chEntity;
            pes += ent->m_iRefLen;
         }
         else
            *ps = *pes++;   // default character copy
         ps++;
      }
      *ps = '\0';

      // total copied characters
      return (int32_t) (ps-str);
   }

   int32_t entities::entity_to_ref( const char * str, char * estr, int32_t estrlen )
   {
      char * ps = (char *)str;
      char * pes = (char *)estr;
      char * pes_end = pes+estrlen;
      while( ps && *ps && pes < pes_end )
      {
         entity * ent = get_entity( *ps );
         if( ent )
         {
            // copy m_chEntity string
            const char * pszRef = ent->m_strRef;
            while(*pszRef )
               *pes++ = *pszRef++;
         }
         else
            *pes++ = *ps;   // default character copy
         ps++;
      }
      *pes = '\0';

      // total copied characters
      return (int32_t) (pes-estr);
   }

   string entities::ref_to_entity(const char * pszSrc)
   {
      string strRet;
      if(pszSrc != NULL)
      {
         strsize iLen = strlen(pszSrc);
         char * pszRet = strRet.GetBufferSetLength(iLen);
         if(pszRet != NULL)
            ref_to_entity(pszSrc, pszRet, (int32_t) iLen);
         strRet.ReleaseBuffer();
      }
      return strRet;
   }

   string entities::entity_to_ref( const char * str )
   {
      string s;
      if( str )
      {
         int32_t nEntityCount = get_entity_count(str);
         if( nEntityCount == 0 )
            return string(str);
         strsize len = strlen(str) + nEntityCount*10 ;
         char * sbuf = s.GetBufferSetLength(len + 1);
         if( sbuf )
            entity_to_ref( str, sbuf, (int32_t) len);
         s.ReleaseBuffer();
      }
      return s;
   }

/*   string XRef2Entity( const char * estr )
   {
      return System.m_entities.ref_to_entity( estr );
   }

   string XEntity2Ref( const char * str )
   {
      return System.m_entities.entity_to_ref( str );
   }*/

} // namespace xml
