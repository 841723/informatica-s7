// 4.24.0 0xd16372ee
// Generated by imageconverter. Please, do not edit!

#include <images/BitmapDatabase.hpp>
#include <touchgfx/Bitmap.hpp>

extern const unsigned char image_dark_theme_images_backgrounds_480x272_hive[]; // BITMAP_DARK_THEME_IMAGES_BACKGROUNDS_480X272_HIVE_ID = 0, Size: 480x272 pixels

const touchgfx::Bitmap::BitmapData bitmap_database[] = {
    { image_dark_theme_images_backgrounds_480x272_hive, 0, 480, 272, 0, 0, 480, ((uint8_t)touchgfx::Bitmap::RGB565) >> 3, 272, ((uint8_t)touchgfx::Bitmap::RGB565) & 0x7 }
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