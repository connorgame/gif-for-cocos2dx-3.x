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

#include "gif_jsb.h"

#include "cocos/cocos2d.h"
#include "scripting/js-bindings/manual/cocos2d_specifics.hpp"
#include "scripting/js-bindings/manual/ScriptingCore.h"

#include "gif/Gif.h"

JSClass* jsb_gif_class;
JSObject* jsb_gif_prototype;

bool js_Gif_create(JSContext* cx, uint32_t argc, jsval* vp) {
	JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
	bool ok = true;

	do {
		if (1 == argc) {
			std::string arg0;
			ok &= jsval_to_std_string(cx, args.get(0), &arg0);
			if (arg0.empty()) {
				ok = false;
			}
			JSB_PRECONDITION2(ok, cx, false, "js_Gif_create : Error processing arguments");

			auto fullPath = cocos2d::FileUtils::getInstance()->fullPathForFilename(arg0.c_str());
			if (fullPath.empty()) {
				cocos2d::log("createGif failed! gifFile fullPath empty!");
				return nullptr;
			}

			cocos2d::Sprite* gif = Gif::create(fullPath.data());

			JS::RootedValue jsret(cx);
			if (gif == nullptr) {
				jsret = JSVAL_NULL;
			} else {
				jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::Sprite>(cx, (cocos2d::Sprite*)gif));
			}

			args.rval().set(jsret);

			return true;
		}
	} while (0);

	JS_ReportError(cx, "js_Gif_create : wrong number of arguments : %d, expecting 1", argc);
	return false;
}

bool js_Gif_constructor(JSContext* cx, uint32_t argc, jsval* vp) {
	return true;
}

void gif::js_register_all(JSContext* cx, JS::HandleObject global) {
	JS::RootedObject ns(cx);
	get_or_create_js_obj(cx, global, "myjsb", &ns);
	js_register_gif(cx, ns);
}

void gif::js_register_gif(JSContext* cx, JS::HandleObject global) {
	jsb_gif_class = (JSClass*)calloc(1, sizeof(JSClass));
	jsb_gif_class->name = "Gif";
	jsb_gif_class->addProperty = JS_PropertyStub;
	jsb_gif_class->delProperty = JS_DeletePropertyStub;
	jsb_gif_class->getProperty = JS_PropertyStub;
	jsb_gif_class->setProperty = JS_StrictPropertyStub;
	jsb_gif_class->enumerate = JS_EnumerateStub;
	jsb_gif_class->resolve = JS_ResolveStub;
	jsb_gif_class->convert = JS_ConvertStub;
	jsb_gif_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		JS_PS_END
	};

	static JSFunctionSpec funcs[] = {
		JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("create", js_Gif_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_gif_prototype = JS_InitClass(
		cx, global,
		JS::NullPtr(),
		jsb_gif_class,
		js_Gif_constructor, // constructor
		0,
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);

	JS::RootedObject proto(cx, jsb_gif_prototype);
	JS::RootedValue className(cx, std_string_to_jsval(cx, "Gif"));
	JS_SetProperty(cx, proto, "_className", className);
	JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
	JS_SetProperty(cx, proto, "__is_ref", JS::TrueHandleValue);
	// add the proto and JSClass to the type->js info hash table
	jsb_register_class<GifBase>(cx, jsb_gif_class, proto, JS::NullPtr());
	anonEvaluate(cx, global, "(function () { myjsb.Gif.extend = cc.Class.extend; })()");

}
