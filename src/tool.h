
//
//  tool.h
//
//  Created by Julien on 30/05/2014.
//
//

#pragma once
#include "ofMain.h"
#include "ofxUI.h"

class toolManager;
class tool
{
	public:
		tool			(string id, toolManager* parent);
		virtual ~tool	();

				void	createControls		(string fontName, ofVec2f posCanvas, ofVec2f dimCanvas);
		virtual	void	createControlsCustom(){}
		virtual	void	createControlsCustomFinalize(){}
		virtual void	updateControls		(){}
		virtual	void	handleEvents		(ofxUIEventArgs& e){}
		virtual	void	saveData			();
		virtual	void	loadData			();
		virtual	void	setup				(){}
		virtual void	update				(){}
		virtual void	drawUI				(){}
		virtual void	draw				(){}
		virtual	void	show				(bool is=true){if (mp_canvas) mp_canvas->setVisible(is);}
				void	hide				(){show(false);}
		virtual	bool	isHit				(int x, int y);
		virtual	void	enableDrawCallback	(bool is=true);
		virtual	void	exit				(){}

		virtual	void	select				(){}
		virtual	void	unselect			(){}


	
		virtual	void	mousePressed		(int x, int y, int button){}
		virtual void	mouseDragged		(int x, int y, int button){}
		virtual void	mouseReleased		(int x, int y, int button){}
		virtual	bool	keyPressed			(int key){return false;}
		virtual	void 	dragEvent			(ofDragInfo dragInfo){}
	
		virtual void	windowResized		(int w, int h){};


		ofxUICanvas*	getCanvas()			{return mp_canvas;}
		string			getControlId		(string which){return which+"_"+m_id;}
		string			_id					(string which){return getControlId(which);}
		string			getDataFileName		(){return m_id+".xml";}
		string			getDataPath			();
		string			getDataPath			(string filename);

		string			m_id;
		toolManager*	mp_toolManager;
		ofxUICanvas*	mp_canvas;
};


class toolManager
{
	public:
		toolManager			();
		~toolManager		();
	
	
		static toolManager* smp_instance;
		static toolManager* instance			();
	
		void				setLogo				(string logoName);
		void				setFontName			(string fontName){m_fontName = fontName;}
	
		void				addTool				(tool*);
		tool*				getTool				(string id);
		tool*				setTool				(string id);
		tool*				selectTool			(string id);
		void				hideAllTools		();
		void				createControls		(ofVec2f posCanvas, ofVec2f dimCanvas);
		void				createControls		(ofVec2f dimCanvas){createControls(ofVec2f(),dimCanvas);}
		void				updateControls		(){}
		void				loadData			();
		void				saveData			();
		void				setup				();
		void				handleEvents		(ofxUIEventArgs& e);
		void				update				();
		void				updateUI			();
		void				drawUI				();
		void				draw				();
		bool				isHit				(int x, int y);
		void				enableDrawCallback	(bool is=true);
		void				exit				();

		string				getDataFileName		(){return "manager.xml";}
		string				getDataPath			(){return m_relPathData+"/"+getDataFileName();}

		void				mousePressed		(int x, int y, int button);
		void				mouseDragged		(int x, int y, int button);
		void				mouseReleased		(int x, int y, int button);
		bool				keyPressed			(int key);
		void 				dragEvent			(ofDragInfo dragInfo);
	
		void				windowResized		(int w, int h);

		map<string, tool*>	m_mapTools;
		string				m_relPathData;
		ofxUICanvas*		mp_toolTab;
		ofxUIRadio*			mp_radioTabs;
		tool*				mp_toolCurrent;
	
		ofImage				m_logo;
		string				m_fontName;
	
	
};
