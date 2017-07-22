

not_installed::not_installed(::aura::application * papp, const char * pszAppId, const char * pszConfiguration, const char * pszPlatform, const char * pszLocale, const char * pszSchema) :
   object(papp),
   ::call_stack(papp),
   ::exception::base(papp)
{

   m_strAppId           = pszAppId;
   m_strConfiguration   = pszConfiguration == NULL ? System.get_system_configuration().c_str() : pszConfiguration;
   m_strPlatform        = pszPlatform == NULL ? System.get_system_platform().c_str() : pszPlatform;
   m_strLocale          = pszLocale == NULL ? Session.m_strLocale.c_str() : pszLocale;
   m_strSchema          = pszSchema == NULL ? Session.m_strSchema.c_str() : pszSchema;

   string str;
   str += "appid=" + m_strAppId + ";";
   str += "configuration=" + m_strConfiguration + ";";
   str += "platform=" + m_strPlatform + ";";
   str += "locale=" + m_strLocale + ";";
   str += "schema=" + m_strSchema + ";";

   debug_print(":not_installed(\"%s\")",str.c_str());

}

not_installed::not_installed(const not_installed & e) :
   object(e),
   ::call_stack(e),
   ::exception::base(e)
{

   debug_print(":not_installed(copy)");

   m_strAppId           = e.m_strAppId;
   m_strConfiguration   = e.m_strConfiguration;
   m_strPlatform        = e.m_strPlatform;
   m_strLocale          = e.m_strLocale;
   m_strSchema          = e.m_strSchema;

}


not_installed::~not_installed()
{


}



