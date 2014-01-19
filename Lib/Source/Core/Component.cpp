
#include "../../../include/Core/ExtLibs.h"
#include "../../../include/Core/Component.h"
#include "../../../include/Core/AbstractFrame.h"

using namespace A2D;

Component::Component(){}

Component::~Component(){}

void Component::paintComponentBorder(){}

Component& Component::getParent()
{
	return *aParent;
}

float Component::getDepth()
{
	return aDepth;
}

AbstractFrame& Component::getFrame()
{
	return *aFrame;
}

void Component::setGraphics(Graphics& xGraphics)
{
	aGraphics = &xGraphics;
}

Graphics& Component::getGraphics()
{
	return *aGraphics;
}

void Component::setDepth( float xDepth)
{
	aDepth = xDepth;
}

void Component::setFrame(AbstractFrame& xFrame)
{
	aFrame = &xFrame;
}

void Component::setParent(Component& xParent)
{
	aParent = &xParent;
}

Rect Component::getBounds()
{
	return aOptRegion;
}

Rect * Component::getBoundsAtPtr()
{
	return &aOptRegion;
}

Rect * Component::getVisibleRegion()
{
	return &aVisibleRegion;
}

void Component::add(Component& xContainer)
{
	aChildren.push_back(&xContainer, NULL);
}

void Component::remove(Component& xContainer)
{
	aChildren.remove(&xContainer);
}

void Component::setBounds(Rect& xRect)
{
	aOptRegion.aWidth = xRect.aWidth;
	aOptRegion.aHeight = xRect.aHeight;
	aOptRegion.aX = xRect.aX;
	aOptRegion.aY = xRect.aY;

	aOptBackgroundRegion.aWidth = xRect.aWidth;
	aOptBackgroundRegion.aHeight = xRect.aHeight;

	invalidate();
}

void Component::invalidate()
{
	aValidatedContents = false;
}

void Component::revalidate()
{
	validate();
}

void Component::validated()
{
	aValidatedContents = true;
}

void Component::validate()
{
	Component * parentComp = aParent;
	Rect& compRect = aOptRegion;
	bool hasParent = parentComp != NULL;

	if (!aVisible)
	{
		aValidatedContents = true;
		return;
	}

	if (!hasParent)
	{
		aCalculatedRegion.aX = _max(0.0f, compRect.aX);
		aCalculatedRegion.aY = _max(0.0f, compRect.aY);
		aCalculatedRegion.aWidth = _max(0.0f, compRect.aWidth);
		aCalculatedRegion.aHeight = _max(0.0f, compRect.aHeight);

		aCalculatedNegativeDeltaX = 0.0f;
		aCalculatedNegativeDeltaY = 0.0f;
	}
	else
	{
		float sX, sY;
		Rect& parentRect = parentComp->aOptRegion;
		Rect& parentCalculatedRegion = parentComp->aCalculatedRegion;
		Rect& parentVisibleRegion = parentComp->aVisibleRegion;
				
		// Running x and y
		aCalculatedRegion.aX = parentCalculatedRegion.aX + compRect.aX;
		aCalculatedRegion.aY = parentCalculatedRegion.aY + compRect.aY;
		
		// Reduce the size based on parent x, y
		// Account for negative x, y of this
		// Accumulate negatives
		aCalculatedRegion.aWidth = compRect.aWidth + (aCalculatedNegativeDeltaX = parentComp->aCalculatedNegativeDeltaX + _min(0.0f, compRect.aX));
		aCalculatedRegion.aHeight = compRect.aHeight + (aCalculatedNegativeDeltaY = parentComp->aCalculatedNegativeDeltaY + _min(0.0f, compRect.aY));
		
		// Account for larger than parent
		aCalculatedRegion.aWidth = _min(aCalculatedRegion.aWidth, parentCalculatedRegion.aWidth);
		aCalculatedRegion.aHeight = _min(aCalculatedRegion.aHeight, parentCalculatedRegion.aHeight);

		// Account for positive shift
		aCalculatedRegion.aWidth -= FLOAT((sX = (compRect.aX + aCalculatedRegion.aWidth)) > parentCalculatedRegion.aWidth ? (sX - parentCalculatedRegion.aWidth) : 0.0f);
		aCalculatedRegion.aHeight -= FLOAT((sY = (compRect.aY + aCalculatedRegion.aHeight)) > parentCalculatedRegion.aHeight ? (sY - parentCalculatedRegion.aHeight) : 0.0f);
		
		// Account for negative height
		aCalculatedRegion.aWidth = _max(0.0f, aCalculatedRegion.aWidth);
		aCalculatedRegion.aHeight = _max(0.0f, aCalculatedRegion.aHeight);

		// Set the visible x and y based on previous
		aVisibleRegion.aX = parentVisibleRegion.aX + _max(0.0f, _min(aCalculatedRegion.aX, compRect.aX));
		aVisibleRegion.aY = parentVisibleRegion.aY + _max(0.0f, _min(aCalculatedRegion.aY, compRect.aY));

		// Set the region based on if it is even visible
		aVisibleRegion.aWidth = FLOAT((aCalculatedRegion.aX + compRect.aWidth) >= 0.0f ? aCalculatedRegion.aWidth : 0.0f);
		aVisibleRegion.aHeight = FLOAT((aCalculatedRegion.aY + compRect.aHeight) >= 0.0f ? aCalculatedRegion.aHeight : 0.0f);		
	}

	CascadingLayout::doLayout(*this);

	aValidatedContents = true;
}

void Component::forceBounds(bool xForce)
{
	aForced = xForce;
}

void Component::setSize(Styles::Units xWidthUnits, float xWidth, Styles::Units xHeightUnits, float xHeight)
{
	aSizeWidthUnits = xWidthUnits;
	aSizeHeightUnits = xHeightUnits;

	aSizeWidth = xWidth;
	aSizeHeight = xHeight;
}

void Component::setDisplay(Styles::Display xDisplay)
{
	aDisplay = xDisplay;
}

void Component::setMargins(Styles::Units xLeftUnits, float xLeft, Styles::Units xTopUnits, float xTop, Styles::Units xRightUnits, float xRight, Styles::Units xBottomUnits, float xBottom)
{
	aMarginLeftUnits = xLeftUnits;
	aMarginTopUnits = xTopUnits;
	aMarginBottomUnits = xRightUnits;
	aMarginRightUnits = xBottomUnits;

	aMarginLeft = xLeft;
	aMarginTop = xTop;
	aMarginBottom = xBottom;
	aMarginRight = xRight;
}

void Component::setPositioning(Styles::Units xLeftUnits, float xLeft, Styles::Units xTopUnits, float xTop, Styles::Units xRightUnits, float xRight, Styles::Units xBottomUnits, float xBottom)
{
	aPositionLeftUnits = xLeftUnits;
	aPositionTopUnits = xTopUnits;
	aPositionBottomUnits = xRightUnits;
	aPositionRightUnits = xBottomUnits;

	aPositionLeft = xLeft;
	aPositionTop = xTop;
	aPositionBottom = xBottom;
	aPositionRight = xRight;
}

void Component::setPosition(Styles::Position xPosition)
{
	aPosition = xPosition;
}

STATUS Component::initialize()
{
	return STATUS_OK;
}


void Component::paintComponent()
{
	if (!aVisible)
	{
		return;
	}

	Graphics& graphics = *aGraphics;

	if (aOptBackgroundSrc != NULL)
	{
		graphics.drawComponent(&aPipeline, aOptBackgroundRegion, aOptBackgroundSrc, m_borderSet, aOptBackgroundPaint, m_backgroundStyle);
	}
	else
	{
		graphics.fillRect(&aPipeline, aOptBackgroundRegion, aOptBackgroundPaint);
	}
}

void Component::update()
{
	Graphics& graphics = *aGraphics;

	if (!aValidatedContents)
	{
		validate();
	}

	graphics.setClip(&aVisibleRegion, aDepth);

	// Render the current component
	paintComponent();

	// Force region
	graphics.setClip(&aVisibleRegion, aDepth);

	// Render the currect component border
	paintComponentBorder();
}

STATUS Component::requestFocus()
{
	// Also it's broken, as aFrame is not initialized.
	if (isFocusable && !isFocused)
	{
		FocusEvent& focusRequest = *new FocusEvent(this, FocusEvent::FOCUS_GAINED);
		Toolkit::getSystemEventQueue(aFrame->id())->processFocusEvent(&focusRequest);
	}
	return STATUS_OK;
}

void Component::setFocusable(bool xFocusable)
{
	isFocusable = xFocusable;
}

Rect * Component::getEventRegion()
{
	return &aVisibleRegion;
}

STATUS Component::addMouseListener(MouseListener * xListener)
{
	if (aComponentManager != NULL)
	{
		// Add depth manually
		AbstractEventQueue * eQ = Toolkit::getSystemEventQueue(aComponentManager->getWindow()->getFrame()->id());

		STATUS hr = ComponentEventSource::addMouseListener(xListener);
		if (xListener != NULL)
		{
			eQ->addEventDepthTracker(this, abs(aDepth));
		}
		else
		{
			eQ->removeEventDepthTracker(this, abs(aDepth + 1));
		}
		return hr;
	}
	return ComponentEventSource::addMouseListener(xListener);
}

STATUS Component::addMouseMotionListener(MouseMotionListener * xListener)
{
	if (aComponentManager != NULL)
	{
		// Add depth manually
		AbstractEventQueue * eQ = Toolkit::getSystemEventQueue(aComponentManager->getWindow()->getFrame()->id());

		STATUS hr = ComponentEventSource::addMouseMotionListener(xListener);
		if (xListener != NULL)
		{
			Toolkit::getSystemEventQueue(aComponentManager->getWindow()->getFrame()->id())->addEventDepthTracker(this, abs(aDepth));
		}
		else
		{
			eQ->removeEventDepthTracker(this, abs(aDepth + 1));
		}
		return hr;
	}
	return ComponentEventSource::addMouseMotionListener(xListener);
}

STATUS Component::addFocusListener(FocusListener * xListener)
{
	if (aComponentManager != NULL)
	{
		// Add depth manually
		STATUS hr = ComponentEventSource::addFocusListener(xListener);
		AbstractEventQueue * eQ = Toolkit::getSystemEventQueue(aComponentManager->getWindow()->getFrame()->id());

		if (xListener != NULL)
		{
			Toolkit::getSystemEventQueue(aComponentManager->getWindow()->getFrame()->id())->addEventDepthTracker(this, abs(aDepth));
		}
		else
		{
			eQ->removeEventDepthTracker(this, abs(aDepth + 1));
		}
		return hr;
	}
	return ComponentEventSource::addFocusListener(xListener);
}

STATUS Component::addActionListener(ActionListener * xListener)
{
	if (aComponentManager != NULL)
	{
		// Add depth manually
		AbstractEventQueue * eQ = Toolkit::getSystemEventQueue(aComponentManager->getWindow()->getFrame()->id());

		STATUS hr = ComponentEventSource::addActionListener(xListener);
		if (xListener != NULL)
		{
			Toolkit::getSystemEventQueue(aComponentManager->getWindow()->getFrame()->id())->addEventDepthTracker(this, abs(aDepth));
		}
		else
		{
			eQ->removeEventDepthTracker(this, abs(aDepth + 1));
		}
		return hr;
	}
	return ComponentEventSource::addActionListener(xListener);
}