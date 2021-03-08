%author: E-Branch
%SinCosAppr
%apriximates sine and cosine
%using taylor series

format long;


t=input('angle ');
disp("sinT :");

disp(sinT(t));
disp("sin :");
disp(sin(t));

t=input('angle ');
disp("cosT :");
disp(cosT(t));
disp("cos :");
disp(cos(t));


function X = sinT(x)
    %x=input('angle ');
    p = pi;
    X = 0;
    
    while(x <= -p)
        x = x + 2*p;
    end
    
    while( x >= p)
        x = x - 2*p;
    end
    
    
    
    k = 1;
    while(k < 13)
        b = floor(k/2);
        X = X + (-1)^b* (x^k)/factorial(k);
        k = k+2;
    end
end

function X = cosT(x)
    p = pi;
    X = 0;
    
    while(x <= -p)
        x = x + 2*p;
    end
    
    while( x >= p)
        x = x - 2*p;
    end
    
    k = 0;
    while(k < 12)
        b = k/2;
        X = X + (-1)^b * x^k / factorial(k);
        k = k+2;
    end
    
end



