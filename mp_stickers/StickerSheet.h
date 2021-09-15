/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
 #pragma once
 #include "Image.h"
 
 class StickerSheet{
	 public:
		//initialize a StickerSheet with a deep copy of the base pictura and the ability to hold a max
		//amount of stickers
		StickerSheet(const Image & picture, unsigned max);
		
		//free all space dynamically allocated by StickerSheet
		~StickerSheet();
		
		//copy constructor that makes StickerSheet an independent copy of the source
		StickerSheet(const StickerSheet & other);
		
    //adds a sticker to the StickerSheet, so that the top-left of the sticker's Image is at (x, y) on the StickerSheet
		int addSticker(Image & sticker, unsigned x, unsigned y);
		
    //Modifies the maximum numbert of stickers that can be stored on this StickerSheet without changing
    //the existing stickers' indices
		void changeMaxStickers(unsigned max);
		
    //Returns a pointer to the sticker at the specified index, not a copy of it
		Image* getSticker(unsigned index);
		
    //Assignment operator for the StickerSheet class
		const StickerSheet & operator=(const StickerSheet & other);
		
    //Removes the sticker at the given zero-based layer index.
		void removeSticker(unsigned index);
		
    //Renders the whole StickerSheet on one Image and returns that Image
		Image render() const;
		
    //Changes the x and y coordinates of the Image in the specified layer
		bool translate(unsigned index, unsigned x, unsigned y);
	private:
		unsigned *_xcoord;
		unsigned *_ycoord;
		Image* base_;
		Image** _stickers;
		unsigned max_;
    //helper function for the destructor
		void _clearSheet();
    //helper function for the assignment operator and copy constructor
		void _copySheet(const StickerSheet & other);
    //helper function for functions that delete and reassign member variables
    void _updater(Image** stickers, unsigned* xcoord, unsigned* ycoord);
 };