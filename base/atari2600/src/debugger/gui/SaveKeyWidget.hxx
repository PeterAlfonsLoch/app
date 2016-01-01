//============================================================================
//
//   SSSS    tt          lll  lll       
//  SS  SS   tt           ll   ll        
//  SS     tttttt  eeee   ll   ll   aaaa 
//   SSSS    tt   ee  ee  ll   ll      aa
//      SS   tt   eeeeee  ll   ll   aaaaa  --  "An Atari 2600 VCS Emulator"
//  SS  SS   tt   ee      ll   ll  aa  aa
//   SSSS     ttt  eeeee llll llll  aaaaa
//
// Copyright (c) 1995-2015 by Bradford W. Mott, Stephen Anthony
// and the Stella Team
//
// See the file "License.txt" for information on usage and redistribution of
// this file, and for a DISCLAIMER OF ALL WARRANTIES.
//
// $Id: SaveKeyWidget.hxx 3182 2015-07-10 18:59:03Z stephena $
//============================================================================

#ifndef SAVEKEY_WIDGET_HXX
#define SAVEKEY_WIDGET_HXX

class ButtonWidget;

#include "Control.hxx"
#include "ControllerWidget.hxx"

class SaveKeyWidget : public ControllerWidget
{
  public:
    SaveKeyWidget(GuiObject* boss, const GUI::Font& font, int x, int y,
                  Controller& controller);
    virtual ~SaveKeyWidget() { }

  private:
    ButtonWidget* myEEPROMErase;
    enum { kEEPROMErase  = 'eeER' };

  private:
    void loadConfig() override { }
    void handleCommand(CommandSender* sender, int cmd, int data, int id) override;

    // Following constructors and assignment operators not supported
    SaveKeyWidget() = delete;
    SaveKeyWidget(const SaveKeyWidget&) = delete;
    SaveKeyWidget(SaveKeyWidget&&) = delete;
    SaveKeyWidget& operator=(const SaveKeyWidget&) = delete;
    SaveKeyWidget& operator=(SaveKeyWidget&&) = delete;
};

#endif
