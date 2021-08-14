% Estimation of derivatives using cubic splines
% E-Branch

format long;    %the default short 4 sig fig formating isn't precice enough to show the differences
                %between iterations ah h becomes very small

disp("estimating derivatives using cubic splines");
disp("for f(x) = e^x");

%PART A
disp("Part A: ESTIMATING f'(0.5) and f''(0.5) using natural cubic splines");
syms x;

AX = [ 0, 0.25, 0.5, 0.75, 1 ];
AY = exp(-AX);

disp("AX:");
disp(AX);

disp("AY");
disp(AY);

%generate the natural cubic spline using built in functions
AS = natural_cubic_spline(AX, AY);

%find the first derivative
ASD = difpp(AS);

%estimate f'(0.5) using the derivative of the spline
disp("f'(0.5) = ");
disp(ppval(ASD,0.5));

%get the second derivative
ASDD = difpp(ASD);

%estimate f''(0.5) using the second derivative of the spline
disp("f''(0.5) = ");
disp(ppval(ASDD,0.5));


input("continue?"); %to give the user time to look over the data


%Part B
disp("Part B:calculate f'(0.5) and f''(0.5) with decreaing value of h (distance between example points)");


for m = 3:7
    h = 2^(-m);
    BX = 0:h:1; %creates range from 0 to 1 with h as the 'distance' between points
    BY = exp(-BX);
    disp(['m:',num2str(m)]);
    disp(['h:',num2str(h)]);
    
    %use the same method as before to estimate f'(0,5) and f''(0.5)
    BS = natural_cubic_spline(BX,BY);
    BSD = difpp(BS);
    disp("f'(0.5) = ");
    disp(ppval(BSD,0.5));
    
    
    
    BSDD = difpp(BSD);
    disp("f''(0.5) = ");
    disp(ppval(BSDD,0.5));
    
    
    
    disp("-----");
end

input("continue?"); %pause to look over output

% PART B ERROR

true_fd = -exp(-0.5);
true_fdd = exp(-0.5);

errord = zeros(2,1);
errordd = zeros(2,1);

i=1;


for m = 3:0.001:10
    h = 2^(-m);
    BX = 0:h:1; %creates range from 0 to 1 with h as the 'distance' between points
    BY = exp(-BX);
    %disp(['m:',num2str(m)]);
    %disp(['h:',num2str(h)]);
        
    BS = natural_cubic_spline(BX,BY);
    BSD = difpp(BS);
       
    
    BSDD = difpp(BSD);
        
    
    errord(1,i) = h;
    errord(2,i) = abs(ppval(BSD,0.5)-true_fd);
    
    errordd(1,i) = h;
    errordd(2,i) = abs(ppval(BSDD,0.5)-true_fdd);
    
    i = i+1;
    
    
    %disp("-----");
end

disp("PART B ERROR f'(0.5)");
hold on;
plot(errord(1,:),errord(2,:));

%{
errord(2,:) = errord(2,:)./errord(1,:);
plot(errord(1,:),errord(2,:));

errord(2,:) = errord(2,:)./errord(1,:);
plot(errord(1,:),errord(2,:));

errord(2,:) = errord(2,:)./errord(1,:);
plot(errord(1,:),errord(2,:));

%}



hold off;

input("continue?")

disp("PART B ERROR f''(0.5)");

hold on;

plot(errordd(1,:),errordd(2,:));

%{

errordd(2,:) = errordd(2,:)./errordd(1,:);
plot(errordd(1,:),errordd(2,:));

errordd(2,:) = errordd(2,:)./errordd(1,:);
plot(errordd(1,:),errordd(2,:));

%}

hold off


input("continue?");

% PART C

disp("Part C: calculating f'(0.5) and f''(0.5) using a clamped cubic spline");
CX = [ 0, 0.25, 0.5, 0.75, 1 ];
CY = exp(-CX);

%derivative at the endpoints
e1 = -exp(0);   
e2 = -exp(-1);

%make the spline
CS = clamped_cubic_spline(CX, CY,e1,e2);

%differenctiate the spline
CSD = difpp(CS);

%estimate f'(0.5)
disp("f'(0.5) = ");
disp(ppval(CSD,0.5));

%get the second derivative of the spline
CSDD = difpp(CSD);

%estimate f''(0.5)
disp("f''(0.5) = ");
disp(ppval(CSDD,0.5));


disp("calculate f'(0.5) and f''(0.5) using clamped cubic spines and decreasing h");

for m = 3:7
    h = 2^(-m);
    BX = 0:h:1; %creates range from 0 to 1 with h as the 'distance' between points
    BY = exp(-BX);
    disp(['m:',num2str(m)]);
    disp(['h:',num2str(h)]);
        
    e1 = -exp(0);
    e2 = -exp(-1);
    
    BS = clamped_cubic_spline(BX,BY,e1,e2);
    BSD = difpp(BS);
    disp("f'(0.5) = ");
    disp(ppval(BSD,0.5));
    
    
    
    BSDD = difpp(BSD);
    disp("f''(0.5) = ");
    disp(ppval(BSDD,0.5));
    
    
    
    disp("-----");
end





input("continue?");

% PART C ERROR
disp("Part C: Error");

true_fd = -exp(-0.5);
true_fdd = exp(-0.5);

errord_c = zeros(2,1);
errordd_c = zeros(2,1);

i=1;


for m = 3:0.001:10
    h = 2^(-m);
    CX = 0:h:1; %creates range from 0 to 1 with h as the 'distance' between points
    CY = exp(-CX);
    

    e1 = -exp(0);
    e2 = -exp(-1);
    
    CS = clamped_cubic_spline(CX,CY,e1,e2);
    CSD = difpp(CS);
  
    
    
    CSDD = difpp(CSD);
   
    
    
    errord_c(1,i) = h;
    errord_c(2,i) = abs(ppval(CSD,0.5)-true_fd);
    
    errordd_c(1,i) = h;
    errordd_c(2,i) = abs(ppval(CSDD,0.5)-true_fdd);
    
    i = i+1;
    
    
    %disp("-----");
end

disp("PART C ERROR f'(0.5): graph of h vs absolute error");
hold on;
plot(errord_c(1,:),errord_c(2,:));

%{
errord_c(2,:) = errord_c(2,:)./errord_c(1,:);
plot(errord_c(1,:),errord_c(2,:));


errord_c(2,:) = errord_c(2,:)./errord_c(1,:);
plot(errord_c(1,:),errord_c(2,:));

errord_c(2,:) = errord_c(2,:)./errord_c(1,:);
plot(errord_c(1,:),errord_c(2,:));

%}


hold off;

input("continue?")

disp("PART C ERROR f''(0.5): graph of h vs absolute error");
hold on;

plot(errordd_c(1,:),errordd_c(2,:));


%{
errordd_c(2,:) = errordd_c(2,:)./errordd_c(1,:);
plot(errordd_c(1,:),errordd_c(2,:));


errordd_c(2,:) = errordd_c(2,:)./errordd_c(1,:);
plot(errordd_c(1,:),errordd_c(2,:));

%}

hold off





%helper function, to make it easier to generate natural cubic splines
% inputs: X = array of x values, Y = array of corresponding y values
function S = natural_cubic_spline(X,Y)
    S = csape(X,Y,"variational");
end

%helper function, to make it easier to generate clamped cubic splines
% inputs: X = array of x values, Y = array of corresponding y values,
% s1 = slope of the left endpoint, s2 = slope of the right endpoint
function S = clamped_cubic_spline(X,Y,s1,s2)
    S = csape(X,[s1,Y,s2],'clamped');
end

%differentiates a cubic polynomial
% input: S = a cubic polynomial
function SD = difpp(S)
    
    [B,C,~,~,~] = unmkpp(S);    %extract coefficients from polynomial
    n = size(C,1);
    D = zeros(n, 4);
    for i = 1:n
        D(i,4) = C(i,3);
        D(i,3) = C(i,2)*2;
        D(i,2) = C(i,1)*3;
        D(i,1) = 0;
    end
    SD = mkpp(B,D);             %remake polynomial
end
