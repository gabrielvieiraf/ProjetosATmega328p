<h1>Projeto Sensor DS18B20 com atmega328P</h1>
<p> Olá devs, tudo tranquilo?</p>
<p> Nesse projeto, desenvolvi um simples testador de sondas de temperatura que recebem dados de através de um <strong>sensor DS18B20</strong>.</p>
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

Utilizamos o ```PORTB``` e ```PORTD``` para as ligações com o display LCD, já para a leitura dos sensores utilizamos o ```PORTC```, 

<p align=center><img src="https://user-images.githubusercontent.com/48156370/86150546-ede07f00-bad3-11ea-9474-517538469a08.JPG"></p>
<p>Para o display, utilizei a <strong>configuração de 4 bits</strong>, sendo a mais recomendada para a <strong>economia de PORT's</strong> de nosso Arduino.</p>
<p align=center><img src="https://user-images.githubusercontent.com/48156370/86151008-8c6ce000-bad4-11ea-9fa3-1d35a9923270.JPG"></p>

<h4 align = "center">
Feito por: Gabriel Vieira Flores 🤓
depois de muito ☕☕☕
</h4>
<p align="center">
<a href="https://www.linkedin.com/in/gvieiraf/"><strong>Siga meu LinkedIn!</strong></a>
</p>
