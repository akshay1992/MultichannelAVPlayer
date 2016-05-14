#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetDataPathRoot("../Resources/data/");

    video.load("marc.mp4");
    
    // find the absolute path to the audio file 
    string audioPath = ofToDataPath("8ChannelTestN.wav", true);
    if(!audio.open_file(audioPath))
    {
        cout << "Error opening file" << endl;
        exit();
    }
    
    video.play();
    audio.play();
    video.setPaused(pauseVideo);
    audio.togglePlay();
    
    ofSoundStreamSetup(8, 0);
}

//--------------------------------------------------------------
void ofApp::setup_w2() {
    
}

//--------------------------------------------------------------
void ofApp::setup_w3() {
    
}

//--------------------------------------------------------------
void ofApp::setup_w4() {
    
}

//--------------------------------------------------------------
void ofApp::setup_w5() {
    
}

//--------------------------------------------------------------
void ofApp::setup_w6() {
    
}

//--------------------------------------------------------------
void ofApp::update(){
    video.update();
    tex = video.getTexture();
}

//--------------------------------------------------------------
void ofApp::draw() {
    tex.allocate(video.getPixels());
    tex.drawSubsection(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, 320, 256);
}


//--------------------------------------------------------------
void ofApp::draw_w2(ofEventArgs & args) {
    tex.drawSubsection(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 320, 0, 320, 256);
}


//--------------------------------------------------------------
void ofApp::draw_w3(ofEventArgs & args) {
    tex.drawSubsection(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 640, 0, 320, 256);

}

//--------------------------------------------------------------
void ofApp::draw_w4(ofEventArgs & args) {
    tex.drawSubsection(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 256, 320, 256);
    
}

//--------------------------------------------------------------
void ofApp::draw_w5(ofEventArgs & args) {
    tex.drawSubsection(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 320, 256, 320, 256);

}

//--------------------------------------------------------------
void ofApp::draw_w6(ofEventArgs & args) {
    tex.drawSubsection(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 640, 256, 320, 256);

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
    // pause video and audio
    if (key == ' ') {
        audio.togglePlay();
        pauseVideo = !pauseVideo;
        video.setPaused(pauseVideo);
    }
    // reset and pause video and audio
    if (key == '0') {
        audio.stop();
        pauseVideo = true;
        video.setPaused(pauseVideo);
        video.setPosition(0);
    }
    // mute audio
    if (key == 'm')
        audio.toggleMute();
}

//--------------------------------------------------------------
void ofApp::exit(){
    ofSoundStreamClose();
}
