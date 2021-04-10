`timescale 1ns / 1ps
`default_nettype none //helps catch typo-related bugs
//////////////////////////////////////////////////////////////////////////////////
// 
// CS 141 - Fall 2015
// Module Name:    MotorControl 
// Author(s): 
// Description: 
//
//
//////////////////////////////////////////////////////////////////////////////////
module PI_tb; 
    `include "../sv/PID.v"

    wire [15:0] out;
	 //reg [15:0] speed;
	 wire [15:0] error;
	 reg reset = 1'b0;
	 reg clk = 1'b0;
	 
	 //parameter definitions
    localparam period = 20;  //use this to test speed

    PID PI_controller (.u_out(out), .e_in(error), .reset(reset), .clk(clk));
    
	 initial begin
	    #period;
		 forever begin
		    #period/2;
			 clk = ~clk;
		 end
	 end

endmodule
`default_nettype wire //some Xilinx IP requires that the default_nettype be set to wire
