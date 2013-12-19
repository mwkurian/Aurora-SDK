////////////////////////////////////////////////////////////////////////////////

#ifndef __A2DCPDEVICE_H__
#define __A2DCPDEVICE_H__

//+-----------------------------------------------------------------------------
//
//  Class:
//      A2DCPDEVICE
//
//  Synopsis:
//      Custom device type to allow a Cross-Platform SDK Implementation
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// FORWARD DECLARATIONS
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// DEFINE
////////////////////////////////////////////////////////////////////////////////

class A2DCPDevice
{
public:
	A2DCPDevice());

	~A2DCPDevice();
private:
#ifndef WIN32
	// code for X11
	HDC  			aDevice;
#else
	//  code for Windows
	ID3D10Device	aDevice;
#endif

public:
	//mutators and accessors

#ifndef WIN32
	HDC				getDevice();
	void			setDevice(HDC xDevice);
#else
	ID3D10Device	getDevice();
	void			setDevice(ID3D10Device xDevice);

#endif

};

#endif