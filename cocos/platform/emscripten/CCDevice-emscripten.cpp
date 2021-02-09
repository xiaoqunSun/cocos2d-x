/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include "platform/CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_EMSCRIPTEN

#include "platform/CCDevice.h"
#include <emscripten/emscripten.h>
#include <emscripten/html5.h>

NS_CC_BEGIN

int Device::getDPI()
{
    return 160;
}

void Device::setAccelerometerEnabled(bool isEnabled)
{
    // TODO: https://emscripten.org/docs/api_reference/html5.h.html?
}

void Device::setAccelerometerInterval(float interval)
{
    // TODO: https://emscripten.org/docs/api_reference/html5.h.html?
}

Data Device::getTextureDataForText(const char * text, const FontDefinition& textDefinition, TextAlign align, int &width, int &height, bool& hasPremultipliedAlpha)
{
    // TODO: implement
    return Data();
}

void Device::setKeepScreenOn(bool value)
{
    // not possible?
}

void Device::vibrate(float duration)
{
    emscripten_vibrate(duration * 1000);
}

NS_CC_END

#endif // CC_TARGET_PLATFORM == CC_PLATFORM_EMSCRIPTEN
