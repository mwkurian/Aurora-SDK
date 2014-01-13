#ifndef __COMMON_H__
#define __COMMON_H__

//+-----------------------------------------------------------------------------
//
//  Class:
//      COMMON
//
//  Synopsis:
//      Differentiates which of the two possible arcs could match the given arc
//      parameters.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// DEFINE
////////////////////////////////////////////////////////////////////////////////


#define _PIPELINE_PREPROCESS_START                         0x2510
#define _PIPELINE_PREPROCESS_CREATE                        0x2511
#define _PIPELINE_PREPROCESS_FINISH                        0x2512

#define _GRAPHICS_ACTIVE_BUFFER_PRIMARY   		          0x3511
#define _GRAPHICS_ACTIVE_BUFFER_SECONDARY		          0x3512
#define _GRAPHICS_ACTIVE_BUFFER_TERTIARY					  0x3513

#define _WINDOW_BOX_SHADOW_SAFELYTY_RATIO					  2
#define _WINDOW_RESIZE_EDGE_DISTANCE                       5
#define _WINDOW_RESIZE_DEFAULT_DISTANCE					  3
#define _WINDOW_MOVE_BAR_DISTANCE							25
#define _WINDOW_MOVE_DEFAULT_DISTANCE						10

#define _GRAPHICSTOOLKIT_BASIC_TEXTURE_SHADER			  0x4000
#define _GRAPHICSTOOLKIT_VERTICAL_BLUR_TEXTURE_SHADER      0x4001
#define _GRAPHICSTOOLKIT_HORIZONTAL_BLUR_TEXTURE_SHADER    0x4002

#define	_OPT_BACKGROUND_REPEAT_REPEAT_X					  0x3001
#define	_OPT_BACKGROUND_REPEAT_REPEAT_Y					  0x3010
#define	_OPT_BACKGROUND_REPEAT_NO_REPEAT					  0x3003

#define	_OPT_BACKGROUND_POSITION_CENTER					  0x3004
#define	_OPT_BACKGROUND_POSITION_TOP						  0x3005
#define	_OPT_BACKGROUND_POSITION_RIGHT					  0x3006
#define	_OPT_BACKGROUND_POSITION_BOTTOM					  0x3007
#define	_OPT_BACKGROUND_POSITION_LEFT					  0x3008

#define	_OPT_BACKGROUND_SIZE_COVER							  0x3009
#define	_OPT_BACKGROUND_SIZE_STRETCH						  0x300A

#define FLT_255												  255.0f
#define FLT_ZERO                                              0.0f
#define FLT_ONE                                               1.0f

#ifndef abs
#endif

#ifndef max
#define max(a,b)										(((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)										(((a) < (b)) ? (a) : (b))
#endif

// Debugging
#include "_A2DDebug.h"

//#define A2D_DE__										"Comment out this line to remove debugging."

#define G_SAFELY(hr)									if(hr != 0)	{ SYSOUT_STR("Failure detected");	return;		   }
#define SAFELY(hr)										if(hr != 0)	{ SYSOUT_STR("Failure detected");	return E_FAIL; }
#define NULLCHECK(hr)									if(!hr)		{ SYSOUT_STR("Failure detected");	return E_FAIL; }
#define	DESTROY(x)										if(x)			{ delete x; x = 0; }
#define D3DDESTROY(x)									if(x)			{ x->Release(); x = 0; }
#define THREAD_DESTROY(x)								if(x)			{ x->stop(); delete x; x = 0; }
#define FLOAT(x)										static_cast<float>(x)
#define INT(x)											static_cast<int>(x)
#define UINT(x)											static_cast<unsigned int>(x)
#define TO_PIXELS(unit, value, range)					((unit == A2D::Styles::PERCENTAGE) ? FLOAT(range * (value / 100)) : (value))

inline float pixelsToRelativePoint(const float xPixelDimension, const float xPixels)
{
	return xPixels / (xPixelDimension / 2) - 1;
}

inline float pixelsToRelativeDistance(const float xPixelDimension, const float xPixels)
{
	return xPixels / xPixelDimension * 2;
}

#ifndef __STATUS_DEFINED__
#define __STATUS_DEFINED__
typedef unsigned int STATUS;
#define _STATUS_TYPEDEF_(_sc)									((STATUS)_sc)
#define STATUS_OK												_STATUS_TYPEDEF_(0)
#define STATUS_FAIL												_STATUS_TYPEDEF_(1)
#define STATUS_RETRY											_STATUS_TYPEDEF_(2)
#define STATUS_FORCE_QUIT										_STATUS_TYPEDEF_(3)
#endif


// TEMPORARILY
//#define STATUS													HRESULT
//#define STATUS_OK												0
//#define STATUS_FAIL												1
//#define STATUS_RETRY											2
//#define STATUS_FORCE_QUIT										3

#endif
