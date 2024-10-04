#ifndef MAIN_VIEW_HPP
#define MAIN_VIEW_HPP

#include <gui_generated/main_screen/MainViewBase.hpp>
#include <gui/main_screen/MainPresenter.hpp>
#include <touchgfx/containers/ZoomAnimationImage.hpp>


class MainView : public MainViewBase
{
public:
    MainView();
    virtual ~MainView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    void animationEndedHandler(const ZoomAnimationImage& image);

protected:

private:
    ZoomAnimationImage zoomAnimationImage;

    int currentAnimation;

    Callback<MainView, const ZoomAnimationImage&> animationEndedCallback;
};

#endif // MAIN_VIEW_HPP
