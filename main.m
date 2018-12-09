clc;
clear all;
close all;

mex mexsquare.cpp

A = rand(3,2,2);
disp('A is');
disp(A);
disp('Square of A is');
disp(A.^2);

output = mexsquare(A);
disp('Square of A via mex file (c++) is');
disp(output);
