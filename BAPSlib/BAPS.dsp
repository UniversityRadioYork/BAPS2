# Microsoft Developer Studio Project File - Name="BAPS" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=BAPS - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "BAPS.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "BAPS.mak" CFG="BAPS - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "BAPS - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "BAPS - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "BAPS - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "BAPS_EXPORTS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "Release\inc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "BAPS_EXPORTS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib rpcrt4.lib strmiids.lib quartz.lib /nologo /dll /machine:I386 /out:"Release/bin/BAPS.dll" /libpath:"Release\lib"
# Begin Custom Build
InputPath=.\Release\bin\BAPS.dll
SOURCE="$(InputPath)"

"Release\lib\BAPS.lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy Release\BAPS.lib Release\lib\BAPS.lib

# End Custom Build

!ELSEIF  "$(CFG)" == "BAPS - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "BAPS_EXPORTS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "Debug\inc" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "BAPS_EXPORTS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x809 /d "_DEBUG"
# ADD RSC /l 0x809 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib rpcrt4.lib strmiids.lib quartz.lib /nologo /dll /debug /machine:I386 /out:"Debug/bin/BAPS.dll" /pdbtype:sept /libpath:"Debug\lib"
# Begin Custom Build
InputPath=.\Debug\bin\BAPS.dll
SOURCE="$(InputPath)"

"Debug\lib\BAPS.lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy Debug\BAPS.lib Debug\lib\BAPS.lib

# End Custom Build

!ENDIF 

# Begin Target

# Name "BAPS - Win32 Release"
# Name "BAPS - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\BAPSAudioOutput.cpp
# End Source File
# Begin Source File

SOURCE=.\BAPSAudioOutputChannel.cpp
# End Source File
# Begin Source File

SOURCE=.\BAPSAudioOutputChannels.cpp
# End Source File
# Begin Source File

SOURCE=.\BAPSAudioOutputDevice.cpp
# End Source File
# Begin Source File

SOURCE=.\BAPSAudioOutputDevices.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\BAPS.h

!IF  "$(CFG)" == "BAPS - Win32 Release"

# Begin Custom Build
InputPath=.\BAPS.h
InputName=BAPS

"Release\inc\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy $(InputName).h Release\inc\$(InputName).h

# End Custom Build

!ELSEIF  "$(CFG)" == "BAPS - Win32 Debug"

# Begin Custom Build
InputPath=.\BAPS.h
InputName=BAPS

"Debug\inc\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy $(InputName).h Debug\inc\$(InputName).h

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\BAPSAudioOutput.h

!IF  "$(CFG)" == "BAPS - Win32 Release"

# Begin Custom Build
InputPath=.\BAPSAudioOutput.h
InputName=BAPSAudioOutput

"Release\inc\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy $(InputName).h Release\inc\$(InputName).h

# End Custom Build

!ELSEIF  "$(CFG)" == "BAPS - Win32 Debug"

# Begin Custom Build
InputPath=.\BAPSAudioOutput.h
InputName=BAPSAudioOutput

"Debug\inc\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy $(InputName).h Debug\inc\$(InputName).h

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\BAPSAudioOutputChannel.h

!IF  "$(CFG)" == "BAPS - Win32 Release"

# Begin Custom Build
InputPath=.\BAPSAudioOutputChannel.h
InputName=BAPSAudioOutputChannel

"Release\inc\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy $(InputName).h Release\inc\$(InputName).h

# End Custom Build

!ELSEIF  "$(CFG)" == "BAPS - Win32 Debug"

# Begin Custom Build
InputPath=.\BAPSAudioOutputChannel.h
InputName=BAPSAudioOutputChannel

"Debug\inc\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy $(InputName).h Debug\inc\$(InputName).h

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\BAPSAudioOutputChannels.h

!IF  "$(CFG)" == "BAPS - Win32 Release"

# Begin Custom Build
InputPath=.\BAPSAudioOutputChannels.h
InputName=BAPSAudioOutputChannels

"Release\inc\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy $(InputName).h Release\inc\$(InputName).h

# End Custom Build

!ELSEIF  "$(CFG)" == "BAPS - Win32 Debug"

# Begin Custom Build
InputPath=.\BAPSAudioOutputChannels.h
InputName=BAPSAudioOutputChannels

"Debug\inc\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy $(InputName).h Debug\inc\$(InputName).h

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\BAPSAudioOutputDevice.h

!IF  "$(CFG)" == "BAPS - Win32 Release"

# Begin Custom Build
InputPath=.\BAPSAudioOutputDevice.h
InputName=BAPSAudioOutputDevice

"Release\inc\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy $(InputName).h Release\inc\$(InputName).h

# End Custom Build

!ELSEIF  "$(CFG)" == "BAPS - Win32 Debug"

# Begin Custom Build
InputPath=.\BAPSAudioOutputDevice.h
InputName=BAPSAudioOutputDevice

"Debug\inc\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy $(InputName).h Debug\inc\$(InputName).h

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\BAPSAudioOutputDevices.h

!IF  "$(CFG)" == "BAPS - Win32 Release"

# Begin Custom Build
InputPath=.\BAPSAudioOutputDevices.h
InputName=BAPSAudioOutputDevices

"Release\inc\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy $(InputName).h Release\inc\$(InputName).h

# End Custom Build

!ELSEIF  "$(CFG)" == "BAPS - Win32 Debug"

# Begin Custom Build
InputPath=.\BAPSAudioOutputDevices.h
InputName=BAPSAudioOutputDevices

"Debug\inc\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy $(InputName).h Debug\inc\$(InputName).h

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\BAPSCommon.h

!IF  "$(CFG)" == "BAPS - Win32 Release"

# Begin Custom Build
InputPath=.\BAPSCommon.h
InputName=BAPSCommon

"Release\inc\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy $(InputName).h Release\inc\$(InputName).h

# End Custom Build

!ELSEIF  "$(CFG)" == "BAPS - Win32 Debug"

# Begin Custom Build
InputPath=.\BAPSCommon.h
InputName=BAPSCommon

"Debug\inc\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy $(InputName).h Debug\inc\$(InputName).h

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
