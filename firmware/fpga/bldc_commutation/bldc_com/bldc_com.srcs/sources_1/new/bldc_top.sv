`timescale 1ns / 1ps

module bldc_top(
    input logic [2:0] uvw,      // hall sensor inputs
    output logic [5:0] axbycz  // switches to activate stators (a,x); (b,y); (c,z);
    );
    
    always_comb begin
        unique case (uvw)
            3'b100: axbycz = 6'b001001;
            3'b110: axbycz = 6'b011000;
            3'b010: axbycz = 6'b010010;
            3'b011: axbycz = 6'b000110;
            3'b001: axbycz = 6'b100100;
            3'b101: axbycz = 6'b100001;
        endcase
            
    end
endmodule
