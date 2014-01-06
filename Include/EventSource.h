////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __EVENTSOURCE_H__
#define __EVENTSOURCE_H__

//+-----------------------------------------------------------------------------
//
//  Abstract Class:
//      EVENTSOURCE
//
//  Synopsis:
//      Class that will throw and fire events.
//
//
////------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "ExtLibs.h"
#include "Abstract.h"
#include "OrderedList.h"

#include "AbstractListener.h"
#include "MouseListener.h"
#include "FocusListener.h"
#include "ActionListener.h"
#include "MouseMotionListener.h"

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// FORWARD DECLARATIONS
	////////////////////////////////////////////////////////////////////////////////

	class Abstract;
	class AbstractListener;
	class MouseListener;
	class MouseEvent;
	class FocusListener;
	class FocusEvent;
	class ActionListener;
	class ActionEvent;
	class MouseMotionListener;

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	class EventSource : public Abstract
	{
	public:

		~EventSource();
		
		HRESULT					processMouseEvent(MouseEvent * xEvent);
		HRESULT					processFocusEvent(FocusEvent * xEvent);
		HRESULT					processActionEvent(ActionEvent * xEvent);

		HRESULT					addMouseListener(MouseListener * xListener);
		HRESULT					addMouseMotionListener(MouseMotionListener * xListener);
		HRESULT					addActionListener(ActionListener * xListener);
		HRESULT					addFocusListener(FocusListener * xListener);

	protected:

		EventSource();

	protected:
		
		AbstractListener 	 *	findListener(const int xListenerID);
		HRESULT					fireListener(AbstractEvent * xEvent, int xListenerID);

		HRESULT					addListener(AbstractListener * xListener); // slow 
		HRESULT					removeListener(AbstractListener * xListener); // slow
	private:

		OrderedList<AbstractListener *> aListenerList;

	public:

		//////////////////////////////////////////////////////////
		// ABSTRACT IMPLEMENTATION
		//////////////////////////////////////////////////////////

		virtual HRESULT                 initialize();
		virtual LPCWSTR                 getClass();
		virtual LPCWSTR                 toString();
	};
	
}



#endif