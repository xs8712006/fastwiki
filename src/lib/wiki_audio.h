/*
 * Copyright (C) 2014 Qian Shanhai (qianshanhai@gmail.com)
 */

/*
 *  format: [ head ] [ hash ][ data ]
 */

#ifndef __WIKI_AUDIO_H
#define __WIKI_AUDIO_H

#include "s_hash.h"

#define FASTWIKI_AUDIO_PREFIX "fastwiki.audio."
#define FW_AUDIO_VERSION 0x1

struct wiki_audio_head {
	int flag; /* 0xfafafa */
	char name[32]; /* FASTWIKI_AUDIO_PREFIX */
	int version;
	unsigned int hash_pos;
	unsigned int hash_size;
	int max_size;
	int total;
	char r[128];
	unsigned int crc32; /* crc32sum() */
};

struct audio_key {
	char title[64];
};

struct audio_value {
	unsigned int pos;
	int len;
	char type[8];
	unsigned char flag[8];
	char r[64];
};

class WikiAudio {
	private:
		int m_fd;
		SHash *m_hash;
		struct wiki_audio_head m_head;
		int m_init_flag;

		int m_max_total;
		int m_max_size;
		unsigned int m_file_pos;

	public:
		WikiAudio();
		~WikiAudio();

	public:
		int wa_reinit(const char *file);
		int wa_init(const char *file);
		int wa_find(const char *title, char *data, int *len, int max_size);
		int wa_find_pos(const char *title, unsigned int *pos, int *len);
		int wa_get_fd();
		int wa_stat();
		int wa_check(struct wiki_audio_head *h);
		int wa_check_file(const char *file);

	public:
		int wa_init_rw(int max_total, const char *outfile);
		int wa_add_one_audio(const char *title, const char *data, int len, const char *type);
		int wa_output();
};

#endif
