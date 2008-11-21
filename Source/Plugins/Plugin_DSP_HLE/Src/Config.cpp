// Copyright (C) 2003-2008 Dolphin Project.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, version 2.0.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License 2.0 for more details.

// A copy of the GPL 2.0 should have been included with the program.
// If not, see http://www.gnu.org/licenses/

// Official SVN repository and contact information can be found at
// http://code.google.com/p/dolphin-emu/

#include "Common.h"
#include "IniFile.h"
#include "Config.h"

CConfig g_Config;

CConfig::CConfig()
{
	Load();
}

void CConfig::LoadDefaults()
{
	m_EnableHLEAudio = true;
	m_EnableDTKMusic = true;
	m_Interpolation = true;
	m_DumpSampleMinLength = true;
	m_DumpSamples = false;
	m_AntiGap = false;
}

void CConfig::Load()
{
	// first load defaults
	LoadDefaults();

	IniFile file;
	file.Load(FULL_CONFIG_DIR "DSP.ini");
	file.Get("Config", "EnableHLEAudio", &m_EnableHLEAudio, true); // Sound Settings
	file.Get("Config", "EnableDTKMusic", &m_EnableDTKMusic, true);
	file.Get("Config", "EnableThrottle", &m_EnableThrottle, true);
	file.Get("Config", "Interpolation", &m_Interpolation, true);
	file.Get("Config", "AntiGap", &m_AntiGap, false);

	file.Get("Config", "DumpSamples", &m_DumpSamples, false); // Sample Dumping
	file.Get("Config", "DumpSampleMinLength", &m_DumpSampleMinLength, true);
#ifdef _WIN32
	file.Get("Config", "DumpSamplePath", &m_szSamplePath, "C:\\");
#else
	file.Get("Config", "DumpSamplePath", &m_szSamplePath, "/dev/null/");
#endif	
}

void CConfig::Save()
{
	IniFile file;
	file.Load(FULL_CONFIG_DIR "DSP.ini");
	file.Set("Config", "EnableHLEAudio", m_EnableHLEAudio); // Sound Settings
	file.Set("Config", "EnableDTKMusic", m_EnableDTKMusic);
	file.Set("Config", "EnableThrottle", m_EnableThrottle);
	file.Set("Config", "Interpolation", m_Interpolation);
	file.Set("Config", "AntiGap", m_AntiGap);

	file.Set("Config", "DumpSamples", m_DumpSamples); // Sample Dumping
	file.Set("Config", "DumpSampleMinLength", m_DumpSampleMinLength);
#ifdef _WIN32
	file.Set("Config", "DumpSamplePath", m_szSamplePath);
#else
	file.Set("Config", "DumpSamplePath", m_szSamplePath);
#endif

	file.Save(FULL_CONFIG_DIR "DSP.ini");
}
