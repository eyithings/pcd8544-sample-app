#include <stdint.h>
#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/display/cfb.h>
#include <zephyr/drivers/gpio.h>

#define BLINK_PERIOD_MS 1000
#define GREETING_DELAY_MS 4000
#define LABEL_DELAY_MS 2000
#define COUNT_STEP_DELAY_MS 10

static const struct gpio_dt_spec led0 = GPIO_DT_SPEC_GET(DT_ALIAS(led0), gpios);

int main(void)
{
	const struct device *dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_display));

	if (!device_is_ready(dev)) {
		return 0;
	}

	uint8_t font_height;

	cfb_framebuffer_init(dev);

	/* MONO10 is white text on black; MONO01 is black on white */
	cfb_framebuffer_invert(dev);

	display_blanking_off(dev);

	cfb_framebuffer_clear(dev, true);
	cfb_get_font_size(dev, 0, NULL, &font_height);
	cfb_draw_text(dev, "hello", 0, 0);
	cfb_draw_text(dev, "world", 0, font_height);
	cfb_framebuffer_finalize(dev);
	k_msleep(GREETING_DELAY_MS);

	cfb_framebuffer_clear(dev, false);

	cfb_print(dev, "Hex", 0, 0);
	cfb_print(dev, "counter", 0, font_height);
	cfb_framebuffer_finalize(dev);
	k_msleep(LABEL_DELAY_MS);

	uint16_t count = 0;
	char buf[8];

	while (1) {
		snprintf(buf, sizeof(buf), "0x%04x", count);
		cfb_print(dev, buf, 0, 2 * font_height);
		cfb_framebuffer_finalize(dev);
		k_msleep(COUNT_STEP_DELAY_MS);
		if (count == UINT16_MAX) {
			break;
		}
		count++;
	}

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
