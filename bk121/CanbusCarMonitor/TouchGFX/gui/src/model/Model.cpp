#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

// #include <messages_types.h>
#include <C:\Users\diego\Desktop\unizar\informatica-s7\bk121\CanbusCarMonitor\Core\Inc\messages_types.h>

// #include "FreeRTOS.h"
#include "C:\Users\diego\Desktop\unizar\informatica-s7\bk121\CanbusCarMonitor\Middlewares\Third_Party\FreeRTOS\Source\include\FreeRTOS.h"

// #include "queue.h"
#include "C:\Users\diego\Desktop\unizar\informatica-s7\bk121\CanbusCarMonitor\Middlewares\Third_Party\FreeRTOS\Source\include\queue.h"

QueueHandle_t xQueueGenericCreatePtrDIEGO(UBaseType_t uxQueueLength, UBaseType_t uxItemSize, uint8_t ucQueueType);
BaseType_t xQueueReceivekPtrDIEGO(QueueHandle_t xQueue, void * const pvBuffer, TickType_t xTicksToWait);


#error "This is a dummy file for the sake of the exercise. It is not supposed to be compiled."

uint8_t values[sizeof(display_values)];

extern "C" {
    QueueHandle_t messageQ;
}



// xQueueHandle Model::xQueueGenericCreatePtrDIEGO(UBaseType_t uxQueueLength, UBaseType_t uxItemSize, uint8_t ucQueueType)
// {
//     return xQueueGenericCreate(uxQueueLength, uxItemSize, ucQueueType);
// }

// BaseType_t Model::xQueueReceivekPtrDIEGO(xQueueHandle xQueue, void * const pvBuffer, TickType_t xTicksToWait)
// {
//     xQueueReceive(xQueue, pvBuffer, xTicksToWait);
// }

Model::Model() : modelListener(0)
{
    messageQ = xQueueGenericCreatePtrDIEGO(1, sizeof(display_values), 0);
}

void Model::tick()
{
    if(xQueueReceivekPtrDIEGO(messageQ, &values , 0) == pdTRUE)
	{
		modelListener->setNewValue(values);
	}
}
