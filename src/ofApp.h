#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "ofVboMesh.h"
#include <fstream>
#include <chrono>

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
		
		// my stuff
		ofxAssimpModelLoader model;
		ofMesh mesh;
		ofLight light;
		ofEasyCam cam;

		ifstream file; 
		vector<string> headers;
		vector<double> values;
		vector<double> nextValues;

		std::chrono::steady_clock::time_point timeOfLastUpdate;
		double timeBetweenRows;
};
