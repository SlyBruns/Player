Пример2(реализованы методы: Play,Pause,Stop,Resume):
#INCLUDE "fbgfx.bi"
 Using FB
 Screen 1
 Declare Function mciSendString Lib "winmm.dll" Alias "mciSendStringA" ( _ 
      Byval lpstrCommand As String, _ 
      Byval lpstrReturnString As String, _ 
      Byval uReturnLength As Long, _ 
      Byval hwndCallback As Long) As Long 
 Print "Press P to Play"
 Print "Press S to Stop"
 Print "Press Q to Pause"
 Print "Press W to Play after Pause"  
 Print "Press ESC to Quit"  
 mciSendString("OPEN C:\Sample.mp3 TYPE MpegVideo ALIAS MP3","",0,0) 

 Do
     If Multikey(SC_ESCAPE) Then 'ESC
        mciSendString("close MP3","",0,0)'Освобождаем хендл и выходим
         End
     Elseif Multikey(SC_P) Then 'Играть
         mciSendString("PLAY MP3 from 0","",0,0)
     Elseif Multikey(SC_S) Then 'Стоп
         mciSendString("STOP MP3","",0,0)
     Elseif Multikey(SC_Q) Then 'Пауза
         mciSendString("PAUSE MP3","",0,0)    
     Elseif Multikey(SC_W) Then 'Играть после паузы
         mciSendString("RESUME MP3","",0,0)                    
     Endif    
 Loop


========================================================================
    WIN32 APPLICATION : Player1 Project Overview
========================================================================

AppWizard has created this Player1 application for you.

This file contains a summary of what you will find in each of the files that
make up your Player1 application.


Player1.vcxproj
    This is the main project file for VC++ projects generated using an Application Wizard.
    It contains information about the version of Visual C++ that generated the file, and
    information about the platforms, configurations, and project features selected with the
    Application Wizard.

Player1.vcxproj.filters
    This is the filters file for VC++ projects generated using an Application Wizard. 
    It contains information about the association between the files in your project 
    and the filters. This association is used in the IDE to show grouping of files with
    similar extensions under a specific node (for e.g. ".cpp" files are associated with the
    "Source Files" filter).

Player1.cpp
    This is the main application source file.

/////////////////////////////////////////////////////////////////////////////
AppWizard has created the following resources:

Player1.rc
    This is a listing of all of the Microsoft Windows resources that the
    program uses.  It includes the icons, bitmaps, and cursors that are stored
    in the RES subdirectory.  This file can be directly edited in Microsoft
    Visual C++.

Resource.h
    This is the standard header file, which defines new resource IDs.
    Microsoft Visual C++ reads and updates this file.

Player1.ico
    This is an icon file, which is used as the application's icon (32x32).
    This icon is included by the main resource file Player1.rc.

small.ico
    This is an icon file, which contains a smaller version (16x16)
    of the application's icon. This icon is included by the main resource
    file Player1.rc.

/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named Player1.pch and a precompiled types file named StdAfx.obj.

/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" comments to indicate parts of the source code you
should add to or customize.

/////////////////////////////////////////////////////////////////////////////
