#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/display/cfb.h>
#include <zephyr/drivers/gpio.h>

#define BLINK_PERIOD_MS 1000

static const struct gpio_dt_spec led0 = GPIO_DT_SPEC_GET(DT_ALIAS(led0), gpios);

int main(void)
{
	const struct device *dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_display));

	if (!device_is_ready(dev)) {
		return 0;
	}

	uint8_t font_height;

	cfb_framebuffer_init(dev);
	cfb_framebuffer_clear(dev, true);
	display_blanking_off(dev);
	cfb_get_font_size(dev, 0, NULL, &font_height);
	cfb_print(dev, "hello", 0, 0);
	cfb_print(dev, "world", 0, font_height);
	cfb_framebuffer_finalize(dev);

	if (!gpio_is_ready_dt(&led0)) {
		return 0;
	}

	gpio_pin_configure_dt(&led0, GPIO_OUTPUT_INACTIVE);

	while (1) {
		gpio_pin_toggle_dt(&led0);
		k_msleep(BLINK_PERIOD_MS);
	}

	return 0;
}
