#pragma once

#include "platform.h"
#include "raop_sink.h"

#define RAOP_SAMPLE_RATE	44100

typedef enum { 	RAOP_SETUP, RAOP_STREAM, RAOP_PLAY, RAOP_FLUSH, RAOP_METADATA, RAOP_ARTWORK, RAOP_PROGRESS, RAOP_PAUSE, RAOP_STOP, 
				RAOP_VOLUME, RAOP_TIMING, RAOP_PREV, RAOP_NEXT, RAOP_REW, RAOP_FWD, 
				RAOP_VOLUME_UP, RAOP_VOLUME_DOWN, RAOP_RESUME, RAOP_TOGGLE } raop_event_t ;

typedef bool (*raop_cmd_cb_t)(raop_event_t event, ...);
typedef bool (*raop_cmd_vcb_t)(raop_event_t event, va_list args);
typedef void (*raop_data_cb_t)(const u8_t *data, size_t len, u32_t playtime);

typedef struct {
	unsigned short cport, tport, aport;
	struct rtp_s *ctx;
} rtp_resp_t;