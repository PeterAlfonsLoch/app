#pragma once

namespace devedge
{

   class solution_document;

   class CLASS_DECL_CA2_CUBE project :
      virtual public ::radix::object
   {
   public:
      project(::ca::application * papp);
      xml::node * m_pnodeProject;
      source                           m_source;
      headers                          m_headers;
      solution_document *              m_pdoc;
      string                           m_strProjectPath;
      string                           m_strProjectDir;

      string calc_project_dir();

      void load(solution_document * pdoc, xml::node * pnodeProject);
   };
}