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
module measure_speed(
   enc, clk, reset, enc_count
); 

   input wire [1:0] enc;
	input wire clk, reset;
	 
   //output reg [7:0] speed = 8'b00000000;
	 
	output reg [15:0] enc_count = 16'b0;

	//parameter definitions
	localparam STEP_0 = 'b00;
   localparam STEP_1 = 'b01;
   localparam STEP_2 = 'b10;
   localparam STEP_3 = 'b11;
	
	//previous enc state
	reg [1:0] enc_d; always @(posedge clk) enc_d <= enc;
	
	wire count_up = ( ((STEP_0 == enc_d) && (STEP_1 == enc)) 
	                || ((STEP_1 == enc_d) && (STEP_3 == enc))
						 || ((STEP_3 == enc_d) && (STEP_2 == enc))
						 || ((STEP_2 == enc_d) && (STEP_0 == enc)) );

   wire count_down = ( ((STEP_0 == enc_d) && (STEP_2 == enc)) 
	                || ((STEP_2 == enc_d) && (STEP_3 == enc))
						 || ((STEP_3 == enc_d) && (STEP_1 == enc))
						 || ((STEP_1 == enc_d) && (STEP_0 == enc)) );

   //encoder counter
	always @( posedge clk ) begin : ENCODER_COUNTER
	   if ( reset ) begin
          enc_count <= 0;
      end else begin
          if (count_up) begin
              enc_count <= enc_count + 1;
          end else if ( count_down ) begin
              enc_count <= enc_count - 1;
          end
      end
	end : ENCODER_COUNTER

   //measure speed

endmodule
`default_nettype wire //some Xilinx IP requires that the default_nettype be set to wire
