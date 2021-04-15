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
module measure_speed_tb;
    `include "./measure_speed.v"

    reg [1:0] enc;
	 //reg [15:0] speed;
	 wire [15:0] count;
	 reg reset = 1'b0;
	 reg clk = 1'b0;
	 
	 //parameter definitions
    //duration for each bit = 20 * timescale = 20 * 1 ns  = 20ns
    localparam period = 20;  //use this to test speed
	 
	 localparam enc_ticks_per_rot = 10; //change this according to motor
	 
	 localparam STEP_0 = 'b00;
    localparam STEP_1 = 'b01;
    localparam STEP_2 = 'b10;
    localparam STEP_3 = 'b11;
	 
	 int rand_delay;
 
    //std::randomize(rand_delay) with {
    //  rand_delay < 100;
    //  rand_delay > 0;
    //};

    measure_speed UUT (.enc(enc), .clk(clk), .reset(reset), .enc_count(count));
    
	 initial begin
	    #period;
		 forever begin
		    #period/2;
			 clk = ~clk;
		 end
	 end
    initial begin
	     #period;
		  #period;
		  #period/4;
		  //#rand_delay; // to test uncertainty
	     repeat(25) begin
		      enc = STEP_0;
            #period/240; // wait for period 
				$display("Count: %d", count);
		      enc = STEP_1;
            #period/240; // wait for period 
				$display("Count: %d", count);
 		      enc = STEP_3;
            #period/240; // wait for period 
				$display("Count: %d", count);
		      enc = STEP_2;
            #period/240; // wait for period 
				$display("Count: %d", count);
        end
		  enc = STEP_0;
		  #period;
		  #period;
		  #period;
		  #period;
		  #period;
		  repeat(25) begin
		      enc = STEP_0;
            #period/240; // wait for period 
				$display("Count: %d", count);
		      enc = STEP_2;
            #period/240; // wait for period 
				$display("Count: %d", count);
 		      enc = STEP_3;
            #period/240; // wait for period 
				$display("Count: %d", count);
		      enc = STEP_1;
            #period/240; // wait for period 
				$display("Count: %d", count);
        end
		  enc = STEP_0;
    end

endmodule
`default_nettype wire //some Xilinx IP requires that the default_nettype be set to wire
