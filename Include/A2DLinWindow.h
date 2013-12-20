////////////////////////////////////////////////////////////////////////////////

#ifndef __A2DLINWINDOW_H__
#define __A2DLINWINDOW_H__

//+-----------------------------------------------------------------------------
//
//  Class:
//      A2DLINWINDOW
//
//  Synopsis:
//      Custom LINUX/UNIX implmentatino of A2DAbstractWindow
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////
#include "A2DFrame.h"
#include "A2DAbstract.h"
#include "A2DRect.h"
#include "A2DAbstractWindow.h"
#include "OpenGlClass.h"
#include "InputClass.h"
#include "GraphicsClass.h"
#include "A2DCPString.h"
#include "A2DCPWindowHandle.h"
#include "A2DCPInstanceHandle.h"
#include "A2DCPResultHandle.h"

////////////////////////////////////////////////////////////////////////////////
// FORWARD DECLARATIONS
////////////////////////////////////////////////////////////////////////////////

class A2DFrame;
class A2DAbstract;
class A2DAbstractWindow;
class A2DCPString;
class A2DCPWindowHandle;
class A2DCPResultHandle;
class A2DCPInstanceHandle;

////////////////////////////////////////////////////////////////////////////////
// DEFINE
////////////////////////////////////////////////////////////////////////////////

class A2DLinWindow: public A2DAbstractWindow
{
public:
	//Constructor
	A2DLinWindow(HINSTANCE * xHInstance); //currently using MS Windows API handles

	//Deconstructor
	~A2DLinWindow();

private:

	//variables		for now I'll leave it as MS WINDOWS instead of X11/LINUX
	int                             aDefaultCloseOperation;

    bool                            aVisible;
    bool                            aShadowed;
    bool                            aUndecorated;

    float                           aPadding;
	float                           aShadowPadding;
	float							aBorderWidth;

    A2DCPWindowHandle               aParentHandle;
	A2DCPWindowHandle               aChildHandle;

    A2DCPString                     aName;

    A2DCPInstanceHandle       *     aHInstance;

    Color                           aBorderColor;

    A2DFrame                  *     aFrame;

    A2DWindow                 *     aRelativeWindow;

    A2DRect                         aRect;
public:

	// Accessors and mutators
    // These don't need mutators because we are giving direct access to the structs
    A2DRect                   *     getBounds();
        
    // Accessing internal variables. Do not provide mutators for these.
    A2DCPWindowHandle         *     getChildHandle();
    A2DCPWindowHandle         *     getParentHandle();

    A2DCPString               *     getName(); // Fix this, should we use pointer or not?
    void                            setName(LPCWSTR * xName); // Fix this, should we use pointer or not?
    
    A2DFrame                  *     getFrame(); // GET
    void                            setFrame(A2DFrame * xFrame); // SET

    bool                            isUndecorated(); // Get
    void                            setUndecorated(bool xUndecoratedFlag); // SET

    int                             getDefaultCloseOperation();
    void                            setDefaultCloseOperation(int xCloseOperation);

    A2DWindow                 *     getLocationRelativeTo();
    void                            setLocationRelativeTo(A2DWindow * xWindow);
    
    bool                            isVisible();
    void                            setVisible(bool xVisibile);

    bool                            isShadowed();
    void                            setShadowed(bool xShadowFlag);

    Color                           getBorderColor();
    void                            setBorderColor(Color xBorderColor);
	
	float		                    getBorderWidth();
	void                            setBorderWidth(float xWidth);

    float                           getPadding();
    void                            setPadding(float xPadding);
    
    float                           getShadowPadding();
    void                            setShadowPadding(float xShadowPadding);
    
    // Additional
    void                            Update();
    void                            Render();
    void                            RenderComponent();
    void                            RenderComponentClear();
    void                            RenderComponentBorder();
    A2DCPResultHandle               CreateResources();
    A2DCPResultHandle               CreateComponentResources();
    
    // Implementation
    // { A2DABSTRACT }
    virtual HRESULT                 Initialize();
    virtual void                    Deinitialize();
    virtual A2DCPString             GetClass();
    virtual A2DCPString             ToString();
    virtual bool                    operator==(A2DAbstract * xAbstract);

    /*********************************************************************/
    /*                      CROSS-PLATFORM END                           */
    /*********************************************************************/

    /*********************************************************************/
    /*                      WINDOWS-SPECIFIC START                       */
    /*********************************************************************/

    // Variables - WINDOW ONLY - INTERNAL USE ONLY

	REAL                            aGdiRealZero = 0;

    REAL                            aGdiRealRealX = 0;
    REAL                            aGdiRealRealY = 0;
    REAL                            aGdiRealRealWidth = 0;
    REAL                            aGdiRealRealHeight = 0;

    REAL                            aGdiRealRelativeX = 0;
    REAL                            aGdiRealRelativeY = 0;
    REAL                            aGdiRealRelativeWidth = 0;
    REAL                            aGdiRealRelativeHeight = 0;

    int                             aStyle;
    SIZE                            aHDCSize;
    Graphics                  *     aGraphics;

    // Builders
    // { NONE }

    // Factory
    // { NONE }
    
    // Accessors
    // { NONE }

    // Mutators
    // { NONE }

    // Factory
    // { NONE }

    // Additional
    void                                                        preCache();

    // Pure Virtual
    // { NONE }

    // Virtual
    // { NONE }     

private:
    
    // Functions
    void                            RunMessageLoop();
    static LRESULT CALLBACK         WndProc(HWND xHwnd, UINT xMessage, WPARAM xWParam, LPARAM xLParam);
    static inline A2DWindow*        GetAppState(HWND xHwnd);

    HRESULT                         RegisterClass();
	HRESULT                         CreateHandle(HWND& xHandle);

    /*********************************************************************/
    /*                      WINDOWS-SPECIFIC END                         */
    /*********************************************************************/
};
	
};

#endif