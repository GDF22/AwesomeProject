#ifndef __HCImage_tga__
#define __HCImage_tga__

#define __HCImage_tga__MASK_TRAME				0x7F
#define __HCImage_tga__BIT_TRAME_RLE			0x80

#define __HCImage_tga__FORMAT_RAW_COLORMAPPED	1
#define __HCImage_tga__FORMAT_RLE_COLORMAPPED	9
#define __HCImage_tga__FORMAT_RAW_TRUECOLOR		2
#define __HCImage_tga__FORMAT_RLE_TRUECOLOR		10
#define __HCImage_tga__FORMAT_RAW_GREYSCALE		3
#define __HCImage_tga__FORMAT_RLE_GREYSCALE		11

unsigned char * Load_TGA(SImage &psdata);

#endif // __HCImage_tga__