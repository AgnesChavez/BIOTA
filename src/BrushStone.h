#pragma once

#include "ofMain.h"

#include "BrushCollection.h"
#include "ColorCollection.h"
#include "ofxConvexHull.h"
#include "ofxCv/ContourFinder.h"

class BrushStone
{
public:
    BrushStone();
    ~BrushStone();
    void init(float _x, float _y);
    void draw(float x, float y, float w, float h);
    void clear();
    void calcBorder(std::vector<ofPoint> poi);
    void renderBorder();

    void grow(ofPolyline line);
    bool grow();
    void grow(int brushIndex);
    void grow(ofPolyline line, ofVec2f center);
    bool growForWaterColor(float rad);
    void growPlain(int brushId);

    void shrink();

    void setRadius(float rad);
    void setFuzzy(float fuzzy);
    void setSize(int size);
    float getRadius();
    float getFuzzy();
    int getNumberOfCircles();
    void setTransparency(float _trans);
    float getTransparency();
    void setBorderTransparency(float _trans);
    void setBorderSize(int _bsize);
    int getBorderSize();
    void setSaturation(float _sat);
    float getSaturation();

    ofFbo getStoneBuffer();

    void setBrushStrokeCount(int count);
    int getBrushStrokeCount();
    void setBrushStrokeSizeMin(float min);
    float getBrushStrokeSizeMin();
    void setBrushStrokeSizeMax(float max);
    float getBrushStrokeSizeMax();
    void setBrushStrokeAlpha(float alpha);
    float getBrushStrokeAlpha();

    void setSelectedColor(ofColor col);
    void setStoneCircleBackgroundColor(ofColor col);

    void setMaxGrowRad(float maxRad);

    void setBrushCollection(BrushCollection _b);
    void setColorCollection(ColorCollection _c);

    void toggleRenderBorder(bool _b);
    void toggleDrawStone(bool _s);

    std::vector<ofPoint> getContourPoints(float x, float y);

    static vector<ofVec3f> resamplePolylineToCount(const ofPolyline& polyline,
                                                   int n);
    float currentGrowRad;
    ofVec2f centroid;
    ofPolyline border;

    int speed = 1;
    float maxGrowRad;
    float maxCircleSize;
    float growRadIncrease = 2.75;

    float spacingSine = 0, speedSine = 1, sizeMinSine = 2, sizeMaxSine = 3;

private:
    float radius, fuzzy;
    int size;
    float transparency, borderTransparency, saturation;
    int borderSize;

    bool tDrawBorder;
    bool tDrawStone;
    ofColor selectedColor;
    ofColor stoneCircleBackgroundColor;

    int getNumberOfStrokes();

    std::vector<ofPoint> locationsPointsDrawn;
    ofxConvexHull convexHull;

    int bufferWidth, bufferHeight;
    ofFbo layer;
    BrushCollection brushes;
    ColorCollection colors;
    int brushStokeCount;
    float brushStrokeSizeMin, brushStrokeSizeMax;
    float brushStrokeAlpha;

    ofFbo tempFbo;
    ofxCv::ContourFinder contourFinder;
    std::vector<ofPoint> contourPoints;
};
