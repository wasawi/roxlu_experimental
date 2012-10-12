#include <videorecorder/VideoRecorder.h>

#if RGB_CONVERTER == CONVERTER_SWSCALE
VideoRecorder::VideoRecorder(int inW, int inH, int outW, int outH, int fps)
	:in_width(inW)
	,in_height(inH)
	,out_width(outW)
	,out_height(outH)
#else
VideoRecorder::VideoRecorder(int inW, int inH, int fps)
	:in_width(inW)
	,in_height(inH)
	,out_width(inW)
	,out_height(inH)
#endif
	,in_stride(inW * 3)
	,fps(fps) 
	,encoder(NULL)
#if RGB_CONVERTER == CONVERTER_SWSCALE
	,sws(NULL)
#endif
	,fp(NULL)
	,io(NULL)
	,num_frames(0)
	,vfr_input(false)
	// timeing
	/*
	,last_dts(0)
	,prev_dts(0)
	,first_dts(0)
	,largest_pts(-1)
	,second_largest_pts(-1)
	,duration(0)
	*/
{
	rec_params.video_width = out_width;
	rec_params.video_height = out_height;
	rec_params.video_codec_id = FLV_VIDEOCODEC_AVC;
	rec_params.audio_codec_id = FLV_SOUNDFORMAT_SPEEX;
	rec_params.x264_param = &params;
	rec_params.x264_nal = nals;
	rec_params.x264_pic = &pic_out;
}

VideoRecorder::~VideoRecorder() {
	closeFile();
}


void VideoRecorder::initEncoder() {
	setParams();

	// create the encoder
	encoder = x264_encoder_open(&params);
	if(!encoder) {
		printf("Error: cannot open encoder.\n");
		::exit(1);
	}
	x264_encoder_parameters(encoder, &params);
	if(io) {
		io->writeParams(&rec_params);
		//	io->writeParamsX264(&params);
	}

	// allocate picture / sws
	x264_picture_alloc(&pic_in, X264_CSP_I420, out_width, out_height);
#if RGB_CONVERTER == CONVERTER_SWSCALE
sws = sws_getContext(in_width, in_height, PIX_FMT_RGB24, out_width, out_height, PIX_FMT_YUV420P, SWS_FAST_BILINEAR, NULL, NULL, NULL);
#endif


	int nheader;
	x264_encoder_headers(encoder, &nals, &nheader);
	if(io) {
		rec_params.x264_nal = nals;
		io->writeHeaders(&rec_params);
		//io->writeHeadersX264(nals);
	}
	printf("NHEADER: %d\n", nheader);
}

void VideoRecorder::setParams() {
	x264_param_t* p = &params;
	x264_param_default_preset(p, "veryfast", "zerolatency");
	p->i_threads = 1;
	p->i_width = out_width;
	p->i_height = out_height;
	p->i_fps_num = fps;
	p->i_fps_den = 1;

	// intra refresh
	p->i_keyint_max = fps;
	p->b_intra_refresh = 1;

	// rate control
	p->rc.i_rc_method = X264_RC_CRF;
	p->rc.f_rf_constant = 25;
	p->rc.f_rf_constant_max = 35;

	// streaming
	p->b_repeat_headers = 0; // 1 for streaming, for now this only works with '0'
	p->b_annexb = 0; // 1 for streaming, for now this only works with '0'

	x264_param_apply_profile(p, "baseline");
}

bool VideoRecorder::openFile(const char* filepath) {
	fp = fopen(filepath, "w+b");
	if(!fp) {
		printf("Error: Cannot open raw file.\n");
		return false;
	}

	if(io) {
		io->writeOpenFileX264();
	}

	initEncoder();

	int r = writeHeaders();
	if(r < 0) {
		printf("Error: cannot write headers.\n");
		return false;
	}

	return true;
}

int VideoRecorder::writeHeaders() {
	x264_nal_t* n = nals;
	int size = n[0].i_payload + n[1].i_payload + n[2].i_payload;
	if(fwrite(n[0].p_payload, size, 1, fp)) {
		return size;
	}
	return -1;
}


int VideoRecorder::addFrame(unsigned char* pixels) {
#if RGB_CONVERTER == CONVERTER_SWSCALE
	int h = sws_scale(sws
							,(const  uint8_t* const*)&pixels 
							,&in_stride
							,0
							,in_height
							,pic_in.img.plane
							,pic_in.img.i_stride
							);
#else
	int r = libyuv::RGB24ToI420(pixels
										 ,in_stride
										 ,pic_in.img.plane[0], pic_in.img.i_stride[0]
										 ,pic_in.img.plane[1], pic_in.img.i_stride[1]
										 ,pic_in.img.plane[2], pic_in.img.i_stride[2]
										 ,in_width, in_height);
#endif

	pic_in.i_pts = num_frames;
	++num_frames;

	int frame_size = x264_encoder_encode(encoder, &nals, &num_nals, &pic_in, &pic_out);
	if(frame_size == 0) {
		printf("Error: frame size is 0\n");
		return 0;
	}
	else {
		if(io) {
			rec_params.x264_nal = nals;
			rec_params.x264_frame_size = frame_size;
			rec_params.x264_pic = &pic_out;
			io->writeVideoFrame(&rec_params);
			//io->writeFrameX264(nals, frame_size, &pic_out);
		}
		if(fwrite(nals[0].p_payload, frame_size, 1, fp)) {
			return frame_size;
		}
	}
	return -1;
}

void VideoRecorder::closeFile() {
	if(fp) {
		fclose(fp);
		fp = NULL;
	}
	if(io) {
		io->writeCloseFile264();
	}
}












