#include <gui/main_screen/MainView.hpp>
#include <BitmapDatabase.hpp>

MainView::MainView() : totalImages(3), currentImage(0) {}

void MainView::setupScreen()
{
    listImages = new uint16_t[totalImages];
    MainViewBase::setupScreen();

    listImages[0] = BITMAP_ERROR_ICON_4_ID;
    listImages[1] = BITMAP_FH_LOGO_ID;
    listImages[2] = BITMAP_WHATSAPP_ICON_ID;

    // Ruta al archivo BMP en la tarjeta SD
    const char* filePath = "a.bmp";
    touchgfx::BitmapId dynamicBmp;

    // Cargar imagen desde la tarjeta SD
    if (loadBitmapFromSD(filePath, dynamicBmp)) {
        ImageDisplayed.setBitmap(touchgfx::Bitmap(dynamicBmp));
        ImageDisplayed.setPosition(63, 33, 356, 206);
        add(ImageDisplayed);
    } 
    else {
        ImageDisplayed.setBitmap(touchgfx::Bitmap(BITMAP_ERROR_ICON_4_ID));
        ImageDisplayed.setPosition(63, 33, 356, 206);
        ImageDisplayed.setOffset(0, 0);
        add(ImageDisplayed);
    }

}

void MainView::tearDownScreen()
{
    MainViewBase::tearDownScreen();
}


void MainView::handleClickPrevious()
{
    currentImage = (currentImage + totalImages - 1) % totalImages;
    displayImage();
}

void MainView::handleClickNext()
{
    currentImage = (currentImage + totalImages + 1) % totalImages;
    displayImage();
}

void MainView::displayImage()
{
    ImageDisplayed.setBitmap(touchgfx::Bitmap(listImages[currentImage]));
    ImageDisplayed.setPosition(63, 33, 356, 206);
    ImageDisplayed.setOffset(0, 0);
    ImageDisplayed.invalidate();
}


bool MainView::loadBitmapFromSD(const char* filePath, touchgfx::BitmapId& bmpId)
{
    FIL file;
    UINT bytesRead;

    // Abre el archivo en la tarjeta SD
    if (f_open(&file, filePath, FA_READ) != FR_OK) {
        printf("Error al abrir el archivo BMP: %s\n", filePath);
        return false;
    }

    // Lee el contenido del archivo BMP al buffer
    if (f_read(&file, bmpBuffer, BMP_BUFFER_SIZE, &bytesRead) != FR_OK) {
        printf("Error al leer el archivo BMP\n");
        f_close(&file);
        return false;
    }

    f_close(&file);

    // Crea un bitmap dinámico en TouchGFX usando el buffer
    bmpId = Bitmap::dynamicBitmapCreate(width, height, Bitmap::RGB888);
    if (bmpId == BITMAP_INVALID) {
        printf("Error al crear el bitmap dinámico\n");
        return false;
    }

    uint8_t* dynamicBitmapData = Bitmap::dynamicBitmapGetAddress(bmpId);
    memcpy(dynamicBitmapData, bmpBuffer, bytesRead);
    return true;
}
