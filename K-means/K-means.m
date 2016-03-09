clear all;clc;close all;
samples=[-5.01 -8.12 -3.68 -0.91 -0.18 -0.05 5.35 2.26 8.13;
        -5.43 -3.48 -3.54 1.30 -2.06 -3.53 5.12 3.22 -2.66;
        1.08 -5.52 1.66 -7.75 -4.54 -0.95 -1.34 -5.31 -9.87;
        0.86 -3.78 -4.11 -5.47 0.50 3.92 4.48 3.42 5.19;
        -2.67 0.63 7.39 6.14 5.72 -4.85 7.11 2.39 9.21;
        4.94 3.29 2.08 3.60 1.26 4.36 7.17 4.33 -0.98;
        -2.51 2.09 -2.59 5.37 -4.63 -3.65 5.75 3.97 6.65;
        -2.25 -2.13 -6.94 7.18 1.46 -6.66 0.77 0.27 2.41;
        5.56 2.86 -2.26 -7.39 1.17 6.30 0.90 -0.43 -8.71;
        1.03 -3.33 4.33 -7.50 -6.32 -0.31 3.52 -0.36 6.43;]
[n,m] = size(samples);

for i=1:3
    mu{i} = mean(samples(:,(i-1)*3+1:i*3))';
    sigma{i} = zeros(3);
    b=zeros(3);
    for j=1:n
        sigma{i}=sigma{i}+(samples(j,(i-1)*3+1:i*3)'-mu{i})*(samples(j,(i-1)*3+1:i*3)'-mu{i})';
     end
     sigma{i} = sigma{i}./n;
end
s = [1 2 1; 5 3 2; 0 0 0; 1 0 0]'
for j=1:size(s,2)
    for i=1:3
        d = sqrt(s(:,j)-mu{i})'*inv(sigma{i})*(s(:,j)-mu{i});
        fprintf(1,'Mahal. dist. for class %d and point %d: %f\n', i, j, d);
    end
end

pw(1,:) =[1/3 0.8];
pw(2,:) =[1/3 0.1];
pw(3,:) =[1/3 0.1];
for p=1:2
    fprintf('\n\n\n\n');
    for j=1:size(s,2)
        class = 0; max_gi = -1000000;
        for i=1:3
            d_i = (s(:,j)-mu{i})'*inv(sigma{i})*(s(:,j)-mu{i});
            g_i = -0.5*d_i - 1.5*log(2*pi) - 0.5*log(det(sigma{i})) + log(pw(i,p));
            if g_i > max_gi,
            max_g_i = g_i;
            class = i;
            end
        end
fprintf('Point %d classified in category %d\n', j, class);
    end
end