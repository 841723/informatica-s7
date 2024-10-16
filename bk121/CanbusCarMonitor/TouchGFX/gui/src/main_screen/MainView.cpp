#include <gui/main_screen/MainView.hpp>
#include <BitmapDatabase.hpp>
#include <touchgfx/EasingEquations.hpp>

MainView::MainView()
{
}

void MainView::setupScreen()
{
    
}

void MainView::tearDownScreen()
{
}


void MainView::updateValue(uint8_t* newValue)
{
    count++;
    Unicode::snprintf(textBuffer, TEXT_SIZE, "%d", count);
    text.invalidate();
}
