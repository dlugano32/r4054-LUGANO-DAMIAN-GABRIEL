`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: UTN FRBA
// Engineer: Damian Lugano
// 
// Create Date: 10/07/2023 03:57:31 PM
// Design Name: 
// Module Name: led_blink
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////

//Definición básica de un módulo

module led_blink#( // Puertos IN/OUT
    parameter N = 8,
    parameter M = 50000000
    )
    (
    input clk,
    input [N-1:0] sw,
    output [N-1:0] leds
    );
//Logica

    assign leds = sw;

endmodule