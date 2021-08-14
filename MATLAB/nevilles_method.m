%Nevilles Method Interpolating Algorithm
% E-Branch

r = input("xp = ");

%example data, example population data vs year 20**
A = [11, 4502104;
     12, 4566769;
     13, 4630077;
     14, 4707103;
     16, 4859250;
     17, 4929384;
     18, 5010476;
     19, 5090955;
     20, 5147712];
 n = 9;
 
 
disp(A);

%display the points on a plot
scatter(A(:,1),A(:,2));
hold on;

P = neville(A,n);
fplot(P);   %plot the appriximation on the same plot


%calculate the value of f(r) using linear approximation between the first
%and last point
l = linear_approximation(A(1,1),A(1,2),A(9,1),A(9,2),r);
scatter([r],[l]); %plot the point (r,l) on the graph

%print l as output
disp("f(xp) by linear approximation:");
disp(l);    

hold off;   %clear the current graph

input("cont?"); % so you can look at and/or save the graph before moving on to the next part

disp("Finding the value of f(xp) using neville point method:");
disp();

X = zeros(1,n);
for k = 2:n
    X(k) = neville_point(A,n,r,k);
end
%plot a graph of the iterations taken towards the solution
plot(X);

%display the data of the iterations taken towards the solution
disp(X);


%returns the interpolating polynomial P found using nevilles method
%PRE-CONDITIONS: 
%V is a n x 2 matrix, with the values of x in the first column, 
%           and the corresponding values of f in the second row
% n is an integer > 0
function P = neville(V,n)
    syms P;
    if(n == 1)  %recursive base case
        P = V(1,2);
    else
        syms x;  %function variable, P in terms of x
        syms Pi; %take out the last elem: P(i,...j-1)
        syms Pj; %take out the first elem: P(i+1,...j)
        
        Pi = neville(V(1:(end-1),:),n-1); %recursive call 1
        Pj = neville(V(2:end,:),n-1);     %recursive call 2
        
        xi = V(1,1);
        xj = V(n,1);
        %nevilles method formula
        P = ( (x-xi)*Pj - (x-xj)*Pi ) / (xj - xi);
    end
end

%returns the value at xp of the interpolating polynomial found by nevilles
%method using i datapoints
%PRE-CONDITIONS
%pre conditions of neville(V,n)
%xp is a real number
%i is an integer
% 0 < i <= n
function p = neville_point(V,n,xp,i)
    syms P;
    
    %O is the data points in V, but arranged with the closest to xp at the
    %top
    O = V;
    O(:,1) = O(:,1)+(zeros(n,1)-xp);
    O = sortrows(O,'ComparisonMethod','abs');
    
    %take the first i data points of O to make I
    for k = 1:i
        I(k,1) = O(k,1)+xp; % (+xp) reverses (-xp) done earlier
        I(k,2) = O(k,2);
    end
    
    %find the nevilles method interpolating polynomial
    P = neville(I,i);
    
    %to get P(xp) substiture in xp
    p = subs(P,xp);
    
    p = double(p);
end

%returns the value at xp of the interpolating polynomial found by nevilles
%method using i datapoints
%uses a different method to choose datapoints than the one above
%obsolete, chose not to use this at all, keeping it to show process
%PRE-CONDITIONS
%pre conditions of neville(V,n)
%xp is a real number
%i is an integer
% 0 < i <= n
function p = neville_point_t(V,n,xp,i)
    syms P;
    
    %O is the data points in V, but arranged with the closest to xp at the
    %top
    O = V;
    O(:,1) = O(:,1)+(zeros(n,1)-xp);
    O = sortrows(O,'ComparisonMethod','abs');
    
    %take the first i data points of O to make I
    for k = 1:i
        if(rem(k,2) == 0) %if even, take from the top
            I(k,1) = O(k/2,1)+xp; % (+xp) reverses (-xp) done earlier
            I(k,2) = O(k/2,2);
        else              %if odd, take from the bottom.
            I(k,1) = O(n-(floor(k/2)),1)+xp; % (+xp) reverses (-xp) done earlier
            I(k,2) = O(n-(floor(k/2)),2);
        end
    end
    
    %find the nevilles method interpolating polynomial
    P = neville(I,i);
    
    %to get P(xp) substiture in xp
    p = subs(P,xp);
    
    p = double(p);
end

function y = linear_approximation(x1,y1,x2,y2,x)
    M = (y2-y1)/(x2-x1);
    b = y1 - M*x1;
    y = M*x + b;
end
