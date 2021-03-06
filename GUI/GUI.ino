//<App !Start!>
// FILE: [GUI.ino]
// Created by GUIslice Builder version: [0.16.b008]
//
// GUIslice Builder Generated File
//
// For the latest guides, updates and support view:
// https://github.com/ImpulseAdventure/GUIslice
//
//<App !End!>

// ------------------------------------------------
// Headers to include
// ------------------------------------------------
#include "GUI_GSLC.h"


// ------------------------------------------------
// Program Globals
// ------------------------------------------------

// Save some element references for direct access
//<Save_References !Start!>
gslc_tsElemRef* m_current_preset  = NULL;
gslc_tsElemRef* m_flange_bypass   = NULL;
gslc_tsElemRef* m_home_bypass     = NULL;
gslc_tsElemRef* m_p_amp_bypass_status= NULL;
gslc_tsElemRef* m_reverb_bypass   = NULL;
//<Save_References !End!>

// User Globals
#include <Audio.h>
#include <Wire.h>
#include <SD.h>
#include <SPI.h>
#include <SerialFlash.h>
#include <Bounce.h>

AudioSynthWaveform    waveform1;
AudioInputI2S         lineIn;  
AudioOutputI2S        i2s1;
AudioMixer4              outMix;
AudioConnection       patchCord1(waveform1, 0, i2s1, 0);
AudioConnection       patchCord2(waveform1, 0, i2s1, 1);
AudioControlSGTL5000  sgtl5000_1;
AudioConnection          outputCord(outMix, 0, i2s1, 1);  
AudioConnection          bypassCord(lineIn, 1, outMix, 3);

int16_t currentPreset = 0;
bool homeBypass = false;

// Define debug message function
static int16_t DebugOut(char ch) { if (ch == (char)'\n') Serial.println(""); else Serial.write(ch); return 0; }

// ------------------------------------------------
// Callback Methods
// ------------------------------------------------
// Common Button callback
bool CbBtnCommon(void* pvGui,void *pvElemRef,gslc_teTouch eTouch,int16_t nX,int16_t nY)
{
  // Typecast the parameters to match the GUI and element types
  gslc_tsGui*     pGui     = (gslc_tsGui*)(pvGui);
  gslc_tsElemRef* pElemRef = (gslc_tsElemRef*)(pvElemRef);
  gslc_tsElem*    pElem    = gslc_GetElemFromRef(pGui,pElemRef);
  char acTxt[MAX_STR];

  if ( eTouch == GSLC_TOUCH_UP_IN ) {
    // From the element's ID we can determine which button was pressed. 
    switch (pElem->nId) {
//<Button Enums !Start!>
      case E_HOME_FLANGE:
        gslc_SetPageCur(&m_gui, 1);
        break;
      case E_HOME_AMP:
        gslc_SetPageCur(&m_gui, 3);
        break;
      case E_HOME_REVERB:
        gslc_SetPageCur(&m_gui, 2);
        break;
      case E_HOME_BYPASS:
        if (homeBypass)
        {
          homeBypass = false;
          snprintf(acTxt, MAX_STR, "OFF");
          gslc_ElemSetTxtStr(&m_gui, m_home_bypass, acTxt);
        }
        else
        {
          homeBypass = true;
          snprintf(acTxt, MAX_STR, "ON");
          gslc_ElemSetTxtStr(&m_gui, m_home_bypass, acTxt);
        }
        
        break;
      case E_HOME_PRESET:
        currentPreset++;
        if (currentPreset == 5)
          currentPreset = 0;
        
        snprintf(acTxt, MAX_STR, "%d", currentPreset);
        gslc_ElemSetTxtStr(&m_gui, m_current_preset, acTxt);
        break;
      case E_FLANGE_BACK:
        gslc_SetPageCur(&m_gui, 0);
        break;
      case E_FLANGE_BYPASS:
        break;
      case E_REVERB_BACK:
        gslc_SetPageCur(&m_gui, 0);
        break;
      case E_REVERB_BYPASS:
        break;
      case E_AMP_BACK:
        gslc_SetPageCur(&m_gui, 0);
        break;
      case E_AMP_BYPASS:
        break;
//<Button Enums !End!>
      default:
        break;
    }
  }
  return true;
}
//<Checkbox Callback !Start!>
//<Checkbox Callback !End!>
//<Keypad Callback !Start!>
//<Keypad Callback !End!>
//<Spinner Callback !Start!>
//<Spinner Callback !End!>
//<Listbox Callback !Start!>
//<Listbox Callback !End!>
//<Draw Callback !Start!>
//<Draw Callback !End!>
//<Slider Callback !Start!>
//<Slider Callback !End!>
//<Tick Callback !Start!>
//<Tick Callback !End!>

void setup()
{
  AudioMemory(10);
  // ------------------------------------------------
  // Initialize
  // ------------------------------------------------
  Serial.begin(115200);
  sgtl5000_1.enable();
  sgtl5000_1.inputSelect(AUDIO_INPUT_LINEIN);
  sgtl5000_1.volume(0.8);
  sgtl5000_1.muteHeadphone();
  sgtl5000_1.unmuteLineout();
  outMix.gain(0, 0.8);
  // Wait for USB Serial 
  //delay(1000);  // NOTE: Some devices require a delay after Serial.begin() before serial port can be used

  gslc_InitDebug(&DebugOut);

  // ------------------------------------------------
  // Create graphic elements
  // ------------------------------------------------
  InitGUIslice_gen();

}

// -----------------------------------
// Main event loop
// -----------------------------------
void loop()
{

  // ------------------------------------------------
  // Update GUI Elements
  // ------------------------------------------------
  
  //TODO - Add update code for any text, gauges, or sliders
  
  // ------------------------------------------------
  // Periodically call GUIslice update function
  // ------------------------------------------------
  gslc_Update(&m_gui);
    
}
