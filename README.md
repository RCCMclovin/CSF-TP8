# CSF-TP8

Neste exercício, vamos testar a comunicação Bluetooth utilizando os códigos disponíveis no repositório git específico. O objetivo é analisar o RSSI e montar a curva de perda no espaço livre.

- Passos para o Experimento:
	- Configuração do Ambiente:
		> Faça o download dos códigos disponíveis no repositório git.
	- Utilize o código fornecido para iniciar a comunicação Bluetooth.
	- Certifique-se de que os dispositivos Bluetooth estejam corretamente emparelhados.
	- Teste de Envio e Recepção:
		> Envie mensagens usando o código de exemplo.
		> Utilize o aplicativo NRF Connect para monitorar o RSSI (Received Signal Strength Indicator) durante a comunicação.
	- Anpalise de Dados:
		> Anote os valores de RSSI recebidos pelo NRF Connect e anote a distância
		> Monte a curva de perda no espaço livre utilizando os valores de RSSI anotados.

- Perguntas a Responder:
	- Curva de Perda no Espaço Livre:
		> Utilize os valores de RSSI anotados para montar a curva de perda no espaço livre.
		> Compare os valores teóricos de perda no espaço livre com os valores medidos.
	- Impacto da Distância no RSSI:
		> Como a variação da distância entre os dispositivos Bluetooth afeta o RSSI?
		> Como a potência de transmissão afetou a qualidade da comunicação? Aquela configurada em:
		
		`esp_power_level_t lst[] = {ESP_PWR_LVL_N11, ESP_PWR_LVL_N9, ESP_PWR_LVL_N6, ESP_PWR_LVL_N3, ESP_PWR_LVL_N0, ESP_PWR_LVL_P3, ESP_PWR_LVL_P6, ESP_PWR_LVL_P9};`

		`BLEDevice::setPower(lst[0]);`
