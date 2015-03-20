#include "testApp.h"

using namespace ofxCv;

void testApp::setup() {
	ofSetVerticalSync(true);
	cam.initGrabber(640, 480);
	tracker.setup();
    
    img.loadImage("mask_test.png");
}

void testApp::update() {
	cam.update();
	if(cam.isFrameNew()) {
		tracker.update(toCv(cam));
	}
}

void testApp::draw() {
	ofSetColor(255);
	cam.draw(0, 0);
	ofDrawBitmapString(ofToString((int) ofGetFrameRate()), 10, 20);
	
	if(tracker.getFound()) {
		//tracker.draw();
		ofMesh objectMesh = tracker.getObjectMesh();
		ofMesh meanMesh = tracker.getMeanObjectMesh();
		
        ofPolyline temp = tracker.getImageFeature(tracker.FACE_OUTLINE);
       
        ofRectangle box = temp.getBoundingBox();
    
        //ofRect(box);
        //img.draw(box);
        
        
        //img.draw(box.x, box.y-100, box.width, box.height*1.5);
        
        img.draw(box.x, box.y-(0.5*box.height), box.width, box.height*1.5);
	}
    
    
}

void testApp::keyPressed(int key) {
	if(key == 'r') {
		tracker.reset();
	}
}