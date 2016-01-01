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
// $Id: SnapshotDialog.hxx 3182 2015-07-10 18:59:03Z stephena $
//============================================================================

#ifndef SNAPSHOT_DIALOG_HXX
#define SNAPSHOT_DIALOG_HXX

class OSystem;
class GuiObject;
class DialogContainer;
class BrowserDialog;
class CheckboxWidget;
class PopUpWidget;
class EditTextWidget;
class SliderWidget;
class StaticTextWidget;

#include "Dialog.hxx"
#include "Command.hxx"

class SnapshotDialog : public Dialog
{
  public:
    SnapshotDialog(OSystem& osystem, DialogContainer& parent,
                   const GUI::Font& font, GuiObject* boss,
                   int max_w, int max_h);
    virtual ~SnapshotDialog();

  private:
    void loadConfig() override;
    void saveConfig() override;
    void setDefaults() override;

    void handleCommand(CommandSender* sender, int cmd, int data, int id) override;

  private:
    enum {
      kChooseSnapSaveDirCmd = 'LOss', // snapshot dir (save files)
      kChooseSnapLoadDirCmd = 'LOsl', // snapshot dir (load files)
      kSnapSaveDirChosenCmd = 'snsc', // snap chosen (save files)
      kSnapLoadDirChosenCmd = 'snlc'  // snap chosen (load files)
    };

    unique_ptr<BrowserDialog> myBrowser;

    // Config paths
    EditTextWidget* mySnapSavePath;
    EditTextWidget* mySnapLoadPath;

    PopUpWidget* mySnapName;
    PopUpWidget* mySnapInterval;

    CheckboxWidget* mySnapSingle;
    CheckboxWidget* mySnap1x;

  private:
    // Following constructors and assignment operators not supported
    SnapshotDialog() = delete;
    SnapshotDialog(const SnapshotDialog&) = delete;
    SnapshotDialog(SnapshotDialog&&) = delete;
    SnapshotDialog& operator=(const SnapshotDialog&) = delete;
    SnapshotDialog& operator=(SnapshotDialog&&) = delete;
};

#endif
