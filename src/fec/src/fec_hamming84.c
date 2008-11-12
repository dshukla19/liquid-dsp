//
// 1/2-rate (8,4) Hamming code
//

#include <stdio.h>

#include "fec_internal.h"
#include "../../utility/src/utility.h"

#define HAMMING84_H0    0xaa
#define HAMMING84_H1    0x66
#define HAMMING84_H2    0x1e

static unsigned char hamming84_enc[] = {
    0x00,   0xd3,   0x54,   0x87,
    0x98,   0x4b,   0xcc,   0x1f,
    0xe0,   0x33,   0xb4,   0x67,
    0x78,   0xab,   0x2c,   0xff
};

static unsigned char hamming84_bflip[] = {
    0x00,
    0x80,   0x40,   0x20,   0x10,
    0x08,   0x04,   0x02,   0x01};

void fec_hamming84_encode(unsigned char *_msg_dec, unsigned int _msg_len, unsigned char *_msg_enc)
{
    unsigned int i, j=0;
    unsigned char s0, s1;
    for (i=0; i<_msg_len; i++) {
        s0 = (_msg_dec[i] >> 4) & 0x0f;
        s1 = (_msg_dec[i] >> 0) & 0x0f;
        _msg_enc[j+0] = hamming84_enc[s0];
        _msg_enc[j+1] = hamming84_enc[s1];
        j+=2;
    }
}

unsigned int
fec_hamming84_decode(unsigned char *_msg_enc, unsigned int _msg_len, unsigned char *_msg_dec)
{
    unsigned int i, j=0, num_errors=0;
    unsigned char r0, r1, z0, z1, s0, s1;
    for (i=0; i<_msg_len; i++) {
        r0 = _msg_enc[2*i+0];
        r1 = _msg_enc[2*i+1];

        // compute syndromes
        z0 = fec_hamming84_compute_syndrome(r0);
        z1 = fec_hamming84_compute_syndrome(r1);

        //if (z0 || z0)
        printf("syndrome[%u] : %d, %d\n", i, (int)z0, (int)z1);
        printf("    input symbols[%u] : 0x%.2x, 0x%.2x\n", i, r0, r1);

        if (z0) r0 ^= hamming84_bflip[z0];
        if (z1) r1 ^= hamming84_bflip[z1];

        printf("corrected symbols[%u] : 0x%.2x, 0x%.2x\n", i, r0, r1);

        s0 = fec_hamming84_decode_symbol(r0);
        s1 = fec_hamming84_decode_symbol(r1);

        _msg_dec[i] = (s0 << 4) | s1;

        j += 2;
    }
    return 0;
}

// internal

#define bdotprod(x,y) (((c_ones[(x)&(y)]&0xff) % 2) & 0x01)
unsigned char fec_hamming84_compute_syndrome(unsigned char _r)
{
    printf("  r : 0x%.2X\n", (int)_r);
    return
        (bdotprod(_r,HAMMING84_H0) << 2) |
        (bdotprod(_r,HAMMING84_H1) << 1) |
         bdotprod(_r,HAMMING84_H2);
}

unsigned char fec_hamming84_decode_symbol(unsigned char _s)
{
    return ((0x20 & _s) >> 2) | ((0x0E & _s) >> 1);
}
