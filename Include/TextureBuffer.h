////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __TEXTUREBUFFER_H__
#define __TEXTUREBUFFER_H__

//+-----------------------------------------------------------------------------
//
//  Struct:
//      TEXTUREBUFFER
//
//  Synopsis:
//      Differentiates which of the two possible arcs could match the given arc
//      parameters.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "Common.h"

#include "TextureVertex.h"
#include "BackBuffer.h"
#include "AbstractTexture.h"
#include "ImageProperties.h"
#include "Rect.h"

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// FORWARD DECLARATIONS
	////////////////////////////////////////////////////////////////////////////////

	class Texture;
	class AbstractTexture;

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	class TextureBuffer : public AbstractTexture
	{

	public:

		// Constructor
		TextureBuffer(ID3D10Device ** xDXDevice, ID3D10DepthStencilView ** xBackBufferaDXDepthStencilView, Dims * xSize);

		// Deconstructor
		~TextureBuffer();

		// Variables
		ID3D10Device				**	aDXDevice;
		ID3D10DepthStencilView		**	aBackBufferaDXDepthStencilView;

		ID3D10Texture2D				*	aDXRenderTargetTexture;
		ID3D10RenderTargetView		*	aDXRenderTargetView;
		ID3D10DepthStencilState		*   aDXDepthStencilState;
		ID3D10ShaderResourceView*		aResource;

		// Accessors
		virtual	bool					hasAlpha();

		// Mutators
		void							SetActive();

		// Additional
		void							Clear();
		virtual void			   *	getPlatformCompatibleResource();

	public:

		// Implementation
		// { ABSTRACT }
		virtual HRESULT                 Initialize();
		virtual void	                Deinitialize();
		virtual LPCWSTR                 GetClass();
		virtual LPCWSTR                 ToString();
		virtual bool                    operator==(Abstract * xAbstract);

	};
}

#endif
