#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxOsc.h"
#include "ofxPubSubOsc.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    static const int stateNum = 3;
    
    //graph
    float pastValue[stateNum][60*5];    //60fps * 5s
    ofColor col[stateNum];
    ofVec2f pos;
    float graphScale;
    
    //gui
    ofxPanel gui;
    ofxFloatSlider max, min;
    ofxIntSlider servoMin, servoMax;
    ofxToggle bSerial;
    
    //receive
    ofxOscMessage mes;
    float state[stateNum];
    float state0, state1, state2, state3;
    
    //send
    int angle;
    
    ofSerial serial;
    bool bbSerial;
	
    //receive wekinator osc
    float wekv[3];
    ofxOscReceiver receiver;
};
