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

    void updateValue(uint8_t* newValue);
protected:

private:
    uint8_t count;
};

#endif // MAIN_VIEW_HPP
