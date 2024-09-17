#include "app_led.h"

void app_led_init(void)
{
    GPIO_InitTypeDef GPIO_Led_InitConfig;

    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_Led_InitConfig.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_Led_InitConfig.Pull  = GPIO_PULLUP;
    GPIO_Led_InitConfig.Speed = GPIO_SPEED_FREQ_HIGH;

    GPIO_Led_InitConfig.Pin = PWM_GPIO_PIN;
    HAL_GPIO_Init(PWM_GPIO_PORT, &GPIO_Led_InitConfig); /* LED2 GPIO≥ı ºªØ */

    PWM_LED(LED_OFF);
}

void app_led_toggle(void)
{
    PWM_LED_TOGGLE();
}