#include <gl/glew.h>
#include "math/maths.h"
#include "graphics/window.h"
#include "graphics/shader.h"
#include "utils/file_utils.h"
#include "log/aplog.h"
#include "timer/timer.h"
#include "graphics/buffer/vertex_array.h"
#include "graphics/buffer/index_buffer.h"
#include "graphics/2d/renderer2d.h"
#include "graphics/2d/renderable2d.h"
#include "graphics/2d/simple_renderer2d.h"
#include "graphics/2d/static_sprite.h"
#include "graphics/2d/sprite.h"
#include "graphics/2d/batch_renderer2d.h"
#include "graphics/2d/layer.h"
#include "graphics/2d/tile_layer.h"
#include "graphics/2d/group.h"
#include "graphics/texture.h"
#include "graphics/2d/label.h"
#include "graphics/2d/font.h"

///** Export function
//* API rule -> define in header files (header.h):
//*/
//#ifdef EXPORT_NARIO_API
//#define NARIO_PAI __declspec(dllexport)   // if export like C style you should : #define NARIO_PAI extern "C" __declspec(dllexport)
//#else
//#define NARIO_PAI __declspec(dllimport)   // if export like C style you should : #define NARIO_PAI extern "C" __declspec(dllimport)
//#endif // EXPORT_NARIO_API
//// define function:
// NARIO_PAI void function();
///**
//* API rule -> define in source files (header.cpp):
//*/
//#define EXPORT_NARIO_API
//#include "header.h"
//// function
// void function() {}

/// Export class: class NARIO_PAI classname {}; 这时导出方式不能用"C" style
// "C" style方式导出时函数签名和函数名一样，可用于显示链接动态库
// 非"C" style方式导出时函数签名在函数名基础上增加随机字符，因此不可用于显示链接动态库