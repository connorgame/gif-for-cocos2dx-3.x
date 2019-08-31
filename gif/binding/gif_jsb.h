/*******************************************************************************
 @ copyright(C), 2019-2020, Connor
 @ filename:	  gif_jsb.h
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

#ifndef GIF_JSB_H_
#define GIF_JSB_H_

#include "jsapi.h"

namespace gif {

void js_register_all(JSContext* cx, JS::HandleObject global);

void js_register_gif(JSContext* cx, JS::HandleObject global);

}

#endif // GIF_JSB_H_