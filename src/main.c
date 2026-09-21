#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/display/cfb.h>

int main(void)
{
	const struct device *dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_display));

	if (!device_is_ready(dev)) {
		return 0;
	}

	cfb_framebuffer_init(dev);
	cfb_framebuffer_clear(dev, true);
	display_blanking_off(dev);
	cfb_print(dev, "hello world", 0, 0);
	cfb_framebuffer_finalize(dev);

	return 0;
}
