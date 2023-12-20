`define S0_ST 4'b0001
`define S1_ST 4'b0010
`define S2_ST 4'b0100
`define S3_ST 4'b1000

/// Automat mealy

module automat(
    input clk, rst_b,
    input a, b,
    output reg m, n
);

    reg [1:0] st, st_next;

    always @(*) begin
        case(st)
            `S0_ST: begin
                if(a&b)     st_next = `S1_ST;
                if(~a&b)    st_next = `S2_ST;
                if(a&~b)    st_next = `S0_ST;
                if(~a&~b)   st_next = `S3_ST;
            end
            `S1_ST:  st_next = `S1_ST;
            `S2_ST: begin
                if(~a)   st_next = `S2_ST;
                if(a)    st_next = `S1_ST;
            end
            `S3_ST:  st_next = `S2_ST;
        endcase
    end

    always @(*) begin // La moore dispar if urile
        case(st)
            `S0_ST: begin
                if(a&b) begin
                    m = 1;
                    n = 0;
                end
                if(a&~b)begin
                    m = 0;
                    n = 1;
                end
                if(~a&~b) begin
                    m = 0;
                    n = 0;
                end
                if(~a&b) begin
                    m = 0;
                    n = 0;
                end
            end
            `S1_ST: begin
                m = 0;
                n = 0;
            end
            `S2_ST: begin
                if(a) begin
                    m = 1;
                    n = 0;
                end
                if(~a) begin
                    m = 0;
                    n = 1;
                end
            end
            `S3_ST: begin
                m = 1;
                n = 1;
            end
        endcase
    end

    always @(posedge clk or negedge rst_b) begin
        if (!rst_b) begin
            st <= `S0_ST;
        end
        else begin
            st <= st_next;
        end
    end

endmodule


module automat_tb;

    reg clk, rst_b;
    reg a, b;
    wire m, n;

    automat_tb dut(.clk(clk), .rst_b(rst_b), .a(a), .b(b), .m(m), .n(n));

    initial begin /// clk

        repeat(9) begin
            clk = 0;
            #50 clk = 1;
            #50;
        end
    end

    initial begin /// rst_b
        rst_b = 0;
        #25  rst_b = 1;
        #395 rst_b = 0;
        #220 rst_b = 1;
    end

    initial begin /// a
        a = 0;
        #150 a = 1;
        #150 a = 0;
        #130 a = 1;
        #190 a = 0;
        #180 a = 1;
    end

    initial begin /// b

        b = 0;
        #100 b = 1;
        #50  b = 0;
        #150 b = 1;
        #50  b = 0;
        #190 b = 1;
        #80  b = 0;
        #220 b = 1;
    end

endmodule
