#include "BrushCollection.h"

BrushCollection::BrushCollection()
{
}

BrushCollection::~BrushCollection()
{
}

void BrushCollection::clear()
{
    brushes.clear();
    fboBrushes.clear();
}

ofFbo BrushCollection::getRandomBrush()
{
    return fboBrushes.at(ofRandom(0, fboBrushes.size()));
}

ofImage& BrushCollection::getCircleBrush() { return circleBrush; }

ofImage& BrushCollection::getOwnBrush1() { return ownBrush1; }

ofFbo BrushCollection::getBrushById(int id) { return fboBrushes.at(id); }

void BrushCollection::load(const int offset, const int count)
{
    for (int i = 1 + offset; i < 1 + offset + count; i++)
    {
        std::stringstream ss;
        ss << "water_color_textures_";
        if (i < 10)
        {
            ss << "0";
        }
        ss << i << ".png";
        ofImage im;
        im.load(ss.str());
        brushes.push_back(im);

        ofFbo fboImage;
        fboImage.allocate(im.getWidth(), im.getHeight());
        fboImage.begin();
        ofClear(1.0f);
        ofEnableAlphaBlending();
        im.draw(0, 0);
        fboImage.end();

        fboBrushes.push_back(fboImage);
    }

    circleBrush.load("brush.png");
    ownBrush1.load("own_brush_2.png");
}

void BrushCollection::loadSingle(std::string path)
{
    ofImage im;
    im.load(path);
    brushes.clear();
    fboBrushes.clear();

    brushes.push_back(im);

    ofFbo fboImage;
    fboImage.allocate(im.getWidth(), im.getHeight());
    fboImage.begin();
    ofClear(1.0f);
    ofEnableAlphaBlending();
    im.draw(0, 0);
    fboImage.end();

    fboBrushes.push_back(fboImage);
}
