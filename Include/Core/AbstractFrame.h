////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __ABSTRACTFRAME_H__
#define __ABSTRACTFRAME_H__

//+-----------------------------------------------------------------------------
//
//  Class:
//      ABSTRACTFRAME
//
//  Synopsis:
//      Differentiates which of the two possible arcs could match the given arc
//      parameters.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "Panel.h"
#include "CameraProperties.h"
#include "AbstractBackBuffer.h"
#include "AbstractWindow.h"
#include "GXSettings.h"
#include "RepaintManager.h"
#include "Rect.h"

namespace A2D {
	
	////////////////////////////////////////////////////////////////////////////////
	// FORWARD DECLARATIONS
	////////////////////////////////////////////////////////////////////////////////

	class	Abstract;
	class	Container;
	struct	CameraProperties;
	class	BackBuffer;
	class	RootPane;
	class	Graphics;
	
	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	class AbstractFrame : public Runnable
	{

	public:

		AbstractFrame();
		~AbstractFrame();

	private:

		AbstractBackBuffer	   *		aBackBuffer;
		AbstractWindow	  	   *		aWindow;
		AbstractEventQueue	   *		aEventQueue = NULL;
		void				   * 		aGraphics;

		Dims				   *		aWindowDims;
		RepaintManager		   *		aRepaintManager;
		Panel                			aRootPane;
		GXSettings			  			aGXSettings;

		int								aId;
		static int						aClassInstances;

		bool							aValidatedContents;

	public:

		Panel&               			getRootPane();
		HRESULT                         createResources();
		void                            update();
		void							dispose();
		void							invalidate();
		// void							revalidate(); --- Unsafe for AbstractFrame!!!

	protected:
		void							validated();
		void							validate();

	public:
		int								id();
		void							setBackground(byte xRed, byte xGreen, byte xBlue);
		void							setBorder(byte xAlpha, byte xRed, byte xGreen, byte xBlue, float xWidth);
		void							setShadow(byte xAlpha, byte xRed, byte xGreen, byte xBlue, float xRadius);
		void							setVisible(bool xVisibility);
		void							setName(LPCWSTR  xName);
		void							setBounds(Rect * xRect);
		void							setBounds(float xLeft, float xTop, float xWidth, float xHeight);
		void							setSize(float xWidth, float xHeight);
		void							setSize(Dims * xDims);
		void							setUndecorated(bool xDecorated);
		void							setLocationRelativeTo(AbstractFrame * xFrame);
		void							setVsync(bool xVsync);
		void							setDefaultCloseOperation(int xOperation);
		AbstractWindow			*		getWindow();
		void							run(int xThreadId);
		RepaintManager*					getRepaintManager();


	protected:

		virtual HRESULT					createPlatformCompatibleEventQueue(AbstractEventQueue ** xEventQueue) = 0;
		virtual HRESULT					createPlatformCompatibleWindow(AbstractWindow ** xWindow) = 0;
		virtual HRESULT					createPlatformCompatibleBackBuffer(AbstractBackBuffer ** xBackBuffer, AbstractWindow * xWindow, GXSettings * xSettings) = 0;
		virtual HRESULT					createAndInitPlatformCompatibleGraphics(void ** xGraphics, AbstractBackBuffer * xBackbuffer) = 0;
		
	public:

		virtual HRESULT                 initialize();

	};
}

#endif