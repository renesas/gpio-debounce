unity_dep = dependency('Unity')
unity_proj = subproject('unity')

include_dir_list = [base_include_dirs, 'data', 'mocks']

debouncer_dep = declare_dependency(
    include_directories: [base_include_dirs],
    link_with: debouncer_lib,
)

pin_spy_code = ['mocks/pin_api_spy.c', 'data/pin_data.c']
pin_spy_test_code = [
    'mocks/test_pin_api_spy.c',
    'runners/test_pin_api_spy_runner.c',
]

pin_spy_test_exe = executable(
    'pin-spy-test',
    sources: [pin_spy_code, pin_spy_test_code],
    include_directories: include_dir_list,
    dependencies: [unity_dep, debouncer_dep],
)

timer_spy_code = ['mocks/timer_spy.c']
timer_spy_test_code = [
    'mocks/test_timer_spy.c',
    'runners/test_timer_spy_runner.c',
]

timer_spy_exe = executable(
    'timer-spy-test',
    sources: [timer_spy_code, timer_spy_test_code],
    include_directories: include_dir_list,
    dependencies: [unity_dep, debouncer_dep],
)

external_irq_spy_code = ['mocks/external_irq_spy.c', 'data/external_irq_data.c']
external_irq_spy_test_code = [
    'mocks/test_external_irq_spy.c',
    'runners/test_external_irq_spy_runner.c',
]

external_irq_spy_exe = executable(
    'external-irq-spy-test',
    sources: [external_irq_spy_code, external_irq_spy_test_code],
    include_directories: include_dir_list,
    dependencies: [unity_dep],
)

lpm_spy_code = ['mocks/lpm_spy.c', 'data/lpm_data.c']
lpm_spy_test_code = ['mocks/test_lpm_spy.c', 'runners/test_lpm_spy_runner.c']

lpm_spy_exe = executable(
    'lpm-spy-test',
    sources: [lpm_spy_code, lpm_spy_test_code],
    include_directories: include_dir_list,
    dependencies: [unity_dep],
)

button_code = ['data/button_data.c', 'data/pin_data.c']
button_test_code = [
    'test_button.c',
    'mocks/pin_api_spy.c',
    'runners/test_button_runner.c',
]
button_test_exe = executable(
    'button-test',
    sources: [button_code, button_test_code],
    include_directories: include_dir_list,
    dependencies: [unity_dep, debouncer_dep],
)

button_cfg_test_code = [
    'runners/test_button_cfg_gen_runner.c',
    'test_button_cfg_gen.c',
    'data/rs_gpio_debounce_cfg_fake.c',
]
button_cfg_gen_test_exe = executable(
    'button-cfg-gen-test',
    sources: [button_code, button_cfg_test_code, 'mocks/pin_api_spy.c'],
    include_directories: include_dir_list,
    dependencies: [unity_dep, debouncer_dep],
)

test('Button Test', button_test_exe)
test('Pin Spy Test', pin_spy_test_exe)
test('Timer Spy Test', timer_spy_exe)
test('External IRQ Spy Test', external_irq_spy_exe)
test('LPM Spy Test', lpm_spy_exe)
test('Button CFG Gen', button_cfg_gen_test_exe)
