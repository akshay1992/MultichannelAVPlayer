#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    status = true;  // Show status initially
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
        receiver.getNextMessage( &m );
        
        // check for mouse moved message
        if ( m.getAddress() == "/mouse/position" )
        {
            // both the arguments are int32's
            mouseX = m.getArgAsInt32( 0 );
            mouseY = m.getArgAsInt32( 1 );
        }
        // check for mouse button message
        else if ( m.getAddress() == "/mouse/button" )
        {
            // the single argument is a string
//            mouseButtonState = m.getArgAsString( 0 ) ;
        }
        else
        {
            // unrecognized message: display on the bottom of the screen
            string msg_string;
            msg_string = m.getAddress();
            msg_string += ": ";
            for ( int i=0; i<m.getNumArgs(); i++ )
            {
                // get the argument type
                msg_string += m.getArgTypeName( i );
                msg_string += ":";
                // display the argument - make sure we get the right type
                if( m.getArgType( i ) == OFXOSC_TYPE_INT32 )
                    msg_string += ofToString( m.getArgAsInt32( i ) );
                else if( m.getArgType( i ) == OFXOSC_TYPE_FLOAT )
                    msg_string += ofToString( m.getArgAsFloat( i ) );
                else if( m.getArgType( i ) == OFXOSC_TYPE_STRING )
                    msg_string += m.getArgAsString( i );
                else
                    msg_string += "unknown";
            }
            // add to the list of strings to display
//            msg_strings[current_msg_string] = msg_string;
//            timers[current_msg_string] = ofGetElapsedTimef() + 5.0f;
//            current_msg_string = ( current_msg_string + 1 ) % NUM_MSG_STRINGS;
//            // clear the next line
//            msg_strings[current_msg_string] = "";
        }
        
    }
}

//--------------------------------------------------------------
void ofApp::draw() {
    if (status) {
        drawInfo(1);
    }
    else {
        tex.allocate(video.getPixels());
        tex.drawSubsection(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, 320, 256);
    }
    
    string buf;
    buf = "listening for osc messages on port" + ofToString( PORT );
    ofDrawBitmapString( buf, 10, 20 );
    
    // draw mouse state
    buf = "mouse: " + ofToString( mouseX, 4) +  " " + ofToString( mouseY, 4 );
    ofDrawBitmapString( buf, 430, 20 );
    ofDrawBitmapString( mouseButtonState, 580, 20 );
    
    for ( int i=0; i<NUM_MSG_STRINGS; i++ )
    {
        ofDrawBitmapString( msg_strings[i], 10, 40+15*i );
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
    if (key == 'w')
        status = !status;
    
    if (key == 's') {
        ofxOscMessage m;
        m.setAddress("\test");
        m.addIntArg( 1 );
        m.addFloatArg( 3.5f );
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
