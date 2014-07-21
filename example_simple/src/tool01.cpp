//
//  tool01.cpp
//  example_simple
//
//  Created by Julien on 21/07/2014.
//
//

#include "tool01.h"

//--------------------------------------------------------------
tool01::tool01(toolManager* parent) : tool("Tool01", parent)
{
}

//--------------------------------------------------------------
void tool01::createControlsCustom()
{
	if (mp_canvas)
	{
		mp_canvas->addWidgetDown(new ofxUILabel("Tool 01", OFX_UI_FONT_MEDIUM));
    	mp_canvas->addWidgetDown(new ofxUISpacer(300, 1));

		mp_canvas->addWidgetDown(new ofxUISlider(_id("Distance"), 100.0, 300.0, 200.0, 300, 20));

		vector<string> selectionIds;
		selectionIds.push_back("A");
		selectionIds.push_back("B");
		selectionIds.push_back("C");

		ofxUIRadio* radioSelect = mp_canvas->addRadio(_id("Selection"), selectionIds, OFX_UI_ORIENTATION_HORIZONTAL,OFX_UI_FONT_SMALL);


		mp_canvas->setVisible(false);
		mp_canvas->autoSizeToFitWidgets();
	}
}

//--------------------------------------------------------------
void tool01::handleEvents(ofxUIEventArgs& e)
{
}