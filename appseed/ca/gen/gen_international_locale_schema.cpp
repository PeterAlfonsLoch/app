#include "StdAfx.h"


namespace gen
{


   namespace international
   {


         locale_schema::locale_schema(::ca::application * papp) :
            ca(papp)
         {

            
            m_idaLocale.set_size(0, 256);
            m_idaSchema.set_size(0, 256);

            m_bSchemaOnly           = false;
            m_bAddAlternateStyle    = true;

         }

         locale_schema::locale_schema(const locale_schema & ls) :
            ca(ls.get_app())
         {

            operator = (ls);
         
         }


         locale_schema::~locale_schema()
         {
         }


         bool locale_schema::add_locale_variant(id idLocale, id idSchema)
         {

            if(m_idLocale.is_empty())
            {
               m_idLocale = idLocale;
               if(m_idLocale.is_empty())
                  m_idLocale = "_std";
            }

            if(m_idSchema.is_empty())
            {
               m_idSchema = idSchema;
               if(m_idSchema.is_empty())
                  m_idSchema = "_std";
            }

            id idLocale2 = idLocale;
            id idSchema2 = idSchema;

            if(idLocale2.is_empty() && idSchema2.is_empty())
               return false;

            if(idLocale2.is_empty())
               idLocale2 = m_idLocale;
            
            if(idSchema2.is_empty())
               idSchema2 = m_idSchema;

            if(defer_add_locale(idLocale2, idSchema2))
            {
               _add_locale_variant(idLocale2, idSchema2);
            }

            stringa stra;
            stra.add_tokens(idLocale2, "-", FALSE);
            if(stra.get_count() > 1)
            {
               for(index i = stra.get_upper_bound(); i >= 0; i--)
               {
                  if(defer_add_locale(stra[i], idSchema))
                  {
                     _add_locale_variant(stra[i], idSchema);
                  }
               }
            }
            
            return true;

         }

         bool locale_schema::finalize(bool bRtlLayout)
         {
            return process_final_locale_schema(bRtlLayout);
         }

         bool locale_schema::finalize()
         {
            return process_final_locale_schema();
         }


         bool locale_schema::_add_locale_variant(id idLocale, id idSchema)
         {
            string idLocale2(idLocale);

            static id id_at("at");
            static id id_de_at("de-at");
            static id id_de("de");
            static id id_de_de("de-de");

            static id id_br("br");
            static id id_pt_br("pt-br");
            static id id_pt("pt");

            static id id_es("es");

            static id id_cn("cn");
            static id id_zh_cn("zh-cn");
            static id id_zh_tw("zh-tw");
            static id id_hk("hk");

            static id id_ja("ja");
            static id id_jp("jp");

            static id id_en("en");
            static id id_std("_std");

            if(idLocale == id_at)
            {
               defer_add_locale(id_de_at, idSchema);
               defer_add_locale(id_de, idSchema);
               defer_add_locale(id_de_de, idSchema);
            }
            else if(idLocale == id_br)
            {
               defer_add_locale(id_pt_br, idSchema);
               defer_add_locale(id_pt, idSchema);
               defer_add_locale(id_es, idSchema);
            }
            else if(idLocale == id_cn)
            {
               defer_add_locale(id_zh_cn, idSchema);
               defer_add_locale(id_zh_tw, idSchema);
            }
            else if(idLocale == id_hk)
            {
               defer_add_locale(id_zh_cn, idSchema);
               defer_add_locale(id_zh_tw, idSchema);
               defer_add_locale(id_cn, idSchema);
            }
            else if(idLocale == id_ja)
            {
               defer_add_locale(id_jp, idSchema);
            }
            else if(idLocale == id_jp)
            {
               defer_add_locale(id_ja, idSchema);
            }
            else if(idLocale == id_pt)
            {
               defer_add_locale(id_br, idSchema);
               defer_add_locale(id_pt_br, idSchema);
               defer_add_locale(id_es, idSchema);
            }
            else if(idLocale == id_es)
            {
               defer_add_locale(id_br, idSchema);
               defer_add_locale(id_pt_br, idSchema);
               defer_add_locale(id_pt, idSchema);
            }
            else if(idLocale == "pe")
            {
               defer_add_locale(id_es, idSchema);
               defer_add_locale(id_br, idSchema);
               defer_add_locale(id_pt_br, idSchema);
               defer_add_locale(id_pt, idSchema);
            }
            else if(idLocale == id_en)
            {
               defer_add_locale(id_std, idSchema);
            }
            else if(idLocale == "mx")
            {
               defer_add_locale(id_es, idSchema);
               defer_add_locale(id_br, idSchema);
               defer_add_locale(id_pt_br, idSchema);
               defer_add_locale(id_pt, idSchema);
            }
            else if(idLocale == "ec")
            {
               defer_add_locale(id_es, idSchema);
               defer_add_locale(id_br, idSchema);
               defer_add_locale(id_pt_br, idSchema);
               defer_add_locale(id_pt, idSchema);
            }
            else if(idLocale == "tw")
            {
               defer_add_locale(id_zh_cn, idSchema);
               defer_add_locale(id_zh_tw, idSchema);
               defer_add_locale(id_cn, idSchema);
            }
            return true;

         }


         bool locale_schema::defer_add_locale(id idLocale, id idSchema)
         {

            bool bAdded = false;

            id idSchema2;

            if(m_bAddAlternateStyle)
            {

               idSchema2 = idSchema;

               if(idSchema2 == m_idSchema && m_idSchema == m_idLocale) // if style is a locale and alternate style is locale too
               {
                  idSchema2 = idLocale;
               }

               if(idSchema2.is_empty())
               {
                  idSchema2 = "_std";
               }

               for(int i = 0; i < m_idaLocale.get_count() && i < m_idaSchema.get_count(); i++)
               {
                  if(m_idaLocale[i] == idLocale && m_idaSchema[i] == idSchema2)
                     goto step2;
               }

               m_idaLocale.add(idLocale);
               m_idaSchema.add(idSchema2);

               bAdded = true;

            }

            step2:

            idSchema2 = m_idSchema;

            if(idSchema2.is_empty())
            {
               idSchema2 = "_std";
            }

            for(int i = 0; i < m_idaLocale.get_count() && i < m_idaSchema.get_count(); i++)
            {
               if(m_idaLocale[i] == idLocale && m_idaSchema[i] == idSchema2)
                  return bAdded;
            }

            m_idaLocale.add(idLocale);
            m_idaSchema.add(idSchema2);

            return true;

         }


         bool locale_schema::process_final_locale_schema(bool bRTLLayout)
         {
         restart:
            for(index i = 0; i < m_idaLocale.get_count(); i++)
            {
               string strLocale = m_idaLocale[i];
               if(i >= m_idaSchema.get_count())
                  m_idaSchema.add(m_idSchema);
               id idSchema = m_idaSchema[i];
               int iFind = strLocale.find("-");
               if(iFind >= 0)
               {
                  id idLocale2 = strLocale.Left(iFind);
                  if(m_idaLocale.find_first(idLocale2) < 0)
                  {
                     m_idaLocale.insert_at(i + 1, idLocale2);
                     m_idaSchema.insert_at(i + 1, idSchema);
                     goto restart;
                  }
                  idLocale2 = strLocale.Mid(iFind + 1);
                  if(idLocale2.is_empty() && m_idaLocale.find_first(idLocale2) < 0)
                  {
                     m_idaLocale.insert_at(i + 1, idLocale2);
                     m_idaSchema.insert_at(i + 1, idSchema);
                     goto restart;
                  }
               }

            }


            comparable_array < id > idaLocaleAdd1;
            comparable_array < id > idaSchemaAdd1;


            if(bRTLLayout)
            {

               idaLocaleAdd1.set_size(0, 256);
               idaSchemaAdd1.set_size(0, 256);

               if(m_idaLocale.get_count() > 256)
               {
                  TRACE("What!!!!!!");
               }

               for(index i = 0; i < m_idaLocale.get_count(); i++)
               {
                  string idLocale2 = m_idaLocale[i];
                  if(i >= m_idaSchema.get_count())
                     m_idaSchema.add(m_idSchema);
                  string strSchema = m_idaSchema[i];
                  if(strSchema.CompareNoCase("_std") != 0)
                  {
                     idaLocaleAdd1.add(idLocale2);
                     idaSchemaAdd1.add(strSchema + "_rl");
                  }
               }
            }
            if(bRTLLayout)
            {
               for(index i = 0; i < m_idaLocale.get_count(); i++)
               {
                  string idLocale2 = m_idaLocale[i];
                  if(i >= m_idaSchema.get_count())
                     m_idaSchema.add("_std");
                  string strSchema = m_idaSchema[i];
                  if(strSchema.CompareNoCase("_std") != 0)
                  {
                     idaLocaleAdd1.add(idLocale2);
                     idaSchemaAdd1.add("_std_rl");
                  }
               }
            }
            if(!m_bSchemaOnly)
            {
               for(index i = 0; i < m_idaLocale.get_count(); i++)
               {
                  string idLocale2 = m_idaLocale[i];
                  if(i >= m_idaSchema.get_count())
                     m_idaSchema.add("_std");
                  string strSchema = m_idaSchema[i];
                  if(strSchema.CompareNoCase("_std") != 0)
                  {
                     idaLocaleAdd1.add(idLocale2);
                     idaSchemaAdd1.add("_std");
                  }
               }
            }
            
            m_idaLocale.add(idaLocaleAdd1);
            m_idaSchema.add(idaSchemaAdd1);


            return true;
         }

         bool locale_schema::process_final_locale_schema()
         {
            return process_final_locale_schema(Application.directrix().m_varTopicQuery.has_property("right_to_left_layout") &&
               (bool) Application.directrix().m_varTopicQuery["right_to_left_layout"]);
         }

         locale_schema & locale_schema::operator = (const locale_schema & ls)
         {

            if(&ls != this)
            {

               m_bSchemaOnly           = ls.m_bSchemaOnly;
               m_bAddAlternateStyle    = ls.m_bAddAlternateStyle;
               m_idLocale              = ls.m_idLocale;
               m_idSchema              = ls.m_idSchema;
               m_idaLocale             = ls.m_idaLocale;
               m_idaSchema             = ls.m_idaSchema;

            }

            return *this;
            
         }


   }  // namespace international


} // namespace gen


