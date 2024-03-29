﻿#include "BrushStone.h"

#include "Misc.h"

BrushStone::BrushStone()
{
    setFuzzy(10.0f);
    setRadius(40.0f);
    setSize(60);
    transparency = 255;
    borderTransparency = 255;
    brushStokeCount = 50;
    brushStrokeSizeMin = 20;
    brushStrokeSizeMax = 100;
    brushStrokeAlpha = 255;
    saturation = 255;

    borderSize = 30;

    selectedColor = ofColor(255, 255, 255);

    bufferWidth = 1920;
    bufferHeight = 1080;

    tDrawStone = true;
    tDrawBorder = false;

    maxGrowRad = 700;

    layer.allocate(Misc::getDefaultFboSettings());
    // underlyingLayer.allocate( settings );
}

BrushStone::~BrushStone()
{
}

void BrushStone::clear()
{
    layer.begin();
    ofClear(0.0, 0.0, 0.0, 1.0);
    layer.end();

    // underlyingLayer.begin();
    // ofClear( 255, 255, 255, 0 );
    // underlyingLayer.end();

    locationsPointsDrawn.clear();
    contourPoints.clear();

    currentGrowRad = 5;

    setFuzzy(10.0f);
    setRadius(40.0f);
    setSize(60);
    transparency = 255;
    borderTransparency = 255;
    brushStokeCount = 50;
    brushStrokeSizeMin = 20;
    brushStrokeSizeMax = 100;
    brushStrokeAlpha = 255;
    saturation = 255;

    borderSize = 30;

    selectedColor = ofColor(255, 255, 255);
}

void BrushStone::init(float _x, float _y)
{
    layer.begin();
    ofClear(255, 255, 255, 0);
    layer.end();

    // underlyingLayer.begin();
    // ofClear( 255, 255, 255, 0 );
    // underlyingLayer.end();

    centroid = ofPoint(_x, _y);

    currentGrowRad = 5;

    setFuzzy(10.0f);
    setRadius(40.0f);
    setSize(60);
    transparency = 255;
    borderTransparency = 255;
    brushStokeCount = 50;
    brushStrokeSizeMin = 20;
    brushStrokeSizeMax = 100;
    brushStrokeAlpha = 250;
    saturation = 255;

    borderSize = 30;

    selectedColor = ofColor(0, 0, 0);
}

void BrushStone::draw(float x, float y, float w, float h)
{
    spacingSine += ofRandom(0.001, 0.01);

    speedSine += ofRandom(0.001, 0.01);
    sizeMinSine += ofRandom(0.001, 0.01);
    sizeMaxSine += ofRandom(0.001, 0.01);

    ofPushStyle();
    ofEnableAlphaBlending();

    if (tDrawStone)
    {
        ofFill();
        ofSetColor(stoneCircleBackgroundColor);
        ofDrawCircle(centroid.x, centroid.y, min(currentGrowRad, maxCircleSize));
        ofSetColor(selectedColor, transparency);
        layer.draw(x, y, w, h);
    }
    // if( tDrawBorder ) {
    //	ofSetColor( selectedColor, borderTransparency );
    //	underlyingLayer.draw( x, y, w, h );
    //}
    ofPopStyle();
}

void BrushStone::grow(ofPolyline line)
{
    if (currentGrowRad < maxGrowRad)
    {
        currentGrowRad += 0.5f;

        layer.begin();

        int nrToCheck = (int)(ofMap(currentGrowRad, 0, maxGrowRad, 5, 15));
        ofPushStyle();
        ofEnableAlphaBlending();
        std::vector<ofVec2f> pointsToDraw(nrToCheck);
        // decide here weather to grow the stone from the centroid of the outline,
        // or from the actual voronoi cell core
        ofVec2f p = line.getCentroid2D(); // centroid
#pragma omp parallel for
        for (int i = 0; i < nrToCheck; i++)
        {
            float deg = ofRandom(0, TWO_PI);
            float _x = currentGrowRad * cos(deg);
            float _y = currentGrowRad * sin(deg);
            // int randomId = ofRandom( 0, points.size() );

            ofVec2f pToSave = p + ofVec2f(_x, _y);
            pointsToDraw.at(i) = pToSave;
        }

        ofPolyline lineToCheck = line.getResampledBySpacing(50);
        std::vector<ofPoint> tempLocationsDrawn(nrToCheck);

        // checking parallelized for overlapping
#pragma omp parallel for
        for (int i = 0; i < pointsToDraw.size(); i++)
        {
            ofVec2f p = pointsToDraw.at(i);
            ofRectangle bb = lineToCheck.getBoundingBox();
            // first check for bounding box inside as its quicker to compute
            if (bb.inside(p))
            {
                if (lineToCheck.inside(p.x, p.y))
                {
                    tempLocationsDrawn.at(i) = ofPoint(p.x, p.y);
                }
            }
        }

        // removing vectors at around location 0, 0
        vector<ofPoint>::iterator it = tempLocationsDrawn.begin();
        for (; it != tempLocationsDrawn.end();)
        {
            ofPoint* _p = &(*it);
            if (_p->x < 4 || _p->y < 4)
            {
                it = tempLocationsDrawn.erase(it);
            }
            else
            {
                ++it;
                locationsPointsDrawn.push_back(*_p);
            }
        }

        for (int i = 0; i < tempLocationsDrawn.size(); i++)
        {
            ofVec2f p = tempLocationsDrawn.at(i);
            float s = ofRandom(brushStrokeSizeMin, brushStrokeSizeMax);
            ofSetColor(colors.getRandomColor(), brushStrokeAlpha);
            brushes.getRandomBrush().draw(p.x - s / 2.0, p.y - s / 2.0, s, s);
        }

        ofDisableAlphaBlending();
        ofPopStyle();

        layer.end();

        if (tDrawBorder)
        {
            calcBorder(locationsPointsDrawn);
            renderBorder();
        }
    }
}

bool BrushStone::grow()
{
    currentGrowRad = currentGrowRad + growRadIncrease;
    if (currentGrowRad < maxGrowRad)
    {
        // calcBorder( locationsPointsDrawn );

        // underlyingLayer.begin();
        // ofClear( 1.0 );
        // underlyingLayer.end();

        // renderBorder();

        layer.begin();

        int nrToCheck = (int)(ofMap(currentGrowRad, 0, maxGrowRad, 2, 30));

        ofPushStyle();
        ofEnableAlphaBlending();
        ofEnableBlendMode(OF_BLENDMODE_ADD);
        for (int i = 0; i < nrToCheck; i++)
        {
            float deg = ofRandom(0, TWO_PI);
            float _x = currentGrowRad * cos(deg);
            float _y = currentGrowRad * sin(deg);
            float s = ofRandom(brushStrokeSizeMin, brushStrokeSizeMax);
            // int randomId = ofRandom( 0, points.size() );

            ofVec2f p(centroid);
            // ofVec2f p = getCenterById( randomId );
            p += ofVec2f(_x, _y);

            ofSetColor(255, 255, 255, brushStrokeAlpha);
            locationsPointsDrawn.push_back(ofVec2f(p.x, p.y));
            brushes.getRandomBrush().draw(p.x - s / 2.0, p.y - s / 2.0, s, s);
        }
        ofDisableBlendMode();
        ofDisableAlphaBlending();
        ofPopStyle();

        layer.end();
        return false;
    }
    return true;
}

void BrushStone::grow(int brushIndex)
{
    currentGrowRad = currentGrowRad + 1.0f;
    if (currentGrowRad < maxGrowRad)
    {
        // calcBorder( locationsPointsDrawn );

        // underlyingLayer.begin();
        // ofClear( 1.0 );
        // underlyingLayer.end();

        // renderBorder();

        layer.begin();

        int nrToCheck = (int)(ofMap(currentGrowRad, 0, maxGrowRad, 5, 15));

        ofPushStyle();
        // ofEnableAlphaBlending();
        ofEnableBlendMode(OF_BLENDMODE_ADD);
        for (int i = 0; i < nrToCheck; i++)
        {
            float deg = ofRandom(0, TWO_PI);
            float _x = currentGrowRad * cos(deg);
            float _y = currentGrowRad * sin(deg);
            float s = ofRandom(brushStrokeSizeMin, brushStrokeSizeMax);
            // int randomId = ofRandom( 0, points.size() );

            ofVec2f p(centroid);
            // ofVec2f p = getCenterById( randomId );
            p += ofVec2f(_x, _y);

            ofSetColor(colors.getRandomColor(), brushStrokeAlpha);
            locationsPointsDrawn.push_back(ofVec2f(p.x, p.y));
            brushes.getBrushById(brushIndex).draw(p.x - s / 2.0, p.y - s / 2.0, s, s);
        }
        ofDisableBlendMode();
        // ofDisableAlphaBlending();
        ofPopStyle();

        layer.end();
    }
}

void BrushStone::grow(ofPolyline line, ofVec2f center)
{
    if (currentGrowRad < maxGrowRad)
    {
        currentGrowRad += 0.5f;

        layer.begin();

        int nrToCheck = (int)(ofMap(currentGrowRad, 0, maxGrowRad, 5, 15));
        ofPushStyle();
        ofEnableAlphaBlending();
        std::vector<ofVec2f> pointsToDraw(nrToCheck);
        // decide here weather to grow the stone from the centroid of the outline,
        // or from the actual voronoi cell core
        ofVec2f p = center; // centroid
#pragma omp parallel for
        for (int i = 0; i < nrToCheck; i++)
        {
            float deg = ofRandom(0, TWO_PI);
            float _x = currentGrowRad * cos(deg);
            float _y = currentGrowRad * sin(deg);
            // int randomId = ofRandom( 0, points.size() );

            ofVec2f pToSave = p + ofVec2f(_x, _y);
            pointsToDraw.at(i) = pToSave;
        }

        ofPolyline lineToCheck = line.getResampledBySpacing(50);
        std::vector<ofPoint> tempLocationsDrawn(nrToCheck);

        // checking parallelized for overlapping
#pragma omp parallel for
        for (int i = 0; i < pointsToDraw.size(); i++)
        {
            ofVec2f p = pointsToDraw.at(i);
            ofRectangle bb = lineToCheck.getBoundingBox();
            // first check for bounding box inside as its quicker to compute
            if (bb.inside(p))
            {
                if (lineToCheck.inside(p.x, p.y))
                {
                    tempLocationsDrawn.at(i) = ofPoint(p.x, p.y);
                }
            }
        }

        // removing vectors at around location 0, 0
        vector<ofPoint>::iterator it = tempLocationsDrawn.begin();
        for (; it != tempLocationsDrawn.end();)
        {
            ofPoint* _p = &(*it);
            if (_p->x < 4 || _p->y < 4)
            {
                it = tempLocationsDrawn.erase(it);
            }
            else
            {
                ++it;
                locationsPointsDrawn.push_back(*_p);
            }
        }

        for (int i = 0; i < tempLocationsDrawn.size(); i++)
        {
            ofVec2f p = tempLocationsDrawn.at(i);
            float s = ofRandom(brushStrokeSizeMin, brushStrokeSizeMax);
            ofSetColor(colors.getRandomColor(), brushStrokeAlpha);
            brushes.getRandomBrush().draw(p.x - s / 2.0, p.y - s / 2.0, s, s);
        }

        ofDisableAlphaBlending();
        ofPopStyle();

        layer.end();

        // underlyingLayer.begin();
        // ofClear( 1.0 );
        // underlyingLayer.end();

        if (tDrawBorder)
        {
            calcBorder(locationsPointsDrawn);
            renderBorder();
        }
    }
}

bool BrushStone::growForWaterColor(float rad)
{
    if (rad < maxGrowRad)
    {
        // calcBorder( locationsPointsDrawn );

        // underlyingLayer.begin();
        // ofClear( 1.0 );
        // underlyingLayer.end();

        // renderBorder();

        // experimenting with drawing on water color canvas. if it failed, reuse
        // this layer
        // layer.begin();

        int nrToCheck = (int)(ofMap(rad, 0, maxGrowRad, 5, 15));

        ofPushStyle();
        ofEnableAlphaBlending();
        for (int i = 0; i < nrToCheck; i++)
        {
            float deg = ofRandom(0, TWO_PI);
            float _x = rad * cos(deg);
            float _y = rad * sin(deg);
            float s = ofRandom(brushStrokeSizeMin, brushStrokeSizeMax);
            // int randomId = ofRandom( 0, points.size() );

            ofVec2f p(centroid);
            // ofVec2f p = getCenterById( randomId );
            p += ofVec2f(_x, _y);

            ofSetColor(colors.getRandomColor(), brushStrokeAlpha);
            locationsPointsDrawn.push_back(ofVec2f(p.x, p.y));
            brushes.getRandomBrush().draw(p.x - s / 2.0, p.y - s / 2.0, s, s);
        }
        ofDisableAlphaBlending();
        ofPopStyle();

        // layer.end();

        return true;
    }
    return false;
}

void BrushStone::growPlain(int brushId)
{
    currentGrowRad += 1.0f;
    if (currentGrowRad < maxGrowRad)
    {
        // calcBorder( locationsPointsDrawn );

        // underlyingLayer.begin();
        // ofClear( 1.0 );
        // underlyingLayer.end();

        // renderBorder();

        // experimenting with drawing on water color canvas. if it failed, reuse
        // this layer
        layer.begin();

        int nrToCheck = (int)(ofMap(currentGrowRad, 0, maxGrowRad, 5, 15));

        ofPushStyle();
        ofEnableAlphaBlending();
        for (int i = 0; i < nrToCheck; i++)
        {
            float deg = ofRandom(0, TWO_PI);
            float _x = currentGrowRad * cos(deg);
            float _y = currentGrowRad * sin(deg);
            float s = ofRandom(brushStrokeSizeMin, brushStrokeSizeMax);
            // int randomId = ofRandom( 0, points.size() );

            ofVec2f p(centroid);
            // ofVec2f p = getCenterById( randomId );
            p += ofVec2f(_x, _y);
            ofSetColor(colors.getRandomColor(), brushStrokeAlpha);
            locationsPointsDrawn.push_back(ofVec2f(p.x, p.y));
            if (brushId == 0)
            {
                brushes.getRandomBrush().draw(p.x - s / 2.0, p.y - s / 2.0, s, s);
            }
            else if (brushId == 1)
            {
                brushes.getCircleBrush().draw(p.x - s / 2.0, p.y - s / 2.0, s, s);
            }
            else
            {
                brushes.getBrushById(brushId).draw(p.x - s / 2.0, p.y - s / 2.0, s, s);
            }
        }
        ofDisableAlphaBlending();
        ofPopStyle();

        layer.end();
    }
}

void BrushStone::shrink()
{
    currentGrowRad = currentGrowRad - 0.75f;
    if (currentGrowRad > 0)
    {
        // calcBorder( locationsPointsDrawn );

        // underlyingLayer.begin();
        // ofClear( 1.0 );
        // underlyingLayer.end();

        // renderBorder();

        layer.begin();

        int nrToCheck = (int)(ofMap(currentGrowRad, 0, maxGrowRad, 15, 30));

        ofPushStyle();
        ofEnableAlphaBlending();
        ofEnableBlendMode(OF_BLENDMODE_SUBTRACT);
        for (int i = 0; i < nrToCheck; i++)
        {
            float deg = ofRandom(0, TWO_PI);
            float _x = (currentGrowRad + 20) * cos(deg);
            float _y = (currentGrowRad + 20) * sin(deg);
            float s = ofRandom(brushStrokeSizeMin, brushStrokeSizeMax);
            // int randomId = ofRandom( 0, points.size() );

            ofVec2f p(centroid);
            // ofVec2f p = getCenterById( randomId );
            p += ofVec2f(_x, _y);

            ofSetColor(ofColor(ofRandom(255), ofRandom(255), ofRandom(255)),
                       brushStrokeAlpha);
            locationsPointsDrawn.push_back(ofVec2f(p.x, p.y));
            brushes.getRandomBrush().draw(p.x - s / 2.0, p.y - s / 2.0, s, s);
        }
        ofDisableBlendMode();
        ofDisableAlphaBlending();
        ofPopStyle();

        layer.end();
    }
}

void BrushStone::setFuzzy(float fuzzy) { this->fuzzy = fuzzy; }

void BrushStone::setRadius(float rad) { this->radius = rad; }

float BrushStone::getRadius() { return this->radius; }

float BrushStone::getFuzzy() { return this->fuzzy; }

void BrushStone::setSize(int size) { this->size = size; }

int BrushStone::getNumberOfCircles() { return this->size; }

std::vector<ofPoint> BrushStone::getContourPoints(float x, float y)
{
    return contourPoints;
}

void BrushStone::calcBorder(std::vector<ofPoint> points)
{
    contourPoints = convexHull.getConvexHull(points);
}

int BrushStone::getNumberOfStrokes() { return getNumberOfCircles(); }

void BrushStone::setBrushCollection(BrushCollection _b) { this->brushes = _b; }

void BrushStone::renderBorder()
{
    /*
    underlyingLayer.begin();
    ofPushStyle();
    ofEnableAlphaBlending();
    ofEnableBlendMode( OF_BLENDMODE_ADD );
  
  
    if( contourPoints.size() > 0 ) {
            ofFill();
  
  
            TS_START_NIF( "convert1" );
            std::vector< Point1 > convexPoints( contourPoints.size() );
  #pragma omp parallel for
            for( int i = 0; i < contourPoints.size(); i += 1 ) {
                    ofPoint _poi = contourPoints.at( i );
                    Point1 p;
                    p.x = _poi.x;
                    p.y = _poi.y;
                    convexPoints.at( i ) = p;
            }
            TS_STOP_NIF( "convert1" );
  
  
            TS_START_NIF( "convex" );
            std::vector< Point1 > ps = VoronoiLayer::convex_hull( convexPoints );
            TS_STOP_NIF( "convex" );
  
  
            border.clear();
            border.setClosed( true );
  
  
            TS_START_NIF( "convert2" );
            std::vector< ofPoint > finalPoints( ps.size() );
  #pragma omp parallel for
            for( int i = 0; i < ps.size(); i++ ) {
                    Point1 from = ps.at( i );
                    finalPoints.at( i ) = ofPoint( from.x, from.y );
            }
            TS_STOP_NIF( "convert2" );
  
  
            TS_START_NIF( "etc" );
            border.addVertices( finalPoints );
  
  
            border.setClosed( true );
            border = border.getResampledBySpacing( 20 );
  
  
            ofSetColor( 51, 25, 0, 255 );
            float s = 10;
            ofSeedRandom( 0 );
            TS_STOP_NIF( "etc" );
  
  
            TS_START_NIF( "drawing_b" );
            for( int i = 0; i < border.getVertices().size(); i++ ) {
                    ofPoint p = border.getVertices().at( i );
                    brushes.getRandomBrush().draw( p.x - borderSize / 2.0, p.y -
  borderSize / 2.0, borderSize, borderSize );
            }
            TS_STOP_NIF( "drawing_b" );
  
  
            ofSeedRandom();
    }
    else {
            std::cout << "Contour points empty. No border!" << std::endl;
    }
  
  
    ofDisableAlphaBlending();
    ofPopStyle();
    underlyingLayer.end();
    */
}

void BrushStone::setColorCollection(ColorCollection _c) { this->colors = _c; }

void BrushStone::setTransparency(float _trans) { transparency = _trans; }

void BrushStone::setBrushStrokeCount(int count)
{
    this->brushStokeCount = count;
}

void BrushStone::setBrushStrokeSizeMin(float min)
{
    this->brushStrokeSizeMin = min;
}

void BrushStone::setBrushStrokeSizeMax(float max) { brushStrokeSizeMax = max; }

void BrushStone::setBrushStrokeAlpha(float alpha) { brushStrokeAlpha = alpha; }

int BrushStone::getBrushStrokeCount() { return this->brushStokeCount; }

float BrushStone::getBrushStrokeSizeMin() { return this->brushStrokeSizeMin; }

float BrushStone::getBrushStrokeSizeMax() { return this->brushStrokeSizeMax; }

float BrushStone::getBrushStrokeAlpha() { return this->brushStrokeAlpha; }

void BrushStone::setBorderTransparency(float _trans)
{
    this->borderTransparency = _trans;
}

ofFbo BrushStone::getStoneBuffer() { return layer; }

void BrushStone::setBorderSize(int _bsize) { this->borderSize = _bsize; }

int BrushStone::getBorderSize() { return this->borderSize; }

void BrushStone::setSaturation(float _sat) { this->saturation = _sat; }

float BrushStone::getSaturation() { return this->saturation; }

vector<ofVec3f> BrushStone::resamplePolylineToCount(const ofPolyline& polyline,
                                                    int n)
{
    vector<ofVec3f> points;
    float jump = 1.0f / (n - 1);

    for (int i = 0; i < n; i++)
    {
        points.push_back(polyline.getPointAtPercent(min(i * jump, 0.99999f)));
    }
    return points;
}

float BrushStone::getTransparency() { return this->transparency; }

void BrushStone::toggleRenderBorder(bool _b) { this->tDrawBorder = _b; }

void BrushStone::toggleDrawStone(bool _s) { this->tDrawStone = _s; }

void BrushStone::setSelectedColor(ofColor col) { this->selectedColor = col; }

void BrushStone::setStoneCircleBackgroundColor(ofColor col)
{
    stoneCircleBackgroundColor = col;
}

void BrushStone::setMaxGrowRad(float maxRad) { maxGrowRad = maxRad; }
