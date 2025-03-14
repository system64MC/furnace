/**
 * Furnace Tracker - multi-system chiptune tracker
 * Copyright (C) 2021-2022 tildearrow and contributors
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "gui.h"

bool FurnaceGUI::drawSysConf(int chan, DivSystem type, DivConfig& flags, bool modifyOnChange) {
  bool altered=false;
  bool restart=settings.restartOnFlagChange && modifyOnChange;

  switch (type) {
    case DIV_SYSTEM_YM2612:
    case DIV_SYSTEM_YM2612_EXT: 
    case DIV_SYSTEM_YM2612_FRAC:
    case DIV_SYSTEM_YM2612_FRAC_EXT: {
      int clockSel=flags.getInt("clockSel",0);
      bool ladder=flags.getBool("ladderEffect",0);

      if (ImGui::RadioButton("NTSC (7.67MHz)",clockSel==0)) {
        clockSel=0;
        altered=true;
      }
      if (ImGui::RadioButton("PAL (7.61MHz)",clockSel==1)) {
        clockSel=1;
        altered=true;
      }
      if (ImGui::RadioButton("FM Towns (8MHz)",clockSel==2)) {
        clockSel=2;
        altered=true;
      }
      if (ImGui::RadioButton("AtGames Genesis (6.13MHz)",clockSel==3)) {
        clockSel=3;
        altered=true;
      }
      if (ImGui::RadioButton("Sega System 32 (8.05MHz)",clockSel==4)) {
        clockSel=4;
        altered=true;
      }
      if (ImGui::Checkbox("Enable DAC distortion",&ladder)) {
        altered=true;
      }
      
      if (altered) {
        e->lockSave([&]() {
          flags.set("clockSel",clockSel);
          flags.set("ladderEffect",ladder);
        });
      }
      break;
    }
    case DIV_SYSTEM_SMS: {
      int clockSel=flags.getInt("clockSel",0);
      int chipType=flags.getInt("chipType",0);
      bool noPhaseReset=flags.getBool("noPhaseReset",false);

      ImGui::Text("Clock rate:");
      if (ImGui::RadioButton("3.58MHz (NTSC)",clockSel==0)) {
        clockSel=0;
        altered=true;
      }
      if (ImGui::RadioButton("3.55MHz (PAL)",clockSel==1)) {
        clockSel=1;
        altered=true;
      }
      if (ImGui::RadioButton("4MHz (BBC Micro)",clockSel==2)) {
        clockSel=2;
        altered=true;
      }
      if (ImGui::RadioButton("1.79MHz (Half NTSC)",clockSel==3)) {
        clockSel=3;
        altered=true;
      }
      if (ImGui::RadioButton("3MHz (Exed Exes)",clockSel==4)) {
        clockSel=4;
        altered=true;
      }
      if (ImGui::RadioButton("2MHz (Sega System 1)",clockSel==5)) {
        clockSel=5;
        altered=true;
      }
      if (ImGui::RadioButton("447KHz (TI-99/4A)",clockSel==6)) {
        clockSel=6;
        altered=true;
      }
      ImGui::Text("Chip type:");
      if (ImGui::RadioButton("Sega VDP/Master System",chipType==0)) {
        chipType=0;
        altered=true;
      }
      if (ImGui::RadioButton("TI SN76489",chipType==1)) {
        chipType=1;
        altered=true;
      }
      if (ImGui::RadioButton("TI SN76489 with Atari-like short noise",chipType==2)) {
        chipType=2;
        altered=true;
      }
      if (ImGui::RadioButton("Game Gear",chipType==3)) {
        chipType=3;
        altered=true;
      }
      if (ImGui::RadioButton("TI SN76489A",chipType==4)) {
        chipType=4;
        altered=true;
      }
      if (ImGui::RadioButton("TI SN76496",chipType==5)) {
        chipType=5;
        altered=true;
      }
      if (ImGui::RadioButton("NCR 8496",chipType==6)) {
        chipType=6;
        altered=true;
      }
      if (ImGui::RadioButton("Tandy PSSJ 3-voice sound",chipType==7)) {
        chipType=7;
        altered=true;
      }
      if (ImGui::RadioButton("TI SN94624",chipType==8)) {
        chipType=8;
        altered=true;
      }
      if (ImGui::RadioButton("TI SN76494",chipType==9)) {
        chipType=9;
        altered=true;
      }

      if (ImGui::Checkbox("Disable noise period change phase reset",&noPhaseReset)) {
        altered=true;
      }

      if (altered) {
        e->lockSave([&]() {
          flags.set("clockSel",clockSel);
          flags.set("chipType",chipType);
          flags.set("noPhaseReset",noPhaseReset);
        });
      }
      break;
    }
    case DIV_SYSTEM_PCE: {
      bool clockSel=flags.getInt("clockSel",0);
      int chipType=flags.getInt("chipType",0);
      bool noAntiClick=flags.getBool("noAntiClick",false);

      if (ImGui::Checkbox("Pseudo-PAL",&clockSel)) {
        altered=true;
      }
      if (ImGui::Checkbox("Disable anti-click",&noAntiClick)) {
        altered=true;
      }
      ImGui::Text("Chip revision:");
      if (ImGui::RadioButton("HuC6280 (original)",chipType==0)) {
        chipType=0;
        altered=true;
      }
      if (ImGui::RadioButton("HuC6280A (SuperGrafx)",chipType==1)) {
        chipType=1;
        altered=true;
      }

      if (altered) {
        e->lockSave([&]() {
          flags.set("clockSel",(int)clockSel);
          flags.set("chipType",chipType);
          flags.set("noAntiClick",noAntiClick);
        });
      }
      break;
    }
    case DIV_SYSTEM_SOUND_UNIT: {
      int clockSel=flags.getInt("clockSel",0);
      bool echo=flags.getBool("echo",false);
      bool swapEcho=flags.getBool("swapEcho",false);
      int sampleMemSize=flags.getInt("sampleMemSize",0);
      bool pdm=flags.getBool("pdm",false);
      int echoDelay=flags.getInt("echoDelay",0);
      int echoFeedback=flags.getInt("echoFeedback",0);
      int echoResolution=flags.getInt("echoResolution",0);
      int echoVol=(signed char)flags.getInt("echoVol",0);

      ImGui::Text("CPU rate:");
      if (ImGui::RadioButton("6.18MHz (NTSC)",clockSel==0)) {
        clockSel=0;
        altered=true;
      }
      if (ImGui::RadioButton("5.95MHz (PAL)",clockSel==1)) {
        clockSel=1;
        altered=true;
      }
      ImGui::Text("Sample memory:");
      if (ImGui::RadioButton("8K (rev A/B/E)",sampleMemSize==0)) {
        sampleMemSize=0;
        altered=true;
      }
      if (ImGui::RadioButton("64K (rev D/F)",sampleMemSize==1)) {
        sampleMemSize=1;
        altered=true;
      }
      ImGui::Text("DAC resolution:");
      if (ImGui::RadioButton("16-bit (rev A/B/D/F)",pdm==0)) {
        pdm=false;
        altered=true;
      }
      if (ImGui::RadioButton("1-bit PDM (rev C/E)",pdm==1)) {
        pdm=true;
        altered=true;
      }
      if (ImGui::Checkbox("Enable echo",&echo)) {
        altered=true;
      }
      if (ImGui::Checkbox("Swap echo channels",&swapEcho)) {
        altered=true;
      }
      ImGui::Text("Echo delay:");
      if (CWSliderInt("##EchoBufSize",&echoDelay,0,63)) {
        if (echoDelay<0) echoDelay=0;
        if (echoDelay>63) echoDelay=63;
        altered=true;
      } rightClickable
      ImGui::Text("Echo resolution:");
      if (CWSliderInt("##EchoResolution",&echoResolution,0,15)) {
        if (echoResolution<0) echoResolution=0;
        if (echoResolution>15) echoResolution=15;
        altered=true;
      } rightClickable
      ImGui::Text("Echo feedback:");
      if (CWSliderInt("##EchoFeedback",&echoFeedback,0,15)) {
        if (echoFeedback<0) echoFeedback=0;
        if (echoFeedback>15) echoFeedback=15;
        altered=true;
      } rightClickable
      ImGui::Text("Echo volume:");
      if (CWSliderInt("##EchoVolume",&echoVol,-128,127)) {
        if (echoVol<-128) echoVol=-128;
        if (echoVol>127) echoVol=127;
        altered=true;
      } rightClickable

      if (altered) {
        e->lockSave([&]() {
          flags.set("clockSel",clockSel);
          flags.set("echo",echo);
          flags.set("swapEcho",swapEcho);
          flags.set("sampleMemSize",sampleMemSize);
          flags.set("pdm",pdm);
          flags.set("echoDelay",echoDelay);
          flags.set("echoFeedback",echoFeedback);
          flags.set("echoResolution",echoResolution);
          flags.set("echoVol",(unsigned char)echoVol);
        });
      }
      break;
    }
    case DIV_SYSTEM_GB: {
      int chipType=flags.getInt("chipType",0);
      bool noAntiClick=flags.getBool("noAntiClick",false);

      if (ImGui::Checkbox("Disable anti-click",&noAntiClick)) {
        altered=true;
      }
      ImGui::Text("Chip revision:");
      if (ImGui::RadioButton("Original (DMG)",chipType==0)) {
        chipType=0;
        altered=true;
      }
      if (ImGui::RadioButton("Game Boy Color (rev C)",chipType==1)) {
        chipType=1;
        altered=true;
      }
      if (ImGui::RadioButton("Game Boy Color (rev E)",chipType==2)) {
        chipType=2;
        altered=true;
      }
      if (ImGui::RadioButton("Game Boy Advance",chipType==3)) {
        chipType=3;
        altered=true;
      }

      if (altered) {
        e->lockSave([&]() {
          flags.set("chipType",chipType);
          flags.set("noAntiClick",noAntiClick);
        });
      }
      break;
    }
    case DIV_SYSTEM_OPLL:
    case DIV_SYSTEM_OPLL_DRUMS:
    case DIV_SYSTEM_VRC7: {
      int clockSel=flags.getInt("clockSel",0);
      int patchSet=flags.getInt("patchSet",0);

      ImGui::Text("Clock rate:");
      if (ImGui::RadioButton("NTSC (3.58MHz)",clockSel==0)) {
        clockSel=0;
        altered=true;
      }
      if (ImGui::RadioButton("PAL (3.55MHz)",clockSel==1)) {
        clockSel=1;
        altered=true;
      }
      if (ImGui::RadioButton("Arcade (4MHz)",clockSel==2)) {
        clockSel=2;
        altered=true;
      }
      if (ImGui::RadioButton("Half NTSC (1.79MHz)",clockSel==3)) {
        clockSel=3;
        altered=true;
      }
      if (type!=DIV_SYSTEM_VRC7) {
        ImGui::Text("Patch set:");
        if (ImGui::RadioButton("Yamaha YM2413",patchSet==0)) {
          patchSet=0;
          altered=true;
        }
        if (ImGui::RadioButton("Yamaha YMF281",patchSet==1)) {
          patchSet=1;
          altered=true;
        }
        if (ImGui::RadioButton("Yamaha YM2423",patchSet==2)) {
          patchSet=2;
          altered=true;
        }
        if (ImGui::RadioButton("Konami VRC7",patchSet==3)) {
          patchSet=3;
          altered=true;
        }
      }

      if (altered) {
        e->lockSave([&]() {
          flags.set("clockSel",clockSel);
          if (type!=DIV_SYSTEM_VRC7) {
            flags.set("patchSet",patchSet);
          }
        });
      }
      break;
    }
    case DIV_SYSTEM_YM2151: {
      int clockSel=flags.getInt("clockSel",0);

      if (ImGui::RadioButton("NTSC/X16 (3.58MHz)",clockSel==0)) {
        clockSel=0;
        altered=true;
      }
      if (ImGui::RadioButton("PAL (3.55MHz)",clockSel==1)) {
        clockSel=1;
        altered=true;
      }
      if (ImGui::RadioButton("X1/X68000 (4MHz)",clockSel==2)) {
        clockSel=2;
        altered=true;
      }

      if (altered) {
        e->lockSave([&]() {
          flags.set("clockSel",clockSel);
        });
      }
      break;
    }
    case DIV_SYSTEM_NES:
    case DIV_SYSTEM_VRC6:
    case DIV_SYSTEM_FDS:
    case DIV_SYSTEM_MMC5: {
      int clockSel=flags.getInt("clockSel",0);

      if (ImGui::RadioButton("NTSC (1.79MHz)",clockSel==0)) {
        clockSel=0;
        altered=true;
      }
      if (ImGui::RadioButton("PAL (1.67MHz)",clockSel==1)) {
        clockSel=1;
        altered=true;
      }
      if (ImGui::RadioButton("Dendy (1.77MHz)",clockSel==2)) {
        clockSel=2;
        altered=true;
      }

      if (altered) {
        e->lockSave([&]() {
          flags.set("clockSel",clockSel);
        });
      }
      break;
    }
    case DIV_SYSTEM_C64_8580:
    case DIV_SYSTEM_C64_6581: {
      int clockSel=flags.getInt("clockSel",0);

      if (ImGui::RadioButton("NTSC (1.02MHz)",clockSel==0)) {
        clockSel=0;
        altered=true;
      }
      if (ImGui::RadioButton("PAL (0.99MHz)",clockSel==1)) {
        clockSel=1;
        altered=true;
      }
      if (ImGui::RadioButton("SSI 2001 (0.89MHz)",clockSel==2)) {
        clockSel=2;
        altered=true;
      }

      if (altered) {
        e->lockSave([&]() {
          flags.set("clockSel",clockSel);
        });
      }
      break;
    }
    case DIV_SYSTEM_YM2610:
    case DIV_SYSTEM_YM2610_EXT:
    case DIV_SYSTEM_YM2610_FULL:
    case DIV_SYSTEM_YM2610_FULL_EXT:
    case DIV_SYSTEM_YM2610B:
    case DIV_SYSTEM_YM2610B_EXT: {
      int clockSel=flags.getInt("clockSel",0);

      if (ImGui::RadioButton("8MHz (Neo Geo MVS)",clockSel==0)) {
        clockSel=0;
        altered=true;
      }
      if (ImGui::RadioButton("8.06MHz (Neo Geo AES)",clockSel==1)) {
        clockSel=1;
        altered=true;
      }

      if (altered) {
        e->lockSave([&]() {
          flags.set("clockSel",clockSel);
        });
      }
      break;
    }
    case DIV_SYSTEM_AY8910:
    case DIV_SYSTEM_AY8930: {
      int clockSel=flags.getInt("clockSel",0);
      int chipType=flags.getInt("chipType",0);
      bool halfClock=flags.getBool("halfClock",false);
      bool stereo=flags.getBool("stereo",false);
      int stereoSep=flags.getInt("stereoSep",0);

      ImGui::Text("Clock rate:");
      if (ImGui::RadioButton("1.79MHz (ZX Spectrum NTSC/MSX)",clockSel==0)) {
        clockSel=0;
        altered=true;
      }
      if (ImGui::RadioButton("1.77MHz (ZX Spectrum)",clockSel==1)) {
        clockSel=1;
        altered=true;
      }
      if (ImGui::RadioButton("1.75MHz (ZX Spectrum)",clockSel==2)) {
        clockSel=2;
        altered=true;
      }
      if (ImGui::RadioButton("2MHz (Atari ST/Sharp X1)",clockSel==3)) {
        clockSel=3;
        altered=true;
      }
      if (ImGui::RadioButton("1.5MHz (Vectrex)",clockSel==4)) {
        clockSel=4;
        altered=true;
      }
      if (ImGui::RadioButton("1MHz (Amstrad CPC)",clockSel==5)) {
        clockSel=5;
        altered=true;
      }
      if (ImGui::RadioButton("0.89MHz (Pre-divided Sunsoft 5B)",clockSel==6)) {
        clockSel=6;
        altered=true;
      }
      if (ImGui::RadioButton("1.67MHz (?)",clockSel==7)) {
        clockSel=7;
        altered=true;
      }
      if (ImGui::RadioButton("0.83MHz (Pre-divided Sunsoft 5B on PAL)",clockSel==8)) {
        clockSel=8;
        altered=true;
      }
      if (ImGui::RadioButton("1.10MHz (Gamate/VIC-20 PAL)",clockSel==9)) {
        clockSel=9;
        altered=true;
      }
      if (ImGui::RadioButton("2^21Hz (Game Boy)",clockSel==10)) {
        clockSel=10;
        altered=true;
      }
      if (ImGui::RadioButton("3.58MHz (Darky)",clockSel==11)) {
        clockSel=11;
        altered=true;
      }
      if (ImGui::RadioButton("3.6MHz (Darky)",clockSel==12)) {
        clockSel=12;
        altered=true;
      }
      if (ImGui::RadioButton("1.25MHz (Mag Max)",clockSel==13)) {
        clockSel=13;
        altered=true;
      }
      if (ImGui::RadioButton("1.536MHz (Kyugo)",clockSel==14)) {
        clockSel=14;
        altered=true;
      }
      if (type==DIV_SYSTEM_AY8910) {
        ImGui::Text("Chip type:");
        if (ImGui::RadioButton("AY-3-8910",chipType==0)) {
          chipType=0;
          altered=true;
        }
        if (ImGui::RadioButton("YM2149(F)",chipType==1)) {
          chipType=1;
          altered=true;
        }
        if (ImGui::RadioButton("Sunsoft 5B",chipType==2)) {
          chipType=2;
          altered=true;
        }
        if (ImGui::RadioButton("AY-3-8914",chipType==3)) {
          chipType=3;
          altered=true;
        }
      }
      ImGui::BeginDisabled(type==DIV_SYSTEM_AY8910 && chipType==2);
      if (ImGui::Checkbox("Stereo##_AY_STEREO",&stereo)) {
        altered=true;
      }
      if (stereo) {
        int sep=256-(stereoSep&255);
        if (CWSliderInt("Separation",&sep,1,256)) {
          if (sep<1) sep=1;
          if (sep>256) sep=256;
          stereoSep=256-sep;
          altered=true;
        }
      }
      ImGui::EndDisabled();
      ImGui::BeginDisabled(type==DIV_SYSTEM_AY8910 && chipType!=1);
      if (ImGui::Checkbox("Half Clock divider##_AY_CLKSEL",&halfClock)) {
        altered=true;
      }
      ImGui::EndDisabled();

      if (altered) {
        e->lockSave([&]() {
          flags.set("clockSel",clockSel);
          if (type==DIV_SYSTEM_AY8910) {
            flags.set("chipType",chipType);
          }
          flags.set("halfClock",halfClock);
          flags.set("stereo",stereo);
          flags.set("stereoSep",stereoSep);
        });
      }
      break;
    }
    case DIV_SYSTEM_SAA1099: {
      int clockSel=flags.getInt("clockSel",0);

      if (ImGui::RadioButton("SAM Coupé (8MHz)",clockSel==0)) {
        clockSel=0;
        altered=true;
      }
      if (ImGui::RadioButton("NTSC (7.15MHz)",clockSel==1)) {
        clockSel=1;
        altered=true;
      }
      if (ImGui::RadioButton("PAL (7.09MHz)",clockSel==2)) {
        clockSel=2;
        altered=true;
      }

      if (altered) {
        e->lockSave([&]() {
          flags.set("clockSel",clockSel);
        });
      }
      break;
    }
    case DIV_SYSTEM_AMIGA: {
      bool clockSel=flags.getInt("clockSel",0);
      int chipType=flags.getInt("chipType",0);
      int stereoSep=flags.getInt("stereoSep",0);
      bool bypassLimits=flags.getBool("bypassLimits",false);

      ImGui::Text("Stereo separation:");
      if (CWSliderInt("##StereoSep",&stereoSep,0,127)) {
        if (stereoSep<0) stereoSep=0;
        if (stereoSep>127) stereoSep=127;
        altered=true;
      } rightClickable
      if (ImGui::RadioButton("Amiga 500 (OCS)",chipType==0)) {
        chipType=0;
        altered=true;
      }
      if (ImGui::RadioButton("Amiga 1200 (AGA)",chipType==1)) {
        chipType=1;
        altered=true;
      }
      if (ImGui::Checkbox("PAL",&clockSel)) {
        altered=true;
      }
      if (ImGui::Checkbox("Bypass frequency limits",&bypassLimits)) {
        altered=true;
      }

      if (altered) {
        e->lockSave([&]() {
          flags.set("clockSel",(int)clockSel);
          flags.set("chipType",chipType);
          flags.set("stereoSep",stereoSep);
          flags.set("bypassLimits",bypassLimits);
        });
      }
      break;
    }
    case DIV_SYSTEM_TIA: {
      bool clockSel=flags.getInt("clockSel",0);
      int mixingType=flags.getInt("mixingType",0);

      ImGui::Text("Mixing mode:");
      if (ImGui::RadioButton("Mono",mixingType==0)) {
        mixingType=0;
        altered=true;
      }
      if (ImGui::RadioButton("Mono (no distortion)",mixingType==1)) {
        mixingType=1;
        altered=true;
      }
      if (ImGui::RadioButton("Stereo",mixingType==2)) {
        mixingType=2;
        altered=true;
      }

      if (ImGui::Checkbox("PAL",&clockSel)) {
        altered=true;
      }

      if (altered) {
        e->lockSave([&]() {
          flags.set("clockSel",(int)clockSel);
          flags.set("mixingType",mixingType);
        });
      }
      break;
    }
    case DIV_SYSTEM_PCSPKR: {
      int speakerType=flags.getInt("speakerType",0);

      ImGui::Text("Speaker type:");
      if (ImGui::RadioButton("Unfiltered",speakerType==0)) {
        speakerType=0;
        altered=true;
      }
      if (ImGui::RadioButton("Cone",speakerType==1)) {
        speakerType=1;
        altered=true;
      }
      if (ImGui::RadioButton("Piezo",speakerType==2)) {
        speakerType=2;
        altered=true;
      }
      if (ImGui::RadioButton("Use system beeper (Linux only!)",speakerType==3)) {
        speakerType=3;
        altered=true;
      }

      if (altered) {
        e->lockSave([&]() {
          flags.set("speakerType",speakerType);
        });
      }
      break;
    }
    case DIV_SYSTEM_QSOUND: {
      int echoDelay=flags.getInt("echoDelay",0);
      int echoFeedback=flags.getInt("echoFeedback",0)&255;

      ImGui::Text("Echo delay:");
      int echoBufSize1=2725-echoDelay;
      if (CWSliderInt("##EchoBufSize",&echoBufSize1,0,2725)) {
        if (echoBufSize1<0) echoBufSize1=0;
        if (echoBufSize1>2725) echoBufSize1=2725;
        echoDelay=2725-echoBufSize1;
        altered=true;;
      } rightClickable
      ImGui::Text("Echo feedback:");
      if (CWSliderInt("##EchoFeedback",&echoFeedback,0,255)) {
        if (echoFeedback<0) echoFeedback=0;
        if (echoFeedback>255) echoFeedback=255;
        altered=true;
      } rightClickable

      if (altered) {
        e->lockSave([&]() {
          flags.set("echoDelay",echoDelay);
          flags.set("echoFeedback",echoFeedback);
        });
      }
      break;
    }
    case DIV_SYSTEM_X1_010: {
      int clockSel=flags.getInt("clockSel",0);
      bool stereo=flags.getBool("stereo",false);

      ImGui::Text("Clock rate:");
      if (ImGui::RadioButton("16MHz (Seta 1)",clockSel==0)) {
        clockSel=0;
        altered=true;
      }
      if (ImGui::RadioButton("16.67MHz (Seta 2)",clockSel==1)) {
        clockSel=1;
        altered=true;
      }

      if (ImGui::Checkbox("Stereo",&stereo)) {
        altered=true;
      }

      if (altered) {
        e->lockSave([&]() {
          flags.set("clockSel",clockSel);
          flags.set("stereo",stereo);
        });
      }
      break;
    }
    case DIV_SYSTEM_N163: {
      int clockSel=flags.getInt("clockSel",0);
      int channels=flags.getInt("channels",0)+1;
      bool multiplex=flags.getBool("multiplex",false);

      ImGui::Text("Clock rate:");
      if (ImGui::RadioButton("NTSC (1.79MHz)",clockSel==0)) {
        clockSel=0;
        altered=true;
      }
      if (ImGui::RadioButton("PAL (1.67MHz)",clockSel==1)) {
        clockSel=1;
        altered=true;
      }
      if (ImGui::RadioButton("Dendy (1.77MHz)",clockSel==2)) {
        clockSel=2;
        altered=true;
      }
      ImGui::Text("Initial channel limit:");
      if (CWSliderInt("##InitialChannelLimit",&channels,1,8)) {
        if (channels<1) channels=1;
        if (channels>8) channels=8;
        altered=true;
      } rightClickable
      if (ImGui::Checkbox("Disable hissing",&multiplex)) {
        altered=true;
      }

      if (altered) {
        e->lockSave([&]() {
          flags.set("clockSel",clockSel);
          flags.set("channels",channels-1);
          flags.set("multiplex",multiplex);
        });
      }
      break;
    }
    case DIV_SYSTEM_OPN:
    case DIV_SYSTEM_OPN_EXT: {
      int clockSel=flags.getInt("clockSel",0);
      int prescale=flags.getInt("prescale",0);

      ImGui::Text("Clock rate:");
      if (ImGui::RadioButton("3.58MHz (NTSC)",clockSel==0)) {
        clockSel=0;
        altered=true;
      }
      if (ImGui::RadioButton("3.54MHz (PAL)",clockSel==1)) {
        clockSel=1;
        altered=true;
      }
      if (ImGui::RadioButton("4MHz",clockSel==2)) {
        clockSel=2;
        altered=true;
      }
      if (ImGui::RadioButton("3MHz",clockSel==3)) {
        clockSel=3;
        altered=true;
      }
      if (ImGui::RadioButton("3.9936MHz (PC-88/PC-98)",clockSel==4)) {
        clockSel=4;
        altered=true;
      }
      if (ImGui::RadioButton("1.5MHz",clockSel==5)) {
        clockSel=5;
        altered=true;
      }
      ImGui::Text("Output rate:");
      if (ImGui::RadioButton("FM: clock / 72, SSG: clock / 16",prescale==0)) {
        prescale=0;
        altered=true;
      }
      if (ImGui::RadioButton("FM: clock / 36, SSG: clock / 8",prescale==1)) {
        prescale=1;
        altered=true;
      }
      if (ImGui::RadioButton("FM: clock / 24, SSG: clock / 4",prescale==2)) {
        prescale=2;
        altered=true;
      }

      if (altered) {
        e->lockSave([&]() {
          flags.set("clockSel",clockSel);
          flags.set("prescale",prescale);
        });
      }
      break;
    }
    case DIV_SYSTEM_PC98:
    case DIV_SYSTEM_PC98_EXT: {
      int clockSel=flags.getInt("clockSel",0);
      int prescale=flags.getInt("prescale",0);

      ImGui::Text("Clock rate:");
      if (ImGui::RadioButton("8MHz (Arcade)",clockSel==0)) {
        clockSel=0;
        altered=true;
      }
      if (ImGui::RadioButton("7.987MHz (PC-88/PC-98)",clockSel==1)) {
        clockSel=1;
        altered=true;
      }
      ImGui::Text("Output rate:");
      if (ImGui::RadioButton("FM: clock / 144, SSG: clock / 32",prescale==0)) {
        prescale=0;
        altered=true;
      }
      if (ImGui::RadioButton("FM: clock / 72, SSG: clock / 16",prescale==1)) {
        prescale=1;
        altered=true;
      }
      if (ImGui::RadioButton("FM: clock / 48, SSG: clock / 8",prescale==2)) {
        prescale=2;
        altered=true;
      }

      if (altered) {
        e->lockSave([&]() {
          flags.set("clockSel",clockSel);
          flags.set("prescale",prescale);
        });
      }
      break;
    }
    case DIV_SYSTEM_RF5C68: {
      int clockSel=flags.getInt("clockSel",0);
      int chipType=flags.getInt("chipType",0);

      ImGui::Text("Clock rate:");
      if (ImGui::RadioButton("8MHz (FM Towns)",clockSel==0)) {
        clockSel=0;
        altered=true;
      }
      if (ImGui::RadioButton("10MHz (Sega System 18)",clockSel==1)) {
        clockSel=1;
        altered=true;
      }
      if (ImGui::RadioButton("12.5MHz (Sega CD/System 32)",clockSel==2)) {
        clockSel=2;
        altered=true;
      }
      ImGui::Text("Chip type:");
      if (ImGui::RadioButton("RF5C68 (10-bit output)",chipType==0)) {
        chipType=0;
        altered=true;
      }
      if (ImGui::RadioButton("RF5C164 (16-bit output)",chipType==1)) {
        chipType=1;
        altered=true;
      }

      if (altered) {
        e->lockSave([&]() {
          flags.set("clockSel",clockSel);
          flags.set("chipType",chipType);
        });
      }
      break;
    }
    case DIV_SYSTEM_MSM6258: {
      int clockSel=flags.getInt("clockSel",0);

      ImGui::Text("Clock rate:");
      if (ImGui::RadioButton("4MHz",clockSel==0)) {
        clockSel=0;
        altered=true;
      }
      if (ImGui::RadioButton("4.096MHz",clockSel==1)) {
        clockSel=1;
        altered=true;
      }
      if (ImGui::RadioButton("8MHz (X68000)",clockSel==2)) {
        clockSel=2;
        altered=true;
      }
      if (ImGui::RadioButton("8.192MHz",clockSel==3)) {
        clockSel=3;
        altered=true;
      }

      if (altered) {
        e->lockSave([&]() {
          flags.set("clockSel",clockSel);
        });
      }
      break;
    }
    case DIV_SYSTEM_MSM6295: {
      int clockSel=flags.getInt("clockSel",0);
      bool rateSel=flags.getBool("rateSel",false);

      ImGui::Text("Clock rate:");
      if (ImGui::RadioButton("1MHz",clockSel==0)) {
        clockSel=0;
        altered=true;
      }
      if (ImGui::RadioButton("1.056MHz",clockSel==1)) {
        clockSel=1;
        altered=true;
      }
      if (ImGui::RadioButton("4MHz",clockSel==2)) {
        clockSel=2;
        altered=true;
      }
      if (ImGui::RadioButton("4.224MHz",clockSel==3)) {
        clockSel=3;
        altered=true;
      }
      if (ImGui::RadioButton("3.58MHz",clockSel==4)) {
        clockSel=4;
        altered=true;
      }
      if (ImGui::RadioButton("1.79MHz",clockSel==5)) {
        clockSel=5;
        altered=true;
      }
      if (ImGui::RadioButton("1.02MHz",clockSel==6)) {
        clockSel=6;
        altered=true;
      }
      if (ImGui::RadioButton("0.89MHz",clockSel==7)) {
        clockSel=7;
        altered=true;
      }
      if (ImGui::RadioButton("2MHz",clockSel==8)) {
        clockSel=8;
        altered=true;
      }
      if (ImGui::RadioButton("2.112MHz",clockSel==9)) {
        clockSel=9;
        altered=true;
      }
      if (ImGui::RadioButton("0.875MHz",clockSel==10)) {
        clockSel=10;
        altered=true;
      }
      if (ImGui::RadioButton("0.9375MHz",clockSel==11)) {
        clockSel=11;
        altered=true;
      }
      if (ImGui::RadioButton("1.5MHz",clockSel==12)) {
        clockSel=12;
        altered=true;
      }
      if (ImGui::RadioButton("3MHz",clockSel==13)) {
        clockSel=13;
        altered=true;
      }
      if (ImGui::RadioButton("1.193MHz (Atari)",clockSel==14)) {
        clockSel=14;
        altered=true;
      }
      ImGui::Text("Output rate:");
      if (ImGui::RadioButton("clock / 132",rateSel==0)) {
        rateSel=false;
        altered=true;
      }
      if (ImGui::RadioButton("clock / 165",rateSel==1)) {
        rateSel=true;
        altered=true;
      }

      if (altered) {
        e->lockSave([&]() {
          flags.set("clockSel",clockSel);
          flags.set("rateSel",rateSel);
        });
      }
      break;
    }
    case DIV_SYSTEM_SCC:
    case DIV_SYSTEM_SCC_PLUS: {
      int clockSel=flags.getInt("clockSel",0);

      ImGui::Text("Clock rate:");
      if (ImGui::RadioButton("1.79MHz (NTSC/MSX)",clockSel==0)) {
        clockSel=0;
        altered=true;
      }
      if (ImGui::RadioButton("1.77MHz (PAL)",clockSel==1)) {
        clockSel=1;
        altered=true;
      }
      if (ImGui::RadioButton("1.5MHz (Arcade)",clockSel==2)) {
        clockSel=2;
        altered=true;
      }
      if (ImGui::RadioButton("2MHz",clockSel==3)) {
        clockSel=3;
        altered=true;
      }

      if (altered) {
        e->lockSave([&]() {
          flags.set("clockSel",clockSel);
        });
      }
      break;
    }
    case DIV_SYSTEM_OPL:
    case DIV_SYSTEM_OPL_DRUMS:
    case DIV_SYSTEM_OPL2:
    case DIV_SYSTEM_OPL2_DRUMS:
    case DIV_SYSTEM_Y8950:
    case DIV_SYSTEM_Y8950_DRUMS: {
      int clockSel=flags.getInt("clockSel",0);

      ImGui::Text("Clock rate:");
      if (ImGui::RadioButton("3.58MHz (NTSC)",clockSel==0)) {
        clockSel=0;
        altered=true;
      }
      if (ImGui::RadioButton("3.54MHz (PAL)",clockSel==1)) {
        clockSel=1;
        altered=true;
      }
      if (ImGui::RadioButton("4MHz",clockSel==2)) {
        clockSel=2;
        altered=true;
      }
      if (ImGui::RadioButton("3MHz",clockSel==3)) {
        clockSel=3;
        altered=true;
      }
      if (ImGui::RadioButton("3.9936MHz (PC-88/PC-98)",clockSel==4)) {
        clockSel=4;
        altered=true;
      }
      if (ImGui::RadioButton("3.5MHz",clockSel==5)) {
        clockSel=5;
        altered=true;
      }

      if (altered) {
        e->lockSave([&]() {
          flags.set("clockSel",clockSel);
        });
      }
      break;
    }
    case DIV_SYSTEM_OPL3:
    case DIV_SYSTEM_OPL3_DRUMS: {
      int clockSel=flags.getInt("clockSel",0);

      ImGui::Text("Clock rate:");
      if (ImGui::RadioButton("14.32MHz (NTSC)",clockSel==0)) {
        clockSel=0;
        altered=true;
      }
      if (ImGui::RadioButton("14.19MHz (PAL)",clockSel==1)) {
        clockSel=1;
        altered=true;
      }
      if (ImGui::RadioButton("14MHz",clockSel==2)) {
        clockSel=2;
        altered=true;
      }
      if (ImGui::RadioButton("16MHz",clockSel==3)) {
        clockSel=3;
        altered=true;
      }
      if (ImGui::RadioButton("15MHz",clockSel==4)) {
        clockSel=4;
        altered=true;
      }

      if (altered) {
        e->lockSave([&]() {
          flags.set("clockSel",clockSel);
        });
      }
      break;
    }
    case DIV_SYSTEM_YMZ280B: {
      int clockSel=flags.getInt("clockSel",0);

      ImGui::Text("Clock rate:");
      if (ImGui::RadioButton("16.9344MHz",clockSel==0)) {
        clockSel=0;
        altered=true;
      }
      if (ImGui::RadioButton("14.32MHz (NTSC)",clockSel==1)) {
        clockSel=1;
        altered=true;
      }
      if (ImGui::RadioButton("14.19MHz (PAL)",clockSel==2)) {
        clockSel=2;
        altered=true;
      }
      if (ImGui::RadioButton("16MHz",clockSel==3)) {
        clockSel=3;
        altered=true;
      }
      if (ImGui::RadioButton("16.67MHz",clockSel==4)) {
        clockSel=4;
        altered=true;
      }
      if (ImGui::RadioButton("14MHz",clockSel==5)) {
        clockSel=5;
        altered=true;
      }

      if (altered) {
        e->lockSave([&]() {
          flags.set("clockSel",clockSel);
        });
      }
      break;
    }
    case DIV_SYSTEM_PCM_DAC: {
      // default to 44100Hz 16-bit stereo
      int sampRate=flags.getInt("rate",44100);
      int bitDepth=flags.getInt("outDepth",15)+1;
      bool stereo=flags.getBool("stereo",false);

      ImGui::Text("Output rate:");
      if (CWSliderInt("##SampRate",&sampRate,1000,96000)) {
        if (sampRate<1000) sampRate=1000;
        if (sampRate>96000) sampRate=96000;
        altered=true;
      } rightClickable
      ImGui::Text("Output bit depth:");
      if (CWSliderInt("##BitDepth",&bitDepth,1,16)) {
        if (bitDepth<1) bitDepth=1;
        if (bitDepth>16) bitDepth=16;
        altered=true;
      } rightClickable
      if (ImGui::Checkbox("Stereo",&stereo)) {
        altered=true;
      }

      if (altered) {
        e->lockSave([&]() {
          flags.set("rate",sampRate);
          flags.set("outDepth",bitDepth-1);
          flags.set("stereo",stereo);
        });
      }
      break;
    }
    case DIV_SYSTEM_SNES: { // TODO: echo
      char temp[64];
      int vsL=127-(flags.getInt("volScaleL",0)&127);
      int vsR=127-(flags.getInt("volScaleR",0)&127);
      bool echo=flags.getBool("echo",false);
      int echoVolL=flags.getInt("echoVolL",127);
      int echoVolR=flags.getInt("echoVolR",127);
      int echoDelay=flags.getInt("echoDelay",0)&15;
      int echoFeedback=flags.getInt("echoFeedback",0);
      int echoMask=flags.getInt("echoMask",0);

      int echoFilter[8];
      echoFilter[0]=flags.getInt("echoFilter0",127);
      echoFilter[1]=flags.getInt("echoFilter1",0);
      echoFilter[2]=flags.getInt("echoFilter2",0);
      echoFilter[3]=flags.getInt("echoFilter3",0);
      echoFilter[4]=flags.getInt("echoFilter4",0);
      echoFilter[5]=flags.getInt("echoFilter5",0);
      echoFilter[6]=flags.getInt("echoFilter6",0);
      echoFilter[7]=flags.getInt("echoFilter7",0);

      ImGui::Text("Volume scale:");
      if (CWSliderInt("Left##VolScaleL",&vsL,0,127)) {
        if (vsL<0) vsL=0;
        if (vsL>127) vsL=127;
        altered=true;
      } rightClickable
      if (CWSliderInt("Right##VolScaleL",&vsR,0,127)) {
        if (vsR<0) vsR=0;
        if (vsR>127) vsR=127;
        altered=true;
      } rightClickable

      if (ImGui::Checkbox("Enable echo",&echo)) {
        altered=true;
      }
      
      ImGui::Text("Initial echo state:");
      for (int i=0; i<8; i++) {
        bool echoChan=(bool)(echoMask&(1<<i));
        snprintf(temp,63,"%d##EON%d",i+1,i);
        if (ImGui::Checkbox(temp,&echoChan)) {
          echoMask&=~(1<<i);
          if (echoChan) {
            echoMask|=1<<i;
          }
          altered=true;
        }
        if (i<7) ImGui::SameLine();
      }

      if (CWSliderInt("Delay##EchoDelay",&echoDelay,0,15)) {
        if (echoDelay<0) echoDelay=0;
        if (echoDelay>15) echoDelay=15;
        altered=true;
      } rightClickable

      if (CWSliderInt("Feedback##EchoFeedback",&echoFeedback,-128,127)) {
        if (echoFeedback<-128) echoFeedback=-128;
        if (echoFeedback>127) echoFeedback=127;
        altered=true;
      } rightClickable

      ImGui::Text("Echo volume:");
      if (CWSliderInt("Left##EchoVolL",&echoVolL,-128,127)) {
        if (echoVolL<-128) echoVolL=-128;
        if (echoVolL>127) echoVolL=127;
        altered=true;
      } rightClickable
      if (CWSliderInt("Right##EchoVolL",&echoVolR,-128,127)) {
        if (echoVolR<-128) echoVolR=-128;
        if (echoVolR>127) echoVolR=127;
        altered=true;
      } rightClickable

      ImGui::Text("Echo filter:");
      for (int i=0; i<8; i++) {
        snprintf(temp,63,"%d##FIR%d",i+1,i);
        if (CWSliderInt(temp,&echoFilter[i],-128,127)) {
          if (echoFilter[i]<-128) echoFilter[i]=-128;
          if (echoFilter[i]>127) echoFilter[i]=127;
          altered=true;
        } rightClickable
      }

      if (altered) {
        e->lockSave([&]() {
          flags.set("volScaleL",127-vsL);
          flags.set("volScaleR",127-vsR);
          flags.set("echo",echo);
          flags.set("echoVolL",echoVolL);
          flags.set("echoVolR",echoVolR);
          flags.set("echoDelay",echoDelay);
          flags.set("echoFeedback",echoFeedback);
          flags.set("echoFilter0",echoFilter[0]);
          flags.set("echoFilter1",echoFilter[1]);
          flags.set("echoFilter2",echoFilter[2]);
          flags.set("echoFilter3",echoFilter[3]);
          flags.set("echoFilter4",echoFilter[4]);
          flags.set("echoFilter5",echoFilter[5]);
          flags.set("echoFilter6",echoFilter[6]);
          flags.set("echoFilter7",echoFilter[7]);
          flags.set("echoMask",echoMask);
        });
      }

      break;
    }
    case DIV_SYSTEM_SWAN:
    case DIV_SYSTEM_VERA:
    case DIV_SYSTEM_BUBSYS_WSG:
    case DIV_SYSTEM_YMU759:
    case DIV_SYSTEM_PET:
    case DIV_SYSTEM_T6W28:
      ImGui::Text("nothing to configure");
      break;
    default: {
      bool sysPal=flags.getInt("clockSel",0);

      if (ImGui::Checkbox("PAL",&sysPal)) {
        altered=true;
      }

      if (altered) {
        e->lockSave([&]() {
          flags.set("clockSel",(int)sysPal);
        });
      }
      break;
    }
  }

  if (altered) {
    if (chan>=0) {
      e->updateSysFlags(chan,restart);
      if (e->song.autoSystem) {
        autoDetectSystem();
      }
      updateWindowTitle();
    }
    MARK_MODIFIED;
  }

  return altered;
}
