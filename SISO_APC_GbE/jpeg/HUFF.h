#pragma once


int generate_size_table(huff_t *hl);
int generate_code_table(huff_t *hl);
int decoder_table_(huff_t *hl);
int huffcode_to_bits(huff_t *huf);
int gen_hufval(huff_t* huf);
int create_hufftable(huff_t *hufft);
