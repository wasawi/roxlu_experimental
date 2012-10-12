#include <videorecorder/VideoIOFLV.h>

int VideoIOFLV::writeOpenFileX264() {
	printf("% writeOpenFileX264()\n");
	return flv.writeHeader(true, false);
}

int VideoIOFLV::writeParamsX264(x264_param_t* p) {
	printf("% writeParamsX264()\n");
	return flv.writeParamsX264(p);
}

int VideoIOFLV::writeHeadersX264(x264_nal_t* nal) {
	printf("% writeHeaderX264()\n");
	return flv.writeHeadersX264(nal);
}

/*
int VideoIOFLV::writeMetaDataX264(x264_param_t* param) {
	printf("% writeMetaDataX264()\n");
	return flv.writeMetaDataX264(param);
}
*/

int VideoIOFLV::writeFrameX264(x264_nal_t* nal, size_t size, x264_picture_t* pic) {
	printf("% writeFrameX264()\n");
	flv.writeVideoFrameX264(nal, size, pic);
	return -1;
}

int VideoIOFLV::writeCloseFile264() {
	flv.saveFile("data/particles_flv.flv");
	return 1;
}
