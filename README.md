# FSE_20221_Trabalho_3

Trabalho desenvolvido a partir do enunciado disponibilizado no [gitlab da disciplina](https://gitlab.com/fse_fga/trabalhos-2022_1/trabalho-3-2022-1)

## Grupo
Iuri de Souza Severo Alves 17/0145514
João Pedro José Santos da Silva Guedes 17/0013910

## Compilação

O projeto foi desenvolvido utilizando o PlatformIO Core 6.1.4, Home 3.4.3. Para fazer a build e upload é necessário settar no menuconfig as variáveis de URI do MQTT e username do dispositivo conectado no ThingsBoard. A conexão Wi-fi é feita utilizando o aplicativo EspTouch, após a execução do código na ESP32.

## Utilização

Na execução são utilizados dois sensores:
* Sensor de Inclinação (SW-520D), conectado na porta GPIO19
* Sensor de Temperatura e Umidade (DHT11), conectado na porta GPIO18

Após a conexão do Wi-fi e do MQTT, o programa começa a enviar os dados dos sensores para o Dashboard, onde é possível ver os valores de temperatura e umidade tanto em gráficos de tempo quanto apenas o valor atual. O sensor de inclinação é utilizado para somar +1 na variável impact_count.

É possível ativar o modo de Light Sleep a partir do Menuconfig, nesse modo tanto o botão de boot (GPIO0) quanto a ativação do sensor de inclinação despertam a ESP32.
