#include "ofApp.h"
#include <sstream>

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetLogLevel(OF_LOG_VERBOSE);
	ofBackground(50, 153, 204);
	ofSetFrameRate(60);

	// load model 
	if (!model.load("PayloadMockUpC.obj", ofxAssimpModelLoader::OPTIMIZE_DEFAULT)) {
		ofLogFatalError() << " can't load model or model file cannot be found " << std::endl;
		while (1);
	}

	file.open("../bin/data/telemetry.csv", ifstream::in);

	if (!file) {
		ofLogFatalError() << " can't open telemetry file " << std::endl;
	}

	string line = "";
	std::getline(file, line);
	//cout << line << endl;
	std::stringstream ss(line);
	string val = "";
	if (ss.peek() == ' ') {
		ss.ignore(256, ' ');
	}
	while (std::getline(ss, val, ',')) {
		headers.push_back(val);
		nextValues.push_back(0);
		values.push_back(0);
		ss.ignore(256, ' ');
	}

	// sync time	
	// get set of data in newValues
	line = "";
	std::getline(file, line);
	std::stringstream ssVal(line);
	string valStr = "";
	for (unsigned int i = 0; i < nextValues.size(); i++) {
		std::getline(ssVal, valStr, ',');
		try {
			nextValues.at(i) = std::stod(valStr);
		}
		catch (std::exception& e) {
			// keep old value
		}
	}
	values = nextValues; 
	this->timeOfLastUpdate = std::chrono::steady_clock::now();
	this->timeBetweenRows = nextValues[0] - values[0];

	//cout << headers.at(0) << endl;
	//for (auto& h : headers) {
	//	cout << h << ", ";
	//}
	//cout << endl;

	ofLogNotice() << " setup done " << std::endl;
}

//--------------------------------------------------------------
void ofApp::update(){

	// update data used

	auto now = std::chrono::steady_clock::now();
	double timeElapsed = std::chrono::duration_cast<chrono::milliseconds>(now - this->timeOfLastUpdate).count();
	double fps = ofGetFrameRate();
	if(fps == 0) fps = 30;
	if (timeElapsed >= this->timeBetweenRows) {
		double lastFrameTime = this->values[0];
		while ((this->values[0] - lastFrameTime) <= (1.0 / fps)) {
			cout << "skipping" << endl;
			values = nextValues;
			string line = "";
			std::getline(file, line);
			std::stringstream ss(line);
			string valStr = "";
			for (unsigned int i = 0; i < nextValues.size(); i++) {
				std::getline(ss, valStr, ',');
				try {
					this->nextValues.at(i) = std::stod(valStr);
				}
				catch (std::exception& e) {
					// keep old value
				}
			}

			this->timeOfLastUpdate = now;
			this->timeBetweenRows = this->nextValues[0] - this->values[0];
		}
	}
	else {
		cout << "maintain data" << endl;
	}

	//for (auto& v : values) {
	//	cout << v << ", ";
	//}
	//cout << endl;

	float sceneHeight = fabs((model.getSceneMaxModelSpace() - model.getSceneMinModelSpace()).y);

	model.setScale(0.5, 0.5, 0.5);
	model.setRotation(0, 90, 1, 0, 0);
	model.setRotation(1, 180, 0, 0, 1);

	float magX = values[4];
	float magY = values[5];
	float magZ = values[6];
	float zRot = std::atan2(magX, magY) * 180 / 3.141592;
	float xRot = std::atan2(magZ, magY) * 180 / 3.141592;

	model.setRotation(2, zRot, 0, 0, 1);
	model.setRotation(3, xRot, 1, 0, 1);

	model.setPosition(ofGetWidth() / 2, ofGetHeight() / 2, 0);

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

	// draw current csv row at the bottom of the screen 
	ofSetColor(255, 255, 255);
	stringstream dataOverlay;
	dataOverlay.precision(2);

	for (int i = 0; i < this->headers.size(); i++) {
		//cout << this->headers.at(i) << ": " << this->values.at(i) << endl;
		dataOverlay << this->headers.at(i) << ":\t" << std::fixed << this->values.at(i) << "\n";
	}

	ofDrawBitmapString(dataOverlay.str(), 20, 20); //(ofGetHeight() - 40));

	ofLogNotice() << " done draw at " << ofGetFrameRate() << endl;
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
