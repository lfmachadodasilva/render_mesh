# Render Mesh Project

Estudo de renderização de malhas utilizando uma API mais nova do OpenGL e Shader. Para esse projeto foram utilizadas as tecnologias:
<ul>
<li>Visual Studio (vc10)</li>
<li><a href="http://webserver2.tecgraf.puc-rio.br/iup/">IUP</a> (Portable User Interface) </li>
<li><a href="http://webserver2.tecgraf.puc-rio.br/cd/">CD</a> (Canvas Draw)</li>
<li><a href="http://webserver2.tecgraf.puc-rio.br/im/">IM</a> (Image Representation, Storage, Capture and Processing)</li>
<li>VIS (biblioteca interna do instituto tecgraf)</li>
<li>OpenGL (version 3.3)</li>
<li><a href="http://glm.g-truc.net/">GLM</a> (OpenGL Mathematics)</li>
<li>Shader (version 3.3)</li>
</ul>

Projetos:

<img src="https://github.com/lfmachado/render_mesh/blob/master/main.png" width="400px"/>

<h3>Main:</h3>
Utilizando a biblioteca IUP foi implementado o diálogo (windows) para a visualização de modelos PLY (Polygon File Format).

<h3>Canvas: </h3>

<img src="https://github.com/lfmachado/render_mesh/blob/master/canvas.png" width="400px"/>

Em conjunto com VIS e IUP, foi implementada uma biblioteca que gerencia toda a parte de manipulação e navegação pelo canvas. Com essa biblioteca é possivel também criar canvas atrelados ao principal, zoom e outras funcionalidades.

<h3>Render: </h3>

<img src="https://github.com/lfmachado/render_mesh/blob/master/MainRender.png" width="400px"/>

<img src="https://github.com/lfmachado/render_mesh/blob/master/render.png" width="400px"/>

Essa biblioteca, sem duvida, é mais complexa. Ela é responsável por receber todas as informações do modelo e desenhar no canvas da melhor forma possivel. Foram criadas várias classes para controlar o desenho de cada tipo de primitiva diferente como: linhas, pontos, triângulos , triângulos com textura. Além disso foi criada a classe que recebe todos os tipos de classe de desenho para definir um objeto que tenha vários tipos de primitivas diferentes. 
Outro segmento dessa biblioteca é a parte de seleção. Utilizando tecnologias de frustum culling e tracado de raio foi possivel fazer uma seleção rápida e precisa, identificando qual o objeto e qual primitiva está sendo selecionada.

<h3>Trabalhos futuros:</h3>
Incorporar essas bibliotecas de canvas e render no projeto Anflex. (já foi incorporada)

