////////////////////////////////////////////////////////////////////////////////
// GUARDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __QUADFACTORY_H__
#define __QUADFACTORY_H__

//+-----------------------------------------------------------------------------
//
//  Class: 
//      QUADFACTORY
//
//  Synopsis:
//      Quad class to be rendered.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "ExtLibs.h"
#include "DXShapeUtils.h"
#include "Texture.h"
#include "Rect.h"
#include "QuadData.h"
#include "ColoredTextureVertex.h"
#include "ColorVertex.h"

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// FORWARD DECLARATIONS
	////////////////////////////////////////////////////////////////////////////////

	class Abstract;
	class DXShapeUtils;
	class Texture;

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	class QuadFactory
	{
	public:

		QuadFactory(ID3D10Device ** xDXDevice, Dims * xWindowDims);
		~QuadFactory();

		ID3D10Buffer	*	aIndexBuffer;
		ID3D10Buffer	*	aVertexBuffer;
		
		float				aDepth = 0.0f;

		///////////////////////////////////////////////////////////

		Rect				aConstraints;
		Dims			*	aWindowDims;
		ID3D10Device	**	aDXDevice;

		///////////////////////////////////////////////////////////
	
		static void						memcpySSE2QuadVertex(TextureVertex * xDest, const TextureVertex * xSrc);
		static void						memcpySSE2QuadVertex(ColoredTextureVertex * xDest, const ColoredTextureVertex * xSrc);
		static void						memcpySSE2QuadVertex(ColorVertex * xDest, const ColorVertex * xSrc);
		HRESULT							updateVertexBuffer(QuadData<ColoredTextureVertex> * xQuadData, Rect * xRect, Rect * xTextureClip, Dims * xTextureDims, bool xRepeat);
		HRESULT							updateVertexBuffer(QuadData<TextureVertex> * xQuadData, Rect * xRect, Rect * xTextureClip, Dims * xTextureDims, bool xRepeat);
		HRESULT							updateVertexBuffer(QuadData<ColorVertex> * xQuadData, Rect * xRect, Rect * xTextureClip, Dims * xTextureDims, bool xRepeat);

		void							setDepth(float xZ);
		void							renderQuad(ID3D10Buffer * xVertexBuffer, unsigned int xStride);
		bool							setConstraints(Rect * xContraints, float xZ);

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