#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetDataPathRoot("../Resources/data/");

    video.load("marc.mp4");
    video.play();
    
    if(!audio.open_file("data/8ChannelTestN.wav"))
    {
        cout << "Error opening file" << endl;
        exit();
    }
    ofSoundStreamSetup(8, 0);
    
    audio.play();

}

void ofApp::setup_w2() {
    
}

void ofApp::setup_w3() {
    
}

void ofApp::setup_w4() {
    
}

void ofApp::setup_w5() {
    
}

void ofApp::setup_w6() {
    
}

//--------------------------------------------------------------
void ofApp::update(){
    video.update();

}

//--------------------------------------------------------------
void ofApp::draw(){
//    video.draw(0, 0, 400, 300);
//    video.draw(0, 0, 960, 512);
//    unsigned char* pixels = video.getPixels();
    
    ofTexture& tex = video.getTexture();
    
    tex.drawSubsection(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, 320, 256);
    
//    tex.bind();
//    glBegin(GL_QUADS);
//    glTexCoord2f(0.0f, 0.0f); glVertex2f(0.0f,0.0f);
//    glTexCoord2f(0.33f, 0.0f); glVertex2f(320.0f,0.0f);
//    glTexCoord2f(0.33f, 0.5f); glVertex2f(320.0f,256.0f);
//    glTexCoord2f(0.0f, 0.5f); glVertex2f(0.0f,256.0f);
//    glEnd();
//    tex.unbind();  
    
}

void ofApp::draw_w2(ofEventArgs & args){
    ofTexture& tex = video.getTexture();
    
    tex.drawSubsection(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 320, 0, 320, 256);

    
//    tex.bind();
//    glBegin(GL_QUADS);
//    glTexCoord2f(0.33f, 0.0f); glVertex2f(0.0f,0.0f);
//    glTexCoord2f(0.66f, 0.0f); glVertex2f(320.0f,0.0f);
//    glTexCoord2f(0.66f, 0.5f); glVertex2f(320.0f,256.0f);
//    glTexCoord2f(0.33f, 0.5f); glVertex2f(0.0f,256.0f);
//    glEnd();
//    tex.unbind();
}

void ofApp::draw_w3(ofEventArgs & args){
    ofTexture& tex = video.getTexture();
    tex.drawSubsection(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 640, 0, 320, 256);

//    tex.bind();
//    glBegin(GL_QUADS);
//    glTexCoord2f(0.66f, 0.0f); glVertex2f(0.0f,0.0f);
//    glTexCoord2f(1.0f, 0.0f); glVertex2f(320.0f,0.0f);
//    glTexCoord2f(1.0f, 0.5f); glVertex2f(320.0f,256.0f);
//    glTexCoord2f(0.66f, 0.5f); glVertex2f(0.0f,256.0f);
//    glEnd();
//    tex.unbind();
}
void ofApp::draw_w4(ofEventArgs & args){
    ofTexture& tex = video.getTexture();
    tex.drawSubsection(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 256, 320, 256);
    
//    tex.bind();
//    glBegin(GL_QUADS);
//    glTexCoord2f(0.0f, 0.5f); glVertex2f(0.0f,0.0f);
//    glTexCoord2f(0.33f, 0.5f); glVertex2f(320.0f,0.0f);
//    glTexCoord2f(0.66f, 1.0f); glVertex2f(320.0f,256.0f);
//    glTexCoord2f(0.0f, 1.0f); glVertex2f(0.0f,256.0f);
//    glEnd();
//    tex.unbind();
}
void ofApp::draw_w5(ofEventArgs & args){
    ofTexture& tex = video.getTexture();
    tex.drawSubsection(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 320, 256, 320, 256);

//    tex.bind();
//    glBegin(GL_QUADS);
//    glTexCoord2f(0.33f, 0.5f); glVertex2f(0.0f,0.0f);
//    glTexCoord2f(0.66f, 0.5f); glVertex2f(320.0f,0.0f);
//    glTexCoord2f(0.66f, 1.0f); glVertex2f(320.0f,256.0f);
//    glTexCoord2f(0.33f, 1.0f); glVertex2f(0.0f,256.0f);
//    glEnd();
//    tex.unbind();
}
void ofApp::draw_w6(ofEventArgs & args){
    ofTexture& tex = video.getTexture();
    tex.drawSubsection(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 640, 256, 320, 256);
    
//    tex.bind();
//    glBegin(GL_QUADS);
//    glTexCoord2f(0.66f, 0.5f); glVertex2f(0.0f,0.0f);
//    glTexCoord2f(1.0f, 0.5f); glVertex2f(320.0f,0.0f);
//    glTexCoord2f(1.0f, 1.0f); glVertex2f(320.0f,256.0f);
//    glTexCoord2f(0.66f, 1.0f); glVertex2f(0.0f,256.0f);
//    glEnd();
//    tex.unbind();
}

//--------------------------------------------------------------
void ofApp::audioOut( float * output, int bufferSize, int nChannels ) {
    for (int i=0; i<bufferSize * nChannels; i+=nChannels)
    {
        for (int chan=0; chan<nChannels; chan++)
            {
            output[i+chan] = audio.audiofile.next_sample();
            }
    }
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
