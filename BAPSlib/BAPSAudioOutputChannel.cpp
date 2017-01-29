// BAPSAudioOutputChannel.cpp


#include "stdafx.h"
#include "BAPSAudioOutputChannel.h"


CBAPSAudioOutputChannel::CBAPSAudioOutputChannel()
{

	// Initialise member variables
	m_iIndex = -1;
	m_pGraphBuilder = NULL;
	m_pMediaControl = NULL;
	m_pMediaEvent = NULL;
	m_pMediaSeeking = NULL;
	m_pBasicAudio = NULL;
	m_pOutputDevice = NULL;
	m_pRendererFilter = NULL;
	m_pSourceFilter = NULL;
//	m_hEventMonitorThread = NULL;
//	m_hStopEventMonitorEvent = NULL;
	m_FilterState = State_Stopped;

}


CBAPSAudioOutputChannel::~CBAPSAudioOutputChannel()
{

	CleanUp();

}


BOOL CBAPSAudioOutputChannel::Initialise(int iIndex, NotifyCallback _callback)
{
	callback = _callback;
	HRESULT hr;
	DWORD dwThreadID;

	// Store the index
	m_iIndex = iIndex;

	// Create the filter graph
	hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void**)&m_pGraphBuilder);

	if (FAILED(hr))
	{
		CleanUp();
		return FALSE;
	}

	// Get the Media Control interface
	hr = m_pGraphBuilder->QueryInterface(IID_IMediaControl, (void**)&m_pMediaControl);

	if (FAILED(hr))
	{
		CleanUp();
		return FALSE;
	}

	// Get the Media Event interface
	hr = m_pGraphBuilder->QueryInterface(IID_IMediaEvent, (void**)&m_pMediaEvent);

	if (FAILED(hr))
	{
		CleanUp();
		return FALSE;
	}

	// Get the Media Seeking interface
	hr = m_pGraphBuilder->QueryInterface(IID_IMediaSeeking, (void**)&m_pMediaSeeking);

	if (FAILED(hr))
	{
		CleanUp();
		return FALSE;
	}

	// Get the Basic Audio interface
	hr = m_pGraphBuilder->QueryInterface(IID_IBasicAudio, (void**)&m_pBasicAudio);

	if (FAILED(hr))
	{
		CleanUp();
		return FALSE;
	}

	// Create the stop monitoring event
	m_hStopEventMonitorEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

	if (NULL == m_hStopEventMonitorEvent)
	{
		CleanUp();
		return FALSE;
	}

	// Create the monitoring thread
	m_hEventMonitorThread = CreateThread(NULL, 0, EventMonitorThreadProc, this, 0, &dwThreadID);

	if (NULL == m_hEventMonitorThread)
	{
		CleanUp();
		return FALSE;
	}

	return TRUE;

}


void CBAPSAudioOutputChannel::CleanUp()
{

	// Make sure the graph's stopped
	if (NULL != m_pMediaControl)
	{
		m_pMediaControl->Stop();
	}

	// Stop the event monitoring thread if it exists
	if (NULL != m_hStopEventMonitorEvent)
	{

		if (NULL != m_hEventMonitorThread)
		{

			// Set the stop event and wait for the thread to exit
			SetEvent(m_hStopEventMonitorEvent);
			WaitForSingleObject(m_hEventMonitorThread, INFINITE);
			CloseHandle(m_hEventMonitorThread);
			m_hEventMonitorThread = NULL;

		}

		// Close the stop event handle
		CloseHandle(m_hStopEventMonitorEvent);
		m_hStopEventMonitorEvent = NULL;

	}

	// Release all the DirectShow interfaces
	if (NULL != m_pRendererFilter)
	{
		m_pRendererFilter->Release();
		m_pRendererFilter = NULL;
	}

	if (NULL != m_pSourceFilter)
	{
		m_pSourceFilter->Release();
		m_pSourceFilter = NULL;
	}

	if (NULL != m_pBasicAudio)
	{
		m_pBasicAudio->Release();
		m_pBasicAudio = NULL;
	}

	if (NULL != m_pMediaSeeking)
	{
		m_pMediaSeeking->Release();
		m_pMediaSeeking = NULL;
	}

	if (NULL != m_pMediaEvent)
	{
		m_pMediaEvent->Release();
		m_pMediaEvent = NULL;
	}

	if (NULL != m_pMediaControl)
	{
		m_pMediaControl->Release();
		m_pMediaControl = NULL;
	}

	if (NULL != m_pGraphBuilder)
	{
		m_pGraphBuilder->Release();
		m_pGraphBuilder = NULL;
	}

}


DWORD CBAPSAudioOutputChannel::EventMonitorThreadProc(void* pParameter)
{

	return ((CBAPSAudioOutputChannel*)pParameter)->EventMonitorThreadProc();

}


DWORD CBAPSAudioOutputChannel::EventMonitorThreadProc()
{

	HRESULT hr;
	HANDLE hObject[2];
	BOOL bExit;
	long lEventCode;
	LONG_PTR lParam1, lParam2;

	// Get the DirectShow event
	hr = m_pMediaEvent->GetEventHandle((OAEVENT*)&hObject[0]);

	// Get the stop event monitoring event
	hObject[1] = m_hStopEventMonitorEvent;

	if (FAILED(hr) || NULL == hObject[0])
	{
		return 1;
	}

	bExit = FALSE;

	while (!bExit)
	{

		switch(WaitForMultipleObjects(sizeof(hObject) / sizeof(HANDLE), hObject, FALSE, INFINITE))
		{

		case WAIT_OBJECT_0:

			m_pMediaEvent->GetEvent(&lEventCode, &lParam1, &lParam2, 0);

			if (EC_COMPLETE == lEventCode)
			{

				// This is slightly dodgy, running on a different thread to the caller
				// Should probably implement some locking, especially if the caller is going to be doing things
				// on different threads
				m_pMediaControl->Pause();

				callback(m_iIndex);
//				PostMessage(m_hWndNotify, WM_BAPS_CHANNEL_EVENT, ChannelPlaybackComplete, m_iIndex);
	
			}

			m_pMediaEvent->FreeEventParams(lEventCode, lParam1, lParam2);

			break;

		case WAIT_OBJECT_0 + 1:

			bExit = TRUE;

			break;

		}

	}

	return 0;

}


int CBAPSAudioOutputChannel::ReferenceTimeToMilliseconds(LONGLONG *pllTime)
{

	return (int)(*pllTime / 10000i64);

}


LONGLONG CBAPSAudioOutputChannel::MillisecondsToReferenceTime(int nMilliseconds)
{

	return nMilliseconds * 10000i64;

}


BOOL CBAPSAudioOutputChannel::SetDevice(CBAPSAudioOutputDevice* pDevice)
// Assumes Initialise has succeeded
{
	if (pDevice == 0)
	{
		return FALSE;
	}
	IBindCtx *pBindCtx;
	IMoniker* pDeviceMoniker;
	ULONG chEaten;
	HRESULT hr;

	// Ensure playback is stopped
	m_pMediaControl->Stop();

	// Unset the current device
	m_pOutputDevice = NULL;

	// Remove the current renderer filter, if it exists
	if (NULL != m_pRendererFilter)
	{

		hr = m_pGraphBuilder->RemoveFilter(m_pRendererFilter);

		if (FAILED(hr))
		{
			return FALSE;
		}

		m_pRendererFilter->Release();
		m_pRendererFilter = NULL;

	}

	// Create a bind context
	hr = CreateBindCtx(0, &pBindCtx);
	
	if (FAILED(hr))
	{
		return FALSE;
	}

	// Create a moniker from the device's GUID
	hr = MkParseDisplayName(pBindCtx, pDevice->GetGUID(), &chEaten, &pDeviceMoniker);

	if (FAILED(hr))
	{
		pBindCtx->Release();
		return FALSE;
	}

	// Create the renderer filter from the moniker
	hr = pDeviceMoniker->BindToObject(pBindCtx, NULL, IID_IBaseFilter, (void**)&m_pRendererFilter);
	pDeviceMoniker->Release();
	pBindCtx->Release();

	if (FAILED(hr))
	{
		return FALSE;
	}

	// Add the renderer filter to the graph
	hr = m_pGraphBuilder->AddFilter(m_pRendererFilter, L"Renderer");

	if (FAILED(hr))
	{
		m_pRendererFilter->Release();
		m_pRendererFilter = NULL;
		return FALSE;
	}

	m_pOutputDevice = pDevice;

	return TRUE;

}


CBAPSAudioOutputDevice* CBAPSAudioOutputChannel::GetDevice()
{

	// Just return the device pointer!
	return m_pOutputDevice;

}


BOOL CBAPSAudioOutputChannel::LoadFile(LPCWSTR szFileName)
// Assumes Initialise has succeeded
{

	HRESULT hr;
	IPin* pPin;

	// Ensure playback is stopped
	m_pMediaControl->Stop();

	// Remove the existing source filter if it exists
	if (NULL != m_pSourceFilter)
	{
		m_pGraphBuilder->RemoveFilter(m_pSourceFilter);
		m_pSourceFilter->Release();
		m_pSourceFilter = NULL;
	}

	// Add the new source filter
	hr = m_pGraphBuilder->AddSourceFilter(szFileName, L"Source", &m_pSourceFilter);

	if (FAILED(hr))
	{
		return FALSE;
	}

	// Find the output pin
	hr = m_pSourceFilter->FindPin(L"Output", &pPin);

	if (FAILED(hr))
	{
		return FALSE;
	}

	// Render the output pin
	hr = m_pGraphBuilder->Render(pPin);
	pPin->Release();

	if (FAILED(hr))
	{
		return FALSE;
	}

	// Seek to the start
	SetPosition(0);

	// Pause the graph ready for a quick start
	hr = m_pMediaControl->Pause();

	return TRUE;

}


BOOL CBAPSAudioOutputChannel::Play()
// Assumes Initialise has succeeded
{

	// Make sure we have a source filter
	if (NULL == m_pSourceFilter)
	{
		return FALSE;
	}

	// Run the graph
	m_pMediaControl->Run();

	return TRUE;

}


BOOL CBAPSAudioOutputChannel::Pause()
// Assumes Initialise has succeeded
{

	// Make sure we have a source filter
	if (NULL == m_pSourceFilter)
	{
		return FALSE;
	}

	// Pause the graph
	m_pMediaControl->Pause();

	return TRUE;

}


BOOL CBAPSAudioOutputChannel::Stop()
// Assumes Initialise has succeeded
{

	// Make sure we have a source filter
	if (NULL == m_pSourceFilter)
	{
		return FALSE;
	}

	// Stop the graph
	m_pMediaControl->Stop();

	// Seek to the beginning
	SetPosition(0);

	// Pause the graph ready for a quick start
	m_pMediaControl->Pause();

	return TRUE;

}


int CBAPSAudioOutputChannel::GetDuration()
// Assumes Initialise has succeeded
{

	HRESULT hr;
	LONGLONG llDuration = 0;

	hr = m_pMediaSeeking->GetDuration(&llDuration);

	if (FAILED(hr))
	{
		llDuration = 0;
	}

	return ReferenceTimeToMilliseconds(&llDuration);

}


int CBAPSAudioOutputChannel::GetPosition()
// Assumes Initialise has succeeded
{

	HRESULT hr;
	LONGLONG llStart = 0;
	LONGLONG llStop;

	hr = m_pMediaSeeking->GetPositions(&llStart, &llStop);

	if (FAILED(hr))
	{
		llStart = 0;
	}

	return ReferenceTimeToMilliseconds(&llStart);

}


void CBAPSAudioOutputChannel::SetPosition(int iPosition)
// Assumes Initialise has succeeded
{

	LONGLONG llCurrent;

	llCurrent = MillisecondsToReferenceTime(iPosition);

	m_pMediaSeeking->SetPositions(&llCurrent, AM_SEEKING_AbsolutePositioning, NULL, AM_SEEKING_NoPositioning);

}


float CBAPSAudioOutputChannel::GetVolume()
// Assumes Initialise has succeeded
{

	HRESULT hr;
	long lVolume;
	double dVolume;

	hr = m_pBasicAudio->get_Volume(&lVolume);

	if (FAILED(hr))
	{
		return 0.0f;
	}

	dVolume = 1.0 / pow(M_E, (double)lVolume / -1000.0);

	return (float)dVolume;

}


void CBAPSAudioOutputChannel::SetVolume(float fVolume)
// Assumes Initialise has succeeded
{

	double dVolume;

	if (0.0f == fVolume)
	{
		dVolume = -10000.0;
	}
	else
	{
		dVolume = -1000.0 * log(1.0 / fVolume);
	}

	if (dVolume < -10000.0)
	{
		dVolume = -10000.0;
	}

	m_pBasicAudio->put_Volume((long)dVolume);
	
}


float CBAPSAudioOutputChannel::GetPan()
// Assumes Initialise has succeeded
{

	HRESULT hr;
	long lPan;
	double dPan;

	hr = m_pBasicAudio->get_Balance(&lPan);

	if (FAILED(hr))
	{
		return 0.0f;
	}


	if (lPan > 0)
	{
		dPan = 1.0 - (1.0 / pow(M_E, (double)lPan / 1000.0));
	}
	else
	{
		dPan = (1.0 / pow(M_E, (double)lPan / -1000.0)) - 1.0;
	}

	return (float)dPan;
	
}


void CBAPSAudioOutputChannel::SetPan(float fPan)
// Assumes Initialise has succeeded
{

	double dPan;

	if (fPan < 0.0f)
	{
		if (-1.0 == fPan)
		{
			dPan = -10000.0;
		}
		else
		{
			dPan = -1000.0 * log(1.0 / 1.0 + fPan);
		}
	}
	else
	{
		if (1.0 == fPan)
		{
			dPan = 10000.0;
		}
		else
		{
			dPan = 1000.0 * log(1.0 / 1.0 - fPan);
		}
	}

	m_pBasicAudio->put_Volume((long)dPan);

}
