%author: E-Branch
%creates an (n-1)×(n-1) matrix A of the form
%   1  -0.5   0    0  ...
% -0.5   1  -0.5   0  ...
%   0  -0.5   1  -0.5 ...
%  ...

% and a vector b of height n-1 of the form
% 0
% 0.5
% 0
% ...

% and estimated the solution of the linear equation
% Ax = b
% using Jacobi's method

n = input("n:");
B = create_test_matrix(n);
disp("B:");
disp(B);
disp("running Jacobi(a)...");
b = create_test_vector(n);
G = jacobi(B,b);
disp("G:")
disp(G);



disp("true solution:");
disp(B\b);
x = G(:,size(G,2));
disp("A*X(k) = ");
disp(B*x);
plot_norm(G);
disp("X(k)");
disp(x);
disp("iterations:");
disp(size(G,2))

%functions

% estimated the solution of the matrix A using Jacobi's Method
% stoping criteria: realative difference between last 2 estimates (max norm) is less
% than 10^(-3)
% pre-cond: A is a square matrix and b is a vector
function X = jacobi(A,b)
    n = size(A,1);
    t = 10^(-3);        %value of TOL
    est = zeros(n,1);   %list of x(n) s
    k = 1;              %iterator
    
    Lu = lumatrix(A);   %L + U matrix
    Dinv = Dinverse(A); %D^-1 matrix
    
    T = Dinv*Lu;        %set T
    c = Dinv*b;         %set c
    
    
    flag = 0;
    
    while( flag == 0)
        k = k+1;
        r = est(:,k-1);     %r is set to the ith col of est aka x(i-1)
        w = (T*r + c);      %formula for jacobis algorithm
        
        est(:,k) = w;       %move to solution list
        
        if(max_norm(w-r)/max_norm(w) < t)   %test for stoping criteria
            flag = 1;
        end
    end
    
    X = est;
end

% estimated the solution of the matrix A using Jacobi's Method
% stopping criteria: relative error (max norm) is less than 10^(-3)
% pre-condition: A is a square matrix and b is a vector
function X = jacobi_err(A,b)
    
    n = size(A,1);
    t = 10^(-3);        %value of TOL
    tx = A\b;           %true x
    est = zeros(n,1);   %list of x(n) s
    k = 1;              %iterator
    
    LU = lumatrix(A);   %L + U matrix
    Dinv = Dinverse(A); %D^-1 matrix
    
    T = Dinv*LU;        %set T
    c = Dinv*b;         %set c
    
    
    flag = 0;
    
    while( flag == 0)
        k = k+1;
        r = est(:,k-1);     %r is set to the ith col of est aka x(i-1)
        w = (T*r + c);      %formula for jacobis algorithm
        
        est(:,k) = w;       %move to solutions list
        
        if(max_norm(tx-w)/max_norm(tx) < t) %test for stoping criteria
            flag = 1;
        end
    end
    
    X = est;
end

% creates (n-1)×(n-1) matrix A as described at the header
% pre-condition: n is an integer, n > 1
function A = create_test_matrix(n)
    n = n-1;
    A = zeros(n);
    %initialize the first row
    A(1, 1) = 1;
    A(1,2) = (-1/2);
    %use iteration to build the rest of the matrix, exept row n
    for i = 2:(n-1)
        A(i,i-1) = (-1/2);
        A(i,i) = 1;
        A(i,i+1) = (-1/2);
    end
    A(n,n-1) = -(1/2);
    A(n,n) = 1;
end

% created a 1×(n-1) vector b as described in the header 
% pre-condition: n is an integer, n > 1
function b = create_test_vector(n)
    n = n-1;
    b = zeros(n,1);
    b(1) = (1/2);
end

% creates a matrix LU representing (L + U), or the upper and lower
% triangular elements of M (excluding the diagonal entries)
% pre-condition, M is a square matrix n>2
function LU = lumatrix(M)
    n = size(M,1);
    LU = zeros(n);
    for i = 1:(n-1)
        for j= (i+1):n
            % (1,2), ... , (n-1,n)
            LU(i,j) = -M(i,j);
        end
    end
    for j = 1:(n-1)
        for i = (j+1):n
            %(2,1), ... , (n,n-1)
            LU(i,j) = -M(i,j);
        end
    end
    %disp(LU)
end

% makes the matrix Dinv representing D^-1, the inverse of
% the matrix made of the diagonal elements of M
% pre-condition: M is a square matrix, n > 0
function Dinv = Dinverse(M)
    n = size(M,1);
    Dinv = zeros(n);
    for i = 1:n
        % 1,1 ... n,n
        Dinv(i,i) = (1/M(i,i));
    end
end

% returns the max norm of X
% precondition: X is a vector (vertical)
function x = max_norm(X)
    x = 0;
    n = size(X,1);
    for i = 1:n
        if( X(i)^2 > x)
            x = X(i)^2;
        end
    end
    x = sqrt(x);
end

% plots the norms of the vectors in the "vector list" X
% used to show how X converges towards the solution
% aka X = {x(1) ; x(2); ... };
function plot_norm(X)
    g = size(X,2);
    G = zeros(g);
    for i = 1:g
        G(i) = max_norm(X(:,i));
    end
    plot(G);
end