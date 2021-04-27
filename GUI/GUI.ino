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
gslc_tsElemRef* m_Amp_Gain_Slider = NULL;
gslc_tsElemRef* m_Damp_Slider     = NULL;
gslc_tsElemRef* m_Dry_Slider      = NULL;
gslc_tsElemRef* m_Mod_Freq_Slider = NULL;
gslc_tsElemRef* m_Room_Slider     = NULL;
gslc_tsElemRef* m_Wet_Slider      = NULL;
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

// startup settings for the effects
#define FLANGE_DELAY_LENGTH (4*AUDIO_BLOCK_SAMPLES)
float flangeOffset = FLANGE_DELAY_LENGTH/4;
float flangeDepth = FLANGE_DELAY_LENGTH/4;
float flangeModFreq = 1;
float ampGain = 20;
float fvDry = 0.5;
float fvWet = 0.5;
float fvRoomSize = 0.5;
float fvDamp = 0.5;
float maxDepth = 165;
float maxFreq = 3.5;
float masterVol = 0.8;
short delayline[FLANGE_DELAY_LENGTH];

// setting on/off logic
bool fvOn = false;
bool distOn = false;
bool flangeOn = false;
bool bypassOn = false;
int activeEff = 0;

// save states and their info
char currentEffect;
int16_t currentPreset = 0;
bool save1[3] = { false };
bool save2[3] = { false };
bool save3[3] = { false };
bool bypassSave[3] = { false } ;
float paramsSave1[8] = {flangeOffset, flangeDepth, flangeModFreq, ampGain, 
                       fvDry, fvWet, fvRoomSize, fvDamp};
float paramsSave2[8] = {flangeOffset, flangeDepth, flangeModFreq, ampGain, 
                       fvDry, fvWet, fvRoomSize, fvDamp};
float paramsSave3[8] = {flangeOffset, flangeDepth, flangeModFreq, ampGain, 
                       fvDry, fvWet, fvRoomSize, fvDamp};
                       

// GUItool: begin automatically generated code
AudioControlSGTL5000     sgtl5000_1;
AudioInputI2S            lineIn;         
AudioEffectFreeverb      freeverbBlock;     
AudioEffectFlange        flangeBlock;       
AudioMixer4              mixFVOut;  
AudioMixer4              bypassMixer;       
AudioAmplifier           ampBlock;        
AudioMixer4              outMix;        
AudioOutputI2S           lineOut;     
AudioConnection          fvInCord(lineIn, 1, freeverbBlock, 0);
AudioConnection          distInCord(lineIn, 1, ampBlock, 0);
AudioConnection          flangeInCord(lineIn, 1, flangeBlock, 0);
AudioConnection          fvDryCord(lineIn, 1, mixFVOut, 1);
AudioConnection          fvMixCord(freeverbBlock, 0, mixFVOut, 0);
AudioConnection          flangeOutCord(flangeBlock, 0, outMix, 2);
AudioConnection          fvOutCord(mixFVOut, 0, outMix, 0);
AudioConnection          distOutCord(ampBlock, 0, outMix, 1);
AudioConnection          outputCord(outMix, 0, lineOut, 1);     
AudioConnection          bypassCord(lineIn, 1, bypassMixer, 3); //use this for bypass
AudioConnection          bypassOut(bypassMixer, 0, outMix, 3);
// GUItool: end automatically generated code

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
        if (!homeBypass) // Turn on bypass
        {
          homeBypass = true;
          snprintf(acTxt, MAX_STR, "ON");
          bypassSave[0] = flangeOn;
          bypassSave[1] = distOn;
          bypassSave[2] = fvOn;
          flangeOutCord.disconnect();
          fvOutCord.disconnect();
          distOutCord.disconnect();
          bypassOut.disconnect();         
          delay(300);
        }
        
        else // Turn off bypass
        {
          homeBypass = false;
          snprintf(acTxt, MAX_STR, "OFF");
          bypassOut.connect();
           if (bypassSave[0] == true)
          {
            flangeOutCord.connect();
          }
            
          if (bypassSave[1] == true)
          {
            distOutCord.connect();
          }
            
          if (bypassSave[2] == true)
          {
            fvOutCord.connect();
          }
          
          delay(300);
        }
        gslc_ElemSetTxtStr(&m_gui, m_home_bypass, acTxt);
        break;
        
      case E_HOME_PRESET:
        currentPreset++;
        if (currentPreset == 5)
          currentPreset = 0;
        
        snprintf(acTxt, MAX_STR, "%d", currentPreset);
        gslc_ElemSetTxtStr(&m_gui, m_current_preset, acTxt);
        break;
      // -------------------------------
      // Flange Screen
      // -------------------------------
      case E_FLANGE_BACK:
        gslc_SetPageCur(&m_gui, 0);
        break;
        
      case E_FLANGE_BYPASS:
        if (flangeOn == false) // off turning on
        {
          snprintf(acTxt, MAX_STR, "ON");
          flangeOutCord.connect();
          flangeOn = true;
        }
        
        else // on turning off
        {
          snprintf(acTxt, MAX_STR, "OFF");
          flangeOutCord.disconnect();
          flangeOn = false;
        }
        gslc_ElemSetTxtStr(&m_gui, m_flange_bypass, acTxt);
        break;
      // -------------------------------
      // Reverb Screen
      // -------------------------------
      case E_REVERB_BACK:
        gslc_SetPageCur(&m_gui, 0);
        break;
        
      case E_REVERB_BYPASS:
        if (fvOn)
        {
          snprintf(acTxt, MAX_STR, "OFF");
          fvOutCord.disconnect();
          fvOn = false;
        }
        
        else
        {
          snprintf(acTxt, MAX_STR, "ON");
          fvOutCord.connect();
          fvOn = true;
        }
        gslc_ElemSetTxtStr(&m_gui, m_reverb_bypass, acTxt);
        break;
      // -------------------------------
      // Amp Screen
      // -------------------------------
      case E_AMP_BACK:
        gslc_SetPageCur(&m_gui, 0);
        break;
        
      case E_AMP_BYPASS:
        if (distOn)
        {
          snprintf(acTxt, MAX_STR, "OFF");
          distOutCord.disconnect();
          distOn = false;
        }
        
        else
        {
          snprintf(acTxt, MAX_STR, "ON");
          distOutCord.connect();
          distOn = true;
        }
        
        gslc_ElemSetTxtStr(&m_gui, m_p_amp_bypass_status, acTxt);
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

// Callback function for when a slider's position has been updated
bool CbSlidePos(void* pvGui,void* pvElemRef,int16_t nPos)
{
  gslc_tsGui*     pGui     = (gslc_tsGui*)(pvGui);
  gslc_tsElemRef* pElemRef = (gslc_tsElemRef*)(pvElemRef);
  gslc_tsElem*    pElem    = gslc_GetElemFromRef(pGui,pElemRef);
  int16_t         nVal;

  // From the element's ID we can determine which slider was updated.
  switch (pElem->nId) {
//<Slider Enums !Start!>
    case E_AMP_GAIN_SLIDER:
      // Fetch the slider position
      nVal = gslc_ElemXSliderGetPos(pGui,m_Amp_Gain_Slider);
      ampGain = nVal * 0.4;
      ampBlock.gain(ampGain);
      break;

    case E_FLANGE_MOD_FREQ_SLIDER:
      // Fetch the slider position
      nVal = gslc_ElemXSliderGetPos(pGui,m_Mod_Freq_Slider);
      flangeModFreq = nVal * 0.01;
      flangeBlock.voices(flangeOffset, flangeDepth, flangeModFreq);
      break;
    case E_REVERB_ROOM_SLIDER:
      // Fetch the slider position
      nVal = gslc_ElemXSliderGetPos(pGui,m_Room_Slider);
      fvRoomSize = nVal * 0.01;
      freeverbBlock.roomsize(fvRoomSize);
      break;
    case E_REVERB_DAMP_SLIDER:
      // Fetch the slider position
      nVal = gslc_ElemXSliderGetPos(pGui,m_Damp_Slider);
      fvDamp = nVal * 0.01;
      freeverbBlock.damping(fvDamp);
      break;
    case E_REVERB_DRY_SLIDER:
      // Fetch the slider position
      nVal = gslc_ElemXSliderGetPos(pGui,m_Dry_Slider);
      fvDry = nVal * 0.01;
      mixFVOut.gain(1, fvDry);
      break;
    case E_REVERB_WET_SLIDER:
      // Fetch the slider position
      nVal = gslc_ElemXSliderGetPos(pGui,m_Wet_Slider);
      fvWet = nVal * 0.01;
      mixFVOut.gain(0, fvWet);
      break;
//<Slider Enums !End!>
    default:
      break;
  }

  return true;
}
//<Tick Callback !Start!>
//<Tick Callback !End!>

void setup()
{
  AudioMemory(524);
  Serial.begin(115200);
  
  // disconnect effects and initialize bypass
  flangeOutCord.disconnect();
  fvOutCord.disconnect();
  distOutCord.disconnect();
  bypassOut.connect();
  bypassSave[0] = flangeOn;
  bypassSave[1] = distOn;
  bypassSave[2] = fvOn;
  
  // setup SGTL5000 and master audio
  sgtl5000_1.enable();
  sgtl5000_1.inputSelect(AUDIO_INPUT_LINEIN);
  sgtl5000_1.volume(masterVol);
  sgtl5000_1.muteHeadphone();
  sgtl5000_1.unmuteLineout();
  outMix.gain(0, masterVol);

  // flange setup
  flangeBlock.begin(delayline, FLANGE_DELAY_LENGTH, flangeOffset, flangeDepth, flangeModFreq);

  // Amp setup
  ampBlock.gain(ampGain);

  // freeverb setup
  mixFVOut.gain(0, fvWet); // "wet" signal
  mixFVOut.gain(1, fvDry); // "dry" signal
  freeverbBlock.roomsize(fvRoomSize);
  freeverbBlock.damping(fvDamp);

  // Create graphic elements
  gslc_InitDebug(&DebugOut);
  InitGUIslice_gen();
}

// Main event loop
void loop()
{
  Serial.print(flangeOffset);
  Serial.print(" ");
  Serial.print(flangeDepth);
  Serial.print(" ");
  Serial.print(flangeModFreq);
  Serial.println();
  // Periodically call GUIslice update function
  gslc_Update(&m_gui);
}
