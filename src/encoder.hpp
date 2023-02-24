
#ifndef ENCODER_HPP_
#define ENCODER_HPP_

#include <memory>
#include <stdint.h>

extern "C" {
#include <x264.h>

#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavformat/avio.h>
#include <libavutil/imgutils.h>
#include <libswscale/swscale.h>
}

namespace h264encoder {

class EncoderImpl;

// simplified version of the x264_nal_t struct containing only the necessary fields for
// encoding
typedef struct x264_nal_t_simple {
	/* Size of payload (including any padding) in bytes. */
	int i_payload;
	/* If param->b_annexb is set, Annex-B bytestream with startcode.
	 * Otherwise, startcode is replaced with a 4-byte size.
	 * This size is the size used in mp4/similar muxing; it is equal to i_payload-4 */
	uint8_t* p_payload;
} x264_nal_t_simple;

class Encoder {
public:
	x264_nal_t_simple* nals;
	int num_nals;
	Encoder(){};
	Encoder(int, int, int, int, float);
	int encode(unsigned char*);

private:
	std::shared_ptr<EncoderImpl> impl;
};

} // namespace h264encoder

#endif /* ENCODER_HPP_ */
