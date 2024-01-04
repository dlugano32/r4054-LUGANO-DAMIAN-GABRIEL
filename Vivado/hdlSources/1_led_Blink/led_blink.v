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

    reg[31 : 0] r_contador = 0;
    reg r_salida = 0;
    
    always @(posedge clk)  //posedge = flanco ascendente de clk
        begin
            if (r_contador == M)begin
                r_salida = !(r_salida);
                r_contador = 0;
            end
            else begin
                r_contador = r_contador + 1;    
            end
        end

    assign leds[0] = sw[0] & r_salida;
    assign leds[1] = sw[1] & r_salida;
    assign leds[2] = sw[2] & r_salida;
    assign leds[3] = sw[3] & r_salida;
    assign leds[4] = sw[4] & r_salida;
    assign leds[5] = sw[5] & r_salida;
    assign leds[6] = sw[6] & r_salida;
    assign leds[7] = sw[7] & r_salida;
        
endmodule
