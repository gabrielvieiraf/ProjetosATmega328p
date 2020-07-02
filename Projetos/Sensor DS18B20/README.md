<h1>Projeto Sensor DS18B20 com atmega328P</h1>
<p> Olá devs, tudo tranquilo?</p>
<p> Nesse projeto, desenvolvi um simples testador de sondas de temperatura que recebem dados de através de um <strong>sensor DS18B20</strong>.</p>

Utilizei as bibliotecas ```OneWire.h``` para a leitura de sondas e ```LiquidCrystal.h``` para o display. Inicialmente iria usar minhas próprias bibliotecas, mas em virtude do tempo decidi optar pelo menos trabalhoso. 
O código foi inteiramente desenvolvido na IDE do Arduino, e cumpre com o objetivo de ler o valor de temperatura da sonda com o DS18B20 em modo parasita, bem como identificar o SerialNumber do chip do sensor de temperatura. O modo com que imprimi a ROM do sensor no display, é únicamente por conta da forma com que fazemos o controle desses dispositivos na empresa em que trabalho.

<p align=center><img src="https://user-images.githubusercontent.com/48156370/86149731-c2a96000-bad2-11ea-9361-9fa8ab6dfda7.JPG"></p>
<p>O sensor DS18B20 pode efetuar leituras com precisão de até ±0,5 ºC, e enviar as informações para o <strong>ATMEGA328p</strong> utilizando a tecnologia 1 wire.</p>
<h3>Características do Sensor</h3>

<ul>Tensão de operação: 3 a 5,5V</ul>
<ul>Faixa de medição de temperatura: -55 ºC a +125 ºC</ul>
<ul>Precisão: +/- 0,5 ºC entre -10 ºC e +85 ºC</ul>

<h2>Materiais/Esquema de ligação</h2>

<p>Para realização do projeto, utilizei um Arduino UNO com o chip Atmega328p e um display LCD. Como eu disse, um projetinho bem simples para se fazer 👌🏻</p>
<p>Nosso equema de ligação 1 wire permite com que possamos conectar o sensor ao Arduino ocupando apenas uma ligação. Não apenas isso, mas também permite com que
coloquemos outros sensores nessa mesma linha.</p>

Utilizamos o ```PORTD``` para as ligações com o display LCD e leitura da(s) sonda(s).

<p align=center><img src="https://user-images.githubusercontent.com/48156370/86312659-9b997e00-bbf9-11ea-9bc7-c960e13d3059.PNG" height="412" width="600"></p>
<p>Para o display, utilizei a <strong>configuração de 4 bits</strong>, sendo a mais recomendada para a <strong>economia de PORT's</strong> de nosso Arduino.</p>
<p align=center><img src="https://user-images.githubusercontent.com/48156370/86151008-8c6ce000-bad4-11ea-9fa3-1d35a9923270.JPG"></p>

<h4 align = "center">
Feito por: Gabriel Vieira Flores 🤓
depois de muito ☕☕☕
</h4>
<p align="center">
<a href="https://www.linkedin.com/in/gvieiraf/"><strong>Siga meu LinkedIn!</strong></a>
</p>
