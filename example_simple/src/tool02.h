//
//  tool02.h
//  example_simple
//
//  Created by Julien on 21/07/2014.
//
//

#pragma once
#include "tool.h"

class tool02 : public tool
{
	public:
		tool02				(toolManager* parent);
		~tool02				();
	
		void				saveData						();
		void				loadData						();
		void				createControlsCustom			();
		void				createControlsCustomFinalize	();
		void				handleEvents					(ofxUIEventArgs& e);

		void				show							(bool is);
		bool				isHit							(int x, int y);

		ofxUICanvas*		mp_canvasExtra; // third column
};


