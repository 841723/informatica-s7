#ifndef MAIN_VIEW_HPP
#define MAIN_VIEW_HPP

#include <gui_generated/main_screen/MainViewBase.hpp>
#include <gui/main_screen/MainPresenter.hpp>

class MainView : public MainViewBase
{
public:
    MainView();
    virtual ~MainView(){}
    virtual void setupScreen();
    virtual void tearDownScreen();

    void handleClickPrev();
private:

  int counter[7] = {0, 0, 0, 0, 0, 0, 0};
};

#endif // MAIN_VIEW_HPP
