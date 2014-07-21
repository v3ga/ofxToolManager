//
//  tool.cpp
//
//  Created by Julien on 30/05/2014.
//
//

#include "tool.h"
#include "ofEventUtils.h"

//--------------------------------------------------------------
tool::tool(string id, toolManager* parent)
{
	m_id = id;
	mp_toolManager = parent;
	mp_canvas = 0;
}

//--------------------------------------------------------------
tool::~tool()
{
	delete mp_canvas;
}

//--------------------------------------------------------------
void tool::createControls(string fontName, ofVec2f posCanvas, ofVec2f dimCanvas)
{
   	mp_canvas = new ofxUICanvas(posCanvas.x,posCanvas.y,dimCanvas.x,dimCanvas.y);
	if (fontName!="")
		mp_canvas->setFont(fontName);
    mp_canvas->setTriggerWidgetsUponLoad(true);
	//mp_canvas->setRetinaResolution();

   createControlsCustom();

   ofAddListener(mp_canvas->newGUIEvent, this, &tool::handleEvents);
}

//--------------------------------------------------------------
void tool::saveData()
{
	if (mp_canvas){
		mp_canvas->saveSettings(getDataPath());
	}
}

//--------------------------------------------------------------
void tool::loadData()
{
	if (mp_canvas){
		mp_canvas->loadSettings(getDataPath());
	}
}

//--------------------------------------------------------------
string tool::getDataPath()
{
	return getDataPath( getDataFileName() );
}

//--------------------------------------------------------------
string tool::getDataPath(string filename)
{
	return mp_toolManager->m_relPathData+"/"+filename;
}

//--------------------------------------------------------------
bool tool::isHit(int x, int y)
{
	if (mp_canvas)
		return mp_canvas->isHit(x,y);
	return false;
}

//--------------------------------------------------------------
void tool::enableDrawCallback(bool is)
{
	if (mp_canvas)
	{
		if (is){
			mp_canvas->enableAppDrawCallback();
			mp_canvas->enableMouseEventCallbacks();
		}
		else{
			mp_canvas->disableAppDrawCallback();
			mp_canvas->disableMouseEventCallbacks();
		}
	}
}

//--------------------------------------------------------------
toolManager::toolManager()
{
	mp_toolTab = 0;
	mp_toolCurrent = 0;
	mp_radioTabs = 0;
	m_relPathData = "gui/tools";
}

//--------------------------------------------------------------
toolManager::~toolManager()
{
	map<string, tool*>::iterator mapToolsIt;
	for (mapToolsIt = m_mapTools.begin(); mapToolsIt != m_mapTools.end(); ++mapToolsIt){
		delete mapToolsIt->second;
	}
	delete mp_toolTab;
	mp_toolTab = 0;
}


//--------------------------------------------------------------
void toolManager::setLogo(string logoName)
{
    m_logo.loadImage(this->m_relPathData+"/"+logoName);
}

//--------------------------------------------------------------
void toolManager::addTool(tool* pTool)
{
	m_mapTools[pTool->m_id] = pTool;
}

//--------------------------------------------------------------
tool* toolManager::getTool(string id)
{
	return m_mapTools[id];
}

//--------------------------------------------------------------
tool* toolManager::setTool(string id)
{
	if (m_mapTools.count(id) == 0) return 0;
	mp_toolCurrent = 0;

	hideAllTools();
	mp_toolCurrent = m_mapTools[id];
	mp_toolCurrent->show();
	
	return mp_toolCurrent;
}

//--------------------------------------------------------------
tool* toolManager::selectTool(string id)
{
	setTool(id);
	if (mp_radioTabs)
		mp_radioTabs->activateToggle(id);
	return mp_toolCurrent;
}

//--------------------------------------------------------------
void toolManager::createControls(ofVec2f posCanvas, ofVec2f dimCanvas)
{
//    m_logo.loadImage(this->m_relPathData+"/ARicon_150x150.png");

	vector<string> toolIds;

	map<string, tool*>::iterator mapToolsIt;
	for (mapToolsIt = m_mapTools.begin(); mapToolsIt != m_mapTools.end(); ++mapToolsIt)
	{
		tool* pTool = mapToolsIt->second;
		toolIds.push_back(pTool->m_id);
	
		pTool->createControls(m_fontName, posCanvas, dimCanvas);
	}

	mp_toolTab = new ofxUICanvas(0,0,400,400);
	if(m_fontName!="")
		mp_toolTab->setFont(m_fontName);

	mp_toolTab->setWidgetFontSize(OFX_UI_FONT_MEDIUM);
	if (m_logo.isAllocated())
	    mp_toolTab->addWidgetDown(new ofxUIImage(0,0,m_logo.getWidth(),m_logo.getHeight(),&m_logo,"logo",false));
    mp_toolTab->addWidgetDown(new ofxUIFPS(OFX_UI_FONT_SMALL));
	mp_radioTabs = mp_toolTab->addRadio("Tabs", toolIds, OFX_UI_ORIENTATION_VERTICAL, OFX_UI_FONT_MEDIUM);
	mp_toolTab->autoSizeToFitWidgets();

	for (mapToolsIt = m_mapTools.begin(); mapToolsIt != m_mapTools.end(); ++mapToolsIt)
	{
		tool* pTool = mapToolsIt->second;
		pTool->getCanvas()->setPosition(mp_toolTab->getRect()->getX()+10+mp_toolTab->getRect()->getWidth(), mp_toolTab->getRect()->getY());
		pTool->createControlsCustomFinalize();
		pTool->hide();
	}

   ofAddListener(mp_toolTab->newGUIEvent, this, &toolManager::handleEvents);
   mp_toolTab->setTriggerWidgetsUponLoad(true);
   mp_toolTab->disableAppDrawCallback();
}

//--------------------------------------------------------------
void toolManager::loadData()
{
	map<string, tool*>::iterator mapToolsIt;
	for (mapToolsIt = m_mapTools.begin(); mapToolsIt != m_mapTools.end(); ++mapToolsIt)
	{
		tool* pTool = mapToolsIt->second;
		pTool->loadData();
	}

	if (mp_toolTab){
		mp_toolTab->loadSettings(getDataPath());
		if (mp_radioTabs)
		{
			ofxUIToggle* pToogleActive = mp_radioTabs->getActive();
				ofLog() << (pToogleActive ? pToogleActive->getName() : "???");
		}
	}
}

//--------------------------------------------------------------
void toolManager::saveData()
{
	map<string, tool*>::iterator mapToolsIt;
	for (mapToolsIt = m_mapTools.begin(); mapToolsIt != m_mapTools.end(); ++mapToolsIt)
	{
		tool* pTool = mapToolsIt->second;
		if (pTool)
			pTool->saveData();
	}
	
	if (mp_toolTab)
		mp_toolTab->saveSettings(getDataPath());
}


//--------------------------------------------------------------
void toolManager::setup()
{
	map<string, tool*>::iterator mapToolsIt;
	for (mapToolsIt = m_mapTools.begin(); mapToolsIt != m_mapTools.end(); ++mapToolsIt)
	{
		tool* pTool = mapToolsIt->second;
		pTool->setup();
	}
}

//--------------------------------------------------------------
void toolManager::hideAllTools()
{
   map<string, tool*>::iterator mapToolsIt;
   
   // Hide all
   mp_toolCurrent = 0;
   for (mapToolsIt = m_mapTools.begin(); mapToolsIt != m_mapTools.end(); ++mapToolsIt)
   {
	   tool* pTool = mapToolsIt->second;
	   if (pTool)
	   {
		   pTool->hide();
		}
   }
}

//--------------------------------------------------------------
void toolManager::handleEvents(ofxUIEventArgs& e)
{
    string name = e.widget->getName();
	ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
	if (toggle && toggle->getValue()) setTool(name);
}

//--------------------------------------------------------------
void toolManager::enableDrawCallback(bool is)
{
	if (mp_toolCurrent)
		mp_toolCurrent->enableDrawCallback(is);
}


//--------------------------------------------------------------
void toolManager::updateUI()
{
	
}

//--------------------------------------------------------------
void toolManager::update()
{
	map<string, tool*>::iterator mapToolsIt;
	for (mapToolsIt = m_mapTools.begin(); mapToolsIt != m_mapTools.end(); ++mapToolsIt)
	{
		tool* pTool = mapToolsIt->second;
		pTool->update();
	}
}

//--------------------------------------------------------------
void toolManager::drawUI()
{
	if (mp_toolTab)
		mp_toolTab->draw();
	
	if (mp_toolCurrent)
		mp_toolCurrent->drawUI();
}

//--------------------------------------------------------------
void toolManager::draw()
{
	if (mp_toolCurrent)
		mp_toolCurrent->draw();
}

//--------------------------------------------------------------
bool toolManager::isHit(int x, int y)
{
	if (mp_toolTab->isHit(x, y))
		return true;

	map<string, tool*>::iterator mapToolsIt;
	for (mapToolsIt = m_mapTools.begin(); mapToolsIt != m_mapTools.end(); ++mapToolsIt)
	{
		tool* pTool = mapToolsIt->second;
		if (pTool->isHit(x, y))
			return true;
	}
	
	return false;
}


//--------------------------------------------------------------
void toolManager::mousePressed(int x, int y, int button)
{
	if (mp_toolCurrent)
		mp_toolCurrent->mousePressed(x,y,button);
}

//--------------------------------------------------------------
bool toolManager::keyPressed(int key)
{
	if (mp_toolCurrent)
		return mp_toolCurrent->keyPressed(key);
	return false;
}

//--------------------------------------------------------------
void toolManager::dragEvent(ofDragInfo dragInfo)
{
	if (mp_toolCurrent)
		mp_toolCurrent->dragEvent(dragInfo);
}

//--------------------------------------------------------------
void toolManager::windowResized(int w, int h)
{
	if (mp_toolCurrent)
		mp_toolCurrent->windowResized(w,h);
}

//--------------------------------------------------------------
void toolManager::exit()
{
	map<string, tool*>::iterator mapToolsIt;
	for (mapToolsIt = m_mapTools.begin(); mapToolsIt != m_mapTools.end(); ++mapToolsIt)
	{
		tool* pTool = mapToolsIt->second;
		pTool->exit();
	}
}









