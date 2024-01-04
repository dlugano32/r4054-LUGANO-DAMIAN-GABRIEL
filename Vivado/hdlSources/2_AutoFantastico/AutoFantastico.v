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

module AutoFantastico#( // Puertos IN/OUT
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
    reg [7 : 0] r_salida = 1;
    reg avanzar = 1;
    
    always @(posedge clk)  //posedge = flanco ascendente de clk
        begin
            if (r_contador == M)begin
                
                if( avanzar == 1)begin
                    r_salida=r_salida<<1;
                    
                    if(r_salida[7] == 1)begin
                        avanzar = 0;
                    end
                    else begin
                        avanzar = 1;
                    end
                end
                else begin
                    r_salida=r_salida>>1;
                    
                    if(r_salida[0] == 1)begin
                       avanzar=1;
                    end
                    else begin
                        avanzar=0;
                    end    
                end      
                r_contador = 0;
            end
            else begin
                r_contador = r_contador + 1;    
            end
        end

    assign leds[0] = r_salida[0];
    assign leds[1] = r_salida[1];
    assign leds[2] = r_salida[2];
    assign leds[3] = r_salida[3];
    assign leds[4] = r_salida[4];
    assign leds[5] = r_salida[5];
    assign leds[6] = r_salida[6];
    assign leds[7] = r_salida[7];
        
endmodule