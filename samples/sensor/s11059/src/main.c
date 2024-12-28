
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/sensor.h>

struct sensors_data {
	uint16_t red;
	uint16_t red_frac;
	uint16_t blue;
	uint16_t blue_frac;
	uint16_t green;
	uint16_t green_frac;
	uint16_t ir;
	uint16_t ir_frac;
};

static const struct device *get_s11059_device(void){
	const struct device *dev = DEVICE_DT_GET_ANY(hamamatsu_s11059);
	if (dev == NULL){
		printk("\nError: no device \n");
		return NULL;
	}

	if (!device_is_ready(dev)){
		printk("\n Error Device \"%s\" is not ready;"
                        "check the driver initialization logs for errors.\n",
                        dev->name);
                return NULL;
	}

	printk("Found device \"%s\", getting sensor data\n", dev->name);
        return dev;

}

static void get_s11059_sensor_val(const struct device *dev){
	struct sensor_value red, green, blue, ir;
	struct sensors_data data;
	sensor_sample_fetch(dev);

	sensor_channel_get(dev, SENSOR_CHAN_RED, &red);
	sensor_channel_get(dev, SENSOR_CHAN_GREEN, &green);
	sensor_channel_get(dev, SENSOR_CHAN_BLUE, &blue);
	sensor_channel_get(dev, SENSOR_CHAN_IR, &ir);

	printk("Red: %d.%-4d lx; Green: %d.%-4d lx; Blue: %d.%-4d lx; IR: %d.%-4d lx;\n",
		red.val1, red.val2, green.val1, green.val2, blue.val1, blue.val2,
		ir.val1, ir.val2);

	data.red = red.val1;
	data.red_frac = red.val2;
	data.green = green.val1;
        data.green_frac = green.val2;
	data.blue = blue.val1;
        data.blue_frac = blue.val2;
	data.ir = ir.val1;
        data.ir_frac = ir.val2;
}

void main(void){
	const struct device *dev_s11059 = get_s11059_device();

	if (dev_s11059 == NULL){
		printk("Failed to get device: s11059\n");
		return;
	}

	while(1){
		get_s11059_sensor_val(dev_s11059);
		k_sleep(K_MSEC(1000));
	}
}
