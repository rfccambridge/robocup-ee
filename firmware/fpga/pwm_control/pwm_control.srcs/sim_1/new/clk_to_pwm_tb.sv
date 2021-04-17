`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/17/2021 11:56:19 AM
// Design Name: 
// Module Name: clk_to_pwm_tb
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


module clk_to_pwm_tb();
    logic rst, clk_in, clk_out, clk_out_2;
    logic [31:0] clk_divider, clk_divider_2;
    
    
    assign clk_divider = 32'd10;
    assign clk_divider_2 = 32'd20;
    
    clk_to_pwm test (.clk_in, .rst, .clk_divider, .clk_out);
    clk_to_pwm test_2 (.clk_in, .rst, .clk_divider(clk_divider_2), .clk_out(clk_out_2));
    
    initial begin
        rst <= 1;
        # 22;
        rst <= 0;
    end

    always begin
        // clock does not need to be
        // divided for simulation
        clk_in <= 1;
        #5;
        clk_in <= 0;
        #5;
    end
endmodule
