#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class minimal01App : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
    
    void drawFullCircle(int resolution, float radius, float rotation, vec2 center);
    void drawFullCircle2(int resolution, float radiusA, float radiusB, float rotation, vec2 center);

private:
    int mCircleRes;
};

void minimal01App::setup()
{
    mCircleRes = 60;
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
}
//! Draws lines inside a circle frome the center
void minimal01App::drawFullCircle(int resolution, float radius, float rotation, vec2 center)
{
    gl::begin(GL_LINES);
    
    
    for (int i=0; i<resolution; ++i) {
        
        float angle = (float)i * 2.0f * M_PI_2/(float)resolution;
        
        vec2 position = vec2(cos(angle+toRadians(rotation)) * radius, sin(angle+toRadians(rotation)) * radius);
        
        position += center;
        
        gl::vertex(position);
        
        float angle2 = (float)i * 2.0f * M_PI_2/(float)resolution;
        
        vec2 position2 = vec2( (cos(angle2+M_PI+toRadians(rotation))) * radius, (sin(angle2+M_PI+toRadians(rotation))) * radius);
        
        position2 += center;
        
        gl::vertex(position2);
        
        //        gl::drawLine(position, position2);
        
    }
    gl::end();
}
//! Draws lines inside a circle frome the a second circle of radius radiusA
void minimal01App::drawFullCircle2(int resolution, float radiusA, float radiusB, float rotation, vec2 center)
{
    gl::begin(GL_LINES);
    
    for (int i=0; i<resolution; ++i) {
        
        float angle = (float)i * 2.0f * M_PI/(float)resolution;
        
        vec2 position = vec2(cos(angle+toRadians(rotation)) * radiusA, sin(angle+toRadians(rotation)) * radiusA);
        
        position += center;
        
        gl::color(0.0, 0.0, 0.0,1.0);
        gl::vertex(position);
        
        float angle2 = (float)i * 2.0f * M_PI/(float)resolution;
        
        vec2 position2 = vec2( (cos(angle2+toRadians(rotation))) * radiusB, (sin(angle2+toRadians(rotation))) * radiusB);
        
        position2 += center;
        
        gl::color(1.0, 0.743, 0.0,1.0);
        gl::vertex(position2);
        
    }
    gl::end();
}

void minimal01App::mouseDown( MouseEvent event )
{
}

void minimal01App::update()
{
}

void minimal01App::draw()
{
	gl::clear( Color( 0, 0, 0 ) );
    gl::clear( Color( 0, 0, 0 ) );
    gl::color(1.0, 1.0, 1.0,1.0);
    
    //    gl::ScopedBlendAlpha alpha;
    
    float radius = getWindowHeight()*0.5f-10.0;
    
    //    gl::color(1.0, 0.843, 0.0,1.0);
    //    drawFullCircle2(mResolution, radius, radius*0.05, 0.0, getWindowCenter()+vec2(sin(getElapsedSeconds())*3.0f,0.0) );
    //    drawFullCircle2(mResolution, radius, radius*0.05, 0.0, getWindowCenter()+vec2(cos(getElapsedSeconds())*3.0f,0.0) );
    //
    
    drawFullCircle(mCircleRes, radius, -toRadians(getElapsedFrames()*1.2), getWindowCenter()+vec2(0.0f,cos(getElapsedFrames()*0.05)*6.0) );
    drawFullCircle(mCircleRes, radius, toRadians(getElapsedFrames()*1.2), getWindowCenter());
    
    gl::color(0.0, 0.0, 0.0,1.0);
    gl::drawSolidCircle(getWindowCenter(), radius*0.051);
    
    gl::color(1.0,1.0,1.0,1.0);
    gl::drawSolidCircle(getWindowCenter(), radius*0.005);
    gl::drawSolidCircle(getWindowCenter()+vec2(sin(getElapsedFrames()*0.015f)*radius*0.05,0.0), radius*0.002);
    gl::drawSolidCircle(getWindowCenter()+vec2(-sin(getElapsedFrames()*0.015f)*radius*0.05,0.0), radius*0.002);
}

CINDER_APP( minimal01App, RendererGl(RendererGl::Options().msaa(8)), [&](App::Settings *settings) {
    
    settings->setFullScreen(true);
    
    settings->setHighDensityDisplayEnabled();
})
