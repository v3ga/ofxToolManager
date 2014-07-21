//
//  tool01.h
//  example_simple
//
//  Created by Julien on 21/07/2014.
//
//

#pragma once
#include "tool.h"

class tool01 : public tool
{
	public:
		tool01				(toolManager* parent);


		void				createControlsCustom();
		void				handleEvents		(ofxUIEventArgs& e);
};
