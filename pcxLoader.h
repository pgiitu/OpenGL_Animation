#ifndef ROBS_PCX_LOADER___H_
#define ROBS_PCX_LOADER___H_


#ifdef __cplusplus
extern "C" {
#endif



/*!
 *	\brief	This function loads a ZSoft PCX File image file.
 *	\param	filename	-	the name of the file to load
 *	\param	pixels		-	pointer to the pointer that will hold the pixel data (yuck)
 *	\param	w			-	the width of the image file
 *	\param	h			-	the height of the image file
 *	\param	bpp			-	the bytes per pixel of the image file.
 *	\return	1 if ok, 0 otherwise
 */
int LoadPcxImage( const char filename[],
				  unsigned char** pixels,
				  unsigned int* w,
				  unsigned int* h,
				  unsigned int* bpp);


#ifdef __cplusplus
}
#endif


#endif

