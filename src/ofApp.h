#pragma once

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 1024

#include "ofMain.h"
#include "WavPlayer.h"

class ofApp : public ofBaseApp{

	public:
    void setup();
    void setup_w2();
    void setup_w3();
    void setup_w4();
    void setup_w5();
    void setup_w6();
    
    void update();
    void draw();
    void draw_w2(ofEventArgs & args);
    void draw_w3(ofEventArgs & args);
    void draw_w4(ofEventArgs & args);
    void draw_w5(ofEventArgs & args);
    void draw_w6(ofEventArgs & args);

    void keyPressed(int key);
//    void keyReleased(int key);
//    void mouseMoved(int x, int y );
//    void mouseDragged(int x, int y, int button);
//    void mousePressed(int x, int y, int button);
//    void mouseReleased(int x, int y, int button);
//    void mouseEntered(int x, int y);
//    void mouseExited(int x, int y);
//    void windowResized(int w, int h);
//    void dragEvent(ofDragInfo dragInfo);
//    void gotMessage(ofMessage msg);
    void audioOut( float * output, int bufferSize, int nChannels );
    void exit();

    ofVideoPlayer video;
    WavPlayer audio;
    ofTexture tex;
    
    bool pauseVideo = true;
};
