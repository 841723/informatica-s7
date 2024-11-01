// 4.24.0 0x0799663c
// Generated by imageconverter. Please, do not edit!

#include <images/BitmapDatabase.hpp>
#include <touchgfx/Bitmap.hpp>

extern const unsigned char image_alternate_theme_images_widgets_button_regular_height_50_medium_rounded_normal[]; // BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_REGULAR_HEIGHT_50_MEDIUM_ROUNDED_NORMAL_ID = 0, Size: 240x50 pixels
extern const unsigned char image_alternate_theme_images_widgets_button_regular_height_50_medium_rounded_pressed[]; // BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_REGULAR_HEIGHT_50_MEDIUM_ROUNDED_PRESSED_ID = 1, Size: 240x50 pixels
extern const unsigned char image_bg[]; // BITMAP_BG_ID = 2, Size: 480x272 pixels
extern const unsigned char image_image00[]; // BITMAP_IMAGE00_ID = 3, Size: 200x200 pixels
extern const unsigned char image_image01_large[]; // BITMAP_IMAGE01_LARGE_ID = 4, Size: 200x200 pixels
extern const unsigned char image_image01_small[]; // BITMAP_IMAGE01_SMALL_ID = 5, Size: 100x100 pixels

const touchgfx::Bitmap::BitmapData bitmap_database[] = {
    { image_alternate_theme_images_widgets_button_regular_height_50_medium_rounded_normal, 0, 240, 50, 5, 0, 230, ((uint8_t)touchgfx::Bitmap::ARGB8888) >> 3, 50, ((uint8_t)touchgfx::Bitmap::ARGB8888) & 0x7 },
    { image_alternate_theme_images_widgets_button_regular_height_50_medium_rounded_pressed, 0, 240, 50, 5, 0, 230, ((uint8_t)touchgfx::Bitmap::ARGB8888) >> 3, 50, ((uint8_t)touchgfx::Bitmap::ARGB8888) & 0x7 },
    { image_bg, 0, 480, 272, 0, 0, 480, ((uint8_t)touchgfx::Bitmap::RGB565) >> 3, 272, ((uint8_t)touchgfx::Bitmap::RGB565) & 0x7 },
    { image_image00, 0, 200, 200, 0, 0, 200, ((uint8_t)touchgfx::Bitmap::RGB565) >> 3, 200, ((uint8_t)touchgfx::Bitmap::RGB565) & 0x7 },
    { image_image01_large, 0, 200, 200, 0, 0, 200, ((uint8_t)touchgfx::Bitmap::RGB565) >> 3, 200, ((uint8_t)touchgfx::Bitmap::RGB565) & 0x7 },
    { image_image01_small, 0, 100, 100, 0, 0, 100, ((uint8_t)touchgfx::Bitmap::RGB565) >> 3, 100, ((uint8_t)touchgfx::Bitmap::RGB565) & 0x7 }
};

namespace BitmapDatabase
{
const touchgfx::Bitmap::BitmapData* getInstance()
{
    return bitmap_database;
}

uint16_t getInstanceSize()
{
    return (uint16_t)(sizeof(bitmap_database) / sizeof(touchgfx::Bitmap::BitmapData));
}
} // namespace BitmapDatabase
