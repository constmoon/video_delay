#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		
    ofVideoGrabber webcam;
    int camWidth;
    int camHeight;
    int maxNumImgs;
    vector <ofTexture> imgs;
    int maxCols, maxRows, col, row;
    
    vector <int> randomNum;
    
};
