#include "ofApp.h"
#include "tool01.h"
#include "tool02.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	toolManager.setLogo("murmur_logo.png");
	toolManager.setFontName("fonts/FOLDERAL.TTF");

	toolManager.addTool( new tool01(&toolManager) );
	toolManager.addTool( new tool02(&toolManager) );
	toolManager.createControls(ofVec2f(150,0), ofVec2f(400,100));

	toolManager.loadData();
}

//--------------------------------------------------------------
void ofApp::exit()
{
	toolManager.saveData();
	toolManager.exit();
}

//--------------------------------------------------------------
void ofApp::update(){
	toolManager.update();
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofBackgroundGradient(ofColor(64), ofColor(0));
	toolManager.drawUI();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
	toolManager.mousePressed(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
