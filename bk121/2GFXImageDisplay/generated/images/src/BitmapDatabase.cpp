// 4.24.0 0xeba9687f
// Generated by imageconverter. Please, do not edit!

#include <images/BitmapDatabase.hpp>
#include <touchgfx/Bitmap.hpp>

extern const unsigned char image_clay_theme_images_backgrounds_480x272_meteor_rain[]; // BITMAP_CLAY_THEME_IMAGES_BACKGROUNDS_480X272_METEOR_RAIN_ID = 0, Size: 480x272 pixels
extern const unsigned char image_dark_theme_images_widgets_button_icon_round_micro_outline_disabled[]; // BITMAP_DARK_THEME_IMAGES_WIDGETS_BUTTON_ICON_ROUND_MICRO_OUTLINE_DISABLED_ID = 1, Size: 36x36 pixels
extern const unsigned char image_dark_theme_images_widgets_button_icon_round_micro_outline_normal[]; // BITMAP_DARK_THEME_IMAGES_WIDGETS_BUTTON_ICON_ROUND_MICRO_OUTLINE_NORMAL_ID = 2, Size: 36x36 pixels
extern const unsigned char image_error_icon_4[]; // BITMAP_ERROR_ICON_4_ID = 3, Size: 320x320 pixels
extern const unsigned char image_fh_logo[]; // BITMAP_FH_LOGO_ID = 4, Size: 380x380 pixels
extern const unsigned char image_icon_theme_images_navigation_chevron_left_36_36_27292c_svg[]; // BITMAP_ICON_THEME_IMAGES_NAVIGATION_CHEVRON_LEFT_36_36_27292C_SVG_ID = 5, Size: 36x36 pixels
extern const unsigned char image_icon_theme_images_navigation_chevron_left_36_36_474b50_svg[]; // BITMAP_ICON_THEME_IMAGES_NAVIGATION_CHEVRON_LEFT_36_36_474B50_SVG_ID = 6, Size: 36x36 pixels
extern const unsigned char image_icon_theme_images_navigation_chevron_right_36_36_2f3134_svg[]; // BITMAP_ICON_THEME_IMAGES_NAVIGATION_CHEVRON_RIGHT_36_36_2F3134_SVG_ID = 7, Size: 36x36 pixels
extern const unsigned char image_icon_theme_images_navigation_chevron_right_36_36_474b50_svg[]; // BITMAP_ICON_THEME_IMAGES_NAVIGATION_CHEVRON_RIGHT_36_36_474B50_SVG_ID = 8, Size: 36x36 pixels
extern const unsigned char image_whatsapp_icon[]; // BITMAP_WHATSAPP_ICON_ID = 9, Size: 640x642 pixels

const touchgfx::Bitmap::BitmapData bitmap_database[] = {
    { image_clay_theme_images_backgrounds_480x272_meteor_rain, 0, 480, 272, 0, 0, 480, ((uint8_t)touchgfx::Bitmap::RGB888) >> 3, 272, ((uint8_t)touchgfx::Bitmap::RGB888) & 0x7 },
    { image_dark_theme_images_widgets_button_icon_round_micro_outline_disabled, 0, 36, 36, 31, 12, 4, ((uint8_t)touchgfx::Bitmap::ARGB8888) >> 3, 12, ((uint8_t)touchgfx::Bitmap::ARGB8888) & 0x7 },
    { image_dark_theme_images_widgets_button_icon_round_micro_outline_normal, 0, 36, 36, 31, 12, 4, ((uint8_t)touchgfx::Bitmap::ARGB8888) >> 3, 12, ((uint8_t)touchgfx::Bitmap::ARGB8888) & 0x7 },
    { image_error_icon_4, 0, 320, 320, 47, 47, 226, ((uint8_t)touchgfx::Bitmap::ARGB8888) >> 3, 226, ((uint8_t)touchgfx::Bitmap::ARGB8888) & 0x7 },
    { image_fh_logo, 0, 380, 380, 0, 0, 380, ((uint8_t)touchgfx::Bitmap::RGB888) >> 3, 380, ((uint8_t)touchgfx::Bitmap::RGB888) & 0x7 },
    { image_icon_theme_images_navigation_chevron_left_36_36_27292c_svg, 0, 36, 36, 13, 16, 2, ((uint8_t)touchgfx::Bitmap::ARGB8888) >> 3, 3, ((uint8_t)touchgfx::Bitmap::ARGB8888) & 0x7 },
    { image_icon_theme_images_navigation_chevron_left_36_36_474b50_svg, 0, 36, 36, 13, 16, 2, ((uint8_t)touchgfx::Bitmap::ARGB8888) >> 3, 3, ((uint8_t)touchgfx::Bitmap::ARGB8888) & 0x7 },
    { image_icon_theme_images_navigation_chevron_right_36_36_2f3134_svg, 0, 36, 36, 19, 16, 2, ((uint8_t)touchgfx::Bitmap::ARGB8888) >> 3, 3, ((uint8_t)touchgfx::Bitmap::ARGB8888) & 0x7 },
    { image_icon_theme_images_navigation_chevron_right_36_36_474b50_svg, 0, 36, 36, 19, 16, 2, ((uint8_t)touchgfx::Bitmap::ARGB8888) >> 3, 3, ((uint8_t)touchgfx::Bitmap::ARGB8888) & 0x7 },
    { image_whatsapp_icon, 0, 640, 642, 131, 121, 379, ((uint8_t)touchgfx::Bitmap::ARGB8888) >> 3, 380, ((uint8_t)touchgfx::Bitmap::ARGB8888) & 0x7 }
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
