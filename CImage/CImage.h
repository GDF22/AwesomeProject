#ifndef __HCImage__
#define __HCImage__ 

#include "../Mathlib.h"
#include "../CString.h"

typedef struct {
	CString filename;
	unsigned short width,height,bpp;
}SImage;

class CImage {
public:
	// Constructeurs
	CImage(void) {
		this->data = NULL;
		this->Empty();
	}
	CImage(const char *filename) {
		this->data = NULL;
		this->Load(filename);
	}
	CImage(SImage &infos) {
		this->data = NULL;
		this->Load(infos);
	}
	~CImage() { this->Empty(); }

	void Empty(void) { // vide le tampon et remet à zéro les paramètres
		if (this->data)
			delete[] this->data;
		this->infos.height = 0;
		this->infos.width = 0;
		this->infos.bpp = 0;
	}
	// méthodes de chargement d'image, reconnait le format d'après l'extension du fichier
	unsigned char * Load(const char *filename);
	unsigned char * Load(const CString &filename);
	unsigned char * Load(SImage &infos);
	void VFlip(void); // renverse l'image verticalement
	void HFlip(void); // renverse l'image horizontalement
	void SwapColors(bool keep_alpha); // inverse les couleurs rouge et bleu de l'image

	unsigned char *data; // les pixels de l'image
	SImage infos; // les infos de l'image
};

#endif // __HCImage__