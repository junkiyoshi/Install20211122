#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofSetColor(255);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->mesh.clear();

	for (float x = -0.25; x <= 0.25; x += 0.25) {

		for (float y = -0.33; y <= 0.33; y += 0.33) {

			this->set_three(glm::vec3(x * ofGetWidth(), y * ofGetHeight(), 0), 7000, 23);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	this->mesh.drawVertices();

	this->cam.end();
}

//--------------------------------------------------------------
void ofApp::set_three(glm::vec3 location, int number_of_loop, float scale) {

	glm::vec3 point, prev_point;
	for (int i = 0; i < number_of_loop; i++) {

		float p = ofRandom(100);
		if (p < 1) {

			point.x = 0 * prev_point.x + 0 * prev_point.y + 0;
			point.y = 0 * prev_point.x + 0.16 * prev_point.y + 0;
		}
		else if (p < 8) {

			point.x = 0.2 * prev_point.x + -0.26 * prev_point.y + 0.0;
			point.y = 0.23 * prev_point.x + 0.22 * prev_point.y + 1.6;
		}
		else if (p < 15) {

			point.x = -0.15 * prev_point.x + 0.28 * prev_point.y + 0.0;
			point.y = 0.26 * prev_point.x + 0.24 * prev_point.y + 0.44;
		}
		else {

			point.x = 0.85 * prev_point.x + 0.04 * prev_point.y + 0.0;
			point.y = -0.04 * prev_point.x + 0.85 * prev_point.y + 1.5;
		}
		
		auto noise_value = ofNoise(glm::vec2((location.x + point.x) * 0.01, (location.y + point.y) * 0.1 + ofGetFrameNum() * 0.0035));

		if (noise_value < 0.35) {

			noise_value = 0;
		}
		else if(noise_value < 0.75) {

			noise_value = ofMap(noise_value, 0.35, 0.75, 0, 1);
		}
		else {

			noise_value = 1;
		}

		auto rotation_x = glm::rotate(glm::mat4(), ofMap(noise_value, 0, 1, -360, 360) * (float)DEG_TO_RAD, glm::vec3(0, 1, 0));
		auto vertex = glm::vec4(point, 0) * rotation_x;

		this->mesh.addVertex(location + vertex * scale);
		prev_point = point;
	}
	
}


//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}