////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __ABSTRACTLISTENER_H__
#define __ABSTRACTLISTENER_H__

//+-----------------------------------------------------------------------------
//
//  Class: 
//      ABSTRACTLISTENER
//
//  Synopsis:
//      Abstract listener class for events.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "ExtLibs.h"
#include "Abstract.h"

using namespace std;

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// FORWARD DECLARATIONS
	////////////////////////////////////////////////////////////////////////////////

	class Abstract;
	class AbstractEvent;

	////////////////////////////////////////////////////////////////////////////////
	// DEFINE
	////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	class AbstractListener : public Abstract
	{
	public:

		virtual ~AbstractListener();
		virtual void notify(AbstractEvent * xEvent) = 0;

	protected:
		// Constructor is protected because this class is abstract.
		AbstractListener(int xID);

	public:

		bool operator==(const AbstractListener& xListener);

	public:

		const int					aID;

	//////////////////////////////////////////////////////////
	// ABSTRACT IMPLEMENTATION
	//////////////////////////////////////////////////////////

	virtual HRESULT                 initialize();
	virtual LPCWSTR                 getClass();
	virtual LPCWSTR                 toString();

	};

}


#endif