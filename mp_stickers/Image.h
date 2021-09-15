/**
 * @file Image.h
 * Contains your declaration of the interface for the Image class.
 */

#pragma once

#include "cs225/PNG.h"

class Image : public cs225::PNG{
  public:
    Image() : cs225::PNG() {}

    Image(unsigned int width, unsigned int height) : cs225::PNG(width, height) {}

    //Lighten an image by increasing the luminance of every pixel by 0.1
    void lighten();

    //Lighten an Image by increasing the luminance of every pixel by amount
    void lighten(double amount);

    //Darken an image by decreasing the luminance of every pixel by 0.1
    void darken();

    //Darken an image by decreasing the luminance of every pixel by amount
    void darken(double amount);

    //Saturates an Image by increasing the saturation of every pixel by 0.1
    void saturate();

    //Saturates an Image by increasing the saturation of every pixel by amount
    void saturate(double amount);

    //Desaturates an Image by decreasing the saturation of every pixel by 0.1
    void desaturate();

    //Desaturates an Image by decreasing the saturation of every pixel by amount
    void desaturate(double amount);

    //Turns the image grayscale
    void grayscale();

    //Rotates the color wheel by degrees
    void rotateColor(double degrees);

    //Illinify(make orange and blue) the image
    void illinify();

    //Scale the image by a given factor
    void scale(double factor);

    //Scale the image to fit within the size (w X h)
    void scale(unsigned w, unsigned h);

};
