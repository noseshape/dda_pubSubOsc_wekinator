#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofSetWindowShape(800, 600);
    ofBackground(255, 255, 255);
    
    //graph
    col[0] = ofColor(255, 0, 0);
    col[1] = ofColor(0, 255, 0);
    col[2] = ofColor(0, 0, 255);
    col[3] = ofColor(255, 255, 0);
    pos = ofVec2f(700, 450);
    graphScale = 300.0;
    
    
    //gui
    gui.setup();
    gui.add(max.setup("Max", 1.00, 0.00, 1.50));
    gui.add(min.setup("min", -0.10, -0.50, 1.00));
    gui.add(bSerial.setup("serial", false));
    gui.add(servoMin.setup("servoMin", 169, 0, 360));
    gui.add(servoMax.setup("servoMax", 145, 0, 360));



    angle = 0;
    
    //arduino serial
    serial.setup("/dev/cu.usbmodem1411",9600);

    //receiver
    receiver.setup(12000);

}

//--------------------------------------------------------------
void ofApp::update(){
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
    
    //receiver
    while(receiver.hasWaitingMessages()){
        ofxOscMessage p;
        receiver.getNextMessage(p);
        for(int i=0;i<3;i++){
            wekv[i]=p.getArgAsFloat(i);
            cout<<ofToString(i)+": "+ofToString(wekv[i])<<endl;
        }
        
    }
    
    //serial value adjusting
    
    if(wekv[1] > min && wekv[1] < max){
        angle = ofMap(wekv[1], min, max, servoMin, servoMax);
    }
    
    //serial value 
    
    if(bSerial && ofGetFrameNum()%12 == 0){
        if(bSerial!=bbSerial){
            serial.writeByte(255);
        }else{
            serial.writeByte(angle);
        }
        bbSerial = bSerial;

    }

    
     
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(255, 255, 255);
    
    //scale
    ofSetColor(0, 0, 0);
    ofDrawBitmapString("dda_valueControler", 10, 10);
    
    //graph
    ofPushMatrix();
    ofTranslate(pos);
    
    ofPushMatrix();
    
    ofScale(ofVec2f(-1, -1));   //x:右→左, y:下→上
    ofSetLineWidth(2);
    for(int n = 0; n < stateNum; n++){
        for(int i = 60*5-1; i > 0; i--){
            pastValue[n][i] = pastValue[n][i-1];
        }
        pastValue[n][0] = wekv[n];
        
        ofPolyline line;
        for(int i = 0; i < 60*5; i++){
            line.addVertex(ofVec2f(i, pastValue[n][i] * graphScale));
        }
        ofSetColor(col[n]);
        line.draw();
    }
    
    ofSetColor(255, 120, 150);
    ofDrawLine(0, max * graphScale, 60 * 5, max * graphScale);
    ofSetColor(120, 255, 255);
    ofDrawLine(0, min * graphScale, 60 * 5, min * graphScale);
    
    ofSetColor(0, 0, 0);
    ofSetLineWidth(1);
    ofNoFill();
    ofDrawRectangle(0, 0, 60*5, graphScale);
    for(int i = 0; i <= 5; i++){
        ofDrawLine(60*i, 0, 60*i, graphScale);
        ofDrawBitmapString(ofToString(i) + 's', 60*i, -15);
    }
    ofPopMatrix();
    ofPopMatrix();
    
    //gui
    gui.draw();
    
    //receive
    ofDrawBitmapString("receive", 10, 185);
    for(int i = 0; i < stateNum; i++){
        string log_state = "state" + ofToString(i) + ": " + ofToString(wekv[i]);
        ofDrawBitmapString(log_state, 10, 200 + 30*i);
    }

    //send
    ofDrawBitmapString("send", 10, 390);
    ofDrawBitmapString("angle: " + ofToString(angle), 10, 400);
    
    if(ofGetFrameNum() % 12 == 0){
        
    }
    

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
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
