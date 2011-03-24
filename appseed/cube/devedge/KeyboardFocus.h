#pragma once

class devedgeView;

namespace devedge
{


class CLASS_DECL_CA2_DEVEDGE KeyboardFocus : public gen::signalizable
{
public:
	virtual void _001OnKeyboardFocusTimer(devedgeView * pview, int iTimer);
   virtual void _001OnChar(devedgeView * pview, gen::signal_object * pobj);
   virtual void _001OnSysChar(devedgeView * pview, gen::signal_object * pobj);
};



} // namespace devedge