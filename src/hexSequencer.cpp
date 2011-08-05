//
//  hexSequencer.cpp
//  OP-1 Sequencer
//
//  Created by Zak Henry on 2/08/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "HexSequencer.h"

int blue = 0x0098D4;
int darkBlue = 0x002f3a;
int green = 0x01BB00;
int lightGrey = 0xDEE8E9;
int orange = 0xFE4F00;
int darkGrey = 0xC3C9C9;
int black = 0x000000;
int white = 0xFFFFFF;

Note::Note(){
    playing = false;
    posX = 0; 
    posY = 0;
//    drawNote = false;
    moveNote = false;
}

void Note::draw(){
//    if (drawNote){
        ofSetHexColor(white);
        ofCircle(posX, posY, 5);
        cout << "posX: "<<posX<<", posY:"<<posY<<endl;
//    }
}

void Note::update(float speed){
    
    if (moveNote){
        float vectorAngle = atan2((targetY-posY),(targetX-posX));
        
        cout << "vector angle is "<<vectorAngle<<endl;
        cout << "float vectorAngle = atan2((targetY-posY),(targetX-posX))"<<vectorAngle<<" = atan2(("<<targetY<<"-"<<posY<<"),("<<targetX<<"-"<<posX<<"))"<<endl;
        
        posX += cos(vectorAngle)*speed;
        posY += sin(vectorAngle)*speed;
    }
    
}

HexGate::HexGate(float _size){
    selected = false;
    active = false;
    turretOneDir = 0;
    turretTwoDir = -1;
    
    radius = _size;
    turretWidth = radius/6;
    turretLength = radius/1.5;
    
    for (int i=0; i<14; i++) {
        int rad = (i<7)?radius:radius+turretWidth;
        ofPoint vertex;
        vertex.x = rad*cos(i*2*PI/6);
        vertex.y = rad*sin(i*2*PI/6);
        hexPoints.push_back(vertex);
    }
    
    verdana30.loadFont("verdana.ttf", 20, true, true);
    verdana10.loadFont("verdana.ttf", 15, true, true);
//	verdana30.setLineHeight(20.0f);
//	verdana30.setLetterSpacing(1.035);
    
}

void HexGate::draw(){
    ofPushMatrix();
        int color = active ? blue:darkBlue;
        ofSetHexColor(color);
        ofTranslate(posX, posY);
//    ofCircle(0, 0, 5);
        ofRotateZ(30);
        ofBeginShape();
            ofVertexes(hexPoints);
        ofEndShape();
    
        ofSetHexColor(green);
    
        ofPushMatrix();
            ofRotateZ(60*(turretOneDir+3)); //top is 0
            ofTranslate(0, radius);
            ofRect(-turretWidth/2, 0, turretWidth, turretLength);
        ofPopMatrix();
    
        if (turretTwoDir>=0){
            ofPushMatrix();
                ofRotateZ(60*(turretTwoDir+3)); //top is 0
                ofTranslate(0, radius);
                ofRect(-turretWidth/2, 0, turretWidth, turretLength);
            ofPopMatrix();
        }
    
        if (selected){
            ofSetHexColor(blue);
            ofCircle(0, 0, 8);
        }
    
        ofSetHexColor(green);
//        verdana30.drawString(ofToString(id), -15, 12);
        
//    if (turretOneDir==0) verdana10.drawString(ofToString(neighbours[0]), -5, -20);
//    if (turretOneDir==1) verdana10.drawString(ofToString(neighbours[1]), 15, -7);
//    if (turretOneDir==2) verdana10.drawString(ofToString(neighbours[2]), 15, 20);
//    if (turretOneDir==3) verdana10.drawString(ofToString(neighbours[3]), -5, 35);
//    if (turretOneDir==4) verdana10.drawString(ofToString(neighbours[4]), -30, 20);
//    if (turretOneDir==5) verdana10.drawString(ofToString(neighbours[5]), -30, -7);
    
        
        
    
    
    
    ofPopMatrix();
}

HexSequencer::HexSequencer(){
    
    beatIndicatorScale = 0;
    currentHover = 0;
    
    ofAddListener(TO.beat, this, &HexSequencer::beatEvent);
    ofAddListener(TO.subBeat, this, &HexSequencer::subBeatEvent);
    TO.start();
    
    
    neighbourhood[0][0] = -1;
    neighbourhood[0][1] = 1;
    neighbourhood[0][2] = 5;
    neighbourhood[0][3] = 4;
    neighbourhood[0][4] = -1;
    neighbourhood[0][5] = -1;
    
    neighbourhood[1][0] = -1;
    neighbourhood[1][1] = 2;
    neighbourhood[1][2] = 6;
    neighbourhood[1][3] = 5;
    neighbourhood[1][4] = 0;
    neighbourhood[1][5] = -1;
    
    neighbourhood[2][0] = -1;
    neighbourhood[2][1] = 3;
    neighbourhood[2][2] = 7;
    neighbourhood[2][3] = 6;
    neighbourhood[2][4] = 1;
    neighbourhood[2][5] = -1;
    
    neighbourhood[3][0] = -1;
    neighbourhood[3][1] = -1;
    neighbourhood[3][2] = 8;
    neighbourhood[3][3] = 7;
    neighbourhood[3][4] = 2;
    neighbourhood[3][5] = -1;
    
    neighbourhood[4][0] = 0;
    neighbourhood[4][1] = 5;
    neighbourhood[4][2] = 9;
    neighbourhood[4][3] = -1;
    neighbourhood[4][4] = -1;
    neighbourhood[4][5] = -1;
    
    neighbourhood[5][0] = 1;
    neighbourhood[5][1] = 6;
    neighbourhood[5][2] = 10;
    neighbourhood[5][3] = 9;
    neighbourhood[5][4] = 4;
    neighbourhood[5][5] = 0;
    
    neighbourhood[6][0] = 2;
    neighbourhood[6][1] = 7;
    neighbourhood[6][2] = 11;
    neighbourhood[6][3] = 10;
    neighbourhood[6][4] = 5;
    neighbourhood[6][5] = 1;
    
    neighbourhood[7][0] = 3;
    neighbourhood[7][1] = 8;
    neighbourhood[7][2] = 12;
    neighbourhood[7][3] = 11;
    neighbourhood[7][4] = 6;
    neighbourhood[7][5] = 2;
    
    neighbourhood[8][0] = -1;
    neighbourhood[8][1] = -1;
    neighbourhood[8][2] = -1;
    neighbourhood[8][3] = 12;
    neighbourhood[8][4] = 7;
    neighbourhood[8][5] = 3;
    
    neighbourhood[9][0] = 5;
    neighbourhood[9][1] = 10;
    neighbourhood[9][2] = -1;
    neighbourhood[9][3] = -1;
    neighbourhood[9][4] = -1;
    neighbourhood[9][5] = 4;
    
    neighbourhood[10][0] = 6;
    neighbourhood[10][1] = 11;
    neighbourhood[10][2] = -1;
    neighbourhood[10][3] = -1;
    neighbourhood[10][4] = 9;
    neighbourhood[10][5] = 5;
    
    neighbourhood[11][0] = 7;
    neighbourhood[11][1] = 12;
    neighbourhood[11][2] = -1;
    neighbourhood[11][3] = -1;
    neighbourhood[11][4] = 10;
    neighbourhood[11][5] = 6;
    
    neighbourhood[12][0] = 8;
    neighbourhood[12][1] = -1;
    neighbourhood[12][2] = -1;
    neighbourhood[12][3] = -1;
    neighbourhood[12][4] = 11;
    neighbourhood[12][5] = 7;
    
}

void HexSequencer::beatEvent(int &beatCount){
    beatIndicatorScale = 1;
    moveNotes();
//    cout << "beat event #"<<beatCount<<" occurred"<<endl;
}

void HexSequencer::subBeatEvent(int &subBeat){
    int noteLength = 8;
    
//    cout <<"subBeatnum is "<<subBeat<<endl;
    
    if (subBeat==noteLength){
        stopNotes();
    }
    
}

void HexSequencer::stopNotes(){
    for (int i=0; i<gates.size(); i++){ //process all the notes
        
        for (int j=0; j<gates[i].notesOutgoing.size();j++){
            
            cout << "stopping "<<gates[i].notesOutgoing.size()<<" notes"<<endl;
            
            if (gates[i].notesOutgoing[j].playing){
                op1->sendNoteOff(gates[i].notesOutgoing[j].midiId, 0);
            }
        }
    }
}

void HexSequencer::moveNotes(){
    
    for (int i=0; i<gates.size(); i++){ //swap all the notes
        
        if (gates[i].notesOutgoing.size()>0){
         
            int nextGate = gates[i].neighbours[gates[i].turretOneDir]; //im only using the one turret for now
            
            cout << "nextGate to visit is "<<nextGate<<endl;
            
            if (nextGate>-1){
                
                gates[nextGate].notesIncoming = gates[i].notesOutgoing;
                
            }
            
            gates[i].notesOutgoing.clear();
        }
        
    }
    
    for (int i=0; i<gates.size(); i++){ //process all the notes
        
        for (int j=0; j<gates[i].notesIncoming.size();j++){
            if (gates[i].active){
                gates[i].notesIncoming[j].playing = true;
                
                
                op1->sendNoteOn(gates[i].notesIncoming[j].midiId, 0);
            }
            gates[i].notesIncoming[j].moveNote = true;
            gates[i].notesIncoming[j].posX = gates[i].posX;
            gates[i].notesIncoming[j].posY = gates[i].posY;
            
            int nextGate = gates[i].neighbours[gates[i].turretOneDir];
            
            if (nextGate>-1){
                gates[i].notesIncoming[j].targetX = gates[nextGate].posX;
                gates[i].notesIncoming[j].targetY = gates[nextGate].posY;
//                gates[i].notesIncoming[j].drawNote = true;
            }else{
//                gates[i].notesIncoming[j].drawNote = false;
            }
            
            
        }
        
        gates[i].notesOutgoing = gates[i].notesIncoming;
        gates[i].notesIncoming.clear();
        
        
    }
    
}

void HexSequencer::setWidth(int _width){
    width = _width;
    height = width/2;
    cout << "width is "<<width<<" height is "<<height<<endl;
    createGates();
}

void HexSequencer::createGates(){
    gates.empty(); //in case it has been initiated before
    
    trackLength = width/5;
    
    for (int i=0; i<13; i++){
        HexGate gate (width/20);
        gate.id = i;
        int yPos = 0;
        int xPos = 0;
        if (i<4){//top row
            xPos = trackLength/2+trackLength*i;
            cout << sin(PI/3)<<endl;
        }else if(i<9){ //middle row
            yPos = trackLength*sin(PI/3);
            xPos = trackLength*(i-4);
        }else{
            yPos = trackLength*sin(PI/3)*2; //bottom row
            xPos = trackLength/2+trackLength*(i-9);
        }
        
        gate.posX = xPos;
        gate.posY = yPos;
        
//        memcpy(gate.neighbours, neighbourhood[i], 7);
        
        gate.neighbours[0] = neighbourhood[i][0];
        gate.neighbours[1] = neighbourhood[i][1];
        gate.neighbours[2] = neighbourhood[i][2];
        gate.neighbours[3] = neighbourhood[i][3];
        gate.neighbours[4] = neighbourhood[i][4];
        gate.neighbours[5] = neighbourhood[i][5];
        
        
        gates.push_back(gate);
    }
    
    gates[0].selected = true;

    
}

void HexSequencer::update(){
    
    beatIndicatorScale-=0.01;
    
}

void HexSequencer::processOP1Event(midiPacket &event){
    
    cout << "## element name: "<<event.elementName<<endl;
    
    
    if (event.elementName=="encoder_blue") {
        
        cout << "event.event is"<<event.event<<endl;

        if(event.event == "button_down"){
            
            gates[currentHover].active = !gates[currentHover].active;
            
            return;
        }
        
        int nextHover = (currentHover>12)?0:currentHover; //weirdly sometimes overflows
        
        gates[nextHover].selected = false;
        
        if (event.event == "encoder_cw"){
            nextHover ++;
        }else if(event.event == "encoder_ccw"){
            nextHover --;
        }
        
        nextHover = (nextHover>12)?0:nextHover;
        nextHover = (nextHover<0)?12:nextHover;
        
        currentHover = nextHover;
        
        gates[currentHover].selected = true;
        
        cout << "blue encoder event"<<endl;
        return;
    }
    
    if (event.elementName=="encoder_green") {
        
        int nextTurretAngle = gates[currentHover].turretOneDir;
        
        if (event.event == "encoder_cw"){
            nextTurretAngle ++;
        }else if(event.event == "encoder_ccw"){
            nextTurretAngle --;
        }
        
        nextTurretAngle = (nextTurretAngle>5)?0:nextTurretAngle;
        nextTurretAngle = (nextTurretAngle<0)?5:nextTurretAngle;
        
        gates[currentHover].turretOneDir = nextTurretAngle;

        
        cout << "blue encoder event"<<endl;
        return;
    }
    
    if (event.elementName=="encoder_white") {
        cout << "blue encoder event"<<endl;
        return;
    }
    
    if (event.elementName=="encoder_orange") {
        cout << "blue encoder event"<<endl;
        return;
    }
    
    
    if (event.elementId>52&&event.elementId<77){ //keyboard press
        Note newNote;
        newNote.midiId = event.elementId;
        newNote.posX = gates[currentHover].posX; //makes it stay in place
        newNote.posY = gates[currentHover].posY;
        newNote.targetX = newNote.posX;
        newNote.targetX = newNote.posY;
//        newNote.drawNote = true;
        gates[currentHover].notesOutgoing.push_back(newNote);
    }
    
    
    
}

void HexSequencer::draw(){
    
    TO.draw();
    
    ofTranslate(480, 247); //delete this when inserting into op1
    
    ofPushStyle();
    
//    cout << "rectmode is "<<ofGetRectMode()<<endl;
    ofSetRectMode(OF_RECTMODE_CORNER);
    
    ofSetHexColor(0x111111);
    ofRect(0, 0, width, height);
    
    ofSetHexColor(orange, beatIndicatorScale*255); //custom hex function in of
    ofCircle(width-30, 30, 10);
    
    ofTranslate(width/2, height/2); //move origin to centre
    ofTranslate(-trackLength*2, -trackLength*sin(PI/3)); //centre gates on origin
    
    for (int i=0; i<gates.size();i++){
        gates[i].draw();
    }
    
    for (int i=0; i<gates.size(); i++){ //process all the notes
        for (int j=0; j<gates[i].notesOutgoing.size();j++){
            int bpm = 120; //link to thread later ###
            float speed = trackLength/30;
            gates[i].notesOutgoing[j].update(speed);
            gates[i].notesOutgoing[j].draw();
        }
    }
    
    ofPopStyle();
}