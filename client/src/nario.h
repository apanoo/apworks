#include "math/Maths.h"
#include "graphics/MainGame.h"

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

/// Export class: class NARIO_PAI classname {}; ��ʱ������ʽ������"C" style
// "C" style��ʽ����ʱ����ǩ���ͺ�����һ������������ʾ���Ӷ�̬��
// ��"C" style��ʽ����ʱ����ǩ���ں�������������������ַ�����˲���������ʾ���Ӷ�̬��