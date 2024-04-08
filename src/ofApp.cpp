#include "ofApp.h"
#include <sstream>

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetLogLevel(OF_LOG_VERBOSE);
	ofBackground(0);

	// load model 
	if (!model.load("PayloadMockUp.obj", ofxAssimpModelLoader::OPTIMIZE_DEFAULT)) {
		ofLogFatalError() << " can't load model or model file cannot be found " << std::endl;
		while (1);
	}

	file.open("../bin/data/telemetry.csv", ifstream::in);

	if (!file) {
		ofLogFatalError() << " can't open telemetry file " << std::endl;
	}

	string line = "";
	std::getline(file, line);
	cout << line << endl;
	std::stringstream ss(line);
	string val = "";
	ss.ignore(256, ' ');
	while (std::getline(ss, val, ',')) {
		headers.push_back(val);
		values.push_back(0);
		ss.ignore(256, ' ');
	}

	for (auto& h : headers) {
		cout << h << ", ";
	}
	cout << endl;

	ofLogNotice() << " setup done " << std::endl;
}

//--------------------------------------------------------------
void ofApp::update(){

	// update data used

	string temp = "";

	string line = "";
	std::getline(file, line);
	std::stringstream ss(line);
	string valStr = "";
	for (unsigned int i = 0; i < values.size(); i++) {
		std::getline(ss, valStr, ',');
		try {
			values.at(i) = std::stof(valStr);
		}
		catch (std::exception& e) {
			// keep old value
		}
	}

	cout << endl;

	for (auto& v : values) {
		cout << v << ", ";
	}
	cout << endl;

	float sceneHeight = fabs((model.getSceneMaxModelSpace() - model.getSceneMinModelSpace()).y);

	model.setScale(0.5, 0.5, 0.5);
	model.setRotation(0, 90, 1, 0, 0);
	model.setRotation(1, 150, 0, 0, 1);
	model.setPosition(ofGetWidth() / 2, ofGetHeight() / 2 + sceneHeight * 0.5, 0);

	light.setPosition(model.getPosition() + glm::vec3(-300, -300, 1200));

	model.update();

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(255);

	ofEnableDepthTest();

	ofEnableLighting();
	light.enable();
	ofEnableSeparateSpecularLight();

	ofPushMatrix();

	model.drawFaces();

	ofPopMatrix();

	light.disable();
	ofDisableLighting();
	ofDisableSeparateSpecularLight();
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
