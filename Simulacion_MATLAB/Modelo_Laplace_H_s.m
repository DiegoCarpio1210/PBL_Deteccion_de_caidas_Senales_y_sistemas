% =========================================================================
% INSTITUTO KRIETE DE INGENIERÍA Y CIENCIAS - SEÑALES Y SISTEMAS
% MODELADO Y VALIDACIÓN EN LAPLACE H(s) - FASE 2
% Autores: Diego Carpio & Emma Palacios
% =========================================================================

clear; clc; close all;

% 1. Parámetros experimentales
alpha = 0.15;
Ts = 0.02; % Período de muestreo de 20 ms (50 Hz)

% 2. Frecuencia de corte angular continua equivalente (wc)
wc = alpha / (Ts * (1 - alpha)); % 8.8235 rad/s
fc = wc / (2 * pi);              % 1.404 Hz

fprintf('=== PARÁMETROS OBTENIDOS DEL MODELO H(s) ===\n');
fprintf('Frecuencia de corte (rad/s): %.4f rad/s\n', wc);
fprintf('Frecuencia de corte (Hz):    %.4f Hz\n', fc);
fprintf('Constante de tiempo tau:      %.4f s\n', 1/wc);

% 3. Ubicación del Polo en el Plano s (s1 = -wc)
polo = -wc;

% 4. Graficar Mapa de Polos y Ceros manualmente
figure('Name', 'Mapa de Polos y Ceros');
plot(real(polo), imag(polo), 'xb', 'LineWidth', 2, 'MarkerSize', 12);
hold on;
xline(0, '--r', 'Frontera de Estabilidad'); % Eje imaginario
yline(0, ':k');                             % Eje real
grid on;
axis([-15 2 -10 10]);
title('Mapa de Polos y Ceros en el Plano s - Filtro IIR ESP32');
xlabel('Eje Real \sigma (rad/s)');
ylabel('Eje Imaginario j\omega (rad/s)');
legend('Polo (s_1 = -8.8235)', 'Location', 'southwest');

% 5. Diagrama de Bode Magnitud y Fase (Cálculo Vectorial)
w = logspace(-1, 3, 1000); % Frecuencias de 0.1 a 1000 rad/s
H_jw = wc ./ (1i * w + wc);

figure('Name', 'Diagrama de Bode');
subplot(2,1,1);
semilogx(w, 20*log10(abs(H_jw)), 'b', 'LineWidth', 1.5);
grid on;
title('Diagrama de Bode Teórico - Magnitud');
ylabel('Magnitud (dB)');

subplot(2,1,2);
semilogx(w, angle(H_jw)*(180/pi), 'r', 'LineWidth', 1.5);
grid on;
title('Diagrama de Bode Teórico - Fase');
xlabel('Frecuencia \omega (rad/s)');
ylabel('Fase (grados)');