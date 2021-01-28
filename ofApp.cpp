#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);

	this->font.loadFont("fonts/Kazesawa-Bold.ttf", 180, true, true, true);
	this->fbo1.allocate(ofGetWidth(), ofGetHeight());
	this->fbo2.allocate(ofGetWidth(), ofGetHeight());
	this->shader.load("shader/shader.vert", "shader/shader.frag");
}

//--------------------------------------------------------------
void ofApp::update() {

	this->fbo1.begin();
	ofClear(0);
	ofSetColor(39);

	vector<string> word_list = {
		"over",
		"15  5",
		"days"
	};

	vector<glm::vec2> base_location_list = {
		glm::vec2(ofGetWidth() * 0.5 - this->font.stringWidth(word_list[0]) * 0.5, ofGetHeight() * 0.5 - 150),
		glm::vec2(ofGetWidth() * 0.5 - this->font.stringWidth(word_list[1]) * 0.5, ofGetHeight() * 0.5 + 60),
		glm::vec2(ofGetWidth() * 0.5 - this->font.stringWidth(word_list[2]) * 0.5, ofGetHeight() * 0.5 + 270)
	};

	this->font.drawString(word_list[0], base_location_list[0].x, base_location_list[0].y);
	this->font.drawString(word_list[1], base_location_list[1].x, base_location_list[1].y);
	this->font.drawString(word_list[2], base_location_list[2].x, base_location_list[2].y);

	this->fbo1.end();

	this->fbo2.begin();
	ofClear(0);
	ofSetColor(39);

	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);

	int radius = 30;

	ofFill();
	ofDrawCircle(glm::vec2(ofGetWidth() * 0.1, 0), radius);

	auto deg_span = 15;
	for (auto deg_start = ofGetFrameNum() * 0.2; deg_start <= ofGetFrameNum() * 0.5 + 360; deg_start += deg_span * 2) {

		vector<glm::vec2> vertices_1, vertices_2;
		for (auto deg = deg_start; deg <= deg_start + deg_span; deg++) {

			vertices_1.push_back(glm::vec2((radius + 10) * cos(deg * DEG_TO_RAD) + ofGetWidth() * 0.1, (radius + 10) * sin(deg * DEG_TO_RAD)));
			vertices_2.push_back(glm::vec2((radius * 14) * cos(deg * DEG_TO_RAD) + ofGetWidth() * 0.1, (radius * 14) * sin(deg * DEG_TO_RAD)));
		}

		reverse(vertices_2.begin(), vertices_2.end());

		ofBeginShape();
		ofVertices(vertices_1);
		ofVertices(vertices_2);
		ofEndShape(true);
	}
	
	this->fbo2.end();
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofSetColor(255);
	ofFill();
	this->shader.begin();
	this->shader.setUniform1f("time", ofGetElapsedTimef());
	this->shader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
	this->shader.setUniformTexture("tex1", this->fbo1.getTexture(), 1);
	this->shader.setUniformTexture("tex2", this->fbo2.getTexture(), 2);

	ofDrawRectangle(glm::vec2(0, 0), ofGetWidth(), ofGetHeight());

	this->shader.end();
}

//--------------------------------------------------------------
int main() {

	ofGLWindowSettings settings;
	settings.setGLVersion(3, 2);
	settings.setSize(720, 720);
	ofCreateWindow(settings);
	ofRunApp(new ofApp());
}