
#ifdef	__cplusplus
extern "C"
{
#endif
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#include "libavdevice/avdevice.h"
#include "libavutil/audio_fifo.h"

#ifdef __cplusplus
};
#endif


AVFormatContext	*pFormatCtx_Video = NULL, *pFormatCtx_Audio = NULL, *pFormatCtx_Out = NULL;
AVCodecContext	*pCodecCtx_Video;
AVCodec			*pCodec_Video;
AVFifoBuffer	*fifo_video = NULL;
AVAudioFifo		*fifo_audio = NULL;
int VideoIndex, AudioIndex;

//CRITICAL_SECTION AudioSection, VideoSection;



int OpenVideoCapture()
{
	AVInputFormat *ifmt = av_find_input_format("gdigrab");
	//������ԼӲ����򿪣��������ָ���ɼ�֡��
	AVDictionary *options = NULL;
	av_dict_set(&options, "framerate", "15", NULL);
	//av_dict_set(&options,"offset_x","20",0);
	//The distance from the top edge of the screen or desktop
	//av_dict_set(&options,"offset_y","40",0);
	//Video frame size. The default is to capture the full screen
	//av_dict_set(&options,"video_size","320x240",0);
		if (avformat_open_input(&pFormatCtx_Video, "desktop", ifmt, &options) != 0)
	{
		printf("Couldn't open input stream.���޷�����Ƶ��������\n");
		return -1;
	}
	if (avformat_find_stream_info(pFormatCtx_Video, NULL) < 0)
	{
		printf("Couldn't find stream information.���޷���ȡ��Ƶ����Ϣ��\n");
		return -1;
	}
	if (pFormatCtx_Video->streams[0]->codec->codec_type != AVMEDIA_TYPE_VIDEO)
	{
		printf("Couldn't find video stream information.���޷���ȡ��Ƶ����Ϣ��\n");
		return -1;
	}
	pCodecCtx_Video = pFormatCtx_Video->streams[0]->codec;
	pCodec_Video = avcodec_find_decoder(pCodecCtx_Video->codec_id);
	if (pCodec_Video == NULL)
	{
		printf("Codec not found.��û���ҵ���������\n");
		return -1;
	}
	if (avcodec_open2(pCodecCtx_Video, pCodec_Video, NULL) < 0)
	{
		printf("Could not open codec.���޷��򿪽�������\n");
		return -1;
	}


	
	return 0;
}


int main()
{
	OpenVideoCapture();
	return 0;
}