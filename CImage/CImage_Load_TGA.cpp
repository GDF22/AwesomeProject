#include <stdio.h>
#include "CImage.h"
#include "CImage_TGA.h"

#pragma pack(push,1)

typedef struct {
	unsigned short FirstEntryIndex,ColorMapLength;
	unsigned char ColorMapEntrySize;
}ColorMapSpec;

typedef struct {
	unsigned short XOrigin,YOrigin,Width,Height;
	unsigned char PixelDepth,ImageDescriptor;
}ImageSpec;

typedef struct {
	unsigned char ID_Length,ColorMapType,ImageType;
	ColorMapSpec CMSpec;
	ImageSpec ISpec;
}TGAheader;

typedef struct {
	unsigned long ExtensionArea,DevelopperDirectory;
	unsigned char Signature[18];
}TGAfooter;

#pragma pack(pop,1)

unsigned char * Load_TGA(SImage &psdata) { // charge une image TGA et renvoie un pointeur sur le buffer la contenant
	unsigned char *buf = NULL;
	unsigned long *TGAcolor;
	unsigned char tmp;
	unsigned short itmp;
	long pixels,i;

	FILE *fp=fopen(psdata.filename,"rb");
	if(!fp) return NULL; // s'il est impossible d'ouvrir le fichier
	// Lecture du header
	TGAheader head;
	fread(&head,1,sizeof(TGAheader),fp);
	if(head.ImageType == 0) { // si pas d'image stockée
		fclose(fp); // on quitte
		return NULL;
	}

	// on enregistre les dimensions de l'image
	psdata.width = head.ISpec.Width;
	psdata.height = head.ISpec.Height;
	// on se positionne après l'id de l'image si elle existe
	if(head.ID_Length > 0) fseek(fp,head.ID_Length,SEEK_CUR);

	switch(head.ISpec.PixelDepth) {
	case 8: // image 8 bits par pixel
		// si aucune table des couleurs n'est déclarée
		if(head.ColorMapType == 0) {
			switch(head.ImageType) {
			case __HCImage_tga__FORMAT_RAW_GREYSCALE:
			case __HCImage_tga__FORMAT_RLE_GREYSCALE: // l'image doit être en niveaux de gris
			case __HCImage_tga__FORMAT_RAW_COLORMAPPED:
			case __HCImage_tga__FORMAT_RLE_COLORMAPPED: // ou palettisée
				break;
			default:
				fclose(fp); //  sinon le format d'image est incorrect
				return NULL;
			}
		}
		fseek(fp,head.CMSpec.FirstEntryIndex,SEEK_CUR);
		switch(head.CMSpec.ColorMapEntrySize) {
		case 0:	// palette à 0 bit par couleur = mode niveaux de gris
			psdata.bpp = 1; // niveaux de gris
			buf = new unsigned char[psdata.width*psdata.height*3];
			if(head.ImageType == __HCImage_tga__FORMAT_RAW_GREYSCALE) { // palette en niveaux de gris et image non compressée
				for(pixels=0; pixels < (psdata.width*psdata.height) ;pixels++) {
					fread(&tmp,1,1,fp);
					buf[pixels*3] = tmp;
					buf[pixels*3+1] = tmp;
					buf[pixels*3+2] = tmp;
				}
			} else if(head.ImageType == __HCImage_tga__FORMAT_RLE_GREYSCALE) { // palette en niveaux de gris et image compressée RLE
				for(pixels=0; pixels < (psdata.width*psdata.height) ;pixels++) {
					fread(&tmp,1,1,fp);
					itmp = (short)(tmp&__HCImage_tga__MASK_TRAME);
					if(tmp&__HCImage_tga__BIT_TRAME_RLE) { // trame RLE
						fread(&tmp,1,1,fp);
						buf[pixels*3] = tmp;
						buf[pixels*3+1] = tmp;
						buf[pixels*3+2] = tmp;
						for(i=0,pixels++; (i < itmp) && (pixels < (psdata.width*psdata.height)) ;i++,pixels++) {
							buf[pixels*3] = tmp;
							buf[pixels*3+1] = tmp;
							buf[pixels*3+2] = tmp;
						}
						if(i < tmp) {
							delete[] buf;
							fclose(fp);
							return NULL;
						}
					} else { // trame RAW
						for(i=0; (i <= itmp) && (pixels < (psdata.width*psdata.height)) ;i++,pixels++) {
							fread(&tmp,1,1,fp);
							buf[pixels*3] = tmp;
							buf[pixels*3+1] = tmp;
							buf[pixels*3+2] = tmp;
						}
						if(i <= tmp) {
							delete[] buf;
							fclose(fp);
							return NULL;
						}
					}
				}
			} else { //  le format d'image est incorrect alors on quitte
				delete[] buf;
				fclose(fp);
				return NULL;
			}
			break;
		case 15: // palette en 15
		case 16: // ou 16 bits par couleur
			psdata.bpp = 3;
			TGAcolor = new unsigned long[head.CMSpec.ColorMapLength];
			for(i = 0; i < head.CMSpec.ColorMapLength ; i++) { // on charge la palette et on la convertit en 24 bits
				fread(&itmp,1,2,fp);
				TGAcolor[i] = ((((long)itmp)&0x001F)<<3) + ((((long)itmp)&0x03E0)<<6) + ((((long)itmp)&0x7C00)<<9);
			}
			buf = new unsigned char[psdata.width*psdata.height*3];
			if(head.ImageType == __HCImage_tga__FORMAT_RAW_COLORMAPPED) { // palette truecolor et image non compressée
				for(pixels=0; pixels < (psdata.width*psdata.height) ;pixels++) {
					fread(&tmp,1,1,fp);
					buf[pixels*3] = (unsigned char)TGAcolor[tmp];
					buf[pixels*3+1] = (unsigned char)(TGAcolor[tmp]>>8);
					buf[pixels*3+2] = (unsigned char)(TGAcolor[tmp]>>16);
				}
			} else if(head.ImageType == __HCImage_tga__FORMAT_RLE_COLORMAPPED) { // palette truecolor et image compressée RLE
				for(pixels=0; pixels < (psdata.width*psdata.height) ;pixels++) {
					fread(&tmp,1,1,fp);
					itmp = (short)(tmp&__HCImage_tga__MASK_TRAME);
					if(tmp&__HCImage_tga__BIT_TRAME_RLE) { // trame RLE
						fread(&tmp,1,1,fp);
						for(i=0; (i <= itmp) && (pixels < (psdata.width*psdata.height)) ;i++,pixels++) {
							buf[pixels*3] = (unsigned char)TGAcolor[tmp];
							buf[pixels*3+1] = (unsigned char)(TGAcolor[tmp]>>8);
							buf[pixels*3+2] = (unsigned char)(TGAcolor[tmp]>>16);
						}
						if(i <= tmp) {
							delete[] buf;
							fclose(fp);
							return NULL;
						}
					} else { // trame RAW
						for(i=0; (i <= itmp) && (pixels < (psdata.width*psdata.height)) ;i++,pixels++) {
							fread(&tmp,1,1,fp);
							buf[pixels*3] = (unsigned char)TGAcolor[tmp];
							buf[pixels*3+1] = (unsigned char)(TGAcolor[tmp]>>8);
							buf[pixels*3+2] = (unsigned char)(TGAcolor[tmp]>>16);
						}
						if(i <= tmp) {
							delete[] buf;
							fclose(fp);
							return NULL;
						}
					}
				}
			} else { //  le format d'image est incorrect alors on quitte
				delete[] buf;
				fclose(fp);
				return NULL;
			}
			delete[] TGAcolor;
			break;
		case 24: // palette en 24 bits par couleur
			psdata.bpp = 3;
			TGAcolor = new unsigned long[head.CMSpec.ColorMapLength];
			for(i=0; i < head.CMSpec.ColorMapLength ; i++) fread(&TGAcolor[i],1,3,fp); // on charge la palette 24 bits
			buf = new unsigned char[psdata.width*psdata.height*3];
			if(head.ImageType == __HCImage_tga__FORMAT_RAW_COLORMAPPED) { // palette truecolor et image non compressée
				for(pixels=0; pixels < (psdata.width*psdata.height) ;pixels++) {
					fread(&tmp,1,1,fp);
					buf[pixels*3] = (unsigned char)TGAcolor[tmp];
					buf[pixels*3+1] = (unsigned char)(TGAcolor[tmp]>>8);
					buf[pixels*3+2] = (unsigned char)(TGAcolor[tmp]>>16);
				}
			} else if(head.ImageType == __HCImage_tga__FORMAT_RLE_COLORMAPPED) { // palette truecolor et image compressée RLE
				for(pixels=0; pixels < (psdata.width*psdata.height) ;pixels++) {
					fread(&tmp,1,1,fp);
					itmp = (short)(tmp&__HCImage_tga__MASK_TRAME);
					if(tmp&__HCImage_tga__BIT_TRAME_RLE) { // trame RLE
						fread(&tmp,1,1,fp);
						for(i=0; (i <= itmp) && (pixels < (psdata.width*psdata.height)) ;i++,pixels++) {
							buf[pixels*3] = (unsigned char)TGAcolor[tmp];
							buf[pixels*3+1] = (unsigned char)(TGAcolor[tmp]>>8);
							buf[pixels*3+2] = (unsigned char)(TGAcolor[tmp]>>16);
						}
						if(i <= tmp) {
							delete[] buf;
							fclose(fp);
							return NULL;
						}
					} else { // trame RAW
						for(i=0; (i <= itmp) && (pixels < (psdata.width*psdata.height)) ;i++,pixels++) {
							fread(&tmp,1,1,fp);
							buf[pixels*3] = (unsigned char)TGAcolor[tmp];
							buf[pixels*3+1] = (unsigned char)(TGAcolor[tmp]>>8);
							buf[pixels*3+2] = (unsigned char)(TGAcolor[tmp]>>16);
						}
						if(i <= tmp) {
							delete[] buf;
							fclose(fp);
							return NULL;
						}
					}
				}
			} else { //  le format d'image est incorrect alors on quitte
				delete[] buf;
				fclose(fp);
				return NULL;
			}
			delete[] TGAcolor;
			break;
		case 32: // palette 32 bits par couleur -> canal alpha
			psdata.bpp = 4;
			TGAcolor = new unsigned long[head.CMSpec.ColorMapLength];
			for(i=0; i < head.CMSpec.ColorMapLength ; i++) fread(&TGAcolor[i],1,4,fp); // on charge la palette 32 bits avec l'alpha
			buf = new unsigned char[psdata.width*psdata.height*4];
			if(head.ImageType == __HCImage_tga__FORMAT_RAW_COLORMAPPED) { // palette truecolor et image non compressée
				for(pixels=0; pixels < (psdata.width*psdata.height) ;pixels++) {
					fread(&tmp,1,1,fp);
					buf[pixels*3] = (unsigned char)TGAcolor[tmp];
					buf[pixels*3+1] = (unsigned char)(TGAcolor[tmp]>>8);
					buf[pixels*3+2] = (unsigned char)(TGAcolor[tmp]>>16);
					buf[pixels*3+3] = (unsigned char)(TGAcolor[tmp]>>24);
				}
			} else if(head.ImageType == __HCImage_tga__FORMAT_RLE_COLORMAPPED) { // palette truecolor et image compressée RLE
				for(pixels=0; pixels < (psdata.width*psdata.height) ;pixels++) {
					fread(&tmp,1,1,fp);
					itmp = (short)(tmp&__HCImage_tga__MASK_TRAME);
					if(tmp&__HCImage_tga__BIT_TRAME_RLE) { // trame RLE
						fread(&tmp,1,1,fp);
						for(i=0; (i <= itmp) && (pixels < (psdata.width*psdata.height)) ;i++,pixels++) {
							buf[pixels*3] = (unsigned char)TGAcolor[tmp];
							buf[pixels*3+1] = (unsigned char)(TGAcolor[tmp]>>8);
							buf[pixels*3+2] = (unsigned char)(TGAcolor[tmp]>>16);
							buf[pixels*3+3] = (unsigned char)(TGAcolor[tmp]>>24);
						}
						if(i <= tmp) {
							delete[] buf;
							fclose(fp);
							return NULL;
						}
					} else { // trame RAW
						for(i=0; (i <= itmp) && (pixels < (psdata.width*psdata.height)) ;i++,pixels++) {
							fread(&tmp,1,1,fp);
							buf[pixels*3] = (unsigned char)TGAcolor[tmp];
							buf[pixels*3+1] = (unsigned char)(TGAcolor[tmp]>>8);
							buf[pixels*3+2] = (unsigned char)(TGAcolor[tmp]>>16);
							buf[pixels*3+3] = (unsigned char)(TGAcolor[tmp]>>24);
						}
						if(i <= tmp) {
							delete[] buf;
							fclose(fp);
							return NULL;
						}
					}
				}
			} else { //  le format d'image est incorrect alors on quitte
				delete[] buf;
				fclose(fp);
				return NULL;
			}
			delete[] TGAcolor;
			break;
		default:	// format d'image non supporté
			fclose(fp);
			return NULL;
			break;
		}
		break;
	case 15 : // image 15
	case 16 : // ou 16 bits par pixel
		if(head.ColorMapType != 0) { // si une table des couleurs est déclarée
			fclose(fp); //  alors le format d'image est incorrect
			return NULL;
		}
		if(head.CMSpec.ColorMapLength > 0) fseek(fp,head.CMSpec.ColorMapLength+head.CMSpec.FirstEntryIndex,SEEK_CUR);
		buf = new unsigned char[head.ISpec.Width*head.ISpec.Height*3];
		psdata.bpp = 3;
		if(head.ImageType == __HCImage_tga__FORMAT_RAW_TRUECOLOR) { // image truecolor non compressée
			for(pixels=0; pixels < (psdata.width*psdata.height) ;pixels++) {
				fread(&itmp,1,2,fp);
				buf[pixels*3] = (unsigned char)((((long)itmp)&0x001F)<<3);
				buf[pixels*3+1] = (unsigned char)((((long)itmp)&0x03E0)>>2);
				buf[pixels*3+2] = (unsigned char)((((long)itmp)&0x7C00)>>7);
			}
		} else if(head.ImageType == __HCImage_tga__FORMAT_RLE_TRUECOLOR) { // image truecolor compressée RLE
			for(pixels=0; pixels < (psdata.width*psdata.height) ;) {
				fread (&tmp,1,1,fp);
				if(tmp&__HCImage_tga__BIT_TRAME_RLE) { // trame RLE
					tmp &= __HCImage_tga__MASK_TRAME;
					fread(&itmp,1,2,fp);
					buf[pixels*3] = (unsigned char)((((long)itmp)&0x001F)<<3);
					buf[pixels*3+1] = (unsigned char)((((long)itmp)&0x03E0)>>2);
					buf[pixels*3+2] = (unsigned char)((((long)itmp)&0x7C00)>>7);
					for(i=0,pixels++; (i < tmp) && (pixels < (psdata.width*psdata.height));i++,pixels++) {
						buf[pixels*3] = buf[(pixels-1)*3];
						buf[pixels*3+1] = buf[(pixels-1)*3+1];
						buf[pixels*3+2] = buf[(pixels-1)*3+2];
					}
					if(i < tmp) {
						delete[] buf;
						fclose(fp);
						return NULL;
					}
				} else { // trame RAW
					for(i=0; (i <= tmp) && (pixels < (psdata.width*psdata.height)) ;i++,pixels++) {
						fread(&itmp,1,2,fp);
						buf[pixels*3] = (unsigned char)((((long)itmp)&0x001F)<<3);
						buf[pixels*3+1] = (unsigned char)((((long)itmp)&0x03E0)>>2);
						buf[pixels*3+2] = (unsigned char)((((long)itmp)&0x7C00)>>7);
					}
					if(i <= tmp) {
						delete[] buf;
						fclose(fp);
						return NULL;
					}
				}
			}
		}
		break;
	case 24: // image 24 bits par pixel
		if(head.ColorMapType != 0) { // si une table des couleurs est déclarée
			fclose(fp); //  alors le format d'image est incorrect
			return NULL;
		}
		if(head.CMSpec.ColorMapLength > 0) fseek(fp,head.CMSpec.ColorMapLength+head.CMSpec.FirstEntryIndex,SEEK_CUR);
		buf = new unsigned char[head.ISpec.Width*head.ISpec.Height*3];
		psdata.bpp = 3;
		if(head.ImageType == __HCImage_tga__FORMAT_RAW_TRUECOLOR) fread(buf,1,head.ISpec.Width*head.ISpec.Height*3,fp); // image truecolor non compressée
		else if(head.ImageType == __HCImage_tga__FORMAT_RLE_TRUECOLOR) { // image truecolor compressée RLE
			for(pixels=0; pixels < (psdata.width*psdata.height) ;) {
				fread(&tmp,1,1,fp);
				if(tmp&__HCImage_tga__BIT_TRAME_RLE) { // trame RLE
					tmp &= __HCImage_tga__MASK_TRAME;
					fread(&buf[pixels*3],1,3,fp);
					for(i=0,pixels++;(i<tmp)&&(pixels < (psdata.width*psdata.height));i++,pixels++) {
						buf[pixels*3] = buf[(pixels-1)*3];
						buf[pixels*3+1] = buf[(pixels-1)*3+1];
						buf[pixels*3+2] = buf[(pixels-1)*3+2];
					}
					if(i < tmp) {
						delete[] buf;
						fclose(fp);
						return NULL;
					}
				} else { // trame RAW
					fread(&buf[pixels*3],1,3*(tmp+1),fp);
					pixels += tmp+1;
				}
			}
		} else { // pas le bon type d'image
			delete[] buf;
			fclose(fp);
			return NULL;
		}
		break;
	case 32: // image 32 bits par pixel (24 bits + canal alpha)
		if(head.ColorMapType != 0) { // si une table des couleurs est déclarée
			fclose(fp); //  alors le format d'image est incorrect
			return NULL;
		}
		if(head.CMSpec.ColorMapLength > 0) fseek(fp,head.CMSpec.ColorMapLength+head.CMSpec.FirstEntryIndex,SEEK_CUR);
		buf = new unsigned char[head.ISpec.Width*head.ISpec.Height*4];
		psdata.bpp = 4;
		if(head.ImageType == __HCImage_tga__FORMAT_RAW_TRUECOLOR) fread(buf,1,head.ISpec.Width*head.ISpec.Height*4,fp); // image truecolor non compressée
		else if(head.ImageType == __HCImage_tga__FORMAT_RLE_TRUECOLOR) { // image truecolor compressée RLE
			for(pixels=0; pixels < (psdata.width*psdata.height) ;) {
				fread(&tmp,1,1,fp);
				if(tmp&__HCImage_tga__BIT_TRAME_RLE) { // trame RLE
					tmp &= __HCImage_tga__MASK_TRAME;
					fread(&buf[pixels*4],1,4,fp);
					for(i=0,pixels++;(i<tmp)&&(pixels < (psdata.width*psdata.height));i++,pixels++) {
						buf[pixels*4] = buf[(pixels-1)*4];
						buf[pixels*4+1] = buf[(pixels-1)*4+1];
						buf[pixels*4+2] = buf[(pixels-1)*4+2];
						buf[pixels*4+3] = buf[(pixels-1)*4+3];
					}
					if(i < tmp) {
						delete[] buf;
						fclose(fp);
						return NULL;
					}
				} else { // trame RAW
					fread(&buf[pixels*4],1,4*(tmp+1),fp);
					pixels += tmp+1;
				}
			}
		} else { // pas le bon type d'image
			delete[] buf;
			fclose(fp);
			return NULL;
		}
		break;
	}

	fclose(fp);
	return buf;
}
