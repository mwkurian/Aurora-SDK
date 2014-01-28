#////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __VERTEXTYPES_H__
#define __VERTEXTYPES_H__

//+-----------------------------------------------------------------------------
//
//  Class: 
//      VERTEXTYPES
//
//  Synopsis:
//      Texture quad.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "ExtLibs.h"

namespace A2D {

	struct A2DUINT4
	{
		unsigned int a1;
		unsigned int a2;
		unsigned int a3;
		unsigned int a4;

		A2DUINT4(){};

		A2DUINT4(unsigned int x, unsigned int y, unsigned int z, unsigned int w)
		{
			a1 = x;
			a2 = y;
			a3 = z;
			a4 = w;
		}
	};

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	struct QuadExpansionVertex
	{
		D3DXVECTOR4 aPosition;
		D3DXVECTOR4 aOptions;
		D3DXVECTOR4 aOptionsSet2;
		D3DXVECTOR4 aBorderWidths;
		D3DXVECTOR4 aBorderRadii;
		D3DXVECTOR4 aColorTex;
		A2DUINT4 aBorderColors;

		static D3D10_INPUT_ELEMENT_DESC aPolygonLayout[];
	};

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	struct ColorVertex
	{
		D3DXVECTOR3 position;
		D3DXVECTOR4 color;

		static D3D10_INPUT_ELEMENT_DESC aPolygonLayout[];
	};
	
	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	struct ColoredTextureVertex
	{
		// Variables
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
		D3DXVECTOR4 color;

		static D3D10_INPUT_ELEMENT_DESC aPolygonLayout[];
	};

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	struct TextureVertex
	{
		// Variables
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;

		static D3D10_INPUT_ELEMENT_DESC aPolygonLayout[];

		static inline void  TextureVertex::memcpySSE2(TextureVertex * xDest, const TextureVertex * xSrc);
	};
}

#endif

