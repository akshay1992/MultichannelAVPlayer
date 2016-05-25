#include "ofApp.h"

bool readSample;

//--------------------------------------------------------------
void ofApp::setup(){
    status = true;  // Show status initially
//    ofSetDataPathRoot("../Resources/data/");

    video.load("berlioz_lossless.mp4");
    
    // find the absolute path to the audio file 
    string audioPath = ofToDataPath("BERLIOZ_REF_MONO.wav", true);
    if(!audio.open_file(audioPath))
    {
        cout << "Error opening file" << endl;
        exit();
    }
    
    video.setLoopState(OF_LOOP_NONE);
    video.play();
    audio.play();
    video.setPaused(pauseVideo);
    audio.togglePlay();
    myFont.load("Futura-Medium.ttf", fontSize);
    
    ofSoundStreamSetup(NUM_CHANNELS, 0);
    
    receiver.setup(RECEIVE_PORT);
    sender.setup(SEND_HOST, SEND_PORT);
    SC_sender.setup(SC_HOST, SC_SEND);

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

void ofApp::setup_GUI() {
    gui.setup();
    gui.add(sliderValue.setup("playHead", 0, 0, 1));
    gui.add(sendSliderValue.setup("send slider value"));
}

//--------------------------------------------------------------
void ofApp::togglePlay() {
    audio.togglePlay();
    pauseVideo = !pauseVideo;
    video.setPaused(pauseVideo);
}

//--------------------------------------------------------------
void ofApp::stopPlayback() {
    audio.stop();
    pauseVideo = true;
    video.setPaused(pauseVideo);
    video.setPosition(0);
}

//--------------------------------------------------------------
void ofApp::toggleStatus() {
    status = !status;
}

//--------------------------------------------------------------
void ofApp::skipToVideo(int frame) {
    audio.stop();
    pauseVideo = true;
    video.setPaused(pauseVideo);
    video.setFrame(frame);
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
        if (m.getAddress() == "/togglePlay")
        {
            togglePlay();
        }
        if (m.getAddress() == "/reset")
        {
            stopPlayback();
        }
        if (m.getAddress() == "/toggleMute")
        {
            audio.toggleMute();
        }
        if (m.getAddress() == "/toggleStatus")
        {
            toggleStatus();
        }
        if (m.getAddress() == "/skipTo")
        {
            skipToVideo(m.getArgAsInt(0));
            audio.audiofile.skip_to(audioFrame);
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
void ofApp::draw_GUI(ofEventArgs & args) {
    gui.draw();
    
    if (sendSliderValue) {
        ofxOscMessage m, SC_m;
        m.setAddress("/skipTo");
        SC_m.setAddress("/skipTo");
        audioFrame = sliderValue*audio.audiofile.getNSamples();
        videoFrame = sliderValue*video.getTotalNumFrames();
        m.addIntArg(videoFrame);
        SC_m.addIntArg(audioFrame);
        sender.sendMessage(m);
        SC_sender.sendMessage(SC_m);
        
        stopPlayback();
    }
}

//--------------------------------------------------------------
void ofApp::audioOut( float * output, int bufferSize, int nChannels ) {
    
    
    
    for (int i=0; i<bufferSize * nChannels; i+=nChannels)
    {
        ++audioFrameCounter;
        audio.audiofile.next_sample();

    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    // pause video and audio
    if (key == ' ') {
        togglePlay();
        ofxOscMessage m, SC_m;
        m.setAddress("/togglePlay");
        SC_m.setAddress("/togglePlay");
        SC_m.addIntArg(audio.isPlaying());
        sender.sendMessage( m );
        SC_sender.sendMessage( SC_m );

    }
    // reset and pause video and audio
    if (key == '0') {
        ofxOscMessage m, SC_m;
        m.setAddress("/reset");
        SC_m.setAddress("/reset");
        SC_m.addIntArg(0);
        sender.sendMessage( m );
        SC_sender.sendMessage( SC_m );
        
        stopPlayback();
    }
    // mute audio
    if (key == 'm')
    {
        ofxOscMessage m, SC_m;
        m.setAddress("/toggleMute");
        SC_m.setAddress("/toggleMute");
        SC_m.addIntArg(audio.isMuted());
        sender.sendMessage( m );
        SC_sender.sendMessage( SC_m );
        
        audio.toggleMute();
    }
    if (key == 'w')
    {
        ofxOscMessage m;
        m.setAddress("/toggleStatus");
        sender.sendMessage( m );
        
        toggleStatus();
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
