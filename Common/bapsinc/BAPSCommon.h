// BAPSCommon.h


#ifndef INCLUDED_BAPSCOMMON_H
#define INCLUDED_BAPSCOMMON_H


#ifdef BAPS_EXPORTS
#define BAPS_API __declspec(dllexport)
#else
#define BAPS_API __declspec(dllimport)
#endif

#define BAPS_CALL __stdcall

#define _CRT_SECURE_NO_DEPRECATE
#define _USE_MATH_DEFINES
#include <math.h>
#include <dshow.h>
#include <rpcdce.h>
#include <windows.h>


// The (only) BAPS window message
// wParam is a member of the BAPSEventType enumeration
// lParam is the index of the channel that sent the message
#define WM_BAPS_CHANNEL_EVENT (WM_APP + 0x1000)

typedef enum
{
	ChannelPlay,
	ChannelStop,
	ChannelPlaybackComplete
} BAPSEventType;


#endif //INCLUDED_BAPSCOMMON_H