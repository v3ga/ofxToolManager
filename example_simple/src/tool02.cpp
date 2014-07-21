//
//  tool02.cpp
//  example_simple
//
//  Created by Julien on 21/07/2014.
//
//
#include "tool02.h"

//--------------------------------------------------------------
tool02 :: tool02(toolManager* parent) : tool("Tool02", parent)
{
}

//--------------------------------------------------------------
void tool02::createControlsCustom()
{
	if (mp_canvas)
	{
		mp_canvas->addWidgetDown(new ofxUILabel("Tool 02", OFX_UI_FONT_MEDIUM));
    	mp_canvas->addWidgetDown(new ofxUISpacer(300, 1));


		mp_canvas->setVisible(false);
		mp_canvas->autoSizeToFitWidgets();

	}
}

//--------------------------------------------------------------
void tool02::createControlsCustomFinalize()
{
	if (mp_canvas)
	{
		ofxUIRectangle* pCanvasRect = mp_canvas->getRect();
	
		mp_canvas2 = new ofxUICanvas(0,0,400,400);
		mp_canvas2->setPosition(pCanvasRect->getX()+pCanvasRect->getWidth()+10, pCanvasRect->getY());
		mp_canvas2->setFont(mp_toolManager->m_fontName);



		mp_canvas2->addWidgetDown(new ofxUILabel("Extra Column", OFX_UI_FONT_MEDIUM));
    	mp_canvas2->addWidgetDown(new ofxUISpacer(300, 1));
		mp_canvas2->addWidgetDown(new ofxUISlider(_id("Test"), 100.0, 300.0, 200.0, 300, 20));

		mp_canvas2->setVisible(false);
		mp_canvas2->autoSizeToFitWidgets();
	}
}

//--------------------------------------------------------------
void tool02::handleEvents(ofxUIEventArgs& e)
{
}

//--------------------------------------------------------------
void tool02::show(bool is)
{
	tool::show(is);
 	if (mp_canvas2)
		mp_canvas2->setVisible(is);
}

//--------------------------------------------------------------
bool tool02::isHit(int x, int y)
{
	if (tool::isHit(x,y) || (mp_canvas2 && mp_canvas2->isHit(x,y)))
		return true;
	return false;
}
