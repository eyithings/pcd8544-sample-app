# pcd8544-sample-app

Minimal Zephyr app that prints "hello world" to a PCD8544 (Nokia 5110) display. 

Created solely to test https://github.com/zephyrproject-rtos/zephyr/pull/120029

## Wiring assumption

| Display | nRF51822 pin |
|---------|--------------|
| CLK     | P0.06        |
| DIN     | P0.10        |
| DC      | P0.14        |
| RST     | P0.19        |
| CE (CS) | P0.20        |

