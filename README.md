% Análisis de Carga Eléctrica - White Tiger Core
t = 0:0.01:10; 
consumo = 5 + sin(t) + randn(size(t))*0.2; % Señal base
consumo(500:520) = 15; % Simulación de un cortocircuito o sobrecarga

umbral_seguridad = 10;
eventos = consumo > umbral_seguridad;

figure;
plot(t, consumo, 'k', 'LineWidth', 1); hold on;
area(t, eventos*max(consumo), 'FaceColor', 'r', 'FaceAlpha', 0.3, 'EdgeColor', 'none');
yline(umbral_seguridad, 'r--', 'Umbral Crítico', 'LineWidth', 2);

title('Detección Automática de Sobrecarga Eléctrica');
xlabel('Tiempo (s)');
ylabel('Corriente (Amperios)');
legend('Consumo Real', 'Zona de Peligro');
grid on;
