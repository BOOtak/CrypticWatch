/******************************************************************************
 *
 * Copyright (c) 2003 PalmSource, Inc.  All rights reserved.
 * Copyright (c) 2003 Fossil, Inc.  All rights reserved.
 *
 * File:        WristPDA.h
 *
 * Description: Include file for the Fossil Wrist PDA.
 *
 *****************************************************************************/

#ifndef __WRISTPDA_H__
#define __WRISTPDA_H__

#include <PalmOS.h>

#include "HAL.h"

///////////////////////////////////////////////////////////////////////////////
// Use the WRISTPDA macro to conditionally compile Wrist PDA code
//
#define WRISTPDA                    1

///////////////////////////////////////////////////////////////////////////////
// Fossil creator codes
//
#define WPdaCreator                 'Foss'  // WPdaSysExt.prc & other use
#define WPdaDialogsCreator          'FosD'  // WPdaDialogs.prc
#define WPdaExt2Creator             'FosX'  // WPdaSysExt2.prc
#define sysFileCWristPDAPnl         'wpda'  // WristPDAPnl.prc

///////////////////////////////////////////////////////////////////////////////
// Use the WPdaGetVersion macro to detect if running on a Fossil OS or not,
// or use the FossilIsWristPDADevice API defined later in this file
//
#define WPdaFtrNumVersion           0
#define WPdaGetVersion( verP )  \
            (Err) FtrGet( WPdaCreator, WPdaFtrNumVersion, verP )

///////////////////////////////////////////////////////////////////////////////
// Fossil Key definitions
//
// Key bit masks
#define keyBitRockerUp              0x1000      // Rocker switch up
#define keyBitRockerDown            0x2000      // Rocker switch down
#define keyBitEnter                 0x4000      // Rocker switch in
#define keyBitBack                  0x8000      // Back key

///////////////////////////////////////////////////////////////////////////////
// Fossil virtual key character codes
//

// Palm OS 5.0 R2 Thumb Characters (also known as Jog)
// The following values exist to allow all hardware that has these
// (optional) control clusters to emit the same key codes.

#define vchrThumbWheelUp            0x012E      // Thumb-wheel up
#define vchrThumbWheelDown          0x012F      // Thumb-wheel down
#define vchrThumbWheelPush          0x0130      // Thumb-wheel press/center
#define vchrThumbWheelBack          0x0131      // Thumb-wheel cluster back

// Alternate Fossil names for the standard Thumb vchr codes

#define vchrHardRockerEnter         vchrThumbWheelPush  // Rocker switch in
#define vchrHardRockerUp            vchrThumbWheelUp    // Rocker switch up
#define vchrHardRockerDown          vchrThumbWheelDown  // Rocker switch down
#define vchrHardBack                vchrThumbWheelBack  // Back key

///////////////////////////////////////////////////////////////////////////////
// Fossil defines for UI
//
#define WPDA_BUTTON_HEIGHT          16  // Default button height on forms

///////////////////////////////////////////////////////////////////////////////
// Fossil Font IDs (map one-to-one onto original PalmOS font set)
//
#define FossilFontIDStart           0x10
#define FossilStdFont               (FossilFontIDStart +0)
#define FossilBoldFont              (FossilFontIDStart +1)
#define FossilLargeFont             (FossilFontIDStart +2)
#define FossilSymbolFont            (FossilFontIDStart +3)
#define FossilSymbol11Font          (FossilFontIDStart +4)
#define FossilSymbol7Font           (FossilFontIDStart +5)
#define FossilLedFont               (FossilFontIDStart +6)
#define FossilLargeBoldFont         (FossilFontIDStart +7)
#define FossilFontIDEnd             (FossilFontIDStart +7)

///////////////////////////////////////////////////////////////////////////////
// Fossil Extended Font IDs (no mapping onto original PalmOS font set)
// 
#define FossilExtendedFontIDStart   0x20
#define FossilLarge8Font            (FossilExtendedFontIDStart +0)
#define FossilLargeBold8Font        (FossilExtendedFontIDStart +1)
#define FossilExtendedFontIDEnd     (FossilExtendedFontIDStart +1)

// Note: While FossilLarge8Font and FossilLargeBold8Font are 'Fossil' fonts,
//       they are NOT part of the Fossil font set with a one-to-one mapping
//       onto the standard font set.  Apps that use these two fonts are
//       directly responsible for managing their use, with no assistance from
//       the Fossil font macros below.

///////////////////////////////////////////////////////////////////////////////
// Fossil Font ID Macros
// 
#define FossilIsFossilFont( _fontId ) \
            ((_fontId >= FossilFontIDStart) && (_fontId <= FossilFontIDEnd))

#define FossilIsSystemFont( _fontId ) \
            ((_fontId >= stdFont) && (_fontId <= largeBoldFont))

#define FossilLargeFontID( _doIt, _fontId ) \
            (_fontId + (_doIt && FossilIsSystemFont(_fontId) ? \
                FossilFontIDStart : 0))

#define FossilNormalFontID( _doIt, _fontId ) \
            (_fontId - (_doIt && FossilIsFossilFont(_fontId) ? \
                FossilFontIDStart : 0))

///////////////////////////////////////////////////////////////////////////////
// Fossil notifications
//

// The fossilNotifyWatchModeWakeup notification is broadcast upon
// wakeup from Watch mode when a Watch app is the current app
// Watch apps respond to this notification as they see fit
#define fossilNotifyWatchModeWakeup     'wkup'

///////////////////////////////////////////////////////////////////////////////
// Fossil Watch app custom launch codes
//

// Draw the time with the current face and immediately return
#define wpdaAppLaunchWatchDrawTime  ( sysAppLaunchCmdCustomBase + 0 )

// Switch to the next face, draw the time, and immediately return
#define wpdaAppLaunchWatchFaceNext  ( sysAppLaunchCmdCustomBase + 1 )

// Switch to the previous face, draw the time, and immediately return
#define wpdaAppLaunchWatchFacePrev  ( sysAppLaunchCmdCustomBase + 2 )

///////////////////////////////////////////////////////////////////////////////
// Fossil Main API
//
#define FossilAPITrap       sysTrapOEMDispatch

#define FOSSIL_API(sel) \
        _SYSTEM_API(_CALL_WITH_SELECTOR)(_SYSTEM_TABLE,FossilAPITrap,sel)

#define FossilAPIUnused1                    0
#define FossilAPIUnused2                    1
#define FossilAPIBackKeyModeGet             2
#define FossilAPIBackKeyModeSet             3
#define FossilAPIMenuCmdBarIconsGet         4
#define FossilAPIMenuCmdBarIconsSet         5
#define FossilAPIDisplayRefreshRateGet      6
#define FossilAPIDisplayRefreshRateSet      7
#define FossilAPIResetStat                  8
#define FossilAPIFrmIsFossil                9
#define FossilAPIMenuSetActiveMenuRscID     10
#define FossilAPIMenuLargeFontGet           11
#define FossilAPIMenuLargeFontSet           12
#define FossilAPIFrmEnlargeObject           13
#define FossilAPIMaxSelector                14

#define FossilIsWristPDADeviceOpCode        ( WPdaExt2Creator + 0 )
#define FossilIsWristPDAHALOpCode           ( WPdaExt2Creator + 1 )
#define FossilExtendedFontSelectGetOpCode   ( WPdaExt2Creator + 2 )
#define FossilExtendedFontSelectSetOpCode   ( WPdaExt2Creator + 3 )

/***********************************************************************
 *
 *  FUNCTION:       FossilIsWristPDADevice
 *
 *  DESCRIPTION:    Determine if this is a Wrist PDA device.
 *
 *                  This provides a simpler alternative to WPdaGetVersion
 *                  for code to determine if it is running on a Wrist PDA,
 *                  i.e. if the Wrist PDA system extensions are available.
 *
 *  PARAMETERS:     None
 *
 *  RETURNS:        Boolean - true if this is a Wrist PDA device,
 *                            undefined if not a Wrist PDA device.
 *
 *                  Note: The return values is *undefined* if this call
 *                        is made on a non Wrist PDA device, so the return
 *                        value must be explicitly compared only to true.
 *
 ***********************************************************************/
#define FossilIsWristPDADevice() \
    HwrCustom( WPdaExt2Creator, \
               FossilIsWristPDADeviceOpCode, \
               NULL, \
               NULL )

/***********************************************************************
 *
 *  FUNCTION:       FossilIsWristPDAHAL
 *
 *  DESCRIPTION:    Determine if this is a Wrist PDA HAL.
 *
 *  PARAMETERS:     None
 *
 *  RETURNS:        Boolean - true if this is a Wrist PDA HAL,
 *                            undefined if not a Wrist PDA HAL.
 *
 *                  Note: The return values is *undefined* if this call
 *                        is made on a non Wrist PDA device, so the return
 *                        value must be explicitly compared only to true.
 *
 ***********************************************************************/
#define FossilIsWristPDAHAL() \
    HwrCustom( WPdaExt2Creator, \
               FossilIsWristPDAHALOpCode, \
               NULL, \
               NULL )

/***********************************************************************
 *
 *  FUNCTION:       FossilBackKeyModeGet
 *
 *  DESCRIPTION:    Gets the Back key interpretation mode.
 *
 *  PARAMETERS:     None
 *
 *  RETURNS:        See FossilBackKeyModeSet() for return values.
 *
 ***********************************************************************/
UInt16  _FossilBackKeyModeGet(void)
            FOSSIL_API(FossilAPIBackKeyModeGet);

#define FossilBackKeyModeGet() \
        ( FossilIsWristPDADevice() == true ) ? \
             _FossilBackKeyModeGet() : 0

#define kFossilBackKeyNoAction  0x0000
#define kFossilBackKeyLauncher  0x0001
#define kFossilBackKeyStopEvent 0x0002  // Default set by FossilResetStat()
                                        // and by Launching a new app.

/***********************************************************************
 *
 *  FUNCTION:       FossilBackKeyModeSet
 *
 *  DESCRIPTION:    Sets the Back key interpretation mode.
 *
 *  PARAMETERS:     newBackKeyMode - The new Back key mode.
 *
 *                  Valid values are:
 *
 *                      kFossilBackKeyNoAction  - Ignore this key.
 *
 *                      kFossilBackKeyLauncher  - Puts this key in the event
 *                                                queue. If not handled,
 *                                                insert an appStopEvent.
 *
 *                      kFossilBackKeyStopEvent - Insert an appStopEvent
 *                                                (without putting any key
 *                                                in the event queue).
 *  RETURNS:        Void
 *
 ***********************************************************************/
void    _FossilBackKeyModeSet( UInt16 newBackKeyMode ) \
            FOSSIL_API(FossilAPIBackKeyModeSet);

#define FossilBackKeyModeSet( newBackKeyMode ) \
        if ( FossilIsWristPDADevice() == true ) \
             _FossilBackKeyModeSet( newBackKeyMode )

/***********************************************************************
 *
 *  FUNCTION:       FossilMenuCmdBarIconsGet
 *
 *  DESCRIPTION:    Gets the Menu Cmd Bar Fossil mode.
 *
 *  PARAMETERS:     None
 *
 *  RETURNS:        UInt16 - Bitmask indicating which icons are present.
 *
 *                  Valid values are any combination of:
 *
 *                          kFossilMenuCmdNone
 *                          kFossilMenuCmdMenu
 *                          kFossilMenuCmdFind
 *                          kFossilMenuCmdFindMenu
 *
 ***********************************************************************/
UInt16  _FossilMenuCmdBarIconsGet(void)
            FOSSIL_API(FossilAPIMenuCmdBarIconsGet);

#define FossilMenuCmdBarIconsGet() \
        ( FossilIsWristPDADevice() == true ) ? \
            _FossilMenuCmdBarIconsGet() : 0

#define kFossilMenuCmdNone      0x0000
#define kFossilMenuCmdMenu      0x0001
#define kFossilMenuCmdFind      0x0002
#define kFossilMenuCmdKeyboard  0x0004
#define kFossilMenuCmdAll       \
            (kFossilMenuCmdMenu | kFossilMenuCmdFind | kFossilMenuCmdKeyboard)

/***********************************************************************
 *
 *  FUNCTION:       FossilMenuCmdBarIconsSet
 *
 *  DESCRIPTION:    Sets the Menu Cmd Bar Fossil mode.
 *
 *  PARAMETERS:     newIconFlags - Bitmask indicating which icons are present
 *
 *                  Valid values are any combination of:
 *
 *                          kFossilMenuCmdNone
 *                          kFossilMenuCmdMenu
 *                          kFossilMenuCmdFind
 *                          kFossilMenuCmdFindMenu
 *
 *  RETURNS:        UInt16 previous menu cmd bar icon bitmask.
 *
 ***********************************************************************/
UInt16  _FossilMenuCmdBarIconsSet( UInt16 newIconFlags )
            FOSSIL_API(FossilAPIMenuCmdBarIconsSet);

#define FossilMenuCmdBarIconsSet( newIconFlags ) \
        ( FossilIsWristPDADevice() == true ) ? \
            _FossilMenuCmdBarIconsSet( newIconFlags ) : 0

/***********************************************************************
 *
 *  FUNCTION:       FossilMenuSetActiveMenuRscID
 *
 *  DESCRIPTION:    Set the active menu from a Resouirce ID
 *                  and indicate if this menu if to be enlarged.
 *
 *  PARAMETERS:     resourceId - Id of menu resource to make active
 *
 *                  largeMenu  - true if menu to be displayed w/ large font
 *
 *  RETURNS:        void
 *
 ***********************************************************************/
void    _FossilMenuSetActiveMenuRscID(UInt16 resourceId, Boolean largeMenu )
            FOSSIL_API(FossilAPIMenuSetActiveMenuRscID);

#define FossilMenuSetActiveMenuRscID( resourceId, largeMenu ) \
        if ( FossilIsWristPDADevice() == true ) \
            _FossilMenuSetActiveMenuRscID( resourceId, largeMenu )

/***********************************************************************
 *
 *  FUNCTION:       FossilMenuLargeFontGet
 *
 *  DESCRIPTION:    Get the large font state of a specified menu.
 *
 *  PARAMETERS:     menuP - Ptr to the menu to query.
 *
 *  RETURNS:        Boolean - true if the menu pointed to by menuP is
 *                            displayed with large font, false otherwise.
 *
 ***********************************************************************/
Boolean _FossilMenuLargeFontGet( MenuBarType* menuP )
            FOSSIL_API(FossilAPIMenuLargeFontGet);

#define FossilMenuLargeFontGet( menuP ) \
        ( FossilIsWristPDADevice() == true ) ? \
            _FossilMenuLargeFontGet( menuP ) : false

/***********************************************************************
 *
 *  FUNCTION:       FossilMenuLargeFontSet
 *
 *  DESCRIPTION:    Set if a menu is to be displayed in large font.
 *
 *  PARAMETERS:     menuP - Ptr to the menu to set.
 *
 *                  setLargeFont - true to display menu w/ large font.
 *
 *  RETURNS:        Boolean - The previous menu large font state.
 *
 ***********************************************************************/
Boolean _FossilMenuLargeFontSet( MenuBarType* menuP, Boolean setLargeFont )
            FOSSIL_API(FossilAPIMenuLargeFontSet);

#define FossilMenuLargeFontSet( menuP, setLargeFont ) \
        ( FossilIsWristPDADevice() == true ) ? \
            _FossilMenuLargeFontSet( menuP, setLargeFont ) : false

/***********************************************************************
 *
 *  FUNCTION:       FossilDisplayRefreshRateGet
 *
 *  DESCRIPTION:    Gets the display refresh rate in number of system ticks.
 *
 *  PARAMETERS:     None
 *
 *  RETURNS:        UInt16 - The current display refresh rate in ticks.
 *                          (1 refresh per rate/SysTicksPerSecond() seconds).
 *                           
 *                  One special return value is defined:
 *
 *                      kFossilRefreshAuto - Auto refresh mode is active.
 *
 ***********************************************************************/
UInt16  _FossilDisplayRefreshRateGet( void )
            FOSSIL_API(FossilAPIDisplayRefreshRateGet);

#define FossilDisplayRefreshRateGet() \
        ( FossilIsWristPDADevice() == true ) ? \
            _FossilDisplayRefreshRateGet() : 1

/***********************************************************************
 *
 *  FUNCTION:       FossilDisplayRefreshRateSet
 *
 *  DESCRIPTION:    Set the display refresh rate in number of system ticks.
 *
 *  PARAMETERS:     newRefreshRate - The new display refresh rate in ticks.
 *                      (1 refresh per rate/SysTicksPerSecond() seconds).
 *
 *                  Two special parameter values are defined:
 *
 *                      kFossilRefreshAuto    - Use auto refresh mode.
 *                      kFossilRefreshDefault - Use default refresh rate.
 *
 ***********************************************************************/
void    _FossilDisplayRefreshRateSet( UInt16 newRefreshRate )
            FOSSIL_API(FossilAPIDisplayRefreshRateSet);

#define FossilDisplayRefreshRateSet( newRefreshRate ) \
        if ( FossilIsWristPDADevice() == true ) \
            _FossilDisplayRefreshRateSet( newRefreshRate )

#define kFossilRefreshAuto      0xFFFE
#define kFossilRefreshDefault   0xFFFD

/***********************************************************************
 *
 *  FUNCTION:       FossilResetStat
 *
 *  DESCRIPTION:    Resets the Wrist PDA to compatibility mode.
 *
 *                  All Fossil modes are reset to the most compatible state.
 *
 *  PARAMETERS:     None
 *
 *  RETURNS:        Void
 *
 ***********************************************************************/
void    _FossilResetStat( void )
            FOSSIL_API(FossilAPIResetStat);

#define FossilResetStat() \
        if ( FossilIsWristPDADevice() == true ) \
            _FossilResetStat()

// Fossil Form gadget spec

#define FossilFrmGadgetLargeFontIDMod100        70

#define FossilFrmGadgetLargeFontRectX           0
#define FossilFrmGadgetLargeFontRectY           1
#define FossilFrmGadgetLargeFontRectW           2
#define FossilFrmGadgetLargeFontRectH           3

#define FossilFrmGadgetLargeFontRect            \
            { FossilFrmGadgetLargeFontRectX,    \
              FossilFrmGadgetLargeFontRectY,    \
              FossilFrmGadgetLargeFontRectW,    \
              FossilFrmGadgetLargeFontRectH }

/***********************************************************************
 *
 *  FUNCTION:       FossilFrmIsLargeFont
 *
 *  DESCRIPTION:    Determine if a speficied form is a Fossil friendly form.
 *                  (That is, if the Fossil gadget is present).
 *
 *  PARAMETERS:     formP - Ptr to form to query.
 *
 *  RETURNS:        Boolean - true if form has Fossil gadget,
 *                            false otherwise.
 *
 ***********************************************************************/
Boolean _FossilFrmIsLargeFont( const FormType* formP )
            FOSSIL_API(FossilAPIFrmIsFossil);

#define FossilFrmIsLargeFont( formP ) \
        ( FossilIsWristPDADevice() == true ) ? \
            _FossilFrmIsLargeFont( formP ) : false

/***********************************************************************
 *
 *  FUNCTION:       FossilFrmEnlargeObject
 *
 *  DESCRIPTION:    Enlarge one or all objects in a form.
 *
 *                  Must be called before a form is first displayed.
 *
 *  PARAMETERS:     formP - Ptr to form to operate on.
 *
 *                  objectIdx - Index of object to enlarge, or
 *                              kFossilFrmEnlargeObjectAll to enlarge all
 *                              objects on the form.
 *
 *  RETURNS:        void
 *
 ***********************************************************************/
void    _FossilFrmEnlargeObject( FormType* formP, UInt16 objectIdx )
            FOSSIL_API(FossilAPIFrmEnlargeObject);

#define FossilFrmEnlargeObject( formP, objectIdx ) \
        if ( FossilIsWristPDADevice() == true ) \
            _FossilFrmEnlargeObject( formP, objectIdx )

#define kFossilFrmEnlargeObjectAll      0xFFFF

/***********************************************************************
 *
 *  FUNCTION:       FossilExtendedFontSelectGet
 *
 *  DESCRIPTION:    Return FontSelect extended dialog state.
 *
 *                  Boolean * extendedP - Ptr to Boolean to receive state
 *
 *  PARAMETERS:     extendedP - Ptr to variable to receive the extended
 *                              dialog state; true if in extended state.
 *
 *  RETURNS:        void
 *
 ***********************************************************************/
#define FossilExtendedFontSelectGet( extendedP ) \
        if ( FossilIsWristPDADevice() == true ) \
            HwrCustom( WPdaExt2Creator, \
                       FossilExtendedFontSelectGetOpCode, \
                       (void *) extendedP, \
                       NULL ); \
        else \
            * extendedP = false

/***********************************************************************
 *
 *  FUNCTION:       FossilExtendedFontSelectSet
 *
 *  DESCRIPTION:    Control use of extended FontSelect dialog.
 *
 *  PARAMETERS:     extended - Indicates whether to use extended
 *                             dialog or not.
 *
 *                             true  -> Use extended dialog
 *                             false -> Use original dialog
 *
 *  RETURNS:        void
 *
 ***********************************************************************/
#define FossilExtendedFontSelectSet( extended ) \
        if ( FossilIsWristPDADevice() == true ) \
            HwrCustom( WPdaExt2Creator, \
                       FossilExtendedFontSelectSetOpCode, \
                       (void *) extended, \
                       NULL )

///////////////////////////////////////////////////////////////////////////////
// Fossil HAL API
//

#define hwrWristPDAUpdateDisplayOpCode      1
#define hwrWristPDAGetSystemStatusOpCode    2
#define hwrWristPDASetWatchAppOpCode        3

/***********************************************************************
 *
 *  FUNCTION:       FossilUpdateDisplay
 *
 *  DESCRIPTION:    Direct the HAL to update the display by copying the
 *                  contents of the DragonBall framebuffer to the
 *                  UltraChip framebuffer.
 *
 *  PARAMETERS:     None
 *
 *  RETURNS:        void
 *
 ***********************************************************************/
#define FossilUpdateDisplay() \
    if ( FossilIsWristPDAHAL() == true ) \
        HwrCustom( WPdaCreator, \
                   hwrWristPDAUpdateDisplayOpCode, \
                   NULL, \
                   NULL )

/***********************************************************************
 *
 *  FUNCTION:       FossilGetSystemStatus
 *
 *  DESCRIPTION:    Direct the HAL to return system status (alarm triggered,
 *                  low battery state) that is needed by Watch applications.
 *
 *  PARAMETERS:     RequestType - The type of system status requested.
 *
 *                      Must be one of these values:
 *
 *                          kFossilGetAlarmState
 *                          kFossilGetBatteryState
 *
 *  RETURNS:        UInt16 - The requested system status.
 *
 *                      Returns one of these values:
 *
 *                          kFossilSystemStatusAlarmNotTriggered
 *                          kFossilSystemStatusAlarmTriggered
 *
 *                          kFossilSystemStatusBatteryOk
 *                          kFossilSystemStatusBatteryLow
 *                          kFossilSystemStatusBatteryVeryLow
 *                          kFossilSystemStatusBatteryEmpty
 *
 ***********************************************************************/
#define FossilGetSystemStatus( RequestType ) \
    ( FossilIsWristPDAHAL() == true ) ? \
        HwrCustom( WPdaCreator, \
                   hwrWristPDAGetSystemStatusOpCode, \
                   (void *) RequestType, \
                   NULL ) : 0

// Values for FossilGetSystemStatus RequestType parameter

#define kFossilGetAlarmState    0
#define kFossilGetBatteryState  1

// Return values for FossilGetSystemStatus

#define kFossilSystemStatusAlarmNotTriggered    0
#define kFossilSystemStatusAlarmTriggered       1

#define kFossilSystemStatusBatteryOk            0
#define kFossilSystemStatusBatteryLow           1
#define kFossilSystemStatusBatteryVeryLow       2
#define kFossilSystemStatusBatteryEmpty         3

/***********************************************************************
 *
 *  FUNCTION:       FossilSetWatchApp
 *
 *  DESCRIPTION:    Inform the HAL if the current app is a Watch app.
 *
 *                  Only Watch apps should make this call, other apps
 *                  should not make this call.
 *
 *                  When the HAL has been informed that the current app
 *                  is a Watch app, it will broadcast the
 *                  fossilNotifyWatchModeWakeup notification upon wakeup
 *                  from Watch mode.  A Watch app may respond to this
 *                  notification (or ignore it) as it sees fit.
 *
 *  PARAMETERS:     WatchAppFlag - Boolean, true for a Watch app,
 *                                 false otherwise.
 *
 *  RETURNS:        void
 *
 ***********************************************************************/

#define FossilSetWatchApp( WatchAppFlag ) \
    ( FossilIsWristPDAHAL() == true ) ? \
        HwrCustom( WPdaCreator, \
                   hwrWristPDASetWatchAppOpCode, \
                   (void *) WatchAppFlag, \
                   NULL ) : 0

#endif  //  __WRISTPDA_H__
