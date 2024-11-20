#ifndef MAIN_VIEW_HPP
#define MAIN_VIEW_HPP

#include <gui_generated/main_screen/MainViewBase.hpp>
#include <gui/main_screen/MainPresenter.hpp>
#include <touchgfx/widgets/TiledImage.hpp>
#include <images/BitmapDatabase.hpp>

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
};

#endif // MAIN_VIEW_HPP
