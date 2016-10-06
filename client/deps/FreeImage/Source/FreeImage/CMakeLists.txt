set (MODULE_NAME freeimage)

set(FREEIMAGE_SOURCES ../FreeImage/BitmapAccess.cpp ../FreeImage/ColorLookup.cpp ../FreeImage/FreeImage.cpp ../FreeImage/FreeImageIO.cpp ../FreeImage/GetType.cpp ../FreeImage/MemoryIO.cpp ../FreeImage/PixelAccess.cpp ../FreeImage/NNQuantizer.cpp ../FreeImage/WuQuantizer.cpp ../FreeImage/Conversion.cpp ../FreeImage/Conversion16_555.cpp ../FreeImage/Conversion16_565.cpp ../FreeImage/Conversion24.cpp ../FreeImage/Conversion32.cpp ../FreeImage/Conversion4.cpp ../FreeImage/Conversion8.cpp ../FreeImage/ConversionFloat.cpp ../FreeImage/ConversionRGB16.cpp ../FreeImage/ConversionRGBF.cpp ../FreeImage/ConversionType.cpp ../FreeImage/ConversionUINT16.cpp ../FreeImage/Halftoning.cpp ../FreeImage/tmoColorConvert.cpp ../FreeImage/tmoDrago03.cpp ../FreeImage/tmoFattal02.cpp ../FreeImage/tmoReinhard05.cpp ../FreeImage/ToneMapping.cpp ../FreeImage/J2KHelper.cpp ../FreeImage/MNGHelper.cpp ../FreeImage/Plugin.cpp ../FreeImage/PluginBMP.cpp ../FreeImage/PluginCUT.cpp ../FreeImage/PluginDDS.cpp ../FreeImage/PluginEXR.cpp ../FreeImage/PluginG3.cpp ../FreeImage/PluginGIF.cpp ../FreeImage/PluginHDR.cpp ../FreeImage/PluginICO.cpp ../FreeImage/PluginIFF.cpp ../FreeImage/PluginJ2K.cpp ../FreeImage/PluginJNG.cpp ../FreeImage/PluginJP2.cpp ../FreeImage/PluginJPEG.cpp ../FreeImage/PluginJXR.cpp ../FreeImage/PluginKOALA.cpp ../FreeImage/PluginMNG.cpp ../FreeImage/PluginPCD.cpp ../FreeImage/PluginPCX.cpp ../FreeImage/PluginPFM.cpp ../FreeImage/PluginPICT.cpp ../FreeImage/PluginPNG.cpp ../FreeImage/PluginPNM.cpp ../FreeImage/PluginPSD.cpp ../FreeImage/PluginRAS.cpp ../FreeImage/PluginRAW.cpp ../FreeImage/PluginSGI.cpp ../FreeImage/PluginTARGA.cpp ../FreeImage/PluginTIFF.cpp ../FreeImage/PluginWBMP.cpp ../FreeImage/PluginWebP.cpp ../FreeImage/PluginXBM.cpp ../FreeImage/PluginXPM.cpp ../FreeImage/PSDParser.cpp ../FreeImage/TIFFLogLuv.cpp ../DeprecationManager/Deprecated.cpp ../DeprecationManager/DeprecationMgr.cpp ../FreeImage/CacheFile.cpp ../FreeImage/MultiPage.cpp ../FreeImage/ZLibInterface.cpp ../Metadata/Exif.cpp ../Metadata/FIRational.cpp ../Metadata/FreeImageTag.cpp ../Metadata/IPTC.cpp ../Metadata/TagConversion.cpp ../Metadata/TagLib.cpp ../Metadata/XTIFF.cpp ../FreeImageToolkit/Background.cpp ../FreeImageToolkit/BSplineRotate.cpp ../FreeImageToolkit/Channels.cpp ../FreeImageToolkit/ClassicRotate.cpp ../FreeImageToolkit/Colors.cpp ../FreeImageToolkit/CopyPaste.cpp ../FreeImageToolkit/Display.cpp ../FreeImageToolkit/Flip.cpp ../FreeImageToolkit/JPEGTransform.cpp ../FreeImageToolkit/MultigridPoissonSolver.cpp ../FreeImageToolkit/Rescale.cpp ../FreeImageToolkit/Resize.cpp ../FreeImage/LFPQuantizer.cpp ../FreeImage/ConversionRGBAF.cpp ../FreeImage/ConversionRGBA16.cpp )

set(FREEIMAGE_HEADERS ../CacheFile.h ../DeprecationManager/DeprecationMgr.h ../Metadata/FIRational.h ../FreeImage.h ../FreeImageIO.h ../Metadata/FreeImageTag.h ../Plugin.h ../FreeImage/PSDParser.h ../Quantizers.h ../ToneMapping.h ../Utilities.h ../FreeImageToolkit/Resize.h ../MapIntrospector.h )

if (NOT BUILD_SHARED_LIBS)
	add_definitions(-DFREEIMAGE_LIB -DLIBRAW_NODLL -DOPJ_STATIC)
endif(NOT BUILD_SHARED_LIBS)

include_directories (.. ../ZLib ../DeprecationManager ../OpenEXR ../OpenEXR/Half ../OpenEXR/Iex ../OpenEXR/IlmImf ../OpenEXR/Imath ../OpenEXR/IlmThread ../LibJXR/jxrgluelib ../LibJXR/image/sys)

file (GLOB ${MODULE_NAME}_SRCS *.cpp ../DeprecationManager/*.cpp ../FreeImageToolkit/*.cpp ../Metadata/*.cpp )

add_library (${MODULE_NAME} ${FREEIMAGE_SOURCES} ${FREEIMAGE_HEADERS})

TARGET_LINK_LIBRARIES(${MODULE_NAME} libjpeg libjxr libopenexr libopenjpeg libpng librawlite libtiff4 libwebp zlib)

# lib output dir
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../../lib)


install (TARGETS ${MODULE_NAME} 
		ARCHIVE DESTINATION lib 
		LIBRARY DESTINATION lib)