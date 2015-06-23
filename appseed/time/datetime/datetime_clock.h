#pragma once


class CLASS_DECL_CA2_TIME clock :
   public clock_interface
{
public:


   point    m_point;
   size     m_size;


   clock(::aura::application * papp);


};