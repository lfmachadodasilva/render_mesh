# Render Mesh Project

Estudo de renderização de malhas utilizando uma API mais nova do OpenGL e Shader. Para esse projeto foram utilizadas as tecnologias:
<ul>
<li>Visual Studio (vc10)</li>
<li>IUP (Portable User Interface) </li>
<li>CD (Canvas Draw)</li>
<li>VIS (biblioteca interna do instituto tecgraf)</li>
<li>OpenGL (versão 3.3)</li>
<li>OpenGL Mathematics (glm)</li>
<li>Shader (versão 3.3)</li>
</ul>

Foi desenvolvida uma estrutura de classes, como visto na imagem do modelo de classes, para que a aplicação possar ser expandida e ser utilizada por outras finalidades. Dentro, desse projeto, foram criadas duas novas bibliotecas para o controle de desenho e canvas.

<h3>Main:</h3>
Utilizando a biblioteca IUP foi implementado o diálogo para a visualização dos modelos importados.

<h3>Canvas: </h3>
Em conjunto com a biblioteca VIS e IUP foi implementada uma biblioteca que gerencia toda a parte de manipulação e navegação pelo canvas. Nessa biblioteca é possivel também criar canvas atrelados a um principal, zoom in e out e outras funcionalidades.

<h3>Render: </h3>
Essa biblioteca, sem duvida, é mais complexa. Ela é responsável por receber todas as informações do modelo e desenhar no canvas da melhor forma possivel. Foram criadas várias classes para controlar o desenho de cada tipo de primitiva diferente como: linhas, pontos, triângulos , triângulos com textura. Além disso foi criada a classe que recebe todos os tipos de classe de desenho para definir um objeto que tenha vários tipos de primitivas diferentes. 
Outro segmento dessa biblioteca é a parte de seleção. Utilizando tecnologias de frustum culling e tracado de raio foi possivel fazer uma seleção rápida e precisa, identificando qual o objeto e qual primitiva está sendo selecionada.

<h3>Trabalhos futuros:</h3>
Incorporar essas bibliotecas de canvas e render no projeto Anflex. (já foi incorporada)

