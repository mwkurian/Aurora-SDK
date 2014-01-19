////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __RUNNABLE_H__
#define __RUNNABLE_H__

//+-----------------------------------------------------------------------------
//
//  Class:  
//      RUNNABLE
//
//  Synopsis:
//      Texture container class.
//
//-----------------------------------------------------------------------------

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	class Runnable
	{
		friend class AbstractThread;
		friend class AbstractEventQueue;

	protected:

		virtual void run(int xThreadId) IMPLEMENT;

	};
}

#endif