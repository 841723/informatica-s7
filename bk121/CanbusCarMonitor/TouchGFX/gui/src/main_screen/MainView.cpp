#include <gui/main_screen/MainView.hpp>
#include <BitmapDatabase.hpp>
#include <touchgfx/EasingEquations.hpp>

MainView::MainView() :
    currentAnimation(0),
    animationEndedCallback(this, &MainView::animationEndedHandler)
{
}

void MainView::setupScreen()
{
    // Setup ZoomAnimationImage
    zoomAnimationImage.setBitmaps(Bitmap(BITMAP_IMAGE01_SMALL_ID), Bitmap(BITMAP_IMAGE01_LARGE_ID));
    zoomAnimationImage.setPosition(100, 10, 100, 100);

    // Attach method callback for the animation. This callback is called
    // when an animation ends
    zoomAnimationImage.setAnimationEndedCallback(animationEndedCallback);

    // Start animation
    zoomAnimationImage.startZoomAndMoveAnimation(240, 40, 200, 200, 30);

    add(zoomAnimationImage);
}

void MainView::tearDownScreen()
{
}

// Handle one animation end by starting another.
void MainView::animationEndedHandler(const ZoomAnimationImage& image)
{
    currentAnimation = (currentAnimation + 1) % 2;

    if (currentAnimation == 0)
    {
        zoomAnimationImage.startZoomAndMoveAnimation(240, 40,200, 200, 60);
    }
    else if (currentAnimation == 1)
    {
        zoomAnimationImage.startZoomAndMoveAnimation(0, 40,200, 200, 60);
    }
}
