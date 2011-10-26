#pragma once

#include "KeyboardFocus.h"

class devedgeView;

namespace devedge
{


class CLASS_DECL_CA2_DEVEDGE Element2D : 
	virtual public KeyboardFocus
{
public:
	point	m_pt;
	size	m_size;

	BaseRect m_rectView;

	virtual void _001OnCalcLayout(CDC * pdc);
	virtual void _001OnDraw(devedgeView * pview, CDC * pdc);

	virtual bool hit_test(int x, int y);

	virtual void _001OnLButtonDown(devedgeView * pview, gen::signal_object * pobj);
	virtual void _001OnLButtonUp(devedgeView * pview, gen::signal_object * pobj);
	virtual void _001OnMouseMove(devedgeView * pview, gen::signal_object * pobj);

};



} // namespace devedge