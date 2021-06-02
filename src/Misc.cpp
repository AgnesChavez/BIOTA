#include "Misc.h"

ofFbo::Settings Misc::getDefaultFboSettings() {
  ofFbo::Settings generalSettings;
  generalSettings.useDepth = true;
  generalSettings.useStencil = false;
  generalSettings.depthStencilAsTexture = true;
  generalSettings.width = 1920;
  generalSettings.height = 1080;
  return generalSettings;
}