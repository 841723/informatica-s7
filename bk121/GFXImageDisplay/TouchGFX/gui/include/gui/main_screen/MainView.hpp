#ifndef MAIN_VIEW_HPP
#define MAIN_VIEW_HPP

#include <stdio.h>
#include <gui_generated/main_screen/MainViewBase.hpp>
#include <gui/main_screen/MainPresenter.hpp>
#include <images/BitmapDatabase.hpp>
#include <touchgfx/widgets/TiledImage.hpp>
#include <touchgfx/hal/OSWrappers.hpp>
#include <touchgfx/Bitmap.hpp>

// #include <drv.h>

#define BMP_BUFFER_SIZE (1024 * 1024)

class MainView : public MainViewBase
{
public:
    MainView();
    virtual ~MainView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    void handleClickPrevious();
    void handleClickNext();

protected:

private:
    void displayImage();
    touchgfx::TiledImage ImageDisplayed;
    
    uint16_t totalImages;
    uint16_t *listImages;
    uint16_t currentImage;

    BitmapId bmpId;
    uint8_t bmpBuffer[BMP_BUFFER_SIZE];
};

#endif // MAIN_VIEW_HPP
