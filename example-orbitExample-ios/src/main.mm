#include "ofMain.h"
#include "testApp.h"

int main(){
#if 0
    ofSetupOpenGL(1024,768, OF_FULLSCREEN);         // <-------- setup the GL context

    ofRunApp(new testApp);
#else
    ofAppiPhoneWindow * window = new ofAppiPhoneWindow();
    window->enableDepthBuffer();
    ofSetupOpenGL(window, 1024, 768, OF_FULLSCREEN);
    ofRunApp(new testApp);
#endif
}
