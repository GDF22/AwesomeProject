#include <windows.h>
#include <stdio.h>
#include <gl/gl.h>
#include "CImage.h"
#include "CImage_JPEG.h"
#include "CImage_TGA.h"
#include "CImage_BMP.h"

// méthode de chargement d'une image
// la fonction reçoit le nom du fichier à charger
// et retourne un pointeur sur l'image en mémoire
unsigned char * CImage::Load(const char *filename) {
	SImage tmpinfos;

	tmpinfos.filename = filename;
	return this->Load(tmpinfos);
}

// méthode de chargement d'une image
// reçoit un pointeur sur une structure SImage contenant le nom du fichier à charger
// et retourne un pointeur sur l'image en mémoire
unsigned char * CImage::Load(SImage &tmpinfos) {
	unsigned char *tmpdata;
	bool rgb_ok=true;
	bool need_vflip=false;

	CString dotext(&tmpinfos.filename[tmpinfos.filename.GetLength()-4]);

	if (dotext.CompareNoCase(".jpg")) {
		tmpdata = Load_JPEG(tmpinfos);
	} else if (dotext.CompareNoCase(".tga")) {
		tmpdata = Load_TGA(tmpinfos);
		rgb_ok=false;
		need_vflip=true;
	} else if (dotext.CompareNoCase(".bmp")) {
		tmpdata = Load_BMP(tmpinfos);
	} else return NULL;

	if(!tmpdata) return NULL;
	if (this->data) this->Empty();
	this->data = tmpdata;
	this->infos = tmpinfos;
	if(!rgb_ok)	this->SwapColors(true);
	if(need_vflip) this->VFlip();
	return this->data;
}

// cette méthode renverse l'image verticalement
// reçoit et retourne aucun paramètre
void CImage::VFlip(void) {
	unsigned char tmp;
	long x,y=(this->infos.height>>1)-1;
	for(long l = this->infos.width*this->infos.bpp; y >= 0 ;y--) {
		for(x=0; x < l ;x++) {
			tmp=this->data[y*l+x];
			this->data[y*l+x]=this->data[(this->infos.height-1-y)*l+x];
			this->data[(this->infos.height-1-y)*l+x]=tmp;
		}
	}
}

// cette méthode renverse l'image horizontalement
// reçoit et retourne aucun paramètre
void CImage::HFlip(void) {
	unsigned char tmp;
	long l = this->infos.width*this->infos.bpp;
	long b,x,y=0;
	for(; y < this->infos.height ;y++) {
		for(x=0; x < (this->infos.width>>1) ;x++) {
			for(b=0; b < this->infos.bpp ;b++) {
				tmp=this->data[y*l+x*this->infos.bpp+b];
				this->data[y*l+x*this->infos.bpp+b]=this->data[y*l+(this->infos.width-1-x)*this->infos.bpp+b];
				this->data[y*l+(this->infos.width-1-x)*this->infos.bpp+b]=tmp;
			}
		}
	}
}

// cette méthode inverse l'ordre des composantes d'une image
// reçoit un booléen indiquant s'il faut garder le canal alpha ou non (dans le cas d'une image RGBA/BGRA)
// ne retourne pas de paramètre
void CImage::SwapColors (bool keep_alpha) { 
	long l;

	if((this->infos.bpp==4)&&(!keep_alpha)) {	// image RGBA->BGR ou BGRA->RGB
		l = this->infos.height*this->infos.width*3;
		unsigned char *tmp=new unsigned char[l];
		for(long dest=0,src=0; dest < l ;src+=4,dest+=3) {
			tmp[dest]   = this->data[src+2];
			tmp[dest+1] = this->data[src+1];
			tmp[dest+2] = this->data[src];
		}
		delete[] this->data;
		this->data = tmp;
		this->infos.bpp=3;
		return;
	}

	// image RGB->BGR ou BGR->RGB ou RGBA->BGRA ou encore BGRA->RGBA
	unsigned char tmp;
	l = this->infos.width*this->infos.height*this->infos.bpp;
	for(long src=0; src < l ;src+=this->infos.bpp) {
		tmp=this->data[src];
		this->data[src]=this->data[src+2];
		this->data[src+2]=tmp;
	}
}