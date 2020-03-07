# gif-for-cocos2dx-3.x
a gif lib for cocos2d-x 3.x（c++, js）

# Use 

use gif widget just like a Sprite:

# c++

#include "gif/gif.h"

std::string name = "g1.gif";

name = FileUtils::getInstance()->fullPathForFilename(name.c_str());

auto gif = Gif::create(name.c_str()); // instant gif ：while playing, while parsing

gif->setPosition(Point(200, 200));

this->addChild(gif);


# js

// in cpp file

#include "gif/gif_jsb.h" 

ScriptingCore* sc = ScriptingCore::getInstance();
sc->addRegisterCallback(gif::js_register_all);

// in js file

var gif = myjsb.Gif.create('res/g1.gif');

gif.setPosition(200, 200);

this.addChild(gif);
