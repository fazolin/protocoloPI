#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(60);
    font.load("monoMMM_5", 64);
    img.load("bikers.jpg");
    
    // 2 output channels,
    // 0 input channels
    // 22050 samples per second
    // 512 samples per buffer
    // 4 num buffers (latency)
    
    int bufferSize		= 512;
    sampleRate 			= 44100;
    phase 				= 0;
    phaseAdder 			= 0.0f;
    phaseAdderTarget 	= 0.0f;
    volume				= 0.1f;
    bNoise 				= false;
    
    lAudio.assign(bufferSize, 0.0);
    rAudio.assign(bufferSize, 0.0);
    
    soundStream.printDeviceList();
    
    //if you want to set the device id to be different than the default
    //soundStream.setDeviceID(1); 	//note some devices are input only and some are output only
    
    soundStream.setup(this, 2, 0, sampleRate, bufferSize, 4);
    
    // on OSX: if you want to use ofSoundPlayer together with ofSoundStream you need to synchronize buffersizes.
    // use ofFmodSetBuffersize(bufferSize) to set the buffersize in fmodx prior to loading a file.


}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    ofSetColor(r,g,b);
    ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
    ofSetColor(255);
    //ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    font.drawString(texto,ofGetWidth()/2,ofGetHeight()/2);
    ofEnableBlendMode(OF_BLENDMODE_MULTIPLY);
    img.draw(0, 0,ofGetWidth(),ofGetHeight());


}

void ofApp::audioOut(float * output, int bufferSize, int nChannels){
    
    
    // sin (n) seems to have trouble when n is very large, so we
    // keep phase in the range of 0-TWO_PI like this:
    //    while (phase > TWO_PI){
    //        phase -= TWO_PI;
    //    }
    
    if ( bNoise == true){
        // ---------------------- noise --------------
        for (int i = 0; i < bufferSize; i++){
            output[i*nChannels    ] = ofRandom(-1, 1) * volume ;
            output[i*nChannels + 1] = ofRandom(-1, 1) * volume ;
        }
    } else {
        
        
        for(int i = 0; i < bufferSize * nChannels; i += 2) {
            float sample = sin(phase);
            output[i] = sample>0?1:-1;; // writing to the left channel
            output[i+1] = sample>0?1:-1; // writing to the right channel
            phase += freq;
            
            
            //                    //sine wave
            //                    samples[i]=sin(a);
            //                    //square wave
            //                    samples[i]=sin(a)>0?1:-1;
            //                    //saw wave
            //                    samples[i]=fmod(i,TWO_PI);
            
            
        }
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case '1': // silencio
            r = 0;
            g = 0;
            b = 0;
            texto = " ";
            bNoise = false;
            freq = 0;
            break;
        case '2':
            r = 255;
            g = 0;
            b = 0;
            texto = ofToString(ofRandom(1000));
            bNoise = true;
            break;
        case '3':
            r = 0;
            g = 255;
            b = 0;
            texto = ofToString(ofRandom(1000));
            bNoise = false;
            freq = ofRandom(.005,.01);
            break;
        case '4':
            r = 0;
            g = 0;
            b = 255;
            texto = ofToString(ofRandom(1000));
            bNoise = false;
            freq = ofRandom(.04,.06);
            break;
        case '5':
            r = 255;
            g = 255;
            b = 0;
            texto = ofToString(ofRandom(1000));
            bNoise = false;
            freq = ofRandom(.06,.08);
            break;
        case '6': // silencio
            r = 255;
            g = 0;
            b = 255;
            texto = ofToString(ofRandom(1000));
            bNoise = false;
            freq = ofRandom(.08,.1);
            break;
            
        default:
            r = 0;
            g = 0;
            b = 0;
            texto = " ";
            bNoise = false;
            break;
    }

}



//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
;

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
