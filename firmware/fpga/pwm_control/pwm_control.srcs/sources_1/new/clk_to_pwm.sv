`timescale 1ns / 1ps

module clk_to_pwm
    (
        input logic clk_in, rst,
        input logic [31:0] clk_divider,
        output logic clk_out
    );
    
    logic [31:0] count;
    

    // output positive edge for every clk_divider number of input positive edges from actual clk
    always @(posedge clk_in, posedge rst) begin   // can also do negedge
        if (rst) begin
            count <= 32'd0;
            clk_out <= 1'b0;
        end
        else if (count == clk_divider) begin  // if we have reached count, switch our pwm pulse
            clk_out <= ~clk_out; 
            count <= 32'd0;
        end 
        else if (clk_in) begin  
            count <= count + 1;
        end
        
    end
    
endmodule

