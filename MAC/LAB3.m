function x = jacobi3(A,B,x0,k)
D = diag(diag(A));
L = tril(A)-D;
U = triu(A)-D;

x(1) = x0;

    for i = 1:k
        x(i+1) = inv(D)*(B-(L+U)*x(i));
    end
    
///////////////////////////////////////////////////////
    
 function [A,x] = gauss(A,B)
n = length(A);
    for i = 1:n-1
        if A(j,j) == 0
            error('Pivot 0');
        end
        for i=j+1:n
            A(i,k) = A(i,k) - (A(i,j)/A(j,j))*A(j,k);
        end
        B(i) = B(i) - (A(i,j)/A(j,j))*B(j);
    end
end

...
      
///////////////////////////////////////////////////////////////
