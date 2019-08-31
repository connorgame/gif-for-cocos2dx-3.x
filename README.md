# gif-for-cocos2dx-3.x
a gif lib for cocos2d-x 3.x（c++, lua, js, cocos creator）

# Use 

c++

//#include "gif/gif.h"

std::string name = "g1.gif";
name = FileUtils::getInstance()->fullPathForFilename(name.c_str());
auto gif = Gif::create(name.c_str()); //instant gif ：While playing, while parsing
gif->setPosition(Point(200, 200));
this->addChild(gif);
