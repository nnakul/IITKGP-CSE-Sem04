
// SWITCHING CIRCUITS AND LOGIC DESIGN LABORATORY
// ASSIGNMENT O8 -- SEQUENTIAL BINARY TO BCD CONVERTER 
// SUBMITTED BY GROUP O9

// To run this verilog program, use following commands on the terminal
//      >   iverilog -o main.vvp BINARY_TO_BCD.v
//      >   vvp main.vvp

`timescale 1s/1ms

// Module for "POSITIVE EDGE TRIGERRED D FLIP FLOP"
module DFF (clk, D, Q, Qb) ;
    input  clk , D ;
    output reg Q , Qb ;
    always @ (posedge clk)
    begin
        Q = D ; Qb = ~D ;
    end
endmodule

// Module for "2-1 MULTIPLEXOR"
module MUX (x, y, s, z) ;
    input x, y, s ;
    output z ;
    assign z = (s & x) | (~s & y) ;
    wire w1, w2, w3 ;
    and U1 (w1, s, x) ;
    not U2 (w2, s) ;
    and U3 (w3, w2, y) ;
    or  U4 (z, w1, w3) ; 
endmodule

// Module for "FULL ADDER"
module FULL_ADDER (a, b, cin, cout, sum) ;
    input  a, b, cin ;
    output cout, sum ;
    wire   w1, w2, w3, w4 ;
    xor U1  (w1, a, b) ;
    xor U2  (sum, w1, cin) ;
    and U3  (w2, a, b) ;
    and U4  (w3, a, cin) ;
    and U5  (w4, b, cin) ;
    or  U6  (cout, w2, w3, w4) ;
endmodule

// Module for "4 BIT RIPPLE CARRY ADDER"
// It is recursively defined using Full Adder modules.
module RIPPLE_CARRY_ADDER_4BIT (A, B, cin, S, cout) ;
    input[3:0] A, B ;
    input cin ;
    output[3:0] S ;
    output cout ;
    wire c1, c2, c3 ;
    FULL_ADDER fa0 (A[0], B[0], cin, c1, S[0]) ;
    FULL_ADDER fa1 (A[1], B[1], c1, c2, S[1]) ;
    FULL_ADDER fa2 (A[2], B[2], c2, c3, S[2]) ;
    FULL_ADDER fa3 (A[3], B[3], c3, cout, S[3]) ;
endmodule

// Module for ">4 COMPARATOR"
// Value of the output port is 1 if and only if the
// decimal value of the 4-bit input binary string
// is greater than 4.
// It is recursively defined using 2-1 Multiplexor modules.
module COMPARATOR (A, d) ;
    output d ;
    input[3:0] A ;
    wire w1, w2, w3 ;
    MUX M1 (A[2], 1'b0, A[0], w1) ;
    MUX M2 (A[2], 1'b0, A[1], w2) ;
    MUX M3 (1'b1, w2, w1, w3) ;
    MUX M4 (1'b1, A[3], w3, d) ;
endmodule

// Module for ">4 3 CONDITIONAL ADDER"
// Binary 3 (0011) is added to the 4-bit input binary
// string if and only if the value at the output port
// of the Comparator component is 1 for the input string.
// It is recursively defined using >4 Comparator module.
module CONDITIONAL_ADDER (A, B) ;
    input[3:0] A ;
    output[3:0] B ;
    wire[3:0] add ;
    wire compare, cout ;
    COMPARATOR CMP (A, compare) ;
    RIPPLE_CARRY_ADDER_4BIT RCA (A, add, 1'b0, B, cout) ;
    assign add[3] = 1'b0 ;
    assign add[2] = 1'b0 ;
    assign add[1] = compare ;
    assign add[0] = compare ;
endmodule

// Module for "INPUT SHIFT REGISTER"
// It represents a "Parallel In Serial Out (PISO)" shift register
// for 8 bit binary strings. It shifts from the most significant bit.
// It is recursively defined using DFF modules.
module INPUT_SHIFT_REGISTER (clk, d, mode, serialOut) ;
    input clk , mode ;
    input[7:0] d ;
    output serialOut ;
    reg[7:0] q = 0 ;
    assign serialOut = q[7] ;
    reg d1, d2, d3, d4, d5, d6, d7, d8 ;
    wire q1, q2, q3, q4, q5, q6, q7, q8 ;
    wire q1b, q2b, q3b, q4b, q5b, q6b, q7b, q8b ;
    DFF D1 (clk, d1, q1, q1b) ;
    DFF D2 (clk, d2, q2, q2b) ;
    DFF D3 (clk, d3, q3, q3b) ;
    DFF D4 (clk, d4, q4, q4b) ;
    DFF D5 (clk, d5, q5, q5b) ;
    DFF D6 (clk, d6, q6, q6b) ;
    DFF D7 (clk, d7, q7, q7b) ;
    DFF D8 (clk, d8, q8, q8b) ;
    always @ ( posedge clk ) begin
        if ( mode )
            q <= d ;
        else begin
            q[7] <= q[6] ;
            q[6] <= q[5] ;
            q[5] <= q[4] ;
            q[4] <= q[3] ;
            q[3] <= q[2] ;
            q[2] <= q[1] ;
            q[1] <= q[0] ;
            q[0] <= 1'bx ;
        end
    end    
endmodule

// Module for "NIBBLE CONVERSION"
// It performs the two essential operations in the Double Dabble
// algorithm that are -- SHIFT LEFT and ADD 3.
module NIBBLE_CONVERTER (clk, reset, si, finalBits, out) ;
    input clk , reset , si ;
    wire[3:0] modified ;
    output reg out ;
    output reg[3:0] finalBits ;
    reg[3:0] nibble ;
    CONDITIONAL_ADDER CA (finalBits, modified) ;
    always @ ( posedge clk ) begin
        if ( reset ) begin
            out <= 1'b0 ;
            finalBits <= 4'b0000 ;
        end
        else begin
            out <= modified[3] ;
            finalBits[3] <= modified[2] ;
            finalBits[2] <= modified[1] ;
            finalBits[1] <= modified[0] ;
            finalBits[0] <= si ;
        end
    end 
endmodule

// TOP Module that simulates the working of the Binary to BCD 
// converter (for 8 bits) by implementing Double Dabble algorithm.
// In the Top module, 3 Nibble Converter modules will be needed because
// the BCD representation of the largest 8 bit binary number (255 in
// decimal) has 3 nibbles.
module TOP() ;
    reg clk, mode, reset ;
    reg[7:0] inputBinaryString ;
    wire[3:0] nibble1, nibble2, nibble3 ;
    reg[3:0] store1, store2, store3 ;
    wire serialIn, out0, out1, out2 ;
    integer count, step ;
    INPUT_SHIFT_REGISTER ISR (clk, inputBinaryString, mode, serialIn) ;
    NIBBLE_CONVERTER NC0 (clk, reset, serialIn, nibble1, out0) ;
    NIBBLE_CONVERTER NC1 (clk, reset, out0, nibble2, out1) ;
    NIBBLE_CONVERTER NC2 (clk, reset, out1, nibble3, out2) ;
    initial begin
        inputBinaryString <= 8'b11111111 ;
        $monitor("\n  [ INPUT 8-BIT BINARY STRING: %b ]\n  [ DECIMAL REPRESENTATION OF INPUT: %d ]\n\n    +++ IMPLEMENTING SEQUENTIAL DOUBLE-DABBLE ALGORITHM +++\n", inputBinaryString, inputBinaryString) ;
        store1 = 4'b0000 ;
        store2 = 4'b0000 ;
        store3 = 4'b0000 ;
        clk = 0 ; count = 0 ; step = 0 ;
        mode = 1 ; reset = 1 ;
        #120 begin
            reset = 0 ; mode = 0 ;
        end
    end
    always begin
        if (count <= 23) begin
            if ( ~ clk ) begin
                store1 <= nibble2 ; store3 <= store2 ; store2 <= nibble1 ;
            end
            if (count == 6) begin
                $monitor("    S.NO.   |   B2    B1    B0") ;
            end
            if (count >= 7) begin
                step += 1 ;
                $monitor("  STEP: %2d  |  %b  %b  %b", step, nibble3, store1, store3) ;
            end
            #30 clk = ~clk ;
            count += 1 ;
        end
        else begin
            $monitor("\n  [ BCD REPRESENTATION:  %b %b %b ]", nibble3, store1, store3) ;
            $finish ;
        end
    end
endmodule
