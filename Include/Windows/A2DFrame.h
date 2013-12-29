////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __FRAME_H__
#define __FRAME_H__

//+-----------------------------------------------------------------------------
//
//  Class:
//      FRAME
//
//  Synopsis:
//      Differentiates which of the two possible arcs could match the given arc
//      parameters.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "../AbstractFrame.h"
#include "Thread.h"

////////////////////////////////////////////////////////////////////////////////
// DECLARATION
////////////////////////////////////////////////////////////////////////////////

class Frame : public AbstractFrame
{

////////////////////////////////////////////////////////////////////////////////
// PLATFORM COMPATIBLE IMPLEMENTATION
////////////////////////////////////////////////////////////////////////////////

public:

	Frame(HINSTANCE xHInstance);

	~Frame();

private:

	HINSTANCE aHInstance;

////////////////////////////////////////////////////////////////////////////////
// ABSTRACTFRAME
////////////////////////////////////////////////////////////////////////////////

protected:

	virtual AbstractWindow *		createPlatformCompatibleWindow();
	virtual AbstractEventQueue*	createPlatformCompatibleEventQueue();

};

#endif
