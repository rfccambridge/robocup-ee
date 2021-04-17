//////////////////////////////////////////////////////////////////////////////////
// 
// CS 141 - Fall 2015
// Module Name:    MotorControl 
// Author(s): 
// Description: 
//
//
//////////////////////////////////////////////////////////////////////////////////
// 1393258757-DigitalPIDControllers_2011.pdf

module PID #(parameter W=15) // bit width - 1
  (output signed [W:0] u_out, // output
  input signed [W:0] e_in, // input
  input clk,
  input reset);
  parameter kp=0.1;
  parameter ki=0.2;
  parameter kd=0;
  parameter k1=kp+ki+kd; // change these values to suit your system
  parameter k2 = -kp-2*kd;
  parameter k3 = kd;
  reg signed [W:0] u_prev;
  reg signed [W:0] e_prev[1:2];
  //PID Controller (w/ D=0)
  assign u_out = u_prev + k1*e_in - k2*e_prev[1] + k3*e_prev[2];
  always @ (posedge clk)
  if (reset == 1) begin
    u_prev <= 0;
    e_prev[1] <= 0;
    e_prev[2] <= 0;
  end else begin
    e_prev[2] <= e_prev[1];
    e_prev[1] <= e_in;
    u_prev <= u_out;
  end
endmodule
