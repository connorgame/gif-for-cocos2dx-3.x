/*******************************************************************************
 @ copyright(C), 2019-2020, Connor
 @ filename:	  Gif.cpp
 @ author:		  Connor
 @ version:	      1.0.0
 @ date:		  2019-08-31
 @ description:
 @ others:
 @ history:
 1.date:
 author:
 modification:
 ********************************************************************************/

#include "Gif.h"

static uint32_t GifId = 0;

bool Gif::init(const char* fileName) {
	FILE* f = GifUtils::openFile(fileName);
	return init(f, fileName);
}

bool Gif::init(FILE* f, const char* fileName) {
	m_gif_fullpath = fileName;
	if (GifUtils::isGifFile(f) == false) {
		GifUtils::closeFile(f);
		return false;
	}

	m_movie = GIFMovie::create(f);
	if (m_movie == NULL || m_movie->getGifCount() <= 0) {
		return false;
	}

	if (m_movie->getGifCount() > 1) {
		scheduleUpdate();
	}
	m_movie->setTime(0);
	cocos2d::Texture2D* texture = createTexture(m_movie->bitmap(), 0, false);

	return initWithTexture(texture);
}

Gif::Gif() {
	m_movie = NULL;

	GifId++;
	if (GifId == UNINITIALIZED_UINT) {
		GifId = 0;
	}
	m_GifId = GifId;// gif id.
}

std::string Gif::getGifFrameName(int index) {
	// Use id to create framename or texturename, to ensure multiple gifs created under the same path, not confusion in the texture cache
	return cocos2d::CCString::createWithFormat("%s_instant_%u", m_gif_fullpath.c_str(), m_GifId)->getCString();
}

Gif::~Gif() {
	CC_SAFE_DELETE(m_movie);
	std::string texture = getGifFrameName(0);
	cocos2d::Director::getInstance()->getTextureCache()->removeTextureForKey(texture.c_str());
}

void Gif::updateGif(uint32_t delta) {
	if (m_movie->appendTime(delta)) {
		cocos2d::Texture2D* texture = createTexture(m_movie->bitmap(), 0, false);
		this->setTexture(texture);
	}
}
