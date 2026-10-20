#!/bin/bash

for builder in "e2studio" "vscode"; do
	for project in "debounce_fpb_ra2e3" "debounce_freertos_fpb_ra2e3"; do
		ln -f -v src/rs_gpio_debounce/rs_gpio_debounce.c examples/$builder/$project/src/rs_gpio_debounce/
		ln -f -v src/rs_gpio_debounce/rs_gpio_debounce.h examples/$builder/$project/src/rs_gpio_debounce/

		ln -f -v src/rs_gpio_debounce/rs_gpio_debounce_cfg_gen.c examples/$builder/$project/src/rs_gpio_debounce/
		ln -f -v src/rs_gpio_debounce/rs_gpio_debounce_cfg_gen.h examples/$builder/$project/src/rs_gpio_debounce/

	done

	ln -f -v src/rs_gpio_debounce/rs_gpio_debounce_demo.c examples/$builder/debounce_fpb_ra2e3/src/

	ln -f -v src/rs_gpio_debounce/configs/baremetal/debounce_config_fpb_ra2e3.* examples/$builder/debounce_fpb_ra2e3/src/rs_gpio_debounce/
	ln -f -v src/rs_gpio_debounce/configs/freertos/debounce_freertos_config_fpb_ra2e3.*  examples/$builder/debounce_freertos_fpb_ra2e3/src/rs_gpio_debounce/

	ln -f -v src/rs_gpio_debounce/rs_gpio_debounce_demo_freertos.c examples/$builder/debounce_freertos_fpb_ra2e3/src/
done
