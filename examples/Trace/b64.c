/*********************************************************************\

                This little utility implements the Base64
                Content-Transfer-Encoding standard described in
                RFC1113 (http://www.faqs.org/rfcs/rfc1113.html).

LICENCE:        Copyright (c) 2001 Bob Trower, Trantor Standard Systems Inc.

                Permission is hereby granted, free of charge, to any person
                obtaining a copy of this software and associated
                documentation files (the "Software"), to deal in the
                Software without restriction, including without limitation
                the rights to use, copy, modify, merge, publish, distribute,
                sublicense, and/or sell copies of the Software, and to
                permit persons to whom the Software is furnished to do so,
                subject to the following conditions:

                The above copyright notice and this permission notice shall
                be included in all copies or substantial portions of the
                Software.

                THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY
                KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
                WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
                PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
                OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
                OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
                OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
                SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

\******************************************************************* */

#include "b64.h"

#include <assert.h>

/* Translation table as described in RFC1113 */

static const char b64EncodeTable[64] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

/* Inverse Table */

static const unsigned int b64DecodeTable[256] =
{
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  62,   0,   0,   0,  63,
  52,  53,  54,  55,  56,  57,  58,  59,  60,  61,   0,   0,   0,   0,   0,   0,
   0,   0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,
  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,   0,   0,   0,   0,   0,
   0,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,  40,
  41,  42,  43,  44,  45,  46,  47,  48,  49,  50,  51,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0
};

/*
** encode 3 8-bit binary bytes as 4 '6-bit' characters
*/
void b64EncodeBlock(char *out, const unsigned char *in, const int len)
{
  const unsigned char i0 = len>0 ? in[0] : 0;
  const unsigned char i1 = len>1 ? in[1] : 0;
  const unsigned char i2 = len>2 ? in[2] : 0;

  assert(len>=1);

  out[0] = b64EncodeTable[ i0 >> 2 ];
  out[1] = b64EncodeTable[ ((i0 & 0x03) << 4) | ((i1 & 0xf0) >> 4) ];
  out[2] = (unsigned char) (len > 1 ? b64EncodeTable[ ((i1 & 0x0f) << 2) | ((i2 & 0xc0) >> 6) ] : '=');
  out[3] = (unsigned char) (len > 2 ? b64EncodeTable[ i2 & 0x3f ] : '=');
}

/*
** decodeblock
**
** decode 4 '6-bit' characters into 3 8-bit binary bytes
*/
void b64DecodeBlock(unsigned char *out, const char *in, const int len)
{
  assert(len>=1);

  if (len<1) return; out[0] = (unsigned char) (  b64DecodeTable[(unsigned char) in[0]] << 2          | b64DecodeTable[(unsigned char) in[1]] >> 4);
  if (len<2) return; out[1] = (unsigned char) (  b64DecodeTable[(unsigned char) in[1]] << 4          | b64DecodeTable[(unsigned char) in[2]] >> 2);
  if (len<3) return; out[2] = (unsigned char) (((b64DecodeTable[(unsigned char) in[2]] << 6) & 0xc0) | b64DecodeTable[(unsigned char) in[3]]     );
}

void b64Encode(FILE *file, const void *buffer, const int len)
{
  char out[5] = { 0,0,0,0,0 };
  int i;

  if (!len)
    return;

  /* For trace purposes use '=' prefix to make parsing easy */

  fprintf(file,"=");

  for (i=0; i<len; i+=3)
  {
    b64EncodeBlock(out,(const unsigned char *)(buffer)+i,(len-i)<3 ? (len-i) : 3);
    fprintf(file,"%s",out);
  }
}
