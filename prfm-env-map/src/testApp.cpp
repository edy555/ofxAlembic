#include "testApp.h"

#include "ofxAlembic.h"

ofEasyCam cam;

ofxAlembic::Reader abc;

//--------------------------------------------------------------
void testApp::setup()
{
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	ofBackground(32);
	glEnable(GL_DEPTH_TEST);
	
	string path = "perfume_global_site_003_sequence.abc";
	
	// load allembic file
	abc.open(path);
	
	// show all drawable names
	abc.dumpNames();

    // specular color, the highlight/shininess color //
	pointLight.setSpecularColor( ofColor(255.f, 255.f, 255.f));
    pointLight.setPosition(0, -100, 100);
    material.setShininess( 64 );
    
    ofDisableArbTex();
    //ofEnableNormalizedTexCoords();

    image.loadImage("cvsphere.rgb");
    texture = image.getTextureReference();
    textureData = texture.getTextureData();
    
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
}

void testApp::exit()
{
	abc.close();
}

//--------------------------------------------------------------
void testApp::update()
{
	float t = fmodf(ofGetElapsedTimef(), abc.getMaxTime());
	
	// update alemblic reader with time in sec
	abc.setTime(t);
}

//--------------------------------------------------------------
void testApp::draw()
{
    //ofEnableLighting();
    // the position of the light must be updated every frame,
    // call enable() so that it can update itself //
    pointLight.enable();
    material.begin();

	cam.begin();

	//glPointSize(4);
    
    texture.bind();
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
	// get meshes and draw
	{
        //gluSphere(quadratic, 100.0, 20, 20);
		ofMesh mesh;
		abc.get("/Aa-CHAN")->get(mesh);
		ofSetColor(192, 192, 255);
		mesh.draw();
	}
	{
		ofMesh mesh;
		abc.get("/KASHIYUKA")->get(mesh);
		ofSetColor(255, 192, 192);
		mesh.draw();
	}
	{
		ofMesh mesh;
		abc.get("/NOCCHi")->get(mesh);
		ofSetColor(255, 255, 255);
		mesh.draw();
	}
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
    texture.unbind();

	// or simply, abc.draw();

	cam.end();
	material.end();
	// turn off lighting //
    ofDisableLighting();
	
	ofSetColor(255);
	
	ofDrawBitmapString(ofToString(abc.getTime()) + "/" + ofToString(abc.getMaxTime()), 10, 20);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key)
{
	
}

//--------------------------------------------------------------
void testApp::keyReleased(int key)
{

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y)
{

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h)
{

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg)
{

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo)
{

}