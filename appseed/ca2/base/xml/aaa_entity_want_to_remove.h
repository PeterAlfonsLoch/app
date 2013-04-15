#pragma once

namespace xml
{

   class CLASS_DECL_ca2 entity
   {
   public:

      char     m_chEntity;      // entity ( & " ' < > )
      string   m_strRef;      // entity reference ( &amp; &quot; etc )
      int      m_iRefLen;      // entity reference length

      entity();
      entity(char chEntity, const char * pszReference);
      entity(const entity & entity);
      entity & operator = (const entity & entity);
   };

   class CLASS_DECL_ca2 entities :
      public base_array < entity >
   {
   public:

      entity * get_entity( int entity );
      entity * get_entity(const char * pszEntity);

      int get_entity_count( const char * str );

      int ref_to_entity( const char * estr, char * str, int strlen );
      int entity_to_ref( const char * str, char * estr, int estrlen );

      string ref_to_entity( const char * estr );
      string entity_to_ref( const char * str );

      void add_entity(char chEntity, const char * pszReference);

   };

   string XRef2Entity( const char * estr );
   string XEntity2Ref( const char * str );

} // namespace xml
