/*
 * Making a Random Video Array with openFrameworks
 * Get video from connected devices, and print it out randomly through an array.
 * The maximum number of outputs(col*row) can be modified through variables.
 * Note that as the maximum number of images increases, there is a slight delay while initialing the array.
 *
 */
 
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    
    // print available devices on console
    vector<ofVideoDevice> devices = webcam.listDevices();
    for(int i = 0; i < devices.size(); i++){
        if(devices[i].bAvailable){
            ofLogNotice() << devices[i].id << ": " << devices[i].deviceName;
        }
        else{
            ofLogNotice() << devices[i].id << ": " << devices[i].deviceName << " - unavailable ";
        }
    }
    webcam.setDeviceID( 0 );  // default setting for mac FaceTime Camera
    
    ofBackground(0,0,0);
    
    
    maxNumImgs = 500;
    maxCols = 3;
    maxRows = 3;
    
    // video size to get from camera
    // be careful with cam's ratio
    camWidth = ofGetWidth()/maxCols;
    camHeight = ofGetHeight()/maxRows;
    webcam.initGrabber(camWidth, camHeight);

    for(int i=0; i<maxNumImgs; i++){
        int rand;
        rand = ofRandom(1,maxNumImgs);  // make random integer and push in vector
        randomNum.push_back(rand);
        
    }
}


//--------------------------------------------------------------
void ofApp::update(){
    
    webcam.update();
    
    // If there is a new frame through camera
    // convert to ofTexture
    // and save in imgs vector
    if(webcam.isFrameNew()){
        ofPixels pixels = webcam.getPixels();
        
        ofTexture currentFrame;
        currentFrame.allocate(pixels);
        
        // push_back in 'vector object'
        // and save new frame
        // if img num is over than maxNumImgs, erase the img which was saved first
        imgs.push_back(currentFrame);
        if(imgs.size() > maxNumImgs){
            imgs.erase(imgs.begin());
        }

        
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    col = 0;
    row = 0;
    
    // pull out the frame imgs(saved in imgs vector) and allocate
    if(imgs.size() == maxNumImgs){
        for(int i=0; i<maxNumImgs; i++){ // print entire screen
            if(i < imgs.size()){
                imgs[randomNum[i]].draw(col*ofGetWidth()/maxCols, row*ofGetHeight()/maxRows); // print image
            }
            col++;
            if(col == maxCols){
                col = 0;
                row++;
            }
        }
    }
    
    ofSetColor(255,255,255);
    ofDrawBitmapString(ofToString(ofGetFrameRate(),1)+"fps", 1, 10);  // print framerate
}

