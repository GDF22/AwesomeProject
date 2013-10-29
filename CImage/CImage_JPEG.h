#ifndef __HCImage_jpeg__
#define __HCImage_jpeg__ 

unsigned char * Load_JPEG(SImage &infos);
bool Save_JPEG(SImage &infos,unsigned char *buffer,unsigned short scalefactor);

#endif // __HCImage_jpeg__