#include "StdAfx.h"

namespace devedge
{

   project::project(::ca::application * papp) :
      ca(papp),
      m_source(papp),
      m_headers(papp)
   {
      m_pdoc = NULL;
   }


   void project::load(solution_document * pdoc, xml::node * pnodeProject)
   {
      m_pdoc = pdoc;
      m_pnodeProject = pnodeProject;
      m_strProjectPath = calc_project_dir();
      m_strProjectDir = System.dir().name(m_strProjectPath);
      m_source.load(this);
      m_headers.load(this);
   }

   string project::calc_project_dir()
   {
      string str = m_pdoc->get_path_name();
      str = System.dir().name(str);
      System.file().path().eat_end_level(str, 3, "\\");
      return System.dir().path(str, m_pnodeProject->attr("path"), "project.ca2project");
   }
} // namespace devedge