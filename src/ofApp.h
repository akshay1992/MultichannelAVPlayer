#pragma once

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 1024

#define NUM_CHANNELS 1

#include "ofMain.h"
#include "WavPlayer.h"
#include "ofxOsc.h"
#include "ofxGui.h"

#define AKSHAY
//#define MATZE

#ifdef AKSHAY
    #define SEND_PORT 12345
    #define SEND_HOST "matze.local"
    #define RECEIVE_PORT 12334
#endif

#ifdef MATZE
    #define SEND_PORT 12334
    #define SEND_HOST "Akshay.local"
    #define RECEIVE_PORT 12345
#endif

#define SC_SEND 57120
#define SC_HOST "matze.local"

class ofApp : public ofBaseApp{

	public:
    void setup();
    void setup_w2();
    void setup_w3();
    void setup_w4();
    void setup_w5();
    void setup_w6();
    void setup_GUI();
    
    void update();
    void draw();
    void draw_w2(ofEventArgs & args);
    void draw_w3(ofEventArgs & args);
    void draw_w4(ofEventArgs & args);
    void draw_w5(ofEventArgs & args);
    void draw_w6(ofEventArgs & args);
    void draw_GUI(ofEventArgs & args);

    void keyPressed(int key);
    void audioOut( float * output, int bufferSize, int nChannels );
    void drawInfo(unsigned short wN);
    void exit();
    
    void togglePlay();
    void stopPlayback();
    void toggleStatus();
    void skipToVideo(int frame);
    unsigned long audioFrameCounter;
    
    int audioFrame = 0;
    int videoFrame = 0;

    ofxOscSender sender;
    ofxOscReceiver receiver;
    ofxOscSender SC_sender;
    
    ofVideoPlayer video;
    WavPlayer audio;
    ofTexture tex;
    
    ofTrueTypeFont myFont;
    int fontSize = 100;
    
    bool pauseVideo = true;
    bool status = false;
    
    ofxPanel gui;
    ofxFloatSlider sliderValue;
    ofxButton sendSliderValue;
    
};
