/*******************************************************************************
 @ copyright(C), 2019-2020, Connor
 @ filename:	  Gif.h
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

#ifndef GIF_H_
#define GIF_H_

#include "GIFMovie.h"
#include "GifBase.h"

 /*
  Gif will just decode some raw data when it init.
  The bitmap data will be parsed when need which be used to create CCTexture.
  */
class Gif : public GifBase {
public:
	CREATE_CCOBJ_WITH_PARAM(Gif, const char*);
	virtual bool init(const char*);

	CREATE_CCOBJ_WITH_PARAMS(Gif, FILE*, const char*);
	virtual bool init(FILE*, const char*);
	Gif();
	~Gif();
	virtual void updateGif(uint32_t delta);
	virtual std::string getGifFrameName(int index);
private:
	GIFMovie* m_movie;
	uint32_t m_GifId;
};

#endif // GIF_H_