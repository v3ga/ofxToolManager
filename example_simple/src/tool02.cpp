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
	mp_canvasExtra = 0;
}

//--------------------------------------------------------------
tool02::~tool02()
{
	delete mp_canvasExtra;
}

//--------------------------------------------------------------
void tool02::saveData()
{
	tool::saveData();
	if (mp_canvasExtra)
		mp_canvasExtra->saveSettings(getDataPath("Tool02_extra.xml"));
}

//--------------------------------------------------------------
void tool02::loadData()
{
	tool::loadData();
	if (mp_canvasExtra)
		mp_canvasExtra->loadSettings(getDataPath("Tool02_extra.xml"));
}


//--------------------------------------------------------------
void tool02::createControlsCustom()
{
	if (mp_canvas)
	{
		mp_canvas->addWidgetDown(new ofxUILabel("Tool 02", OFX_UI_FONT_MEDIUM));
    	mp_canvas->addWidgetDown(new ofxUISpacer(300, 1));


		mp_canvas->addWidgetDown(new ofxUISlider("Slider01", 100.0, 300.0, 200.0, 300, 20));
		mp_canvas->addWidgetDown(new ofxUISlider("Slider02", 100.0, 300.0, 200.0, 300, 20));
		mp_canvas->addWidgetDown(new ofxUISlider("Slider03", 100.0, 300.0, 200.0, 300, 20));


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
	
		mp_canvasExtra = new ofxUICanvas(0,0,400,400);
		mp_canvasExtra->setPosition(pCanvasRect->getX()+pCanvasRect->getWidth()+10, pCanvasRect->getY());
		if (mp_toolManager->m_fontName != "")
			mp_canvasExtra->setFont(mp_toolManager->m_fontName);

		mp_canvasExtra->addWidgetDown(new ofxUILabel("Tool 02 extra column", OFX_UI_FONT_MEDIUM));
    	mp_canvasExtra->addWidgetDown(new ofxUISpacer(300, 1));
		mp_canvasExtra->addWidgetDown(new ofxUISlider("Test", 100.0, 300.0, 200.0, 300, 20));

		mp_canvasExtra->setVisible(false);
		mp_canvasExtra->autoSizeToFitWidgets();

	   ofAddListener(mp_canvasExtra->newGUIEvent, this, &tool02::handleEvents);
	}
}

//--------------------------------------------------------------
void tool02::handleEvents(ofxUIEventArgs& e)
{
	string name = e.getName();
	if (name == "Slider01"){
	
	}
	else
	if (name == "Slider01"){
	
	}
	// ...
}

//--------------------------------------------------------------
void tool02::show(bool is)
{
	tool::show(is);
 	if (mp_canvasExtra)
		mp_canvasExtra->setVisible(is);
}

//--------------------------------------------------------------
bool tool02::isHit(int x, int y)
{
	if (tool::isHit(x,y) || (mp_canvasExtra && mp_canvasExtra->isHit(x,y)))
		return true;
	return false;
}
