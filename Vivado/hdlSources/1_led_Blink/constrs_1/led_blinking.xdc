# Esta información se obtiene de varios lados: de la hoja de datos del chip usado, y del esquemático de la placa en uso.
# Se define basicamente: el puerto del top module mapeado al pin del chip FPGA, y el voltaje de operación.

# ZedBoard LED Constraints
set_property PACKAGE_PIN T22 [get_ports {leds[0]}]
set_property IOSTANDARD LVCMOS33 [get_ports {leds[0]}]
set_property PACKAGE_PIN T21 [get_ports {leds[1]}]
set_property IOSTANDARD LVCMOS33 [get_ports {leds[1]}]
set_property PACKAGE_PIN U22 [get_ports {leds[2]}]
set_property IOSTANDARD LVCMOS33 [get_ports {leds[2]}]
set_property PACKAGE_PIN U21 [get_ports {leds[3]}]
set_property IOSTANDARD LVCMOS33 [get_ports {leds[3]}]
set_property PACKAGE_PIN V22 [get_ports {leds[4]}]
set_property IOSTANDARD LVCMOS33 [get_ports {leds[4]}]
set_property PACKAGE_PIN W22 [get_ports {leds[5]}]
set_property IOSTANDARD LVCMOS33 [get_ports {leds[5]}]
set_property PACKAGE_PIN U19 [get_ports {leds[6]}]
set_property IOSTANDARD LVCMOS33 [get_ports {leds[6]}]
set_property PACKAGE_PIN U14 [get_ports {leds[7]}]
set_property IOSTANDARD LVCMOS33 [get_ports {leds[7]}]

# Esto reemplaza la asignación individual
# PACKAGE_PIN solo se aplica a I/O individuales
#set_property IOSTANDARD LVCMOS33 [get_ports leds]      

## ----------------------------------------------------------------------------
## DIP Switches - Bank 35
## ---------------------------------------------------------------------------- 
set_property PACKAGE_PIN F22 [get_ports {sw[0]}];  # "SW0"
set_property PACKAGE_PIN G22 [get_ports {sw[1]}];  # "SW1"
set_property PACKAGE_PIN H22 [get_ports {sw[2]}];  # "SW2"
set_property PACKAGE_PIN F21 [get_ports {sw[3]}];  # "SW3"
set_property PACKAGE_PIN H19 [get_ports {sw[4]}];  # "SW4"
set_property PACKAGE_PIN H18 [get_ports {sw[5]}];  # "SW5"
set_property PACKAGE_PIN H17 [get_ports {sw[6]}];  # "SW6"
set_property PACKAGE_PIN M15 [get_ports {sw[7]}];  # "SW7"

# set_property IOSTANDARD LVCMOS33 [get_ports -of_objects [get_iobanks 35]];
# set_property IOSTANDARD LVCMOS25 [get_ports -of_objects [get_iobanks 35]];
set_property IOSTANDARD LVCMOS25 [get_ports sw];

## ----------------------------------------------------------------------------
## Creamos un clock
## ---------------------------------------------------------------------------- 
set_property IOSTANDARD LVCMOS33 [get_ports clk]
set_property PACKAGE_PIN Y9 [get_ports clk]
create_clock -period 10 [get_ports clk]