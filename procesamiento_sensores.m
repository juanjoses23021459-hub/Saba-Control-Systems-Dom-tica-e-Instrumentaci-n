% Proyecto White Tiger: Procesamiento Digital de Señales (DSP)
clear; clc; close all;

% 1. GENERACIÓN DE DATOS SINTÉTICOS (Simulación de sensor DHT22 con ruido)
fs = 10; % Frecuencia de muestreo (Hz)
t = 0:1/fs:60; % 1 minuto de datos
temp_real = 24 + 2*sin(2*pi*0.05*t); % Señal térmica base (lenta)
ruido_electrico = 0.5 * randn(size(t)); % Ruido aleatorio
ruido_picos = zeros(size(t)); % Ruido de picos aleatorios
ruido_picos(randi(length(t), 1, 5)) = 3; % 5 picos de interferencia

temp_sensor = temp_real + ruido_electrico + ruido_picos; % Señal cruda

% 2. DISEÑO DE FILTRO DIGITAL (Filtro de Media Móvil)
% Este filtro suaviza la señal eliminando el ruido de alta frecuencia.
ventana = 5; % Promedio de las últimas 5 lecturas
temp_filtrada = movmean(temp_sensor, ventana);

% 3. VISUALIZACIÓN DE RESULTADOS
figure('Name', 'DSP para Domótica', 'Position', [100 100 1000 600]);

% Gráfica de Señal Cruda vs Real
subplot(2,1,1);
plot(t, temp_sensor, 'Color', [0.8 0.2 0.2 0.5], 'LineWidth', 1); hold on;
plot(t, temp_real, 'k--', 'LineWidth', 2);
title('Señal Cruda del Sensor (con Ruido y Picos)');
ylabel('Temperatura (°C)');
legend('Lectura Sensor', 'Temp. Real');
grid on;

% Gráfica de Señal Filtrada
subplot(2,1,2);
plot(t, temp_filtrada, 'b', 'LineWidth', 2); hold on;
plot(t, temp_real, 'k--', 'LineWidth', 1.5);
title(['Señal Suavizada (Filtro Media Móvil, ventana=' num2str(ventana) ')']);
xlabel('Tiempo (segundos)');
ylabel('Temperatura (°C)');
legend('Señal Filtrada', 'Temp. Real');
grid on;

% Guardar figura para el README
saveas(gcf, 'analysis/dsp_results.png');
fprintf('DSP completado. Figura guardada en analysis/dsp_results.png\n');
