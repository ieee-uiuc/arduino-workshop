% init
clc

cap_values = [10 15 22 33 47 68]; % E6 Series (20%)
exponents = [1e-12 1e-11 1e-10 1e-9 1e-8 1e-7 1e-6];
resistor = [10 10e3];
new_cap_values = [];

for i = 1:length(exponents)
    new_cap_values = [new_cap_values cap_values*exponents(i)];
end

% brute force the least squares problem 
for j = 1:length(new_cap_values);
   f_high(j) = 1./(2*pi*resistor(1)*new_cap_values(j));
   f_low(j) = 1./(2*pi*resistor(2)*new_cap_values(j));
   bandwidth = f_high(j)-f_low(j);
   fprintf('FL = %2.1f, FH = %4.2f, C = %d\n', f_low(j), f_high(j)/1e3, new_cap_values(j));
end

% find solution manually
c_opt = 1e-6;

% notes to self:
% the flow/fhigh were defined for LPF solution, but work for both since you
% want the same bandwidth, just scaling the opposite direction for each.
% C = 1e-6 means we have FL = 15.9 Hz, FH = 15.92kHz

%% LPF System (2nd order system)
%         w^2
% ----------------------
% s^2  + 2*alpha*s + w^2

dig_resistor = linspace(0, 10e3, 128);
c_opt = 1e-6;

w = 1./(2*pi*dig_resistor*c_opt);
alpha = 2./(c_opt*dig_resistor); 

%% HPF System (2nd order system)
%         s^2
% ----------------------
% s^2  + (w/Q)*s + w^2

dig_resistor = linspace(0, 10e3, 128);
c_opt = 1e-6;

w = 1./(2*pi*dig_resistor*c_opt);
Q = 0.5; % predetermined
