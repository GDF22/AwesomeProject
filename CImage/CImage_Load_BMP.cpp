#include <windows.h>
#include <gl/gl.h>
#include <gl/glaux.h>
#include "CImage.h"

// fonction de chargement d'une image BMP
// reçoit un pointeur sur une structure SImage contenant le nom du fichier à charger
// renvoie un pointeur sur le buffer contenant l'image
unsigned char * Load_BMP(SImage &psdata) {
	AUX_RGBImageRec *bmpHeader;
	bmpHeader = auxDIBImageLoad(psdata.filename);
	if (!bmpHeader) return NULL;

	psdata.width = bmpHeader->sizeX;
	psdata.height = bmpHeader->sizeY;
	psdata.bpp = 3;

	return bmpHeader->data;
}
