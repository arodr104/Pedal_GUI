//<File !Start!>
// FILE: [GUI_GSLC.h]
// Created by GUIslice Builder version: [0.16.b008]
//
// GUIslice Builder Generated GUI Framework File
//
// For the latest guides, updates and support view:
// https://github.com/ImpulseAdventure/GUIslice
//
//<File !End!>

#ifndef _GUISLICE_GEN_H
#define _GUISLICE_GEN_H

// ------------------------------------------------
// Headers to include
// ------------------------------------------------
#include "GUIslice.h"
#include "GUIslice_drv.h"

// Include any extended elements
//<Includes !Start!>
//<Includes !End!>

// ------------------------------------------------
// Headers and Defines for fonts
// Note that font files are located within the Adafruit-GFX library folder:
// ------------------------------------------------
//<Fonts !Start!>
#if defined(DRV_DISP_TFT_ESPI)
  #error Project tab->Target Platform should be tft_espi
#endif
#include <Adafruit_GFX.h>
#include "Fonts/FreeMono9pt7b.h"
#include "Fonts/FreeSans9pt7b.h"
//<Fonts !End!>

// ------------------------------------------------
// Defines for resources
// ------------------------------------------------
//<Resources !Start!>
//<Resources !End!>

// ------------------------------------------------
// Enumerations for pages, elements, fonts, images
// ------------------------------------------------
//<Enum !Start!>
enum {E_PG_MAIN,E_FLANGE_PAGE,E_REVERB_PAGE,E_AMP_PAGE};
enum {E_AMP_BACK,E_AMP_BYPASS,E_AMP_BYPASS_STATUS,E_AMP_GAIN
      ,E_AMP_TITLE,E_FLANGE_BACK,E_FLANGE_BYPASS,E_FLANGE_BYPASS_STATUS
      ,E_FLANGE_DEPTH,E_FLANGE_MOD_FREQ,E_FLANGE_OFFSET,E_FLANGE_TITLE
      ,E_HOME_AMP,E_HOME_BYPASS,E_HOME_BYPASS_STATUS,E_HOME_CURR_PRESET
      ,E_HOME_FLANGE,E_HOME_PRESET,E_HOME_REVERB,E_HOME_TITLE_TEXT
      ,E_REVERB_BACK,E_REVERB_BYPASS,E_REVERB_BYPASS_STATUS
      ,E_REVERB_DAMPING,E_REVERB_DRY_LEVEL,E_REVERB_ROOM_SIZE
      ,E_REVERB_TITLE};
// Must use separate enum for fonts with MAX_FONT at end to use gslc_FontSet.
enum {E_FREEMONO9,E_FREESANS9,MAX_FONT};
//<Enum !End!>

// ------------------------------------------------
// Instantiate the GUI
// ------------------------------------------------

// ------------------------------------------------
// Define the maximum number of elements and pages
// ------------------------------------------------
//<ElementDefines !Start!>
#define MAX_PAGE                4

#define MAX_ELEM_PG_MAIN 8 // # Elems total on page
#define MAX_ELEM_PG_MAIN_RAM MAX_ELEM_PG_MAIN // # Elems in RAM

#define MAX_ELEM_FLANGE_PAGE 7 // # Elems total on page
#define MAX_ELEM_FLANGE_PAGE_RAM MAX_ELEM_FLANGE_PAGE // # Elems in RAM

#define MAX_ELEM_REVERB_PAGE 7 // # Elems total on page
#define MAX_ELEM_REVERB_PAGE_RAM MAX_ELEM_REVERB_PAGE // # Elems in RAM

#define MAX_ELEM_AMP_PAGE 5 // # Elems total on page
#define MAX_ELEM_AMP_PAGE_RAM MAX_ELEM_AMP_PAGE // # Elems in RAM
//<ElementDefines !End!>

// ------------------------------------------------
// Create element storage
// ------------------------------------------------
gslc_tsGui                      m_gui;
gslc_tsDriver                   m_drv;
gslc_tsFont                     m_asFont[MAX_FONT];
gslc_tsPage                     m_asPage[MAX_PAGE];

//<GUI_Extra_Elements !Start!>
gslc_tsElem                     m_asPage1Elem[MAX_ELEM_PG_MAIN_RAM];
gslc_tsElemRef                  m_asPage1ElemRef[MAX_ELEM_PG_MAIN];
gslc_tsElem                     m_asPage2Elem[MAX_ELEM_FLANGE_PAGE_RAM];
gslc_tsElemRef                  m_asPage2ElemRef[MAX_ELEM_FLANGE_PAGE];
gslc_tsElem                     m_asPage3Elem[MAX_ELEM_REVERB_PAGE_RAM];
gslc_tsElemRef                  m_asPage3ElemRef[MAX_ELEM_REVERB_PAGE];
gslc_tsElem                     m_asPage4Elem[MAX_ELEM_AMP_PAGE_RAM];
gslc_tsElemRef                  m_asPage4ElemRef[MAX_ELEM_AMP_PAGE];

#define MAX_STR                 100

//<GUI_Extra_Elements !End!>

// ------------------------------------------------
// Program Globals
// ------------------------------------------------

// Element References for direct access
//<Extern_References !Start!>
extern gslc_tsElemRef* m_current_preset;
extern gslc_tsElemRef* m_flange_bypass;
extern gslc_tsElemRef* m_home_bypass;
extern gslc_tsElemRef* m_p_amp_bypass_status;
extern gslc_tsElemRef* m_reverb_bypass;
//<Extern_References !End!>

// Define debug message function
static int16_t DebugOut(char ch);

// ------------------------------------------------
// Callback Methods
// ------------------------------------------------
bool CbBtnCommon(void* pvGui,void *pvElemRef,gslc_teTouch eTouch,int16_t nX,int16_t nY);
bool CbCheckbox(void* pvGui, void* pvElemRef, int16_t nSelId, bool bState);
bool CbDrawScanner(void* pvGui,void* pvElemRef,gslc_teRedrawType eRedraw);
bool CbKeypad(void* pvGui, void *pvElemRef, int16_t nState, void* pvData);
bool CbListbox(void* pvGui, void* pvElemRef, int16_t nSelId);
bool CbSlidePos(void* pvGui,void* pvElemRef,int16_t nPos);
bool CbSpinner(void* pvGui, void *pvElemRef, int16_t nState, void* pvData);
bool CbTickScanner(void* pvGui,void* pvScope);

// ------------------------------------------------
// Create page elements
// ------------------------------------------------
void InitGUIslice_gen()
{
  gslc_tsElemRef* pElemRef = NULL;

  if (!gslc_Init(&m_gui,&m_drv,m_asPage,MAX_PAGE,m_asFont,MAX_FONT)) { return; }

  // ------------------------------------------------
  // Load Fonts
  // ------------------------------------------------
//<Load_Fonts !Start!>
    if (!gslc_FontSet(&m_gui,E_FREEMONO9,GSLC_FONTREF_PTR,&FreeMono9pt7b,1)) { return; }
    if (!gslc_FontSet(&m_gui,E_FREESANS9,GSLC_FONTREF_PTR,&FreeSans9pt7b,1)) { return; }
//<Load_Fonts !End!>

//<InitGUI !Start!>
  gslc_PageAdd(&m_gui,E_PG_MAIN,m_asPage1Elem,MAX_ELEM_PG_MAIN_RAM,m_asPage1ElemRef,MAX_ELEM_PG_MAIN);
  gslc_PageAdd(&m_gui,E_FLANGE_PAGE,m_asPage2Elem,MAX_ELEM_FLANGE_PAGE_RAM,m_asPage2ElemRef,MAX_ELEM_FLANGE_PAGE);
  gslc_PageAdd(&m_gui,E_REVERB_PAGE,m_asPage3Elem,MAX_ELEM_REVERB_PAGE_RAM,m_asPage3ElemRef,MAX_ELEM_REVERB_PAGE);
  gslc_PageAdd(&m_gui,E_AMP_PAGE,m_asPage4Elem,MAX_ELEM_AMP_PAGE_RAM,m_asPage4ElemRef,MAX_ELEM_AMP_PAGE);

  // NOTE: The current page defaults to the first page added. Here we explicitly
  //       ensure that the main page is the correct page no matter the add order.
  gslc_SetPageCur(&m_gui,E_PG_MAIN);
  
  // Set Background to a flat color
  gslc_SetBkgndColor(&m_gui,GSLC_COL_BLACK);

  // -----------------------------------
  // PAGE: E_PG_MAIN
  
  
  // Create E_HOME_TITLE_TEXT text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_HOME_TITLE_TEXT,E_PG_MAIN,(gslc_tsRect){113,10,94,15},
    (char*)"Jacket DSP",0,E_FREESANS9);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,((gslc_tsColor){255,225,0}));
  
  // create E_HOME_FLANGE button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_HOME_FLANGE,E_PG_MAIN,
    (gslc_tsRect){10,150,80,30},(char*)"Flange",0,E_FREEMONO9,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,((gslc_tsColor){47,78,158}),((gslc_tsColor){47,78,158}),((gslc_tsColor){100,124,206}));
  
  // create E_HOME_AMP button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_HOME_AMP,E_PG_MAIN,
    (gslc_tsRect){120,150,80,30},(char*)"Amp",0,E_FREEMONO9,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,((gslc_tsColor){47,78,158}),((gslc_tsColor){47,78,158}),((gslc_tsColor){100,124,206}));
  
  // create E_HOME_REVERB button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_HOME_REVERB,E_PG_MAIN,
    (gslc_tsRect){230,150,80,30},(char*)"Reverb",0,E_FREEMONO9,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,((gslc_tsColor){47,78,158}),((gslc_tsColor){47,78,158}),((gslc_tsColor){100,124,206}));
  
  // Create E_HOME_BYPASS_STATUS runtime modifiable text
  static char m_sDisplayText21[5] = "OFF";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_HOME_BYPASS_STATUS,E_PG_MAIN,(gslc_tsRect){100,217,40,15},
    (char*)m_sDisplayText21,5,E_FREESANS9);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  m_home_bypass = pElemRef;
  
  // create E_HOME_BYPASS button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_HOME_BYPASS,E_PG_MAIN,
    (gslc_tsRect){10,209,80,30},(char*)"Bypass:",0,E_FREEMONO9,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,((gslc_tsColor){47,78,158}),((gslc_tsColor){47,78,158}),((gslc_tsColor){100,124,206}));
  
  // Create E_HOME_CURR_PRESET runtime modifiable text
  static char m_sDisplayText25[5] = "0";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_HOME_CURR_PRESET,E_PG_MAIN,(gslc_tsRect){295,217,25,15},
    (char*)m_sDisplayText25,5,E_FREESANS9);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  m_current_preset = pElemRef;
  
  // create E_HOME_PRESET button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_HOME_PRESET,E_PG_MAIN,
    (gslc_tsRect){205,209,80,30},(char*)"Preset:",0,E_FREEMONO9,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,((gslc_tsColor){47,78,158}),((gslc_tsColor){47,78,158}),((gslc_tsColor){100,124,206}));

  // -----------------------------------
  // PAGE: E_FLANGE_PAGE
  
  
  // create E_FLANGE_BACK button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_FLANGE_BACK,E_FLANGE_PAGE,
    (gslc_tsRect){0,209,80,30},(char*)"Effects",0,E_FREEMONO9,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,((gslc_tsColor){47,78,158}),((gslc_tsColor){47,78,158}),((gslc_tsColor){100,124,206}));
  
  // Create E_FLANGE_TITLE text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_FLANGE_TITLE,E_FLANGE_PAGE,(gslc_tsRect){260,0,54,23},
    (char*)"Flange",0,E_FREESANS9);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_FLANGE_MOD_FREQ text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_FLANGE_MOD_FREQ,E_FLANGE_PAGE,(gslc_tsRect){10,90,80,21},
    (char*)"Mod Freq:",0,E_FREESANS9);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_FLANGE_DEPTH text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_FLANGE_DEPTH,E_FLANGE_PAGE,(gslc_tsRect){10,60,51,21},
    (char*)"Depth:",0,E_FREESANS9);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_FLANGE_OFFSET text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_FLANGE_OFFSET,E_FLANGE_PAGE,(gslc_tsRect){10,30,51,15},
    (char*)"Offset:",0,E_FREESANS9);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // create E_FLANGE_BYPASS button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_FLANGE_BYPASS,E_FLANGE_PAGE,
    (gslc_tsRect){239,209,80,30},(char*)"On/Off",0,E_FREEMONO9,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,((gslc_tsColor){47,78,158}),((gslc_tsColor){47,78,158}),((gslc_tsColor){100,124,206}));
  
  // Create E_FLANGE_BYPASS_STATUS runtime modifiable text
  static char m_sDisplayText13[5] = "OFF";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_FLANGE_BYPASS_STATUS,E_FLANGE_PAGE,(gslc_tsRect){263,185,40,15},
    (char*)m_sDisplayText13,5,E_FREESANS9);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  m_flange_bypass = pElemRef;

  // -----------------------------------
  // PAGE: E_REVERB_PAGE
  
  
  // create E_REVERB_BACK button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_REVERB_BACK,E_REVERB_PAGE,
    (gslc_tsRect){0,209,80,30},(char*)"Effects",0,E_FREEMONO9,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,((gslc_tsColor){47,78,158}),((gslc_tsColor){47,78,158}),((gslc_tsColor){100,124,206}));
  
  // Create E_REVERB_TITLE text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_REVERB_TITLE,E_REVERB_PAGE,(gslc_tsRect){256,4,58,15},
    (char*)"Reverb",0,E_FREESANS9);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_REVERB_ROOM_SIZE text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_REVERB_ROOM_SIZE,E_REVERB_PAGE,(gslc_tsRect){10,30,91,15},
    (char*)"Room Size:",0,E_FREESANS9);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_REVERB_DRY_LEVEL text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_REVERB_DRY_LEVEL,E_REVERB_PAGE,(gslc_tsRect){10,90,79,23},
    (char*)"Dry Level:",0,E_FREESANS9);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_REVERB_DAMPING text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_REVERB_DAMPING,E_REVERB_PAGE,(gslc_tsRect){10,60,75,23},
    (char*)"Damping:",0,E_FREESANS9);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // create E_REVERB_BYPASS button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_REVERB_BYPASS,E_REVERB_PAGE,
    (gslc_tsRect){239,209,80,30},(char*)"On/Off",0,E_FREEMONO9,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,((gslc_tsColor){47,78,158}),((gslc_tsColor){47,78,158}),((gslc_tsColor){100,124,206}));
  
  // Create E_REVERB_BYPASS_STATUS runtime modifiable text
  static char m_sDisplayText14[5] = "OFF";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_REVERB_BYPASS_STATUS,E_REVERB_PAGE,(gslc_tsRect){263,185,40,15},
    (char*)m_sDisplayText14,5,E_FREESANS9);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  m_reverb_bypass = pElemRef;

  // -----------------------------------
  // PAGE: E_AMP_PAGE
  
  
  // create E_AMP_BACK button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_AMP_BACK,E_AMP_PAGE,
    (gslc_tsRect){0,209,80,30},(char*)"Effects",0,E_FREEMONO9,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,((gslc_tsColor){47,78,158}),((gslc_tsColor){47,78,158}),((gslc_tsColor){100,124,206}));
  
  // Create E_AMP_TITLE text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_AMP_TITLE,E_AMP_PAGE,(gslc_tsRect){267,0,38,21},
    (char*)"Amp",0,E_FREESANS9);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_AMP_GAIN text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_AMP_GAIN,E_AMP_PAGE,(gslc_tsRect){10,30,41,15},
    (char*)"Gain:",0,E_FREESANS9);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // create E_AMP_BYPASS button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_AMP_BYPASS,E_AMP_PAGE,
    (gslc_tsRect){239,209,80,30},(char*)"On/Off",0,E_FREEMONO9,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,((gslc_tsColor){47,78,158}),((gslc_tsColor){47,78,158}),((gslc_tsColor){100,124,206}));
  
  // Create E_AMP_BYPASS_STATUS runtime modifiable text
  static char m_sDisplayText16[5] = "OFF";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_AMP_BYPASS_STATUS,E_AMP_PAGE,(gslc_tsRect){263,185,40,15},
    (char*)m_sDisplayText16,5,E_FREESANS9);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  m_p_amp_bypass_status = pElemRef;
//<InitGUI !End!>

//<Startup !Start!>
//<Startup !End!>

}

#endif // end _GUISLICE_GEN_H
