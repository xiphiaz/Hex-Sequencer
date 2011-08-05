#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    op1.setDimensions(ofGetWidth()/2, ofGetHeight()/2, ofGetWidth()-100);
    ofBackground(0, 0, 0);
    ofSetWindowTitle("OP-1 Sequencer");
    ofAddListener(op1.midiEvent, this, &testApp::op1Event);
//    sequencer.setWidth(op1.getScreenWidth());
    sequencer.setWidth(385);
    sequencer.op1 = &op1;
    
    ofSetFrameRate(60); //may cause timing issues, keep an eye on it
    
    
}

//--------------------------------------------------------------
void testApp::update(){
    sequencer.update();
}


void testApp::op1Event(midiPacket &packet){
    sequencer.processOP1Event(packet);
    cout << "midi packet: channel ["<<packet.channel<<"], event ["<<packet.event<<"], keyId ["<<packet.elementId<<"], keyName ["<<packet.elementName<<"], timestamp ["<<packet.timestamp<<"]\n";
}

//--------------------------------------------------------------
void testApp::draw(){
    
    op1.draw();
    sequencer.draw();
}

//void OP1::drawScreen(){
//    ofSetHexColor(0x0ffff0);
//    ofRect(10, 10, 20, 20);
//    
//}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    op1.updateCursorPosition(x, y);
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    op1.mouseDown(x, y);
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    op1.mouseUp();
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}