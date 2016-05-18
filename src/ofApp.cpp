#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    status = true;  // Show status initially
//    ofSetDataPathRoot("../Resources/data/");

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
    myFont.load("Futura-Medium.ttf", fontSize);
    
    ofSoundStreamSetup(NUM_CHANNELS, 0);
    
    receiver.setup(PORT);
    sender.setup(HOST, PORT);
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
    
    // check for waiting messages
    while( receiver.hasWaitingMessages() )
    {
        // get the next message
        ofxOscMessage m;
        receiver.getNextMessage(&m);
        if (m.getAddress() == "\togglePlay")
        {
            audio.togglePlay();
            pauseVideo = !pauseVideo;
            video.setPaused(pauseVideo);
        }
        if (m.getAddress() == "\reset")
        {
            audio.stop();
            pauseVideo = true;
            video.setPaused(pauseVideo);
            video.setPosition(0);
        }
        if (m.getAddress() == "\toggleMute")
        {
            audio.toggleMute();
        }
        if (m.getAddress() == "\toggleStatus")
        {
            status = !status;
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw() {
    if (status) {
        drawInfo(1);
    }
    else {
        tex.drawSubsection(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, 320, 256);
    }

}


//--------------------------------------------------------------
void ofApp::draw_w2(ofEventArgs & args) {
    if (status) {
        drawInfo(2);
    }
    else {
        tex.drawSubsection(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 320, 0, 320, 256);
    }
}


//--------------------------------------------------------------
void ofApp::draw_w3(ofEventArgs & args) {
    if (status) {
        drawInfo(3);
    }
    else {
        tex.drawSubsection(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 640, 0, 320, 256);
    }

}

//--------------------------------------------------------------
void ofApp::draw_w4(ofEventArgs & args) {
    if (status) {
        drawInfo(4);
    }
    else {
        tex.drawSubsection(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 256, 320, 256);
    }
    
}

//--------------------------------------------------------------
void ofApp::draw_w5(ofEventArgs & args) {
    if (status) {
        drawInfo(5);
    }
    else {
        tex.drawSubsection(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 320, 256, 320, 256);
    }

}

//--------------------------------------------------------------
void ofApp::draw_w6(ofEventArgs & args) {
    if (status) {
        drawInfo(6);
    }
    else {
        tex.drawSubsection(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 640, 256, 320, 256);
    }

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
        ofxOscMessage m;
        m.setAddress("\togglePlay");
        sender.sendMessage( m );
        
        audio.togglePlay();
        pauseVideo = !pauseVideo;
        video.setPaused(pauseVideo);
    }
    // reset and pause video and audio
    if (key == '0') {
        ofxOscMessage m;
        m.setAddress("\reset");
        sender.sendMessage( m );

        audio.stop();
        pauseVideo = true;
        video.setPaused(pauseVideo);
        video.setPosition(0);
    }
    // mute audio
    if (key == 'm')
    {
        ofxOscMessage m;
        m.setAddress("\toggleMute");
        sender.sendMessage( m );
        
        audio.toggleMute();
    }
    if (key == 'w')
    {
        ofxOscMessage m;
        m.setAddress("\toggleStatus");
        sender.sendMessage( m );
        
        status = !status;
    }
    
    if (key == 's') {
        ofxOscMessage m;
        m.setAddress("\test");
        m.addStringArg( "hello" );
        m.addFloatArg( ofGetElapsedTimef() );
        sender.sendMessage( m );
    }
}
//--------------------------------------------------------------

void ofApp::drawInfo(unsigned short wN) {
    int xMargin = 100;
    int yMargin = fontSize*2.0;
    ofBackground(30, 30, 30);

    
    ofPushMatrix();
    ofScale(0.25, 0.25);
    
    // draw window number
    ofSetColor(255, 255, 255);
    myFont.drawString("Window: " + to_string(wN), xMargin, yMargin*1);
    
    // draw play/pause status
    if (pauseVideo) {
        ofSetColor(0, 0, 255);
        myFont.drawString("Paused", xMargin, yMargin*2);
    } else {
        ofSetColor(0, 255, 0);
        myFont.drawString("Playing", xMargin, yMargin*2);
    }
    
    // draw time elapsed status
    TimeStruct dur = audio.getCurrentTime();
    string t_elapsed = "Time elapsed: " + to_string(dur.minutes) + ":" + to_string(dur.seconds);
    ofSetColor(255, 255, 255);
    myFont.drawString(t_elapsed, xMargin, yMargin*3);
    
    // draw mute status
    if (audio.isMuted()) {
        ofSetColor(255, 0, 0);
        myFont.drawString("Muted", xMargin, yMargin*4);
    }
    
    // reset colors so they don't affec video texture
    ofSetColor(255, 255, 255);
    ofPopMatrix();
}
//--------------------------------------------------------------
void ofApp::exit(){
    ofSoundStreamClose();
    if (video.isLoaded()) {
        video.close();
    }
}
